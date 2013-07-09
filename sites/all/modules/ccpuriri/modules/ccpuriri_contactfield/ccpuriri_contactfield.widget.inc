<?php 


function ccpuriri_contactfield_generate(
    &$form, &$form_state, $field, $instance, $langcode,
    $items, $delta, $element)
{

  // Get the default contact used to build the widget form elements, looking
  // first in the stored value for the field, and then in the default values of the instance.
  $contact = array();

  if (!empty($items[$delta])) {
    // Else use the saved value for the field.
    $contact = $items[$delta];
  }


  // get feidl_state
  $parents = $form['#parents'];
  $field_name= $field['field_name'];
  // use field_form_get_state to get current field state
  $field_state = field_form_get_state($parents, $field_name, $langcode, $form_state);

  // control blank item
  // only render one when items_coount 0 which is first initial rendering 
    if ($field_state['items_count']> 0 && $delta ==$field_state['items_count'])
    {
      $element=array();

      return $element; // not rendering anything
    }
  
  // check if the call is ajax, for form sumission, this will not be run, as process will go to submit handlers straight away
  if (!empty($form_state['triggering_element'])
      && !empty($form_state['triggering_element']['#parents']))
  {

    //  it is either add more button or drop down
    $ajaxParent = $form_state['triggering_element']['#parents'];
    $button_name = $ajaxParent[sizeof($ajaxParent)-1];


    // load the $contact from form_state
    if($button_name=='contacttype')
    {
      // we always have $delta matching with form_state,
      // so everytime the one extra blank will be back 
      if($delta < $field_state['items_count'])
      {
        // to get object from form_state['values']
        // the activating contacttype might not be on same item
        $key_exists = NULL;

        $deltaParent = array_slice($ajaxParent, 0,sizeof($ajaxParent)-2);
        $deltaParent[] = $delta;

        $value = drupal_array_get_nested_value($form_state['values'],
            $deltaParent, $key_exists);
        if ($key_exists) {
          // replace contact type with new value
          $contact = $value;

        }

      } 

    }else if ($button_name=='add_more')
    {
      // add_more button click
      //-> 'field_add_more_submit'
      //-> items_count in field_state increased one
      //-> form rebuild
      //-> coming to here
      //-> no form_state, no $items of course
      //-> do not render the last blank one as we do not want two blank ones
       
      if($delta < $field_state['items_count']-1)
      {
        // to get object from form_state['values']
         
        $key_exists = NULL;

        $deltaParent = array_slice($ajaxParent, 0,sizeof($ajaxParent)-1);

        $deltaParent[] = $delta;

        $value = drupal_array_get_nested_value($form_state['values'],
            $deltaParent, $key_exists);
        if ($key_exists) {
          // replace contact type with new value
          $contact = $value;
        }

      }
      else if ($delta == $field_state['items_count']-1) {
        // this is new blank one

        //an empty item, as it is asked by add_more, do not set it now, leave it to last data population step to use default values


      }// if($delta < $field_state['items_count']-1)
  

    } //if($button_name=='contacttype')
  } //  if (!empty($form_state['triggering_element']) && !empty($form_state['triggering_element']['#parents']))

  // Merge in default values to provide a value for every expected array key.

  $contact += _ccpuriri_contactfield_default_value();
   
  // always having a tree structure for UI
  $element['#tree'] = true;


  // add the type
  $element['contacttype'] = array(
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
  $element['names_block'] = array(
      '#type' => 'ccpuriri_container',
      '#attributes' => array('class' => array('names-block')),
      '#id' => 'names_block_div'.$delta, // this will be controlled by ajax
      '#weight' => 20,
  );


  // then render names_block depending on which contact type is
  switch ($contact['contacttype'])
  {
    case 10:
      // it is a person
      $element['names_block']['first_name'] = array(
      '#type' => 'textfield',
      '#title' => t('First name'),
      '#size' => 50,
      '#weight' => 24,
      '#default_value' =>$contact['first_name'],
      '#attributes' => array('class' => array('contact-first-name')),
      '#required' => TRUE,
      );

      $element['names_block']['last_name'] = array(
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
      $element['names_block']['organisation_name'] = array(
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

  $element['mobile'] = array(
      '#type' => 'textfield',
      '#title' => t('Mobile'),
      '#size' => 50,
      '#weight' => 30,
      '#default_value' =>$contact['mobile'],
      '#attributes' => array('class' => array('contact-mobile')),
  );

  $element['workphone'] = array(
      '#type' => 'textfield',
      '#title' => t('Work'),
      '#size' => 50,
      '#weight' => 40,
      '#default_value' =>$contact['workphone'],
      '#attributes' => array('class' => array('contact-workphone')),
  );

  $element['ahphone'] = array(
      '#type' => 'textfield',
      '#title' => t('After hours'),
      '#size' => 50,
      '#weight' => 50,
      '#default_value' =>$contact['ahphone'],
      '#attributes' => array('class' => array('contact-ahphone')),
  );

  $element['email'] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#size' => 50,
      '#weight' => 60,
      '#default_value' =>$contact['email'],
      '#attributes' => array('class' => array('contact-email')),
  );

  $element['bestway'] = array(
      '#type' => 'textfield',
      '#title' => t('Notes'),
      '#size' => 50,
      '#weight' => 60,
      '#default_value' =>$contact['bestway'],
      '#attributes' => array('class' => array('contact-bestway')),
  );
   

  return $element;
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
