<?php 

/*
 * The form to /list
* */
function ccpuriri_list_form($form, &$form_state)
{
  if (!user_is_logged_in())
  {    
    $destination = drupal_get_destination();
    drupal_goto('user/login',array('query' => $destination));
  }
  return $form;
  
}