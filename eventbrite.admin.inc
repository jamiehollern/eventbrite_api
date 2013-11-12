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
      'file' => 'eventbrite.admin.inc',
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
  if ($event->is_new = isset($event->is_new) ? $event->is_new : 0){
    $event->created = eventbrite_ctime(time());
  }

  $event->modified = eventbrite_ctime(time());
  
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

function eventbrite_currencies() {
  return array(
    'AFN' => t('Afghanistani Afghani'),
    'ALL' => t('Albanian Lek'),
    'DZD' => t('Algerian Dinar'),
    'ARS' => t('Argentine Peso'),
    'AWG' => t('Aruba Florin'),
    'AUD' => t('Australian Dollar'),
    'AZN' => t('Azerbaijan New Maneat'),
    'BSD' => t('Bahamian Dollar'),
    'BHD' => t('Bahraini Dinar'),
    'BDT' => t('Bangladeshi Taka'),
    'BBD' => t('Barbadian Dollar'),
    'BYR' => t('Belarus Ruble'),
    'BZD' => t('Belize Dollar'),
    'BMD' => t('Bermuda Dollar'),
    'BTN' => t('Bhutanese Ngultrum'),
    'BOB' => t('Bolivian Boliviano'),
    'BAM' => t('Bosnia and Herzegovina Convertible Marka'),
    'BWP' => t('Botswana Pula'),
    'BRL' => t('Brazilian Real'),
    'GBP' => t('British Pound'),
    'BND' => t('Brunei Dollar'),
    'BGN' => t('Bulgarian Lev'),
    'BIF' => t('Burundi Franc'),
    'KHR' => t('Cambodia Riel'),
    'CAD' => t('Canadian Dollar'),
    'CVE' => t('Cape Verdean Escudo'),
    'KYD' => t('Cayman Islands Dollar'),
    'XOF' => t('CFA Franc'),
    'XAF' => t('CFA Franc'),
    'CLP' => t('Chilean Peso'),
    'CNY' => t('Chinese Yuan'),
    'COP' => t('Colombian Peso'),
    'KMF' => t('Comoros Franc'),
    'CRC' => t('Costa Rica Colon'),
    'HRK' => t('Croatian Kuna'),
    'CUP' => t('Cuban Peso'),
    'CYP' => t('Cyprus Pound'),
    'CZK' => t('Czech Koruna'),
    'DKK' => t('Danish Krone'),
    'DJF' => t('Dijiboutian Franc'),
    'DOP' => t('Dominican Peso'),
    'XCD' => t('East Caribbean Dollar'),
    'EGP' => t('Egyptian Pound'),
    'SVC' => t('El Salvador Colon'),
    'ERN' => t('Eritrean Nakfa'),
    'EEK' => t('Estonian Kroon'),
    'ETB' => t('Ethiopian Birr'),
    'EUR' => t('Euro'),
    'FKP' => t('Falkland Islands Pound'),
    'FJD' => t('Fiji Dollar'),
    'GMD' => t('Gambian Dalasi'),
    'GHC' => t('Ghanian Cedi'),
    'GIP' => t('Gibraltar Pound'),
    'XAU' => t('Gold Ounces'),
    'GTQ' => t('Guatemala Quetzal'),
    'GGP' => t('Guernsey Pound'),
    'GNF' => t('Guinea Franc'),
    'GYD' => t('Guyana Dollar'),
    'HTG' => t('Haiti Gourde'),
    'HNL' => t('Honduras Lempira'),
    'HKD' => t('Hong Kong Dollar'),
    'HUF' => t('Hungarian Forint'),
    'ISK' => t('Iceland Krona'),
    'INR' => t('Indian Rupee'),
    'IDR' => t('Indonesian Rupiah'),
    'IRR' => t('Iran Rial'),
    'IQD' => t('Iraqi Dinar'),
    'ILS' => t('Israeli Shekel'),
    'JMD' => t('Jamaican Dollar'),
    'JPY' => t('Japanese Yen'),
    'JOD' => t('Jordanian Dinar'),
    'KZT' => t('Kazakhstan Tenge'),
    'KES' => t('Kenyan Shilling'),
    'KRW' => t('Korean Won'),
    'KWD' => t('Kuwaiti Dinar'),
    'KGS' => t('Kyrgyzstan Som'),
    'LAK' => t('Lao Kip'),
    'LVL' => t('Latvian Lat'),
    'LBP' => t('Lebanese Pound'),
    'LSL' => t('Lesotho Loti'),
    'LRD' => t('Liberian Dollar'),
    'LYD' => t('Libyan Dinar'),
    'LTL' => t('Lithuanian Lita'),
    'MOP' => t('Macau Pataca'),
    'MKD' => t('Macedonian Denar'),
    'MGA' => t('Malagasy ariary'),
    'MWK' => t('Malawian Kwacha'),
    'MYR' => t('Malaysian Ringgit'),
    'MVR' => t('Maldives Rufiyaa'),
    'MTL' => t('Maltese Lira'),
    'MRO' => t('Mauritania Ougulya'),
    'MUR' => t('Mauritius Rupee'),
    'MXN' => t('Mexican Peso'),
    'MDL' => t('Moldovan Leu'),
    'MNT' => t('Mongolian Tugrik'),
    'MAD' => t('Moroccan Dirham'),
    'MZM' => t('Mozambique Metical'),
    'MMK' => t('Myanmar Kyat'),
    'NAD' => t('Namibian Dollar'),
    'NPR' => t('Nepalese Rupee'),
    'ANG' => t('Neth Antilles Guilder'),
    'NZD' => t('New Zealand Dollar'),
    'NIO' => t('Nicaragua Cordoba'),
    'NGN' => t('Nigerian Naira'),
    'KPW' => t('North Korean Won'),
    'NOK' => t('Norwegian Krone'),
    'OMR' => t('Omani Rial'),
    'XPF' => t('Pacific Franc'),
    'PKR' => t('Pakistani Rupee'),
    'XPD' => t('Palladium Ounces'),
    'PAB' => t('Panama Balboa'),
    'PGK' => t('Papua New Guinea Kina'),
    'PYG' => t('Paraguayan Guarani'),
    'PEN' => t('Peruvian Nuevo Sol'),
    'PHP' => t('Philippine Peso'),
    'XPT' => t('Platinum Ounces'),
    'PLN' => t('Polish Zloty'),
    'QAR' => t('Qatar Rial'),
    'RON' => t('Romanian New Leu'),
    'RUB' => t('Russian Rouble'),
    'RWF' => t('Rwandese Franc'),
    'WST' => t('Samoan Tala'),
    'STD' => t('Sao Tome Dobra'),
    'SAR' => t('Saudi Arabian Riyal'),
    'SCR' => t('Seychelles Rupee'),
    'RSD' => t('Serbian Dinar'),
    'SLL' => t('Sierra Leone Leone'),
    'XAG' => t('Silver Ounces'),
    'SGD' => t('Singapore Dollar'),
    'SKK' => t('Slovak Koruna'),
    'SBD' => t('Solomon Islands Dollar'),
    'SOS' => t('Somali Shilling'),
    'ZAR' => t('South African Rand'),
    'LKR' => t('Sri Lanka Rupee'),
    'SHP' => t('St Helena Pound'),
    'SDG' => t('Sudanese Pound'),
    'SRD' => t('Surinam Dollar'),
    'SZL' => t('Swaziland Lilageni'),
    'SEK' => t('Swedish Krona'),
    'CHF' => t('Swiss Franc'),
    'SYP' => t('Syrian Pound'),
    'TWD' => t('Taiwan Dollar'),
    'TZS' => t('Tanzanian Shilling'),
    'THB' => t('Thai Baht'),
    'TOP' => t("Tonga Pa'anga"),
    'TTD' => t('Trinidad & Tobago Dollar'),
    'TND' => t('Tunisian Dinar'),
    'TRY' => t('Turkish Lira'),
    'USD' => t('U.S. Dollar'),
    'AED' => t('UAE Dirham'),
    'UGX' => t('Ugandan Shilling'),
    'UAH' => t('Ukraine Hryvnia'),
    'UYU' => t('Uruguayan New Peso'),
    'UZS' => t('Uzbekistan Sum'),
    'VUV' => t('Vanuatu Vatu'),
    'VEB' => t('Venezuelan Bolivar'),
    'VND' => t('Vietnam Dong'),
    'YER' => t('Yemen Riyal'),
    'YUM' => t('Yugoslav Dinar'),
    'ZMK' => t('Zambian Kwacha'),
    'ZWD' => t('Zimbabwe Dollar'),
  );
}

function eventbrite_ctime($timestamp) {
	$time = date('c', $timestamp);
	$time = str_replace('T', ' ', $time);
	$time = explode('+', $time);
	return $time[0];
}
