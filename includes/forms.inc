<?php

/**
 * @file
 * Provides the form functions for all Eventbrite API forms.
 */
 
/**
 * Admin configiguration form.
 */
function _eventbrite_api_admin() {
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
		'#title' => t('Event import settings'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
  $form['import']['eventbrite_api_cron_import'] = array(
    '#type' => 'checkbox',
    '#title' => t('Import events from Eventbrite during cron runs'),
    '#default_value' => variable_get('eventbrite_api_cron_import', 1),
  );
  $form['import']['eventbrite_api_import_delete'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete all Eventbrite information from the database before import'),
    '#default_value' => variable_get('eventbrite_api_import_delete', 0),
  );
	$form['#validate'][] = '_eventbrite_api_admin_validate';
  return system_settings_form($form);
}

/**
 * Validation function for the admin configiguration form.
 * Essentially, we're testing to see if the keys work.
 */
function _eventbrite_api_admin_validate($form, &$form_state) {
	// Get the app key and user key values from the form..
	$akey = $form_state['values']['eventbrite_api_appkey'];
	$ukey = $form_state['values']['eventbrite_api_userkey'];
	// Connect to Eventbrite.
  $eb_client = eb_connect($akey, $ukey);
	// Try to get a list of events from Eventbrite with our credentials.
	try {
		// If it works, don't do anything as we want to save the details.
		$events = eb_get_events($eb_client);
		dpm($events);
		// Show a message.
		if (isset($events)) {
			drupal_set_message(t('Eventbrite connection successful.'));
		}
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
