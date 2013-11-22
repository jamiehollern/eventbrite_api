<?php

/**
 * @file
 * Eventbrite forms file.
 */

/**
 * Admin configiguration form.
 */
function eventbrite_api_config_form() {
  $form = array();
  $form['auth'] = array(
    '#type' => 'fieldset',
    '#title' => t('Eventbrite authentication details'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['auth']['eventbrite_api_userkey'] = array(
    '#type' => 'textfield',
    '#title' => t('Eventbrite user key'),
    '#default_value' => variable_get('eventbrite_api_userkey', ''),
    '#required' => TRUE,
    '#description' => t('Get your user key at <a href="@url">@url</a>.', array('@url' => 'https://www.eventbrite.com/userkeyapi')),
  );
  $form['auth']['eventbrite_api_appkey'] = array(
    '#type' => 'textfield',
    '#title' => t('Eventbrite app key'),
    '#default_value' => variable_get('eventbrite_api_appkey', ''),
    '#required' => TRUE,
    '#description' => t('Get your app keys at <a href="@url">@url</a>.', array('@url' => 'https://www.eventbrite.com/api/key/')),
  );
  $form['import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Eventbrite data import'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['import']['import_all'] = array(
    '#type' => 'submit',
    '#value' => t('Import all Eventbrite event data'),
    '#submit' => array('eventbrite_api_import_all'),
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
  $form['import_settings']['eventbrite_api_import_delete'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete all existing data before import.'),
    '#default_value' => variable_get('eventbrite_api_import_delete', 1),
  );
  $form['import_settings']['eventbrite_api_cron_import'] = array(
    '#type' => 'checkbox',
    '#title' => t('Import events from Eventbrite during cron runs'),
    '#default_value' => variable_get('eventbrite_api_cron_import', 1),
  );
  $form['import_settings']['eventbrite_api_import_strip'] = array(
    '#type' => 'checkbox',
    '#title' => t('Strip HTML code from the event description (recommended)'),
    '#default_value' => variable_get('eventbrite_api_import_strip', 1),
  );
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['general']['eventbrite_api_currency'] = array(
    '#type' => 'select',
    '#title' => t('Default currency'),
    '#default_value' => variable_get('eventbrite_api_currency', 'USD'),
    '#options' => eventbrite_api_currencies(),
  );
  $form['#validate'][] = 'eventbrite_api_config_form_validate';
  return system_settings_form($form);
}

/**
 * Validation function for the admin configiguration form.
 * Essentially, we're testing to see if the keys work.
 */
function eventbrite_api_config_form_validate($form, &$form_state) {
  // Get the app key and user key values from the form..
  $akey = $form_state['values']['eventbrite_api_appkey'];
  $ukey = $form_state['values']['eventbrite_api_userkey'];
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
      $element = 'eventbrite_api_userkey';
    }
    // If it's the app key.
    elseif (strpos($error, 'application key') !== FALSE) {
      $element = 'eventbrite_api_appkey';
    }
    // Then stop the form from saving the details while printing the error.
    form_set_error($element, t('Connection to Eventbrite failed with the following error: @error', array('@error' => $error)));
  }
}

/**
 * Event add form.
 */
function event_add_form($form, &$form_state, $event) {
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
    '#default_value' => isset($event->currency) ? $event->currency : variable_get('eventbrite_api_currency', 'USD'),
    '#options' => eventbrite_api_currencies(),
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
  
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('event_add_form_submit'),
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
  $form['#validate'][] = 'event_add_form_validate';
  // Add the field related form elements.
  $form_state['event'] = $event;
  $form_state['eid'] = $event->eid;
  
  field_attach_form('event', $event, $form, $form_state);
  
  return $form;
}

/**
 * Validation function for event add form.
 */
function event_add_form_validate($form, &$form_state) {
  $event_submit = (object) $form_state['values'];
  field_attach_form_validate('event', $event_submit, $form, $form_state);
}

/**
 * Submit function for event add form.
 */
function event_add_form_submit($form, &$form_state) {
  $event_submit = (object) $form_state['values'];
	// Assign them to an array to send to Eventbrite.
  $eventbrite = $form_state['values'];
	// Format the dates properly.
	$eventbrite['start_date'] = eventbrite_api_datef($eventbrite['start_date']);
	$eventbrite['end_date'] = eventbrite_api_datef($eventbrite['end_date']);//$time = eventbrite_api_ctime(time());
	// Add extra fields.
  field_attach_submit('event', $event_submit, $form, $form_state);
	// Connect to Eventbrite.
  $auth = array('app_key'  => variable_get('eventbrite_api_appkey', ''), 'user_key' => variable_get('eventbrite_api_userkey', ''));
  $eb_client = new Eventbrite($auth);
  try {
		$response = $eb_client->event_new($eventbrite);
		// If the event is added.
		if ($response->process->status == 'OK') {
			// Event ID.
			$eid = $response->process->id;
			// Get the full event details.
		  $response = $eb_client->event_get(array('id' => $eid));
			// This is the retured event.
			$event = $response->event;
			// Make sure the id is correctly labeled.
			$event->eid = $event->id;
		}
  }
  catch (Exception $e) {
		$response = $e->getMessage();
		form_set_error(NULL, $response);
  }
	$event = (object) array_merge((array) $form_state['event'], (array) $event);
  $save = event_save($event);
	if (!empty($save)) {
    drupal_set_message(t('Event @title saved to Eventbrite and cached locally.', array('@title' => '<em>' . $event->title . '</em>')));
    $form_state['redirect'] = 'admin/eventbrite/event';
	}
}

/**
 * Form API submit callback for the delete button.
 */
function event_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/eventbrite/event/' . $form_state['eid'] . '/delete';
}

/**
 * Event delete form.
 */
function event_delete_form($form, &$form_state, $event) {
  $form_state['event'] = $event;

  $form['#submit'][] = 'event_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete event "@title"?', array('@title' => $event->title)),
    'admin/content/events/event',
    '<p>' . t('This will cancel the event on Eventbrite and delete it locally. This action cannot be undone.') . '</p>',
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

  $form_state['redirect'] = 'admin/eventbrite/event';
}

function event_add_wrapper() {
  $event = event_create();
  return drupal_get_form('event_add_form', $event);
}

function event_edit_wrapper($event) {
  return drupal_get_form('event_add_form', $event);
}

function event_delete_wrapper($event) {
  return drupal_get_form('event_delete_form', $event);
}
