<?php 

/*
 * This is not a hook, but a callback from menu item admin/config/ccpuriri_openlayers
 * 
*/

function ccpuriri_openlayers_admin_settings() {
  
  $form['maptypes'] = array('#type' => 'fieldset', '#title' => t('Map settings for openlayer'));

  // map provider
  
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
  
  // default geo coordinates
  // when there is valid geo coordinates for an address, 
  // it will first check browser geo if successfull, use browser geo
  // if no browser geo, the use this setting as the last resort
  $description2 = t('When geo coordinates can not be decided for an address, neither can it be retireved from browser, the default coorindates defined here will be used');
  
  
  $form['maptypes']['ccpuriri_openlayers_defaultlat'] = array(
      '#type' => 'textfield',
      '#title' => t('Default latitude'),
      '#default_value' => variable_get('ccpuriri_openlayers_defaultlat', '-36.8666700'),
      '#description' => $description2,
  );
  
  $form['maptypes']['ccpuriri_openlayers_defaultlon'] = array(
      '#type' => 'textfield',
      '#title' => t('Default lontitude'),
      '#default_value' => variable_get('ccpuriri_openlayers_defaultlon', '174.7666700'),
      '#description' => $description2,
  );
   
  return system_settings_form($form);
}
