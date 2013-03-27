<?php

/*
 * to replace jquery in misc with nwer version 
 */
function bootstrapcc_js_alter(&$javascript) {
  
  $javascript['misc/jquery.js']['data'] = drupal_get_path('theme', 'bootstrapcc').'/jquery/jquery-1.9.1.js';
}


/*
 * html theming
 * Add met tag with viewport to head
*/
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


/**
 * Pagetheming
 * Add own theme suggestions for page when user logged in
 *
 * @see page.tpl.php
 */
function bootstrapcc_preprocess_page(&$variables) {
  if (user_is_logged_in())
  {
    $variables['theme_hook_suggestions'][]='page__loggedin';
  }
  
}

/*
 *Main menu item theming
 * in default menu_tree_output there is override of menu_link_main_menu
 */
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

/*
 * Secondary menu item theming
 * 
 * */

function bootstrapcc_menu_link(array $variables) {
 
  
  $element = $variables['element'];
  $sub_menu = '';
  
  $options = $element['#localized_options'];
  
  // add active class on li level
  
  if (($element['#href'] == $_GET['q']
      || ($element['#href'] == '<front>' && drupal_is_front_page()))
      && (empty($element['#localized_options']['language'])
          || $element['#localized_options']['language']->language == $language_url->language)) {
    $element['#attributes']['class'][] ='active';
  
  }
  
 // if($element['#href']=='user')
 // {
//    $output = l('Hello '.format_username($user),$element['#href'],$options);
    
 // }
 // else
 //{
    $output = l($element['#title'],$element['#href'],$options);
 // }
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}


/*
 * Navigation  menu item theming
*
* */

function bootstrapcc_menu_link__navigation(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  $element['#localized_options']['html'] = TRUE;
  
  if ($element['#below']) {
    // Ad our own wrapper
    unset($element['#below']['#theme_wrappers']);

    $sub_menu = '<ul id="childmenu" class="nestednav">' . drupal_render($element['#below']) . '</ul>';
  
    
  }

  // add active class on li level

  if (($element['#href'] == $_GET['q']
      || ($element['#href'] == '<front>' && drupal_is_front_page()))
      && (empty($element['#localized_options']['language'])
          || $element['#localized_options']['language']->language == $language_url->language)) {
    $element['#attributes']['class'][] ='active';

  }

  $options = $element['#localized_options'];
  
  $output = l('<i class="icon-chevron-right"></i>'. $element['#title'],
      $element['#href'],$options);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}



/*
 * The navigation menu wrapper
 * Other menu wrappers
 * bootstrap_menu_tree__primary in bootstrap.tmplate.php for main menu wrapper
 * bootstrap_menu_tree__secondary in bootstrap.tmplate.php for secondary menu wrapper 
 */

function bootstrapcc_menu_tree(&$variables) {
  return '<ul class="nav nav-list  cc-sidenav">' . $variables['tree'] . '</ul>';
}


/**
 * remove the well class from base bootstrap
 *
 * @see region.tpl.php
 */
function bootstrapcc_preprocess_region(&$variables, $hook) {
  
  if ($variables['region'] == "sidebar_first") {
    
    if (($key = array_search('well', 
        $variables['classes_array'])) !== false) 
        unset($variables['classes_array'][$key]);
    
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for search_block_form().
 * add span* to customized the width of search box
 */
function bootstrapcc_form_search_block_form_alter(&$form, &$form_state) {
 
  // form
  // when fluid, 12 means 100% of parent
  $form['#attributes']['class'][] = 'span12';
  
  // input, remove  remove span2 which was added by base theme
  if (($key = array_search('span2',
      $form['search_block_form']['#attributes']['class'])) !== false)
    unset($form['search_block_form']['#attributes']['class'][$key]);
  
   
  // increase size attribute which is conflicting with span*
  // it is added by theme_textfield, so better not to override it
  // it is not attribute, but rendered as an attribute
  $form['search_block_form']['#size']=45;
}

/**
 * Implements hook_form_FORM_ID_alter() for search_form().
 * add span* to customized the width of search box
 * 
 */
function bootstrapcc_form_search_form_alter(&$form, &$form_state) {
 
  // form
  // when fluid, 12 means 100% of parent
  $form['#attributes']['class'][] = 'span12';
  
  // input, remove  remove span2 which was added by base theme
  if (($key = array_search('span2',
      $form['basic']['keys']['#attributes']['class'])) !== false)
    unset($form['basic']['keys']['#attributes']['class'][$key]);
  
  
  // increase size attribute which is conflicting with span*
  // it is added by theme_textfield, so better not to override it
  // it is not attribute, but rendered as an attribute
  $form['basic']['keys']['#size']=45;
  
}

