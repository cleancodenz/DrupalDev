<?php 

function ccpuriri_field_attach_one_form($entity_type,
    $entity,$bundle, $instance,
    &$form, &$form_state,
    $options)
{

  $field = field_info_field_by_id($instance['field_id']);

  $field_name = $field['field_name'];

  $function = 'field_default_form';
  if (function_exists($function)) {

    // Determine the list of languages to iterate on.
    $available_languages = field_available_languages($entity_type, $field);
    $languages = _field_language_suggestion($available_languages, $options['language'], $field_name);

    $return = array();

    foreach ($languages as $langcode) {
      $items = isset($entity->{$field_name}[$langcode]) ? $entity->{$field_name}[$langcode] : array();
      $result = $function($entity_type, $entity, $field, $instance, $langcode, $items, $form, $form_state);
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
  $form+=$return;
 
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