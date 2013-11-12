<?php

/**
 * @file
 * Config page settings.
 */

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
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['general']['eventbrite_currency'] = array(
    '#type' => 'select',
    '#title' => t('Default currency'),
    '#default_value' => variable_get('eventbrite_currency', 'USD'),
    '#options' => eventbrite_currencies(),
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

function eventbrite_import_all() {
	$auth = array('app_key'  => variable_get('eventbrite_appkey', ''), 'user_key' => variable_get('eventbrite_userkey', ''));
  $eb_client = new Eventbrite($auth);
  // For more information about the features that are available through the Eventbrite API, see http://developer.eventbrite.com/doc/
  $events = $eb_client->user_list_events();
	dpm($events);
}
