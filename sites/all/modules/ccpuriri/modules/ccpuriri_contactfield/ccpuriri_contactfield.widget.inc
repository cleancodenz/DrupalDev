<?php 


function ccpuriri_contactfield_generate(&$form, &$form_state,$contact, $context)
{
  $settings =$context['instance']['widget']['settings'];

  $elements = array();

  // always having a tree structure for UI
  $elements['#tree'] = true;


  $delta = $context['delta'];

  $contactype =  $contact['contacttype'];

  // add the type
  $elements['contacttype'] = array(
      '#type' => 'select',
      '#title' => t('Type'),
      '#weight' => 10,
      '#options' => array(
          10=>t('Personal'),
          20=>t('Company')),
      '#default_value' => $contact['contacttype'],
      '#ajax' => array(
          'callback' => 'ccpuriri_contact_type_callback',
          // 'wrapper' is the HTML id of the page element that will be replaced.
          'wrapper' => 'names_block_div'.$delta,

          'effect' => 'fade',
          
          'method' => 'replaceWith',
          // There are also several optional keys - see ajax_example_autocheckboxes
          // below for details on 'method', 'effect' and 'speed' and
          // ajax_example_dependent_dropdown for 'event'.
      ),
  );

  // The names block.
  $elements['names_block'] = array(
      '#type' => 'ccpuriri_container',
      '#attributes' => array('class' => array('names-block')),
      '#id' => 'names_block_div'.$delta, // this will be controlled by ajax
      '#weight' => 20,
  );


  // see if this is triggered by ajax
  if (!empty($form_state['triggering_element']['#parents']))
  {

    $n =sizeof($form_state['triggering_element']['#parents']);

    $parents = $form_state['triggering_element']['#parents'];

    if ($parents[$n-1] =='contacttype')
    {
      // the ajax triggered
      $key_exists = NULL;
      $value = drupal_array_get_nested_value($form_state['values'], $parents, $key_exists);
      if ($key_exists) {
        // replace contact type with new value
        $contactype = $value;

      }
    }
  }

  // then render names_block depending on which contact type is
  switch ($contactype)
  {
    case 10:
      // it is a person
      $elements['names_block']['first_name'] = array(
      '#type' => 'textfield',
      '#title' => t('First name'),
      '#size' => 50,
      '#weight' => 24,
      '#default_value' =>$contact['first_name'],
      '#attributes' => array('class' => array('contact-first-name')),
      '#required' => TRUE,
      );

      $elements['names_block']['last_name'] = array(
          '#type' => 'textfield',
          '#title' => t('Last name'),
          '#size' => 50,
          '#weight' => 26,
          '#default_value' =>$contact['last_name'],
          '#attributes' => array('class' => array('contact-last-name')),
          '#required' => TRUE,
      );

      break;
    case 20:
      // it is a company
      $elements['names_block']['organisation_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Company'),
        '#size' => 50,
        '#weight' => 22,
        '#default_value' =>$contact['organisation_name'],
        '#attributes' => array('class' => array('contact-organisation-name')),
        '#required' => TRUE,
      );
      break;

    default:
      break;

  }




  $elements['mobile'] = array(
      '#type' => 'textfield',
      '#title' => t('Mobile'),
      '#size' => 50,
      '#weight' => 30,
      '#default_value' =>$contact['mobile'],
      '#attributes' => array('class' => array('contact-mobile')),
  );

  $elements['workphone'] = array(
      '#type' => 'textfield',
      '#title' => t('Work'),
      '#size' => 50,
      '#weight' => 40,
      '#default_value' =>$contact['workphone'],
      '#attributes' => array('class' => array('contact-workphone')),
  );

  $elements['ahphone'] = array(
      '#type' => 'textfield',
      '#title' => t('After hours'),
      '#size' => 50,
      '#weight' => 50,
      '#default_value' =>$contact['ahphone'],
      '#attributes' => array('class' => array('contact-ahphone')),
  );

  $elements['email'] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#size' => 50,
      '#weight' => 60,
      '#default_value' =>$contact['email'],
      '#attributes' => array('class' => array('contact-email')),
  );

  $elements['bestway'] = array(
      '#type' => 'textfield',
      '#title' => t('Notes'),
      '#size' => 50,
      '#weight' => 60,
      '#default_value' =>$contact['bestway'],
      '#attributes' => array('class' => array('contact-bestway')),
  );
   

  return $elements;
}

function ccpuriri_contact_type_callback($form, $form_state) {
  // The form has already been submitted and updated. We can return the replaced
  // item as it is.
  $names_block = array();
  
  $n =sizeof($form_state['triggering_element']['#parents']);
  
  $parents = $form_state['triggering_element']['#parents'];
  
  $parents[$n-1] = 'names_block'; // replace contacttype with names_block
  
  $key_exists = NULL;
  $value = drupal_array_get_nested_value($form, $parents, $key_exists);
  if ($key_exists) {

   $names_block = $value;
  
  }
  
  return  $names_block;
  
}
