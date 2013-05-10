<?php 

/**
 * Implements  hook_field_widget_settings_form
 */
function ccpuriri_addressfield_field_widget_settings_form($field, $instance)
{
  $widget = $instance['widget'];
  $settings = $widget['settings'];

  $form['showname'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show name fields for address'),
      '#default_value' => $settings['showname'],
      
  );

  return $form;

}