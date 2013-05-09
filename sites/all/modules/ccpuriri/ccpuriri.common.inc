<?php 

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
      $field, $instance, &$form, &$form_state, $options);
   
 
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

function ccpuriri_field_attach_one_form_validate($entity_type,
    $entity,$bundle, $instance,
    &$form, &$form_state,
    $options)
{
  if ($form_state["#formfieldinstance"] &&
      $form_state["#formfieldinstance"]['field_id'] == $instance['field_id'] )
  {
    $field =  $form_state["#formfield"];


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

