<?php

/**
 * @file
 * Page callbacks and form builder functions for administering events.
 */

/**
 * Form callback wrapper: create or edit a product.
 *
 * @param $product
 *   The product object being edited by this form.
 *
 * @see commerce_product_product_form()
 */
function commerce_product_ui_product_form_wrapper($product) {
  // Include the forms file from the Product module.
  module_load_include('inc', 'commerce_product', 'includes/commerce_product.forms');
  return drupal_get_form('commerce_product_ui_product_form', $product);
}
