<?php

class eb extends Eventbrite {
	
	private $ukey;
	private $akey;
	
  function __construct() {
		$this->ukey = variable_get('eventbrite_userkey');
		$this->akey = variable_get('eventbrite_appkey');
    parent::__construct(array('app_key' => $this->akey, 'user_key' => $this->ukey));
	}
	
	public function get_data() {
		$data = $tickets = array();
		// Run through all event data.
		foreach (parent::user_list_events()->events as $key => $value) {
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
   * Truncates all 4 of the entities tables.
	 * @todo Make this more secure.
   */
  public function delete_all() {
	  $truncate = db_truncate('eventbrite_events')->execute();
	  $truncate = db_truncate('eventbrite_organizers')->execute();
	  $truncate = db_truncate('eventbrite_tickets')->execute();
	  $truncate = db_truncate('eventbrite_venues')->execute();
  }
	
}
