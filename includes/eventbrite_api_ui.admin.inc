<?php

/**
 * @file
 * Model editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

/**
 * UI controller.
 */
class EventbriteAPIUIController extends EntityDefaultUIController {
/**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Eventbrite events',
      'description' => 'Add edit and update events.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );
    
    // Change the overview menu type for the list of models.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    
    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add an Eventbrite event',
      'description' => 'Add a new Eventbrite event',
      'page callback'  => 'eventbrite_api_event_add_page',
      'access callback'  => 'eventbrite_api_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'eventbrite_api.admin.inc',
      'file path' => drupal_get_path('module', 'includes/' . $this->entityInfo['module'])

    );

    // Loading and editing model entities
    $items[$this->path . '/model/' . $wildcard] = array(
      'page callback' => 'model_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'model_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'model.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/model/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    
    $items[$this->path . '/model/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'model_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'model_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'model.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    
    // Menu item for viewing models
    $items['event/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'model_page_title',
      'title arguments' => array(1),
      'page callback' => 'model_page_view',
      'page arguments' => array(1),
      'access callback' => 'model_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }
}
