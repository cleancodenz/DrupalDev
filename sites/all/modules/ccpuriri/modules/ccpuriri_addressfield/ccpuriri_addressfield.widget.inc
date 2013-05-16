<?php 

function ccpuriri_addressfield_generate($address, $context)
{

  $settings =$context['instance']['widget']['settings'];

  $country = variable_get('ccpuriri_country', "NZ");
   
  $elements = array();

  // always having a tree structure for UI
  $elements['#tree'] = true;

  // name
  if ($settings['showname'])
  {
    ccpuriri_addressfield_name_full($elements, $address, $context);
  }
  // organizartion 
  if ($settings['showorganization'])
  {
    ccpuriri_addressfield_organisation($elements, $address, $context);
  }
  $streetfunction = 'ccpuriri_addressfield_street_'.$country;

  if (function_exists($streetfunction)) {
    $streetfunction($elements, $address, $context);

  }

  return $elements;
}

/*
 * Street block, locality block, NZ
* */
function ccpuriri_addressfield_street_NZ(&$elements, $address, $context)
{

  // The street block.
  $elements['street_block'] = array(
      '#type' => 'ccpuriri_addressfield_container',
      '#attributes' => array('class' => array('street-block')),
      '#weight' => 10,
  );

  // first column

  $elements['street_block']['sub_premise'] = array(
      '#type' => 'textfield',
      '#title' => t('Unit'),
      '#tag' => 'div',
      '#attributes' => array('class' => array('sub_premise')),
      '#default_value' =>$address['sub_premise'],
      '#size' => 30,
      '#weight' => 10,
      '#description' =>'A unit(flat, suite etc) and/or floor. It can also include a building name',
  );


  $elements['street_block']['premise'] = array(
      '#type' => 'textfield',
      '#title' => t('Street Number'),
      '#tag' => 'div',
      '#attributes' => array('class' => array('premise')),
      '#default_value' =>$address['premise'],
      '#size' => 30,
      '#weight' => 20,
  );

  $elements['street_block']['thoroughfare'] = array(
      '#type' => 'textfield',
      '#title' => t('Street'),
      '#tag' => 'div',
      '#attributes' => array('class' => array('thoroughfare')),
      '#default_value' =>$address['thoroughfare'],
      '#size' => 50,
      '#weight' => 30,
      // The #required will be automatically set to FALSE when processing.
      '#required' => TRUE,
  );

  $elements['locality_block'] = array(
      '#type' => 'ccpuriri_addressfield_container',
      '#attributes' => array('class' => array('addressfield-container-inline', 'locality-block')),
      '#weight' => 20,
  );
  // $format['locality_block']['#attached']['css'][] = drupal_get_path('module', 'addressfield') . '/addressfield.css';
  $elements['locality_block']['dependent_locality'] = array(
      '#type' => 'textfield',
      '#title' => t('Suburb'),
      '#size' => 30,
      '#weight' => 10,
      '#prefix' => ' ',
      '#default_value' =>$address['dependent_locality'],
      '#attributes' => array('class' => array('dependent_locality')),
  );


  $elements['locality_block']['locality'] = array(
      '#type' => 'textfield',
      '#title' => t('Town or City'),
      '#size' => 30,
      '#weight' => 20,
      '#required' => TRUE,
      '#prefix' => ' ',
      '#default_value' =>$address['locality'],
      '#attributes' => array('class' => array('locality')),
  );

  $elements['locality_block']['postal_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Postal Code'),
      '#size' => 30,
      '#weight' => 30,
      // '#required' => TRUE,
      '#default_value' =>$address['postal_code'],
      '#attributes' => array('class' => array('postal-code')),
  );

  module_load_include('inc', 'ccpuriri', 'ccpuriri.utility');

  $elements['country'] = array(
      '#type' => 'select',
      '#title' => t('Country'),
      '#weight' => 30,
      '#options' => ccpuriri_country_list(),
      '#default_value' =>$address['country'],
      '#disabled'=> true,
  );

}

/*
 * name_block
* */
function ccpuriri_addressfield_name_full(&$elements, $address, $context) {
  $elements['name_block'] = array(
      '#type' => 'ccpuriri_addressfield_container',
      '#attributes' => array('class' => array('addressfield-container-inline', 'name-block')),
      '#weight' => -100,
  );
  $elements['name_block']['first_name'] = array(
      '#type' => 'textfield',
      '#title' => t('First name'),
      '#size' => 30,
      '#default_value' =>$address['first_name'],
      '#required' => TRUE,
      '#attributes' => array('class' => array('first-name')),
  );
  $elements['name_block']['last_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Last name'),
      '#size' => 30,
      '#default_value' =>$address['last_name'],
      '#required' => TRUE,
      '#prefix' => ' ',
      '#attributes' => array('class' => array('last-name')),
  );
}

/**
 *
 * Organization_block
 */
function ccpuriri_addressfield_organisation(&$elements, $address, $context) {
  $elements['organisation_block'] = array(
      '#type' => 'ccpuriri_addressfield_container',
      '#attributes' => array('class' => array('addressfield-container-inline', 'name-block')),
      '#weight' => -50,
  );
  $elements['organisation_block']['organisation_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Company'),
      '#size' => 30,
      '#default_value' =>$address['organisation_name'],
      '#attributes' => array('class' => array('organisation-name')),
  );
}