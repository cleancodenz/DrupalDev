<?php

/**
 * Implements hook_pathauto().
 */
function ccruby_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'ccruby';
      $settings['token_type'] = 'user';
      $settings['groupheader'] = t('Account paths');
      $settings['patterndescr'] = t('Pattern for ccruby account page paths');
      $settings['patterndefault'] = 'accounts/[user:name]';
      $settings['batch_update_callback'] = 'account_pathauto_bulk_update_batch_process';
      return (object) $settings;
    default:
      break;
  }
}

/**
 * Batch processing callback; Generate aliases for users.
 */
function account_pathauto_bulk_update_batch_process(&$context) {
  if (!isset($context['sandbox']['current'])) {
    $context['sandbox']['count'] = 0;
    $context['sandbox']['current'] = 0;
  }

  $query = db_select('users', 'u');
  $query->leftJoin('url_alias', 'ua', "CONCAT('account/', u.uid) = ua.source");
  $query->addField('u', 'uid');
  $query->isNull('ua.source');
  $query->condition('u.uid', $context['sandbox']['current'], '>');
  $query->orderBy('u.uid');
  $query->addTag('pathauto_bulk_update');
  $query->addMetaData('entity', 'user');

  // Get the total amount of items to process.
  if (!isset($context['sandbox']['total'])) {
    $context['sandbox']['total'] = $query->countQuery()->execute()->fetchField();

    // If there are no nodes to update, the stop immediately.
    if (!$context['sandbox']['total']) {
      $context['finished'] = 1;
      return;
    }
  }

  $query->range(0, 25);
  $uids = $query->execute()->fetchCol();

  pathauto_account_update_alias_multiple($uids, 'bulkupdate', array('alias blog' => FALSE));
  $context['sandbox']['count'] += count($uids);
  $context['sandbox']['current'] = max($uids);
  $context['message'] = t('Updated alias for user @uid.', array('@uid' => end($uids)));

  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}


/**
 * Update the URL aliases for multiple user accounts.
 *
 * @param $uids
 *   An array of user account IDs.
 * @param $op
 *   Operation being performed on the accounts ('insert', 'update' or
 *   'bulkupdate').
 * @param $options
 *   An optional array of additional options.
 */
function pathauto_account_update_alias_multiple(array $uids, $op, array $options = array()) {
  $options += array('message' => FALSE);

  $accounts = user_load_multiple($uids);
  foreach ($accounts as $account) {
    pathauto_account_update_alias($account, $op, $options);
  }

  if (!empty($options['message'])) {
    drupal_set_message(format_plural(count($uids), 'Updated URL alias for 1 user account.', 'Updated URL aliases for @count user accounts.'));
  }
}

/**
 * Update the URL aliases for an individual user account.
 *
 * @param $account
 *   A user account object.
 * @param $op
 *   Operation being performed on the account ('insert', 'update' or
 *   'bulkupdate').
 * @param $options
 *   An optional array of additional options.
 */
function pathauto_account_update_alias(stdClass $account, $op, array $options = array()) {
  // Skip processing if the user has disabled pathauto for the account.
  if (isset($account->path['pathauto']) && empty($account->path['pathauto'])) {
    return;
  }

  $options += array(
      'language' => LANGUAGE_NONE,
  );

  // Skip processing if the account has no pattern.
  if (!pathauto_pattern_load_by_entity('user', '', $options['language'])) {
    return;
  }

  module_load_include('inc', 'pathauto');
  
  pathauto_create_alias('ccruby', $op, "account/{$account->uid}", array('user' => $account), NULL, $options['language']);
  
}