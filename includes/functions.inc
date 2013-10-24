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
function eb_get_events($object = '$eb_client') {
	$events = array();
  foreach ($object->user_list_events()->events as $event) {
		$events[] = $event->event;
	}
	return $events;
}

/**
 * Takes an event object returned by Eventbrite and
 * prepares it to be saved as a Drupal object.
 */
function eb_event_object_prepare($object) {
	$event = array(
	  'eid' => $object->id,
	  'oid' => $object->organizer->id,
	  'locale' => $object->locale,
	  'timezone' => $object->timezone,
	  'category' => $object->category,
	  'capacity' => $object->capacity,
	  'num_attendee_rows' => $object->num_attendee_rows,
	  'title' => $object->title,
	  'start_date' => $object->start_date,
	  'status' => $object->status,
	  'description' => strip_tags($object->description),
	  'end_date' => $object->end_date,
	  'tags' => (isset($object->tags) ? $object->tags : ''),
	  'timezone_offset' => $object->timezone_offset,
	  'password' => (isset($object->password) ? $object->password : ''),
	  'created' => $object->created,
	  'url' => $object->url,
	  'privacy' => $object->privacy,
	  'modified' => $object->modified,
	  'repeats' => $object->repeats,
	);
	return $event;
}

/**
 * Worker callback for the eventbrite_api_events cron queue.
 */
function eventbrite_api_entity_import($item) {
	// Prepare events.
	$event = eb_event_object_prepare($item);
	$entity = entity_create('eventbrite_api_event', $event);
	$save = entity_save('eventbrite_api_event', $entity);
	watchdog('Eventbrite API', ($save == FALSE ? 'Entity not saved' : $save));
}
