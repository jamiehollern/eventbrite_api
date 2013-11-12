<?php

/**
 * Views for the default Eventbrite UI.
 */

/**
 * Implements hook_views_default_views().
 */
function eventbrite_views_default_views() {
  $views = array();

  $view = new view;
  $view->name = 'events';
  $view->description = 'A list of all events';
  $view->tag = 'events';
  $view->base_table = 'event';
  $view->human_name = 'Events';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Eventbrite';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create any event type';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'event_id' => 'event_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'event_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty ';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No events have been created yet';
  /* Field: Event: Event ID */
  $handler->display->display_options['fields']['event_id']['id'] = 'event_id';
  $handler->display->display_options['fields']['event_id']['table'] = 'event';
  $handler->display->display_options['fields']['event_id']['field'] = 'event_id';
  $handler->display->display_options['fields']['event_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['event_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['event_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['event_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['event_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['event_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['event_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['event_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['event_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['event_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['event_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['event_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['event_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['event_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['event_id']['empty_zero'] = 0;
  /* Field: Event: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'event';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  /* Field: Event: Link */
  $handler->display->display_options['fields']['link_event']['id'] = 'link_event';
  $handler->display->display_options['fields']['link_event']['table'] = 'event';
  $handler->display->display_options['fields']['link_event']['field'] = 'link_event';
  $handler->display->display_options['fields']['link_event']['label'] = 'View';
  $handler->display->display_options['fields']['link_event']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['link_event']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['link_event']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['link_event']['alter']['external'] = 0;
  $handler->display->display_options['fields']['link_event']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['link_event']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['link_event']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['link_event']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['link_event']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['link_event']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['link_event']['alter']['html'] = 0;
  $handler->display->display_options['fields']['link_event']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['link_event']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['link_event']['hide_empty'] = 0;
  $handler->display->display_options['fields']['link_event']['empty_zero'] = 0;
  /* Field: Event: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'event';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;
  
  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'events_admin_page');
  $handler->display->display_options['path'] = 'admin/eventbrite/events/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Events';
  $handler->display->display_options['tab_options']['description'] = 'Manage events';
  $handler->display->display_options['tab_options']['weight'] = '';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['events'] = array(
    t('Master'),
    t('Events'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Empty '),
    t('No events have been created yet'),
    t('Event ID'),
    t('.'),
    t(','),
    t('Name'),
    t('View'),
    t('Operations links'),
    t('Page'),
  );
  $views[] = $view;
  return $views;

}
