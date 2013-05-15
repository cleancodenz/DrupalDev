<?php 

function ccpuriri_addressfield_generate($address, $context)
{
  $elements = array();

  // always having a tree structure for UI
  $elements['#tree'] = true;

  ccpuriri_addressfield_street($elements, $address, $context);

  return $elements;
}

/*
 * Street block, locality block
* */
function ccpuriri_addressfield_street($elements, $address, $context)
{

  // The street block.
  $elements['street_block'] = array(
      '#type' => 'ccpuriri_addressfield_container',
      '#attributes' => array('class' => array('street-block')),
      '#weight' => 0,
  );

  // first column

  $elements['street_block']['sub_premise'] = array(
      '#type' => 'textfield',
      '#title' => t('Unit'),
      '#tag' => 'div',
      '#attributes' => array('class' => array('sub_premise')),
      '#size' => 10,
  );


  $elements['street_block']['premise'] = array(
      '#type' => 'textfield',
      '#title' => t('Street Number'),
      '#tag' => 'div',
      '#attributes' => array('class' => array('premise')),
      '#size' => 20,
  );

  $elements['street_block']['thoroughfare'] = array(
      '#type' => 'textfield',
      '#title' => t('Street'),
      '#tag' => 'div',
      '#attributes' => array('class' => array('thoroughfare')),
      '#size' => 30,
      // The #required will be automatically set to FALSE when processing.
      '#required' => TRUE,
  );

  $elements['locality_block'] = array(
      '#type' => 'ccpuriri_addressfield_container',
    //  '#attributes' => array('class' => array('addressfield-container-inline', 'locality-block', 'country-' . $address['country'])),
      '#weight' => 50,
  );
  // $format['locality_block']['#attached']['css'][] = drupal_get_path('module', 'addressfield') . '/addressfield.css';
  $elements['locality_block']['dependent_locality'] = array(
      '#type' => 'textfield',
      '#title' => t('Suburb'),
      '#size' => 10,
      '#prefix' => ' ',
      '#attributes' => array('class' => array('dependent_locality')),
  );


  $elements['locality_block']['locality'] = array(
      '#type' => 'textfield',
      '#title' => t('City'),
      '#size' => 20,
      '#required' => TRUE,
      '#prefix' => ' ',
      '#attributes' => array('class' => array('locality')),
  );

  $elements['locality_block']['postal_code'] = array(
      '#title' => t('Postal Code'),
      '#size' => 30,
      // '#required' => TRUE,
      '#attributes' => array('class' => array('postal-code')),
  );


}