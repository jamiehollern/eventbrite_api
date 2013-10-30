<?php

/**
 * @file
 * Providing extra functionality for the Eventbrite API UI via views.
 */

/**
 * Implements hook_views_data()
 */
function eventbrite_api_views_data() {
  $data = array();
	
  $data['eventbrite_api_event']['table']['group']  = t('Eventbrite Event');

  $data['eventbrite_api_event']['table']['base'] = array(
    'field' => 'eid',
    'title' => t('Eventbrite Event'),
    'help' => t('Eventbrite Events.'),
    //'access query tag' => 'commerce_product_access',
  );
	
  $data['eventbrite_api_event']['table']['entity type'] = 'eventbrite_api_event';
	
	// Expose the event ID.
  $data['eventbrite_api_event']['eid'] = array(
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
  $data['eventbrite_api_event']['oid'] = array(
    'title' => t('Organizer'),
    'help' => t('Relate an event to the person who organized it.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'eventbrite_api_organizer',
      'field' => 'oid',
      'label' => t('Event organizer'),
    ),
  );
	
	if (module_exists('locale')) {
    // Expose the language.
    $data['eventbrite_api_event']['locale'] = array(
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
  $data['eventbrite_api_event']['timezone'] = array(
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
  $data['eventbrite_api_event']['category'] = array(
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
  $data['eventbrite_api_event']['capacity'] = array(
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
  $data['eventbrite_api_event']['num_attendee_rows'] = array(
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
  $data['eventbrite_api_event']['title'] = array(
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
  $data['eventbrite_api_event']['start_date'] = array(
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
  $data['eventbrite_api_event']['description'] = array(
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
		// Needed or not? Probably not.
    /*'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),*/
  );
	
	// Expose the event tags.
  $data['eventbrite_api_event']['tags'] = array(
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
  $data['eventbrite_api_event']['timezone_offset'] = array(
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
  $data['eventbrite_api_event']['password'] = array(
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
  $data['eventbrite_api_event']['created'] = array(
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
  $data['eventbrite_api_event']['url'] = array(
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
  $data['eventbrite_api_event']['privacy'] = array(
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
  $data['eventbrite_api_event']['modified'] = array(
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
  $data['eventbrite_api_event']['repeats'] = array(
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
	
}
