<?php
/*
 * The form to change password
 * */
function user_password_form($form, &$form_state, $account)
{
  global $user;
  
  $form['#user'] = $account;
 
  
  $form['mail'] = array(
      '#type' => 'textfield',
      '#title' => t('E-mail address'),
      '#maxlength' => EMAIL_MAX_LENGTH,
      '#description' => t('A valid e-mail address. All e-mails from the system will be sent to this address. The e-mail address is not made public and will only be used if you wish to receive a new password or wish to receive certain news or notifications by e-mail.'),
      '#required' => TRUE,
      '#default_value' => $account->mail,
  );
  
    $form['pass'] = array(
        '#type' => 'password_confirm',
        '#size' => 25,
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
      $form['current_pass_required_values'] = array(
          '#type' => 'value',
          '#value' => $protected_values,
      );
      $form['current_pass'] = array(
          '#type' => 'password',
          '#title' => t('Current password'),
          '#size' => 25,
          '#access' => !empty($protected_values),
          '#description' => $current_pass_description,
          '#weight' => -5,
          '#attributes' => array('autocomplete' => 'off'),
      );
      $form['#validate'][] = 'user_validate_current_pass';
    }
  
  
  
  
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
  );
  
  
  
  return $form;
}