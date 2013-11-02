<?php

/**
 * @file
 * Provides general functions for the Eventbrite API module.
 */

/**
 * This is a quicker, less clumsy way of instantiating a new
 * instance of the Eventbrite class.
 */
function eb_connect($akey = '', $ukey = '') {
  if (empty($ukey)) {
    $ukey = variable_get('eventbrite_api_userkey');
  }
  if (empty($akey)) {
    $akey = variable_get('eventbrite_api_appkey');
  }
  return new Eventbrite(array('app_key' => $akey, 'user_key' => $ukey));
}

/**
 * This function gets all events and changes the format of the
 * returned data object into a simpler array.
 */
function eb_get_data($object = '$eb_client') {
  $data = $tickets = array();
  foreach ($object->user_list_events()->events as $key => $value) {
    // We'll use the event ID as the array key.
    $id = $value->event->id;
		// Event start date.
		$start = $value->event->start_date;
    // Run through the tickets.
		$tickets = array();
    foreach ($value->event->tickets as $ticket) {
      // Get all variables plus the event id.
      $temp = get_object_vars($ticket->ticket) + array('eid' => $id);
			// Make sure there's a start date.
			if (!isset($temp['start_date']) || empty($temp['start_date'])) {
				$temp['start_date'] = $start;
			}
      $tickets[] = $temp;
    }
    // Add the organizer, tickets and venue to the array.
    $data[$id] = array (
      'organizer' => get_object_vars($value->event->organizer),
      'tickets' => $tickets,
      'venue' => get_object_vars($value->event->venue),
    );
    // Get rid of non event entity specific details from the object.
    unset($value->event->organizer, $value->event->tickets, $value->event->venue);
    // Add the event details to the start of the array.
    $data[$id] = array('event' => get_object_vars($value->event)) + $data[$id];
    // Add in extra IDs that we need.
    $data[$id]['event']['oid'] = $data[$id]['organizer']['id'];
    $data[$id]['event']['vid'] = $data[$id]['venue']['id'];
  }
  return $data;
}

/**
 * 
 */
function eventbrite_api_entity_prepare($data, $type) {
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
 * Worker callback for the eventbrite_api_events cron queue.
 */
function eventbrite_api_entity_import($item) {
  // Prepare events.
  $entity = eventbrite_api_entity_prepare($item['event'], 'event');
  $entity = entity_create('eventbrite_api_event', $entity);
  $entity->save();
  // Prepare organizer.
  $entity = eventbrite_api_entity_prepare($item['organizer'], 'organizer');
  $entity = entity_create('eventbrite_api_organizer', $entity);
  $entity->save();
  // Prepare tickets.
  foreach ($item['tickets'] as $ticket) {
    $entity = eventbrite_api_entity_prepare($ticket, 'ticket');
    $entity = entity_create('eventbrite_api_ticket', $entity);
    $entity->save();
  }
  // Prepare venue.
  $entity = eventbrite_api_entity_prepare($item['venue'], 'venue');
  $entity = entity_create('eventbrite_api_venue', $entity);
  $entity->save();
}

function eventbrite_api_import_all($form, $form_state) {
  // Instantiate Eventbrite.
  $eb_client = eb_connect();
  // Get a list of events.
  $items = eb_get_data($eb_client);
	// Save the entities.
  foreach ($items as $item) {
    eventbrite_api_entity_import($item);
	}
}
