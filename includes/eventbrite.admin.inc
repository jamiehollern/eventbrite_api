<?php

/**
 * @file
 * Admin and UI.
 */

/**
 * UI controller.
 */
class EventUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Models',
      'description' => 'Add edit and update models.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );
    
    // Change the overview menu type for the list of models.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    
    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a model',
      'description' => 'Add a new model',
      'page callback'  => 'model_add_page',
      'access callback'  => 'model_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'model.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );
    
    // Add menu items to add each different type of entity.
    foreach (model_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'model_form_wrapper',
        'page arguments' => array(model_create(array('type' => $type->type))),
        'access callback' => 'model_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'model.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing model entities
    $items[$this->path . '/model/' . $wildcard] = array(
      'page callback' => 'model_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'model_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'model.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/model/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    
    $items[$this->path . '/model/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'model_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'model_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'model.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    
    // Menu item for viewing models
    $items['model/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'model_page_title',
      'title arguments' => array(1),
      'page callback' => 'model_page_view',
      'page arguments' => array(1),
      'access callback' => 'model_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }
  
  
  /**
   * Create the markup for the add Model Entities page within the class
   * so it can easily be extended/overriden.
   */ 
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }    
        
    return theme('model_add_list', array('content' => $content));
  }
  
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

/**
 * This is a helper function that takes an array of event data
 * returned from Eventbrite and depending on the $type returns
 * a properly formatted entity array.
 */
function eventbrite_entity_prepare($data, $type) {
  $entity = array();
  switch ($type) {
    case 'event':
      $entity = array(
        'eid' => $data['id'],
        'oid' => $data['oid'],
        'vid' => $data['vid'],
        'locale' => $data['locale'],
        'timezone' => $data['timezone'],
        'category' => $data['category'],
        'capacity' => $data['capacity'],
        'num_attendee_rows' => $data['num_attendee_rows'],
        'title' => $data['title'],
        'start_date' => $data['start_date'],
        'status' => $data['status'],
        'description' => $data['description'],
        'end_date' => $data['end_date'],
        'tags' => $data['tags'],
        'timezone_offset' => $data['timezone_offset'],
        'password' => (!empty($data['password']) ? $data['password'] : ''),
        'created' => $data['created'],
        'url' => $data['url'],
        'privacy' => $data['privacy'],
        'modified' => $data['modified'],
        'repeats' => $data['repeats'],
      );
      break;
    case 'organizer':
      $entity = array(
        'oid' => $data['id'],
        'name' => $data['name'],
        'description' => $data['description'],
        'long_description' => $data['long_description'],
        'url' => $data['url'],
      );
      break;
    case 'ticket':
      $entity = array(
        'tid' => $data['id'],
        'eid' => $data['eid'],
        'name' => $data['name'],
        'type' => $data['type'],
        'description' => $data['description'],
        'start_date' => $data['start_date'],
        'end_date' => $data['end_date'],
        'min' => $data['min'],
        'max' => $data['max'],
        'price' => (!empty($data['price']) ? $data['price'] : '0.00'),
        'quantity_sold' => $data['quantity_sold'],
        'visible' => $data['visible'],
        'currency' => $data['currency'],
        'quantity_available' => $data['quantity_available'],
        'display_price' => (!empty($data['display_price']) ? $data['display_price'] : '0.00'),
      );
      break;
    case 'venue':
      $entity = array(
        'vid' => $data['id'],
        'city' => $data['city'],
        'name' => $data['name'],
        'country' => $data['country'],
        'region' => $data['region'],
        'address' => $data['address'],
        'address_2' => $data['address_2'],
        'postal_code' => $data['postal_code'],
        'country_code' => $data['country_code'],
        'longitude' => $data['longitude'],
        'latitude' => $data['latitude'],
        'lat_long' => $data['Lat-Long'],
      );
      break;
  }
  return $entity;
}

/**
 * Imports the entities.
 */
function eventbrite_entity_import($item) {
  // Prepare events.
  $entity = eventbrite_entity_prepare($item['event'], 'event');
  $entity = entity_create('eventbrite_event', $entity);
  $entity->save();
  // Prepare organizer.
  $entity = eventbrite_entity_prepare($item['organizer'], 'organizer');
  $entity = entity_create('eventbrite_organizer', $entity);
  $entity->save();
  // Prepare tickets.
  foreach ($item['tickets'] as $ticket) {
    $entity = eventbrite_entity_prepare($ticket, 'ticket');
    $entity = entity_create('eventbrite_ticket', $entity);
    $entity->save();
  }
  // Prepare venue.
  $entity = eventbrite_entity_prepare($item['venue'], 'venue');
  $entity = entity_create('eventbrite_venue', $entity);
  $entity->save();
}

/**
 * Imports all events, organizers, tickets and venues
 * from Eventbrite.
 */
function eventbrite_import_all($form, $form_state) {
  // Instantiate Eventbrite.
  $eb = new eb();
  // Get a list of events.
  $items = $eb->get_data();
	// Clear the current data from the database.
	$eb->delete_all();
	// Save the entities.
  foreach ($items as $item) {
    eventbrite_entity_import($item);
	}
	// Count how many events, organizers, tickets and venues you have.
	$types = array('eventbrite_event', 'eventbrite_organizer', 'eventbrite_ticket', 'eventbrite_venue');
	$placeholders = array();
	foreach ($types as $type) {
	  // Run a query.
	  $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $type);
	  $placeholders['@' . $type] = $query->count()->execute();
	}
	drupal_set_message(t('Eventbrite data import completed successfully. 
	@eventbrite_event events, @eventbrite_organizer organizers, 
	@eventbrite_ticket tickets and @eventbrite_venue venues
	in the database.', $placeholders));
}
