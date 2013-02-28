<?php

function bootstrapcc_js_alter(&$javascript) {
  
  $javascript['misc/jquery.js']['data'] = drupal_get_path('theme', 'bootstrapcc').'/jquery/jquery-1.9.1.js';
}

function bootstrapcc_preprocess_html(&$variables) {
  
  // add view port tag to head
  $element = array(
      '#type'=>'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
          'name' => 'viewport',
          'content' =>'width=device-width, initial-scale=1.0', 
          ),
  );
  
  drupal_add_html_head($element, 'bootstrap_viewport');
  
}


function bootstrapcc_menu_tree__primary(&$variables) {
  return '<ul class="nav">' . $variables['tree'] . '</ul>';
}

function bootstrapcc_menu_link__main_menu(array $variables) {
  
  global $language_url;
  
  $element = $variables['element'];
  $sub_menu = '';
  
  if ($element['#below']) {
    //can not make make below on main manu, do no tknow why
    // Ad our own wrapper
    
    unset($element['#below']['#theme_wrappers']);
    $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
    $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
    $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
  
    // Check if this element is nested within another
    if ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] > 1)) {
      // Generate as dropdown submenu
      $element['#attributes']['class'][] = 'dropdown-submenu';
    }
    else {
      // Generate as standard dropdown
      $element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;
      $element['#title'] .= '<span class="caret"></span>';
    }
  
    // Set dropdown trigger element to # to prevent inadvertant page loading with submenu click
    $element['#localized_options']['attributes']['data-target'] = '#';
  }
  // add active class on li level
  
  if (($element['#href'] == $_GET['q'] 
      || ($element['#href'] == '<front>' && drupal_is_front_page())) 
      && (empty($element['#localized_options']['language']) 
          || $element['#localized_options']['language']->language == $language_url->language)) {
    $element['#attributes']['class'][] ='active';
    
  }
  
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
    
}