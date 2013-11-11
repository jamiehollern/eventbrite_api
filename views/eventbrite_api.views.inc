<?php

/**
 * @file
 * Providing extra functionality for the Eventbrite UI via views.
 */

/**
 * Implements hook_views_data()
 */
function eventbrite_views_data() {
  $data = array();
  
  /**
   * Integrate the events table.
   */
  $data['eventbrite_events']['table']['group']  = t('Eventbrite');
  $data['eventbrite_events']['table']['entity type'] = 'eventbrite_event';

  $data['eventbrite_events']['table']['base'] = array(
    'field' => 'eid',
    'title' => t('Eventbrite Event'),
    'help' => t('Eventbrite Events.'),
  );
  
  // Expose the event ID.
  $data['eventbrite_events']['eid'] = array(
    'title' => t('Event ID'),
    'help' => t('The unique internal identifier of the event.'),
    'field' => array(  
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
  // Expose the organizer id.
  $data['eventbrite_events']['oid'] = array(
    'title' => t('Organizer ID'),
    'help' => t('The unique internal identifier of the event organizer.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'eventbrite_organizers',
      'base field' => 'oid',
      'label' => t('Event organizer'),
    ),
  );
  
  // Expose the venue id.
  $data['eventbrite_events']['vid'] = array(
    'title' => t('Venue ID'),
    'help' => t('The unique internal identifier of the event venue.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'eventbrite_venues',
      'base field' => 'vid',
      'label' => t('Event venue'),
    ),
  );
  
  if (module_exists('locale')) {
    // Expose the language.
    $data['eventbrite_events']['locale'] = array(
      'title' => t('Language'),
      'help' => t('The language the event is in.'),
      'field' => array(
       'handler' => 'views_handler_field_locale_language',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_locale_language',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_locale_language',
     ),
     'sort' => array(
     'handler' => 'views_handler_sort',
     ),
    );
  }
  
  // Expose the timezone.
  $data['eventbrite_events']['timezone'] = array(
    'title' => t('Timezone'),
    'help' => t('The event timezone.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the category.
  $data['eventbrite_events']['category'] = array(
    'title' => t('Category'),
    'help' => t('The event category.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the event capacity.
  $data['eventbrite_events']['capacity'] = array(
    'title' => t('Capacity'),
    'help' => t('The capacity of the event.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
  // Expose the number of registered event attendees.
  $data['eventbrite_events']['num_attendee_rows'] = array(
    'title' => t('Registered attendees'),
    'help' => t('The umber of registered event attendees.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the event title.
  $data['eventbrite_events']['title'] = array(
    'title' => t('Title'),
    'help' => t('The title of the event.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the event start date.
  $data['eventbrite_events']['start_date'] = array(
    'title' => t('Start date'),
    'help' => t('The date the event starts.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // Expose the event description.
  $data['eventbrite_events']['description'] = array(
    'title' => t('Description'),
    'help' => t('The description of the event.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  // Expose the event tags.
  $data['eventbrite_events']['tags'] = array(
    'title' => t('Tags'),
    'help' => t('The event tags.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the event timezone offset.
  $data['eventbrite_events']['timezone_offset'] = array(
    'title' => t('Timezone offset'),
    'help' => t('The event timezone offset.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the event password.
  $data['eventbrite_events']['password'] = array(
    'title' => t('Password'),
    'help' => t('The event password.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the date the event was created.
  $data['eventbrite_events']['created'] = array(
    'title' => t('Created'),
    'help' => t('The date the event was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
  
  // Expose the event URL.
  $data['eventbrite_events']['url'] = array(
    'title' => t('URL'),
    'help' => t('The event URL.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the event privacy setting.
  $data['eventbrite_events']['privacy'] = array(
    'title' => t('Privacy'),
    'help' => t('Whether the event is public or private.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the date the event was modified.
  $data['eventbrite_events']['modified'] = array(
    'title' => t('Modified'),
    'help' => t('The date the event was modified.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
  
  // Expose the event repetition setting.
  $data['eventbrite_events']['repeats'] = array(
    'title' => t('Repeats'),
    'help' => t('Whether the event repeats or not.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  /**
   * Integrate the organizers table.
   */
  $data['eventbrite_organizers']['table']['group']  = t('Eventbrite');
  $data['eventbrite_organizers']['table']['entity type'] = 'eventbrite_organizers';

  $data['eventbrite_organizers']['table']['base'] = array(
    'field' => 'oid',
    'title' => t('Eventbrite Organizers'),
    'help' => t('Organizers of Eventbrite events.'),
  );
  
  // Expose the organizer ID.
  $data['eventbrite_organizers']['oid'] = array(
    'title' => t('Organizer ID'),
    'help' => t('The unique internal identifier of the event organizer.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
  // Expose the organizer name.
  $data['eventbrite_organizers']['name'] = array(
    'title' => t('Name'),
    'help' => t('The name of the event organizer.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  /*$data['eventbrite_organizers']['table']['join'] = array(
    'eventbrite_events' => array(
      'left_field' => 'oid',
      'field' => 'oid',
    )
  );

  $data['eventbrite_organizers']['table']['default_relationship'] = array(
    'eventbrite_events' => array(
      'table' => 'eventbrite_events',
      'field' => 'oid',
    ),
  );*/
  
  // Expose the organizer description.
  $data['eventbrite_organizers']['description'] = array(
    'title' => t('Description'),
    'help' => t('The description of the event organizer.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the organizer long description.
  $data['eventbrite_organizers']['long_description'] = array(
    'title' => t('Long description'),
    'help' => t('The long description of the event organizer.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the organizer's URL.
  $data['eventbrite_organizers']['url'] = array(
    'title' => t('URL'),
    'help' => t('The URL of the event organizer.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  /**
   * Integrate the tickets table.
   */
  /*$data['eventbrite_tickets']['table']['group']  = t('Eventbrite');
  $data['eventbrite_tickets']['table']['entity type'] = 'eventbrite_tickets';

  $data['eventbrite_tickets']['table']['base'] = array(
    'field' => 'tid',
    'title' => t('Eventbrite Tickets'),
    'help' => t('Tickets for Eventbrite events.'),
    'defaults' => array(
      'field' => 'name',
    ),
  );

  $data['eventbrite_tickets']['table']['join'] = array(
    'eventbrite_events' => array(
      'left_field' => 'eid',
      'field' => 'eid',
    )
  );

  $data['eventbrite_tickets']['table']['default_relationship'] = array(
    'eventbrite_events' => array(
      'table' => 'eventbrite_events',
      'field' => 'eid',
    ),
  );
  
  // Expose the organizer ID.
  $data['eventbrite_organizers']['oid'] = array(
    'title' => t('Organizer ID'),
    'help' => t('The unique internal identifier of the event organizer.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );*/

  return $data;

}
