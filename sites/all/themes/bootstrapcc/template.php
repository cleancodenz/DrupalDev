<?php

/*
 * to replace jquery in misc with newer version
*/
function bootstrapcc_js_alter(&$javascript) {

  $javascript['misc/jquery.js']['data'] = drupal_get_path('theme', 'bootstrapcc').'/jquery/jquery-1.9.1.js';
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
* Menu style in base theme
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
    $output = l('<i class="glyphicon glyphicon-'.$element['#localized_options']['icon'].'"></i>'.$element['#title'], $element['#href'], $element['#localized_options']);
  }
  else
  {
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  }


  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";

}



/*
 * Secondary top item theming
* Menu style in base theme
*
* */

function bootstrapcc_menu_link__secondoary_top(array $variables) {


  $element = $variables['element'];


  // no below rendering

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

  if (isset($element['#localized_options']['icon']))
  {
    $output = l('<i class="glyphicon glyphicon-'.$element['#localized_options']['icon'].'"></i>'.$element['#title'], $element['#href'], $element['#localized_options']);
  }
  else
  {
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  }

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . "</li>";
}

/*
 * Navigation menu item theming
*


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
$output = l('<i class="glyphicon glyphicon-'.$element['#localized_options']['icon'].'"></i>'.$element['#title'], $element['#href'], $element['#localized_options']);
}
else
{
$output = l($element['#title'], $element['#href'], $element['#localized_options']);
}

return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>";
}

* */

/*
 * Navigation menu item theming
 * No nav pill version, active bold the text 
*
* */


function bootstrapcc_menu_link(array $variables) {

  $element = $variables['element'];
  $sub_menu = '';
  $active = false;
  
  // set the localized options html to true, no matter what has been set,
  // in order to make bold text, bages 
  
  $element['#localized_options']['html']= true;
  
  if ($element['#below']) {
    //can not make make below on main manu, do no tknow why
    // Ad our own wrapper

    unset($element['#below']['#theme_wrappers']);
    $sub_menu = "<ul class='nav nav-stacked' style='max-width: 250px;'>" . drupal_render($element['#below']) . "</ul>\n";
  }

  // add active class on li level
  if (isset($element['#localized_options']) &&
      isset($element['#localized_options']['attributes']) &&
      isset($element['#localized_options']['attributes']['class']) &&
      (in_array("active-trail", $element['#localized_options']['attributes']['class'])
          ||in_array("active", $element['#localized_options']['attributes']['class']))) {
     
    $active=true;

  }

  $strpos = strpos($element['#href'],'#');

  if( $strpos!==false)
  {
    if ($strpos>0)
    {
      //$strpos==0, this local named tags, do not use fragment
    
      $parts =explode('#',$element['#href']);

      $element['#href'] = $parts[0];
      $element['#localized_options']['fragment']=$parts[1];
    }
  }
  
  if ($active)
  {
    $element['#title'] ='<strong>'.$element['#title'].'</strong>';
  
     
  }
  
  if ($element['#title']=='Home'){

    $element['#localized_options']['html']=true;

    $output = l('<i class="glyphicon glyphicon-home"></i>'.$element['#title'], $element['#href'], $element['#localized_options']);

  }elseif (isset($element['#localized_options']['icon']))
  {
    $output = l('<i class="glyphicon glyphicon-'.$element['#localized_options']['icon'].'"></i>'.$element['#title'], $element['#href'], $element['#localized_options']);
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


function bootstrapcc_menu_tree(&$variables) {
return "<div class='cp-sidebar hidden-print' role='complementary'>
<ul class='nav nav-pills nav-stacked' style='max-width: 250px;'>" . $variables['tree'] . "</ul></div>\n";
}

*/

/*
 * The navigation menu wrapper
 *  No nav pill version, active bold the text 
 *  
* Other menu wrappers
* bootstrap_menu_tree__primary in bootstrap.tmplate.php for main menu wrapper
* bootstrap_menu_tree__secondary in bootstrap.tmplate.php for secondary menu wrapper
*/

function bootstrapcc_menu_tree(&$variables) {
  return "<div class='cp-sidebar hidden-print' role='complementary'>
  <ul class='nav nav-stacked' style='max-width: 250px;'>" . $variables['tree'] . "</ul></div>\n";
}



/**
 * Render a button which has a title
 * theme wrapper for ccpuriri_titlebutton
 */
function bootstrapcc_ccpuriri_dropdownbutton($variables) {
  $element = $variables['element'];

  element_set_attributes($element, array('id', 'name', 'value'));
  
  $element['#attributes']['type'] = 'button';

  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  $element['#attributes']['class'][] = 'btn';

  // button color
  if (!empty($element['#colorcode']))
  {
    $element['#attributes']['class'][] = 'btn-'.$element['#colorcode'];

  }
  else
  {
    $element['#attributes']['class'][] = 'btn-default';
  }

  
  $element['#attributes']['class'][] = 'dropdown-toggle';

  $element['#attributes']['data-toggle'] = 'dropdown';

  //move value to text
  $val = '';

  if (!empty($element['#attributes']['value']))
  {
    $val = $element['#attributes']['value'];
    unset($element['#attributes']['value']);
  }

  $buttonOutput ='<button '.drupal_attributes($element['#attributes']).'>';

  if (!empty($element['#icon']))
  {
    $buttonOutput .= '<i class="glyphicon glyphicon-'.$element['#icon'].'"></i> ' ;
  }
  $buttonOutput.=$val.'<span class="caret"></span></button>';


  $buttonOutput .='<ul class="dropdown-menu" role="menu">';

  foreach($element['#items'] as $item)
  {
    if ($item['id']==0)
    {
      $buttonOutput.='<li class="divider" value="'.$item['id'].'"></li>';
    }
    else
    {
      $buttonOutput.='<li value="'.$item['id'].'"><a href="#">'.$item['description'].'</a></li>';
    }
  }

  $buttonOutput.='</ul>';

  //wrap them under a div with a id as elementid-div, this will be used by clientside javascript

  return '<div class="btn-group" id="'.$element['#id'].'-div'. '">' .
      $buttonOutput.$element['#children']."</div>\n";

}

/**
 * Render a button which has an icon
 * theme wrapper for ccpuriri_imagebutton
 */
function bootstrapcc_ccpuriri_imagebutton($variables) {

  $element = $variables['element'];

  element_set_attributes($element, array('id', 'name', 'value', 'type'));


  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  // add bootstrap attributes

  $element['#attributes']['class'][] = 'btn';


  // button color
  if (!empty($element['#colorcode']))
  {
    $element['#attributes']['class'][] = 'btn-'.$element['#colorcode'];

  }
  else
  {
    $element['#attributes']['class'][] = 'btn-default';
  }


  $buttonoutput = '<button' . drupal_attributes($element['#attributes']) . '>';

  if (!empty($element['#icon']))
  {
    $buttonoutput.='<i class="glyphicon glyphicon-'.$element['#icon'].'"></i> ';

  }

  $buttonoutput .= $element['#title'] ."</button>\n"; // This line break adds inherent margin between multiple buttons

  return '<div class="btn-group">'.$buttonoutput."</div>\n";

}


