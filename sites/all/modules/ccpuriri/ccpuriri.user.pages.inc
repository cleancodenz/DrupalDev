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



