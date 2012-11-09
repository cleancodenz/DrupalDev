<?php
/**
 * @file
 * ol_locator.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ol_locator_user_default_permissions() {
  $permissions = array();

  // Exported permission: create ol_locator_location content
  $permissions['create ol_locator_location content'] = array(
    'name' => 'create ol_locator_location content',
    'roles' => array(),
  );

  // Exported permission: delete any ol_locator_location content
  $permissions['delete any ol_locator_location content'] = array(
    'name' => 'delete any ol_locator_location content',
    'roles' => array(),
  );

  // Exported permission: delete own ol_locator_location content
  $permissions['delete own ol_locator_location content'] = array(
    'name' => 'delete own ol_locator_location content',
    'roles' => array(),
  );

  // Exported permission: edit any ol_locator_location content
  $permissions['edit any ol_locator_location content'] = array(
    'name' => 'edit any ol_locator_location content',
    'roles' => array(),
  );

  // Exported permission: edit own ol_locator_location content
  $permissions['edit own ol_locator_location content'] = array(
    'name' => 'edit own ol_locator_location content',
    'roles' => array(),
  );

  return $permissions;
}
