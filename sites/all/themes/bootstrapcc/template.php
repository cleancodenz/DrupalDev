<?php

/*
 * to replace jquery in misc with newer version 
 */
function bootstrapcc_js_alter(&$javascript) {
  
  $javascript['misc/jquery.js']['data'] = drupal_get_path('theme', 'bootstrapcc').'/jquery/jquery-1.9.1.js';
}

/*
 * to add fontawesome to css
*/
function bootstrapcc_css_alter(&$css) {

  $cdn = '//netdna.bootstrapcdn.com/font-awesome/3.2.1/css/font-awesome.css';
  $css[$cdn] = array(
      'data' => $cdn,
      'type' => 'external',
      'every_page' => TRUE,
      'media' => 'all',
      'preprocess' => TRUE,
      'group' => CSS_THEME,
      'browsers' => array('IE' => TRUE, '!IE' => TRUE),
      'weight' => 10,
  );

  return $css;
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

/**
 * Implements hook_preprocess_block().
 */
function bootstrapcc_preprocess_block(&$variables) {
  // add well class to all block.
 // if (!($variables['block']->module == 'search' && $variables['block']->delta=='form')) {
//  $variables['classes_array'][] = 'well';
//  }
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
  
  if (isset($element['#localized_options']) && 
      isset($element['#localized_options']['attributes']) &&
      isset($element['#localized_options']['attributes']['class']) &&
      (in_array("active-trail", $element['#localized_options']['attributes']['class'])
          ||in_array("active", $element['#localized_options']['attributes']['class']))) {
    $element['#attributes']['class'][] ='active';
  
  }
  
 if ($element['#title']=='Home'){
    
    $element['#localized_options']['html']=true;
    
    $output = l('<i class="glyphicon glyphicon-home"></i>'.$element['#title'], $element['#href'], $element['#localized_options']);
    
  }elseif (isset($element['#localized_options']['icon']))
  {
    $output = l('<i class="'.$element['#localized_options']['icon'].'"></i>'.$element['#title'], $element['#href'], $element['#localized_options']);
  }
  else
  {
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  }
  

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
    
}

/*
 * Secondary and all others menu item theming
 * 
 * */

function bootstrapcc_menu_link(array $variables) {
 
  
  $element = $variables['element'];
  $sub_menu = '';
  
  if ($element['#below']) {
    //can not make make below on main manu, do no tknow why
    // Ad our own wrapper
  
    unset($element['#below']['#theme_wrappers']);
    $sub_menu = "<ul class='nav nav-pills nav-stacked' style='max-width: 250px;'>" . drupal_render($element['#below']) . "</ul>\n";
     
    $element['#localized_options']['html'] = TRUE;
  
    // Set dropdown trigger element to # to prevent inadvertant page loading with submenu click
  }
  
  // add active class on li level
  
  if (isset($element['#localized_options']) &&
      isset($element['#localized_options']['attributes']) &&
      isset($element['#localized_options']['attributes']['class']) &&
      (in_array("active-trail", $element['#localized_options']['attributes']['class'])
          ||in_array("active", $element['#localized_options']['attributes']['class']))) {
    $element['#attributes']['class'][] ='active';
  
  }
  
  $strpos = strpos($element['#href'],'#');
  
  if( $strpos!==false)
  {
    $parts =explode('#',$element['#href']);
    
    $element['#href'] = $parts[0];
    $element['#localized_options']['fragment']=$parts[1];
    
  }
  if ($element['#title']=='Home'){
    
    $element['#localized_options']['html']=true;
    
    $output = l('<i class="glyphicon glyphicon-home"></i>'.$element['#title'], $element['#href'], $element['#localized_options']);
    
  }elseif (isset($element['#localized_options']['icon']))
  {
    $output = l('<i class="'.$element['#localized_options']['icon'].'"></i>'.$element['#title'], $element['#href'], $element['#localized_options']);
  }
  else
  {
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  }
   
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>";
}





/*
 * The navigation menu wrapper
 * Other menu wrappers
 * bootstrap_menu_tree__primary in bootstrap.tmplate.php for main menu wrapper
 * bootstrap_menu_tree__secondary in bootstrap.tmplate.php for secondary menu wrapper 
 */

function bootstrapcc_menu_tree(&$variables) {
  return "<div class='cp-sidebar hidden-print' role='complementary'>
  <ul class='nav nav-pills nav-stacked' style='max-width: 250px;'>" . $variables['tree'] . "</ul></div>\n";
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
  $form['#attributes']['class'][] = 'col-md-12';
  
  // input, remove  remove span2 which was added by base theme
  if (($key = array_search('col-md-2',
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

function bootstrapcc_form_search_form_alter(&$form, &$form_state) {
 
  // form
  // when fluid, 12 means 100% of parent
  $form['#attributes']['class'][] = 'span12';
  
  // input, remove  remove span2 which was added by base theme
  if (($key = array_search('col-md-2',
      $form['basic']['keys']['#attributes']['class'])) !== false)
    unset($form['basic']['keys']['#attributes']['class'][$key]);
  
  
  // increase size attribute which is conflicting with span*
  // it is added by theme_textfield, so better not to override it
  // it is not attribute, but rendered as an attribute
  $form['basic']['keys']['#size']=45;
  
}
 * 
 */

/*
 * Bread crumb override, add current title to the end of bread crumb
 * and title will not be displayed separately
 * */

/**
 * Override theme_breadrumb().
 *
 * Print breadcrumbs as a list, with separators.
 
function bootstrapcc_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  $item = menu_get_item();
  
  if (!empty($breadcrumb)) {
    $breadcrumbs = '<ul class="breadcrumb">';
    
  
    foreach ($breadcrumb as $key => $value) {
     
        $breadcrumbs .= '<li>' . $value . '<span class="divider">/</span></li>';
  
  
     
    }
    // add current title to it
    $breadcrumbs .= '<li>' . $item['title'] . '</li>'.'</ul>';
    
  
    
    return $breadcrumbs;
  }
}
*/
