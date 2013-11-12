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
    
    // Add an event.
    $items[$this->path . '/events/add'] = array(
        'title' => t('Add an event'),
        'page callback' => 'event_form_wrapper',
        'page arguments' => array(event_create(array())),
        'access callback' => 'event_access',
        'access arguments' => array('edit'),
        'file' => 'eventbrite.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );

    $items[$this->path . '/config'] = array(
      'title' => 'Configuration',
      'description' => 'Manage Eventbrite settings.',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('eventbrite_config_form'),
      'access arguments' => array('access administration pages'),
      'type' => MENU_NORMAL_ITEM,
      'file' => 'eventbrite.config.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
      'weight' => 50,
    );

    // Loading and editing event entities
    $items[$this->path . '/events/' . $wildcard] = array(
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

  $form['details'] = array(
    '#type' => 'fieldset',
    '#title' => t('General information'),
  );
  
  $form['details']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Event title'),
    '#default_value' => isset($event->title) ? $event->title : '',
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  
  /*$form['details']['description'] = array(
    '#type' => 'text_format',
    '#title' => t('Description'),
    '#default_value' => isset($event->description) ? $event->description : '',
    '#format' => variable_get('event_desdc_format', 'filtered_html'),
  );*/
  
  $form['details']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => isset($event->description) ? $event->description : '',
  );
  
  $form['details']['capacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Capacity'),
    '#default_value' => isset($event->capacity) ? $event->capacity : '',
    '#size' => 5,
  );
  
  $form['details']['currency'] = array(
    '#type' => 'select',
    '#title' => t('Currency'),
    '#default_value' => isset($event->currency) ? $event->currency : variable_get('eventbrite_currency', 'USD'),
    '#options' => eventbrite_currencies(),
  );
  
  $form['details']['status'] = array(
    '#type' => 'select',
    '#title' => t('Event status'),
    '#default_value' => isset($event->status) ? $event->status : 'draft',
    '#options' => array(
		  'draft' => t('Draft'),
		  'live' => t('Live'),
    ),
  );

  $form['dates'] = array(
    '#type' => 'fieldset',
    '#title' => t('Date information'),
  );
  
  $form['dates']['start_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start date'),
    '#default_value' => isset($event->start_date) ? $event->start_date : '',
    '#required' => TRUE,
  );
  
  $form['dates']['end_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('End date'),
    '#default_value' => isset($event->end_date) ? $event->end_date : '',
    '#required' => TRUE,
  );

  $form['dates']['date_default_timezone'] = array(
    '#type' => 'select',
    '#title' => t('Default time zone'),
    '#default_value' => variable_get('date_default_timezone', date_default_timezone_get()),
    '#options' => system_time_zones(),
    '#required' => TRUE,
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
  
  if (!empty($event->title)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete event'),
      '#suffix' => l(t('Cancel'), 'admin/eventbrite/events'),
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
	$time = eventbrite_ctime(time());
  if ($event->is_new = isset($event->is_new) ? $event->is_new : 0){
    $event->created = $time;
  }

  $event->modified = $time;
  $event->save();
  $form_state['redirect'] = 'admin/eventbrite/events';
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
 * Displays the list of available event types for event creation.
 *
 * @ingroup themeable
 */
function theme_event_add_list($variables) {
  dpm($variables);
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
    l(t('Eventbrite'), 'admin/eventbrite'),
    l(t('Events'), 'admin/eventbrite/events'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
