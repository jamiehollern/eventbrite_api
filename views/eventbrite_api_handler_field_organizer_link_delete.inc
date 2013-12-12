<?php

/**
 * Field handler to present a link to delete an event.
 */
class eventbrite_api_handler_field_organizer_link_delete extends eventbrite_api_handler_field_organizer_link_edit {
  function construct() {
    parent::construct();
  }

  function render($values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $oid = $this->get_value($values, 'oid');
    return l($text, 'admin/eventbrite/organizer/' . $oid . '/delete');
  }
}
