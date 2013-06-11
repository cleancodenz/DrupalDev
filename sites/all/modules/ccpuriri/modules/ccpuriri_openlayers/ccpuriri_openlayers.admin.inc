<?php 

/*
 * This is not a hook, but a callback from menu item admin/config/ccpuriri_openlayers
 * 
*/

function ccpuriri_openlayers_admin_settings() {
  
  $form['maptypes'] = array('#type' => 'fieldset', '#title' => t('Map settings for openlayer'));

  $description = t('Here will be map providers that are supported by this module');
  
  
  $form['maptypes']['ccpuriri_openlayers_mapprovider'] = array(
      '#type' => 'select',
      '#title' => t('Map provider'),
      '#options' => array(
          'Google' => t('Google'),
          'OSM' => t('OpenStreetMap'),
        ),
      '#default_value' => variable_get('ccpuriri_openlayers_mapprovider', "Google"),
      '#description' => $description,
  );
  return system_settings_form($form);
}
