<?php

function eventbrite_currencies() {
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

function eventbrite_ctime($timestamp) {
	$time = date('c', $timestamp);
	$time = str_replace('T', ' ', $time);
	$time = explode('+', $time);
	return $time[0];
}

function eventbrite_datef($date) {
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

function eventbrite_import_all() {
	// Authorisation details.
  $auth = array('app_key'  => variable_get('eventbrite_appkey', ''), 'user_key' => variable_get('eventbrite_userkey', ''));
	// Connect to Eventbrite.
  $eb_client = new Eventbrite($auth);
	// Get all data by using the user_list_events method.
  $data = $eb_client->user_list_events();
	// Format it nicely.
	$events = eventbrite_format_all($data);
	dpm($events);
	return;
	// Should we delete everything before importing?
	if (variable_get('eventbrite_import_delete', 1) == 1) {
		// Yes.
    $result = db_truncate('eventbrite_events')->execute();
    $result = db_truncate('eventbrite_organizers')->execute();
    $result = db_truncate('eventbrite_tickets')->execute();
    $result = db_truncate('eventbrite_venues')->execute();
	}
	else {
		// Update.
	}
}

function eventbrite_format_all($data) {// Create an array for our events.
	$events = array();
	// Run through each row of data.
	foreach ($data->events as $row) {
		// Set the eid.
		$eid = $row->event->id;
		// Add the organizer.
		$events[$eid]['organizer'] = (array) $row->event->organizer;
		// Change the id to oid.
		$oid = $events[$eid]['organizer']['id'];
		$events[$eid]['organizer']['oid'] = $oid;
		unset($events[$eid]['organizer']['id']);
		// Remove the organizer from the original data.
		unset($row->event->organizer);
		// Check if there are tickets for this event.
		if (isset($row->event->tickets) && !empty($row->event->tickets)) {
			// Run through each ticket.
		  foreach ($row->event->tickets as $ticket) {
				// Ticket ID.
				$tid = $ticket->ticket->id;
			  $events[$eid]['tickets'][$tid] = (array) $ticket->ticket;
				// Change the ID to tid.
			  $events[$eid]['tickets'][$tid]['tid'] = $tid;
			  unset($events[$eid]['tickets'][$tid]['id']);
				// Add event ID.
			  $events[$eid]['tickets'][$tid]['eid'] = $eid;
		  }
		  // Remove the tickets from the original data.
		  unset($row->event->tickets);
		}
		// Check if there is a venue for this event.
		if (isset($row->event->venue) && !empty($row->event->venue)) {
			// Add the venue.
			$events[$eid]['venue'] = (array) $row->event->venue;
			// Change the id to vid.
			$vid = $events[$eid]['venue']['id'];
			$events[$eid]['venue']['vid'] = $vid;
			unset($events[$eid]['venue']['id']);
			// Change Lat-Long to lat_long.
			$events[$eid]['venue']['lat_long'] = $events[$eid]['venue']['Lat-Long'];
			unset($events[$eid]['venue']['Lat-Long']);
			// Remove the organizer from the original data.
			unset($row->event->venue);
		}
		// Add the organizer.
		$events[$eid]['event'] = (array) $row->event;
		// Change the id to eid.
		$events[$eid]['event']['eid'] = $events[$eid]['event']['id'];
		unset($events[$eid]['event']['id']);
		// Add vid and oid.
		$events[$eid]['event']['oid'] = $oid;
		if (!empty($vid)) {
		  $events[$eid]['event']['vid'] = $vid;
		}
	}
	return $events;
}
