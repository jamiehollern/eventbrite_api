<?php

/**
 * Views for the default Eventbrite API UI.
 */

/**
 * Implements hook_views_default_views().
 */
function eventbrite_api_ui_views_default_views() {
  
  $views = array();
  

  $views[$view->name] = $view;

  return $views;
}
