<?php 

/*
 * field_attach_form for one field
 * */
function ccpuriri_field_attach_one_form($entity_type,
    $entity,$bundle, $field, $instance,
    &$form, &$form_state,$langcode = NULL,
    $options = array())
{

  $options = is_array($options) ? $options : array();

  // If no language is provided use the default site language.
  $options['language'] = field_valid_language($langcode);


  $options['default'] = true;

  $form+= _ccpuriri_field_one_field_invoke(
      'form', $entity_type, $entity,
      $field, $instance, $form, $form_state, $options);
   

  //extra fields do not apply to a one field form
  // $form['#pre_render'][] = '_field_extra_fields_pre_render';
  $form['#entity_type'] = $entity_type;
  $form['#bundle'] = $bundle;


  // Let other modules make changes to the form.
  // Avoid module_invoke_all() to let parameters be taken by reference.
  foreach (module_implements('field_attach_form') as $module) {
    $function = $module . '_field_attach_form';
    $function($entity_type, $entity, $form, $form_state, $langcode);
  }

}

/*
 * field_attach_form_validate for only one field
 * */
function ccpuriri_field_attach_one_form_validate($entity_type,
    $entity, $field, $instance,
    &$form, &$form_state, $options = array())
{

  $options = is_array($options) ? $options : array();
  $options['default'] = true;

  _ccpuriri_field_one_field_invoke(
      'extract_form_values', $entity_type, $entity,
      $field, $instance,  $form, $form_state, $options);

  // Perform field_level validation.
  try {

    $errors = array();
    $null = Null;
    //default validate
    _ccpuriri_field_one_field_invoke(
        'validate', $entity_type, $entity,
        $field, $instance,  $errors, $null, $options);

    $options['default'] = false;

    // field specific validate
    _ccpuriri_field_one_field_invoke(
        'validate', $entity_type, $entity,
        $field, $instance,  $errors, $null, $options);

    // Let other modules validate the entity.
    // Avoid module_invoke_all() to let $errors be taken by reference.
    foreach (module_implements('field_attach_validate') as $module) {
      $function = $module . '_field_attach_validate';
      $function($entity_type, $entity, $errors);
    }

    if ($errors) {
      throw new FieldValidationException($errors);
    }

  }
  catch (FieldValidationException $e) {
    // Pass field-level validation errors back to widgets for accurate error
    // flagging.
    foreach ($e->errors as $field_name => $field_errors) {
      foreach ($field_errors as $langcode => $errors) {
        $field_state = field_form_get_state($form['#parents'], $field_name, $langcode, $form_state);
        $field_state['errors'] = $errors;
        field_form_set_state($form['#parents'], $field_name, $langcode, $form_state, $field_state);
      }
    }
    _field_invoke_default('form_errors', $entity_type, $entity, $form, $form_state, $options);
  }

}

/*
 * field_attach_form_submit for one field
 * */
function ccpuriri_field_attach_one_form_submit($entity_type,
    $entity, $field, $instance,
    &$form, &$form_state, $options = array())
{
  $options = is_array($options) ? $options : array();
  $options['default'] = true;
  
  _ccpuriri_field_one_field_invoke(
      'extract_form_values', $entity_type, $entity,
      $field, $instance,  $form, $form_state, $options);
  
  $options['default'] = false;
  
  // field specific submit
  _ccpuriri_field_one_field_invoke(
      'submit', $entity_type, $entity,
      $field, $instance,  $form, $form_state, $options);

  // Let other modules act on submitting the entity.
  // Avoid module_invoke_all() to let $form_state be taken by reference.
  foreach (module_implements('field_attach_submit') as $module) {
    $function = $module . '_field_attach_submit';
    $function($entity_type, $entity, $form, $form_state);
  }
  
}

/*
 * field_attach_one_presave for one field only 
 * */
function ccpuriri_field_attach_one_presave($entity_type, $entity,$field, $instance)
{
   _ccpuriri_field_one_field_invoke(
      'presave', $entity_type, $entity,
      $field,$instance);
  
   // Let other modules act on presaving the entity.
   module_invoke_all('field_attach_presave', $entity_type, $entity);
}

// update is done by deleting first, so if it is inserting, calling update should be the same
function ccpuriri_field_attach_one_update($entity_type, $entity,$field, $instance)
{
  _ccpuriri_field_one_field_invoke(
      'update', $entity_type, $entity,
      $field,$instance);
  
  // Let any module update field data before the storage engine, accumulating
  // saved fields along the way.
  $skip_fields = array();
  foreach (module_implements('field_storage_pre_update') as $module) {
    $function = $module . '_field_storage_pre_update';
    $function($entity_type, $entity, $skip_fields);
  }
  
  // Collect the storage backends used by the remaining fields in the entities.
  $storages = array();
  
  $field_id = $field['id'];
  $field_name = $field['field_name'];
  
  // Leave the field untouched if $entity comes with no $field_name property,
  // but empty the field if it comes as a NULL value or an empty array.
  // Function property_exists() is slower, so we catch the more frequent
  // cases where it's an empty array with the faster isset().
  if (isset($entity->$field_name) || property_exists($entity, $field_name)) {
    // Collect the storage backend if the field has not been written yet.
    if (!isset($skip_fields[$field_id])) {
      $storages[$field['storage']['type']][$field_id] = $field_id;
    }
  }
  
  // Field storage backends save any remaining unsaved fields.
  foreach ($storages as $storage => $fields) {
    $storage_info = field_info_storage_types($storage);
    module_invoke($storage_info['module'], 'field_storage_write', $entity_type, $entity, FIELD_STORAGE_UPDATE, $fields);
  }
  
  // Let other modules act on updating the entity.
  module_invoke_all('field_attach_update', $entity_type, $entity);
  
  $entity_info = entity_get_info($entity_type);
  if ($entity_info['field cache']) {
    cache_clear_all("field:$entity_type:$id", 'cache_field');
  }
  
}


/*
 * just invoke one field
* */
function _ccpuriri_field_one_field_invoke(
    $op, $entity_type, $entity,
    $field,$instance, &$a = NULL, &$b = NULL, $options = array())
{
  // Merge default options.
  $default_options = array(
      'default' => FALSE,
      'deleted' => FALSE,
      'language' => NULL,
  );
  $options += $default_options;

  // Iterate through the instances and collect results.
  $return = array();
  // field_info_field() is not available for deleted fields, so use
  // field_info_field_by_id().
  $field_name = $field['field_name'];
  $function = $options['default'] ? 'field_default_' . $op : $field['module'] . '_field_' . $op;
  if (function_exists($function)) {
    // Determine the list of languages to iterate on.
    $available_languages = field_available_languages($entity_type, $field);
    $languages = _field_language_suggestion($available_languages, $options['language'], $field_name);

    foreach ($languages as $langcode) {
      $items = isset($entity->{$field_name}[$langcode]) ? $entity->{$field_name}[$langcode] : array();
      $result = $function($entity_type, $entity, $field, $instance, $langcode, $items, $a, $b);
      if (isset($result)) {
        // For hooks with array results, we merge results together.
        // For hooks with scalar results, we collect results in an array.
        if (is_array($result)) {
          $return = array_merge($return, $result);
        }
        else {
          $return[] = $result;
        }
      }

      // Populate $items back in the field values, but avoid replacing missing
      // fields with an empty array (those are not equivalent on update).
      if ($items !== array() || isset($entity->{$field_name}[$langcode])) {
        $entity->{$field_name}[$langcode] = $items;
      }
    }
  }

  return $return;

}

