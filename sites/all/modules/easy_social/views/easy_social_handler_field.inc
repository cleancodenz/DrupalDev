<?php
/**
 * @file
 * Views handler for Easy Social.
 */

/**
* Handler for showing Easy Social share buttons in views
 */
class easy_social_handler_field extends views_handler_field {

  function query() {
    // Do nothing, as this handler does not need to do anything to the query itself.
  }
  
  /**
   * Render field. 
   */
  function render($values) {
    // Get absolute URL.
    $url = url('node/' . $values->nid, array('absolute' => TRUE));
    $node = node_load($values->nid);
    
    // Check if easy social is enabled for this content type.
    if (variable_get_value("easy_social_{$node->type}_enable")) {
      $type = $this->options['easy_social_type'];
      $enabled_widgets = $this->options['easy_social_widgets'];
      $widgets = _easy_social_render_widgets($url, $node->title, $type, $enabled_widgets, $node->language);
      return theme('easy_social_links', array('widgets' => $widgets));
    }
  }
  
  /**
   * Define extra Easy Social field options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['easy_social_type'] = array('default' => EASY_SOCIAL_WIDGET_HORIZONTAL);
    $options['easy_social_widgets'] = array('default' => variable_get_value('easy_social_global_widgets'));
    return $options;
  }
  
  /**
   * Extra Easy Social field options form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['easy_social'] = array(
      '#type' => 'fieldset',
      '#title' => t('Easy Social'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => -1,
//      '#tree' => TRUE,
    );
    
    $form['easy_social']['easy_social_type'] = array(
      '#type' => 'radios',
      '#title' => t('Type of buttons'),
      '#options' => array(
        EASY_SOCIAL_WIDGET_HORIZONTAL => t('Horizontal'),
        EASY_SOCIAL_WIDGET_VERTICAL => t('Vertical')
      ),
      '#default_value' => $this->options['easy_social_type'],
    );
    
    $form['easy_social']['easy_social_widgets'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Enabled Widgets'),
      '#options' => _easy_social_get_options(),
      '#default_value' => $this->options['easy_social_widgets'],
      '#description' => t('Some widgets may appear unformatted in the Views preview'),
    );
  }
  
  /**
   * Extra Easy Social options submit callback.
   */
  function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);
    $form_state['values']['options']['easy_social_type'] = $form_state['values']['options']['easy_social']['easy_social_type'];
    $form_state['values']['options']['easy_social_widgets'] = $form_state['values']['options']['easy_social']['easy_social_widgets'];
    unset($form_state['values']['options']['easy_social']);
  }
}