<?php

function eventbrite_api_currencies() {
  $currencies =  array(
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
  return $currencies;
}

function eventbrite_api_ctime($timestamp = NULL) {
	if (empty($timestamp)) {
		$timestamp = time();
	}
  $time = date('c', $timestamp);
  $time = str_replace('T', ' ', $time);
  $time = explode('+', $time);
  return $time[0];
}

function eventbrite_api_datef($date) {
  return $date . ':00';
}

function event_save(&$event) {
  return entity_save('event', $event);
}

function event_delete($entity) {
  entity_delete('event', $entity->eid);
  // MAKE THIS CANCEL EVENT WITH EVENTBRITE.
}

function event_create() {
  $event = (object) array(
    'eid' => '',
    'oid' => '',
    'vid' => '',
    'is_new' => TRUE,
    'locale' => '',
    'timezone' => '',
    'category' => '',
    'capacity' => '',
    'num_attendee_rows' => '',
    'title' => '',
    'start_date' => '',
    'status' => '',
    'description' => '',
    'end_date' => '',
    'tags' => '',
    'timezone_offset' => '',
    'password' => '',
    'created' => '',
    'url' => '',
    'privacy' => '',
    'modified' => '',
    'repeats' => '',
  );
  return $event;
}

function organizer_create() {
  $organizer = (object) array(
    'oid' => '',
    'name' => '',
    'description' => '',
    'long_description' => '',
    'url' => '',
    'is_new' => TRUE,
  );
  return $organizer;
}

function organizer_save(&$organizer) {
  return entity_save('organizer', $organizer);
}

function organizer_delete($entity) {
  entity_delete('organizer', $entity->oid);
  // MAKE THIS DELETE ORGANIZER WITH EVENTBRITE.
}

function ticket_create() {
  $ticket = (object) array(
    'tid' => '',
    'eid' => '',
    'name' => '',
    'type' => '',
    'description' => '',
    'start_date' => '',
    'end_date' => '',
    'min' => '',
    'max' => '',
    'price' => '',
    'quantity_sold' => '',
    'visible' => '',
    'currency' => '',
    'quantity_available' => '',
    'display_price' => '',
    'is_new' => TRUE,
  );
  return $ticket;
}

function ticket_save(&$ticket) {
  return entity_save('ticket', $ticket);
}

function ticket_delete($entity) {
  entity_delete('ticket', $entity->tid);
  // MAKE THIS CANCEL EVENT WITH EVENTBRITE.
}

function eventbrite_api_import_all() {
  // Authorisation details.
  $auth = array('app_key'  => variable_get('eventbrite_api_appkey', ''), 'user_key' => variable_get('eventbrite_api_userkey', ''));
  // Connect to Eventbrite.
  $eb_client = new Eventbrite($auth);
  // Get all data by using the user_list_events method.
  $import = $eb_client->user_list_events();
  // Format it nicely.
  $events = eventbrite_api_format_all($import);
  // Should we delete everything before importing?
  if (variable_get('eventbrite_api_import_delete', 1) == 1) {
    // Yes.
    $result = db_truncate('eventbrite_api_events')->execute();
    $result = db_truncate('eventbrite_api_organizers')->execute();
    $result = db_truncate('eventbrite_api_tickets')->execute();
    $result = db_truncate('eventbrite_api_venues')->execute();
    // Set a count array for our entities.
    $count = array();
    // Run through the array.
    foreach ($events as $type => $data) {
      // Count how many entities we have.
      $count[$type] = count($data);
      // Run through the sub arrays.
      foreach ($data as $record) {
        // Make sure all records have the correct keys.
        $record = (object) array_merge((array) eventbrite_api_entity_prepare($type), (array) $record);
        // Write the record.
        $write = drupal_write_record('eventbrite_api_' . $type, $record);
      }
    }
    // Set a message and let the user know what's been imported.
    $placeholders =  array(
      '@events' => $count['events'],
      '@organizers' => $count['organizers'],
      '@tickets' => $count['tickets'],
      '@venues' => $count['venues'],
    );
    drupal_set_message(t('Import successful. @events events, @organizers organizers, 
    @tickets tickets and @venues venues imported.', $placeholders));
  }
  else {
    // Update.
  }
}

function eventbrite_api_format_all($data) {
  // Create an array for our events.
  $events = array();
  foreach ($data->events as $row) {
    // Set the eid.
    $eid = $row->event->id;
    // Check for an organizer.
    if (!empty($row->event->organizer)) {
      // Set the oid.
      $oid = $row->event->organizer->id;
      // Add the oid and remove the id.
      $row->event->organizer->oid = $oid;
      unset($row->event->organizer->id);
      // Assign the organizer object as an array to $events.
      $events['organizers'][$oid] = (array) $row->event->organizer;
      // Remove the organizer from the data.
      unset($row->event->organizer);
    }
    // Check for a venue.
    if (!empty($row->event->venue)) {
      // Set the vid.
      $vid = $row->event->venue->id;
      // Add the vid and remove the id.
      $row->event->venue->vid = $vid;
      unset($row->event->venue->id);
      // Assign the venue object as an array to $events.
      $events['venues'][$vid] = (array) $row->event->venue;
      // Change Lat-Long to lat_long.
      $events['venues'][$vid]['lat_long'] = $events['venues'][$vid]['Lat-Long'];
      unset($events['venues'][$vid]['Lat-Long']);
      // Remove the venue from the data.
      unset($row->event->venue);
    }
    // Check for tickets.
    if (!empty($row->event->tickets)) {
      // Run through each ticket.
      foreach ($row->event->tickets as $ticket) {
        // Set the tid.
        $tid = $ticket->ticket->id;
        // Add the tid and remove the id.
        $ticket->ticket->tid = $tid;
        unset($ticket->ticket->id);
        // Add the eid.
        $ticket->ticket->eid = $eid;
				// Remove commas from ticket prices.
				if (!empty($ticket->ticket->price)) {
          $ticket->ticket->price = str_replace(',', '', $ticket->ticket->price);
				}
        // Assign the venue object as an array to $events.
        $events['tickets'][$tid] = (array) $ticket->ticket;
      }
      // Remove the tickets from the data.
      unset($row->event->tickets);
    }
    // Add the eid and remove the id.
    $row->event->eid = $eid;
    unset($row->event->id);
    // Assign the event object as an array to $events.
    $events['events'][$eid] = (array) $row->event;
    // Add vid and oid.
    if (!empty($oid)) {
      $events['events'][$eid]['oid'] = $oid;
    }
    if (!empty($vid)) {
      $events['events'][$eid]['vid'] = $vid;
    }
  }
  ksort($events);
  return $events;
}

/**
 * This prepares an empty entity object for Eventbrite
 * events, organizers, tickets and venues.
 */
function eventbrite_api_entity_prepare($type) {
  $event = array(
    'eid' => '',
    'oid' => '',
    'vid' => '',
    'locale' => '',
    'timezone' => '',
    'category' => '',
    'capacity' => '',
    'num_attendee_rows' => '',
    'title' => '',
    'start_date' => eventbrite_api_ctime(),
    'status' => '',
    'description' => '',
    'end_date' => eventbrite_api_ctime(),
    'tags' => '',
    'timezone_offset' => '',
    'password' => '',
    'created' => eventbrite_api_ctime(),
    'url' => '',
    'privacy' => '',
    'modified' => eventbrite_api_ctime(),
    'repeats' => '',
    'is_new' => TRUE,
  );
  $organizer = array(
    'oid' => '',
    'name' => '',
    'description' => '',
    'long_description' => '',
    'url' => '',
    'is_new' => TRUE,
  );
  $ticket = array(
    'tid' => '',
    'eid' => '',
    'name' => '',
    'type' => '',
    'description' => '',
    'start_date' => eventbrite_api_ctime(),
    'end_date' => eventbrite_api_ctime(),
    'min' => '',
    'max' => '',
    'price' => '0.00',
    'quantity_sold' => '',
    'visible' => '',
    'currency' => '',
    'quantity_available' => '',
    'display_price' => '0.00',
    'is_new' => TRUE,
  );
  $venue = array(
    'vid' => '',
    'city' => '',
    'name' => '',
    'country' => '',
    'region' => '',
    'address' => '',
    'address_2' => '',
    'postal_code' => '',
    'country_code' => '',
    'longitude' => '',
    'latitude' => '',
    'lat_long' => '',
    'is_new' => TRUE,
  );
  switch ($type) {
    case 'event':
      $entity = $event;
      break;
    case 'events':
      $entity = $event;
      break;
    case 'organizer':
      $entity = $organizer;
      break;
    case 'organizers':
      $entity = $organizer;
      break;
    case 'ticket':
      $entity = $ticket;
      break;
    case 'tickets':
      $entity = $ticket;
      break;
    case 'venue':
      $entity = $venue;
      break;
    case 'venues':
      $entity = $venue;
      break;
  }
  return (object) $entity;
}

/**
 * Entity reference fields store entity target IDs as 10
 * character integers but Eventbrite event IDs are longer
 * than this. We use this hook to alter the field size
 * to a "bigint" if it references an event entity.
 */
function _eventbrite_api_alter_field($data) {
  // Set some shorthand vars.
  $type = $data['type'];
  $target_type = $data['settings']['target_type'];
  // Check to see if this is the correct field.
  if ($type == 'entityreference' && $target_type == 'event') {
    // Get all of the necessary variables together.
    $table = 'field_data_' . $data['field_name'];
    $field = $data['storage']['details']['sql']['FIELD_LOAD_CURRENT'][$table]['target_id'];
    $field_new = $field;
    $spec = array('type' => 'int', 'size' => 'big');
    // Update the field.
    db_change_field($table, $field, $field_new, $spec);
    // Now do the revisions table.
    $table = 'field_revision_' . $data['field_name'];
    db_change_field($table, $field, $field_new, $spec);
  }
}

/**
 * Autocomplete results for the ticket form event field.
 */
function _eventbrite_event_autocomplete($string) {
  $matches = array();
  // Select the organizers table.
  $query = db_select('eventbrite_api_events', 'e');
  // Select rows that match the string.
  $return = $query
    ->fields('e', array('eid', 'title'))
    ->condition('e.title', '%' . db_like($string) . '%', 'LIKE')
    ->range(0, 10)
    ->execute();
  // Add matches to $matches . 
  foreach ($return as $row) {
    $matches[$row->eid] = check_plain($row->title);
  }
  // Return for JS.
  drupal_json_output($matches);
}

/**
 * Autocomplete results for the event form organizer field.
 */
function _eventbrite_organizer_autocomplete($string) {
  $matches = array();
  // Select the organizers table.
  $query = db_select('eventbrite_api_organizers', 'o');
  // Select rows that match the string.
  $return = $query
    ->fields('o', array('oid', 'name'))
    ->condition('o.name', '%' . db_like($string) . '%', 'LIKE')
    ->range(0, 10)
    ->execute();
  // Add matches to $matches . 
  foreach ($return as $row) {
    $matches[$row->oid] = check_plain($row->name);
  }
  // Return for JS.
  drupal_json_output($matches);
}

/**
 * Autocomplete results for the event form venue field.
 */
function _eventbrite_venue_autocomplete($string) {
  $matches = array();
  // Select the organizers table.
  $query = db_select('eventbrite_api_venues', 'v');
  // Select rows that match the string.
  $return = $query
    ->fields('v', array('vid', 'name'))
    ->condition('v.name', '%' . db_like($string) . '%', 'LIKE')
    ->range(0, 10)
    ->execute();
  // Add matches to $matches . 
  foreach ($return as $row) {
    $matches[$row->vid] = check_plain($row->name);
  }
  // Return for JS.
  drupal_json_output($matches);
}
