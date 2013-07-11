<?php
/*
 * The form to change password
* */
function ccpuriri_user_account_info_form($form, &$form_state, $account)
{
  // do not worry about admin, admin is still using the old user/%/edit
  global $user;

  module_load_include('module', 'user', 'user');
  module_load_include('inc', 'user', 'user.pages');

  if (!isset($form_state['user'])) {
    $form_state['user'] = $account;
  }
  else {
    $account = $form_state['user'];
  }

  $form['#user'] = $account;

  $form['#user_category'] = 'account'; // to satisfy shared validation functions

  // this checks user name, email(if it is mandatory, singnature size conditionally
  // so it is all right if no signature is asked on this page)

  $form['#validate'][] = 'user_account_form_validate';

  // Account information.
  $form['account'] = array(
      '#type'   => 'container',
      '#weight' => -10,
  );

  // Only show name field form when the user is owner.
  $form['account']['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Username'),
      '#maxlength' => USERNAME_MAX_LENGTH,
      '#description' => t('Spaces are allowed; punctuation is not allowed except for periods, hyphens, apostrophes, and underscores.'),
      '#required' => TRUE,
      '#attributes' => array('class' => array('username')),
      '#default_value' => $account->name,
      '#access' => $user->uid == $account->uid && user_access('change own username'),
      '#weight' => 10,
  );

  $form['account']['mail'] = array(
      '#type' => 'textfield',
      '#title' => t('E-mail address'),
      '#maxlength' => EMAIL_MAX_LENGTH,
      '#description' => t('A valid e-mail address. All e-mails from the system will be sent to this address. The e-mail address is not made public and will only be used if you wish to receive a new password or wish to receive certain news or notifications by e-mail.'),
      '#required' => TRUE,
      '#weight' => 20,
      '#default_value' => $account->mail,
  );

  $form['account']['pass'] = array(
      '#type' => 'password_confirm',
      '#size' => 25,
      '#weight' => 40,
      '#description' => t('To change the current user password, enter the new password in both fields.'),
  );
  // To skip the current password field, the user must have logged in via a
  // one-time link and have the token in the URL.
  $pass_reset = isset($_SESSION['pass_reset_' . $account->uid]) && isset($_GET['pass-reset-token']) && ($_GET['pass-reset-token'] == $_SESSION['pass_reset_' . $account->uid]);
  $protected_values = array();
  $current_pass_description = '';
  // The user may only change their own password without their current
  // password if they logged in via a one-time login link.
  if (!$pass_reset) {
    $protected_values['mail'] = $form['account']['mail']['#title'];
    $protected_values['pass'] = t('Password');
    $request_new = l(t('Request new password'), 'user/password', array('attributes' => array('title' => t('Request new password via e-mail.'))));
    $current_pass_description = t('Enter your current password to change the %mail or %pass. !request_new.', array('%mail' => $protected_values['mail'], '%pass' => $protected_values['pass'], '!request_new' => $request_new));
  }
  // The user must enter their current password to change to a new one.
  if ($user->uid == $account->uid) {
    $form['account']['current_pass_required_values'] = array(
        '#type' => 'value',
        '#value' => $protected_values,
    );
    $form['account']['current_pass'] = array(
        '#type' => 'password',
        '#title' => t('Current password'),
        '#size' => 25,
        '#access' => !empty($protected_values),
        '#description' => $current_pass_description,
        '#weight' => 30,
        '#attributes' => array('autocomplete' => 'off'),
    );
    $form['#validate'][] = 'user_validate_current_pass';
  }


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
  );

  // Add the final user profile form submit handler.
  $form['#submit'][] = 'user_profile_form_submit';

  return $form;
}


/*
 * The form to change picture/avarta
* */
function ccpuriri_user_picture_form($form, &$form_state, $account)
{
  // do not worry about admin, admin is still using the old user/%/edit
 

  module_load_include('module', 'user', 'user');
  module_load_include('inc', 'user', 'user.pages');

  if (!isset($form_state['user'])) {
    $form_state['user'] = $account;
  }
  else {
    $account = $form_state['user'];
  }

  $form['#user'] = $account;

  $form['#user_category'] = 'account'; // to satisfy shared validation functions


  $form['picture'] = array(
      '#type' => 'fieldset',
      '#title' => t('Picture'),
      '#weight' => 1,
      '#access' => variable_get('user_pictures', 0),
  );
  
  $form['picture']['picture'] = array(
      '#type' => 'value',
      '#value' => isset($account->picture) ? $account->picture : NULL,
  );
  
  $form['picture']['picture_current'] = array(
      '#markup' => theme('user_picture', array('account' => $account)),
  );
  
  $form['picture']['picture_delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete picture'),
      '#access' => !empty($account->picture->fid),
      '#description' => t('Check this box to delete your current picture.'),
  );
  $form['picture']['picture_upload'] = array(
      '#type' => 'file',
      '#title' => t('Upload picture'),
      '#size' => 48,
      '#description' => t('Your virtual face or picture. Pictures larger than @dimensions pixels will be scaled down.', array('@dimensions' => variable_get('user_picture_dimensions', '85x85'))) . ' ' . filter_xss_admin(variable_get('user_picture_guidelines', '')),
  );
  $form['#validate'][] = 'user_validate_picture';


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
  );


  // Add the final user profile form submit handler.
  $form['#submit'][] = 'user_profile_form_submit';

  return $form;
}


/*
 * The form to change address
* */
function ccpuriri_user_address_form($form, &$form_state, $account)
{
  // do not worry about admin, admin is still using the old user/%/edit
   
  module_load_include('inc', 'ccpuriri_common', 'ccpuriri_common.field');
  
  if (!isset($form_state['user'])) {
    $form_state['user'] = $account;
  }
  else {
    $account = $form_state['user'];
  }
  
  $form['#user'] = $account;
  
  $form['#user_category'] = 'account'; // to satisfy shared validation functions
  
  //field_attach_form on one field address field
  
  // only available after 5.15
 // $langcode = entity_language('user', $account);
  $langcode = NULL;
  // to get all instances
  
  // Determine the list of instances to iterate on.
  list(, , $bundle) = entity_extract_ids('user', $account);
  $options = array(
      'deleted' => FALSE,
  );
  
  $instances = _field_invoke_get_instances('user', $bundle, $options);
    
  if($instances['field_ccpuriri_addressfield'])
  {       
    // get the form element for that field
    
    // Set #parents to 'top-level' by default.
    $form += array('#parents' => array());
    
    
    $instance = $instances['field_ccpuriri_addressfield'];
        
    $field = field_info_field_by_id($instance['field_id']);
    
    // save it in $form_state
    $form_state["#formfield"] = $field;
    
    $form_state["#formfieldinstance"] = $instance;
    
    ccpuriri_field_attach_one_form('user',
        $account, $bundle, $field, 
        $instance, $form, $form_state, $langcode);

    
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );
    
  } 
  
  return $form;
  
}

/*
 * Validate handler for address form
 * */
function ccpuriri_user_address_form_validate(&$form, &$form_state)
{
   
  module_load_include('inc', 'ccpuriri_common', 'ccpuriri_common.field');
  
  
  $account = $form['#user'];
        
   
   if($form_state["#formfield"] &&
       $form_state["#formfieldinstance"])
   {
          
     ccpuriri_field_attach_one_form_validate('user',
         $account, 
         $form_state["#formfield"],
         $form_state["#formfieldinstance"],
         $form, $form_state);
     
   }
   
}

/*
 * Submit handler  for address form
* */
function ccpuriri_user_address_form_submit(&$form, &$form_state)
{
   module_load_include('inc', 'ccpuriri_common', 'ccpuriri_common.field');
  
  // to get field values from form
  $account = $form['#user'];
  
  
  if($form_state["#formfield"] &&
      $form_state["#formfieldinstance"])
  {
    // field_attach_submit
    ccpuriri_field_attach_one_submit('user',
        $account,
        $form_state["#formfield"],
        $form_state["#formfieldinstance"],
        $form, $form_state);
  
    //field_attach_presave
    ccpuriri_field_attach_one_presave('user',
        $account,
        $form_state["#formfield"],
        $form_state["#formfieldinstance"]);
    
    
    // field_attach_update, to actually save field to db
    ccpuriri_field_attach_one_update('user',
        $account,
        $form_state["#formfield"],
        $form_state["#formfieldinstance"]);
    
    drupal_set_message(t('The address changes have been saved.'));
    
    // no need to clear the edited entity cache as it has been done in field_attach_update
    // do not do cache_clear_all() as in this case the edit form is 
    
    // rebuild the form again
   // $form_state["rebuild"]= true;
    
  }
}


/*
 * The form to change address
* */
function ccpuriri_user_contact_form($form, &$form_state,  $account)
{
  // do not worry about admin, admin is still using the old user/%/edit

   module_load_include('inc', 'ccpuriri_common', 'ccpuriri_common.field');

  if (!isset($form_state['user'])) {
    $form_state['user'] = $account;
  }
  else {
    $account = $form_state['user'];
  }

  $form['#user'] = $account;

  $form['#user_category'] = 'account'; // to satisfy shared validation functions

  //field_attach_form on one field address field

  // only available after 5.15
  // $langcode = entity_language('user', $account);
  $langcode = NULL;
  // to get all instances

  // Determine the list of instances to iterate on.
  list(, , $bundle) = entity_extract_ids('user', $account);
  $options = array(
      'deleted' => FALSE,
  );

  $instances = _field_invoke_get_instances('user', $bundle, $options);

  if($instances['field_ccpuriri_contactfield'])
  {
    // get the form element for that field

    // Set #parents to 'top-level' by default.
    $form += array('#parents' => array());

    // add desction 
    $form['description'] = array(
        '#type'=> 'markup',
        '#markup'=>'<div>The contacts set here can be copied to contacts of a listing</div>',
        );
    
    $instance = $instances['field_ccpuriri_contactfield'];

    $field = field_info_field_by_id($instance['field_id']);

    // save it in $form_state
    $form_state["#formfield"] = $field;

    $form_state["#formfieldinstance"] = $instance;

    ccpuriri_field_attach_one_form('user',
        $account, $bundle, $field,
        $instance, $form, $form_state, $langcode);


    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );

  }

  return $form;

}

/*
 * Validate handler for contact form
* */
function ccpuriri_user_contact_form_validate(&$form, &$form_state)
{

   module_load_include('inc', 'ccpuriri_common', 'ccpuriri_common.field');

  $account = $form['#user'];


  if($form_state["#formfield"] &&
      $form_state["#formfieldinstance"])
  {

    ccpuriri_field_attach_one_form_validate('user',
        $account,
        $form_state["#formfield"],
        $form_state["#formfieldinstance"],
        $form, $form_state);

  }

}

/*
 * Submit handler  for contact form
* */
function ccpuriri_user_contact_form_submit(&$form, &$form_state)
{
   module_load_include('inc', 'ccpuriri_common', 'ccpuriri_common.field');

  // to get field values from form
  $account = $form['#user'];


  if($form_state["#formfield"] &&
      $form_state["#formfieldinstance"])
  {
    // field_attach_submit
    ccpuriri_field_attach_one_submit('user',
        $account,
        $form_state["#formfield"],
        $form_state["#formfieldinstance"],
        $form, $form_state);

    //field_attach_presave
    ccpuriri_field_attach_one_presave('user',
        $account,
        $form_state["#formfield"],
        $form_state["#formfieldinstance"]);


    // field_attach_update, to actually save field to db
    ccpuriri_field_attach_one_update('user',
        $account,
        $form_state["#formfield"],
        $form_state["#formfieldinstance"]);

    drupal_set_message(t('The contacts changes have been saved.'));

    // no need to clear the edited entity cache as it has been done in field_attach_update
    // do not do cache_clear_all() as in this case the edit form is

 
  }
}


