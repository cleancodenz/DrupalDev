<?php 


function ccpuriri_admin_settings() {
  
  $form['countries'] = array('#type' => 'fieldset', '#title' => t('Country settings'));

  $description = t('This module only supports one country at moment, and it is set here');
  
  module_load_include('inc', 'ccpuriri', 'ccpuriri.utility');
  
  $form['countries']['ccpuriri_country'] = array(
      '#type' => 'select',
      '#title' => t('Country'),
      '#options' => ccpuriri_country_list(),
     
      '#default_value' => variable_get('ccpuriri_country', "NZ"),
      '#description' => $description,
  );
  return system_settings_form($form);
}
