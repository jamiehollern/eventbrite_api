<?php

/**
 * @file
 * Example tpl file for theming a single event-specific theme
 *
 * Available variables:
 * - $status: The variable to theme (while only show if you tick status)
 * 
 * Helper variables:
 * - $event: The Event object this status is derived from
 */
?>

<div class="event-status">
  <?php print '<strong>Event Sample Data:</strong> ' . $event_sample_data = ($event_sample_data) ? 'Switch On' : 'Switch Off' ?>
</div>