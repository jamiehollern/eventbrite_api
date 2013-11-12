<?php

/**
 * @file
 * Event editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

/**
 * UI controller.
 */
class EventbriteUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Eventbrite',
      'description' => 'Manage Eventbrite events and other data.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
			'weight' => -7,
    );
    
    // Change the overview menu type for the list of events.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    
    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a event',
      'description' => 'Add a new event',
      'page callback'  => 'event_add_page',
      'access callback'  => 'event_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'eventbrite.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );

    $items[$this->path . '/config'] = array(
      'title' => 'Configuration',
      'description' => 'Manage Eventbrite settings.',
      'page callback' => 'drupal_get_form',
			'page arguments' => 'eventbrite_config_form',
      'access arguments' => array('access administration pages'),
      'type' => MENU_NORMAL_ITEM,
      'file' => 'eventbrite.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
			'weight' => 50,
    );

    // Loading and editing event entities
    $items[$this->path . '/event/' . $wildcard] = array(
      'page callback' => 'event_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'event_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'eventbrite.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/event/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    
    $items[$this->path . '/event/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'event_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'event_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'eventbrite.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    
    // Menu item for viewing events
    $items['event/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'event_page_title',
      'title arguments' => array(1),
      'page callback' => 'event_page_view',
      'page arguments' => array(1),
      'access callback' => 'event_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
		
    return $items;
  }
  
  /**
   * Create the markup for the add Event Entities page within the class
   * so it can easily be extended/overriden.
   */ 
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }    
        
    return theme('event_add_list', array('content' => $content));
  }
  
}

/**
 * Form callback wrapper: create or edit a event.
 *
 * @param $event
 *   The event object being edited by this form.
 *
 * @see event_edit_form()
 */
function event_form_wrapper($event) {
  // Add the breadcrumb for the form's location.
  event_set_breadcrumb();
  return drupal_get_form('event_edit_form', $event);
}

/**
 * Form callback wrapper: delete a event.
 *
 * @param $event
 *   The event object being edited by this form.
 *
 * @see event_edit_form()
 */
function event_delete_form_wrapper($event) {
  // Add the breadcrumb for the form's location.
  //event_set_breadcrumb();
  return drupal_get_form('event_delete_form', $event);
}

/**
 * Form callback: create or edit a event.
 *
 * @param $event
 *   The event object to edit or for a create form an empty event object
 *     with only a event type defined.
 */
function event_edit_form($form, &$form_state, $event) {
  // Add the default field elements.
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Event Name'),
    '#default_value' => isset($event->name) ? $event->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );
  
  $form['data']['#tree'] = TRUE;
  $form['data']['sample_data'] = array(
    '#type' => 'checkbox',
    '#title' => t('An interesting event switch'),
    '#default_value' => isset($event->data['sample_data']) ? $event->data['sample_data'] : 1,
  );

  // Add the field related form elements.
  $form_state['event'] = $event;
  field_attach_form('event', $event, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save event'),
    '#submit' => $submit + array('event_edit_form_submit'),
  );
  
  if (!empty($event->name)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete event'),
      '#suffix' => l(t('Cancel'), 'admin/content/events'),
      '#submit' => $submit + array('event_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'event_edit_form_validate';
  return $form;
}

/**
 * Form API validate callback for the event form
 */
function event_edit_form_validate(&$form, &$form_state) {
  $event = $form_state['event'];
  
  // Notify field widgets to validate their data.
  field_attach_form_validate('event', $event, $form, $form_state);
}

/**
 * Form API submit callback for the event form.
 * 
 * @todo remove hard-coded link
 */
function event_edit_form_submit(&$form, &$form_state) {
  
  $event = entity_ui_controller('event')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the event and go back to the list of events
  
  // Add in created and changed times.
  if ($event->is_new = isset($event->is_new) ? $event->is_new : 0){
    $event->created = time();
  }

  $event->changed = time();
  
  $event->save();
  $form_state['redirect'] = 'admin/content/events';
}

/**
 * Form API submit callback for the delete button.
 * 
 * @todo Remove hard-coded path
 */
function event_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/events/event/' . $form_state['event']->event_id . '/delete';
}

/**
 * Form callback: confirmation form for deleting a event.
 *
 * @param $event
 *   The event to delete
 *
 * @see confirm_form()
 */
function event_delete_form($form, &$form_state, $event) {
  $form_state['event'] = $event;

  $form['#submit'][] = 'event_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete event %name?', array('%name' => $event->name)),
    'admin/content/events/event',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );
  
  return $form;
}

/**
 * Submit callback for event_delete_form
 */
function event_delete_form_submit($form, &$form_state) {
  $event = $form_state['event'];

  event_delete($event);

  drupal_set_message(t('The event %name has been deleted.', array('%name' => $event->name)));
  watchdog('event', 'Deleted event %name.', array('%name' => $event->name));

  $form_state['redirect'] = 'admin/content/events';
}

/**
 * Page to add Event Entities.
 *
 * @todo Pass this through a proper theme function
 */
function event_add_page() {
  $controller = entity_ui_controller('event');
  return $controller->addPage();
}

/**
 * Displays the list of available event types for event creation.
 *
 * @ingroup themeable
 */
function theme_event_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="event-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer event types')) {
      $output = '<p>' . t('Event Entities cannot be added because you have not created any event types yet. Go to the <a href="@create-event-type">event type creation page</a> to add a new event type.', array('@create-event-type' => url('admin/structure/event_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No event types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}

/**
 * Sets the breadcrumb for administrative event pages.
 */
function event_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Events'), 'admin/content/events'),
  );

  drupal_set_breadcrumb($breadcrumb);
}

/**
 * Admin configiguration form.
 */
function eventbrite_config_form() {
  $form = array();
  $form['auth'] = array(
    '#type' => 'fieldset',
    '#title' => t('Eventbrite authentication details'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['auth']['eventbrite_userkey'] = array(
    '#type' => 'textfield',
    '#title' => t('Eventbrite user key'),
    '#default_value' => variable_get('eventbrite_userkey', ''),
    '#required' => TRUE,
    '#description' => t('Get your user key at <a href="@url">@url</a>.', array('@url' => 'https://www.eventbrite.com/userkeyapi')),
  );
  $form['auth']['eventbrite_appkey'] = array(
    '#type' => 'textfield',
    '#title' => t('Eventbrite app key'),
    '#default_value' => variable_get('eventbrite_appkey', ''),
    '#required' => TRUE,
    '#description' => t('Get your app keys at <a href="@url">@url</a>.', array('@url' => 'https://www.eventbrite.com/api/key/')),
  );
  $form['import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Event import settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['import']['import_all'] = array(
    '#type' => 'submit',
    '#value' => t('Import all Eventbrite event data'),
    '#submit' => array('eventbrite_import_all'),
  );
  $form['import']['import_all_help'] = array(
    '#markup' => '<div>' . t('If you already have Eventbrite data imported,
		this will delete that data before importing the new data. This
		cannot be undone.') . '</div>',
  );
  $form['import_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Event import settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['import_settings']['eventbrite_cron_import'] = array(
    '#type' => 'checkbox',
    '#title' => t('Import events from Eventbrite during cron runs'),
    '#default_value' => variable_get('eventbrite_cron_import', 1),
  );
  $form['import_settings']['eventbrite_import_strip'] = array(
    '#type' => 'checkbox',
    '#title' => t('Strip HTML code from the event description (recommended)'),
    '#default_value' => variable_get('eventbrite_import_strip', 1),
  );
  $form['#validate'][] = 'eventbrite_config_form_validate';
  return system_settings_form($form);
}

/**
 * Validation function for the admin configiguration form.
 * Essentially, we're testing to see if the keys work.
 */
function eventbrite_config_form_validate($form, &$form_state) {
  // Get the app key and user key values from the form..
  $akey = $form_state['values']['eventbrite_appkey'];
  $ukey = $form_state['values']['eventbrite_userkey'];
  // Connect to Eventbrite using the Eventbrite class.
  $eb_client = new Eventbrite(array('app_key' => $akey, 'user_key' => $ukey));
  // Try to get a list of events from Eventbrite with our credentials.
  try {
    // If it works, don't do anything as we want to save the details.
    $events = $eb_client->user_list_events();
  }
  // If it doesn't work, catch the error.
  catch (Exception $e) {
    // Variable for the form element.
    $element = 'config';
    // Variable for the error message.
    $error = $e->getMessage();
    // If it's the user key.
    if (strpos($error, 'user_key') !== FALSE) {
      $element = 'eventbrite_userkey';
    }
    // If it's the app key.
    elseif (strpos($error, 'application key') !== FALSE) {
      $element = 'eventbrite_appkey';
    }
    // Then stop the form from saving the details while printing the error.
    form_set_error($element, t('Connection to Eventbrite failed with the following error: @error', array('@error' => $error)));
  }
}
