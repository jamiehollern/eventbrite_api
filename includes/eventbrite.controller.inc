<?php

/**
 * Eventbrite controller.
 */
class EventbriteEventController extends EntityAPIController {

  public function save($entity) {
    field_attach_presave('eventbrite_event', $entity);
    field_attach_update('eventbrite_event', $entity);
    // Send to Eventbrite.
    //remote_web_service_save($entity);
    return parent::save($entity);
  }

}