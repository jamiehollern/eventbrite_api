<?php

/**
 * Views for the default Eventbrite UI.
 */

/**
 * Implements hook_views_default_views().
 */
function eventbrite_views_default_views() {
  $views = array();

  $view = new view();
	$view->name = 'events';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'eventbrite_events';
	$view->human_name = 'Events';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
	
	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Events';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'none';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'full';
	$handler->display->display_options['pager']['options']['items_per_page'] = '50';
	$handler->display->display_options['style_plugin'] = 'default';
	$handler->display->display_options['row_plugin'] = 'fields';
	/* Field: Eventbrite: Event ID */
	$handler->display->display_options['fields']['eid']['id'] = 'eid';
	$handler->display->display_options['fields']['eid']['table'] = 'eventbrite_events';
	$handler->display->display_options['fields']['eid']['field'] = 'eid';
	
	/* Display: Page */
	$handler = $view->new_display('page', 'Page', 'page');
	$handler->display->display_options['path'] = 'admin/eventbrite/events/list';
	$handler->display->display_options['menu']['type'] = 'default tab';
	$handler->display->display_options['menu']['title'] = 'Events';
	$handler->display->display_options['menu']['description'] = 'Manage Eventbrite event data.';
	$handler->display->display_options['menu']['weight'] = '0';
	$handler->display->display_options['menu']['name'] = 'management';
	$handler->display->display_options['menu']['context'] = 0;
	$handler->display->display_options['menu']['context_only_inline'] = 0;
	$handler->display->display_options['tab_options']['type'] = 'normal';
	$handler->display->display_options['tab_options']['title'] = 'Events';
	$handler->display->display_options['tab_options']['description'] = 'Manage Eventbrite event data.';
	$handler->display->display_options['tab_options']['weight'] = '0';
	$handler->display->display_options['tab_options']['name'] = 'management';

  $views[] = $view;
  return $views;

}
