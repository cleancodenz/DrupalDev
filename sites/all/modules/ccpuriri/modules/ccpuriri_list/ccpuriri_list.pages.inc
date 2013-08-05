<?php 

/*
 * The form to /list
* */
function ccpuriri_list_form($form, &$form_state)
{
  if (!user_is_logged_in())
  {    
    $destination = drupal_get_destination();
    drupal_goto('user/login',array('query' => $destination));
  }
  return $form;
  
}

/*
 * The form to  add a list , url: list/add
* */
function ccpuriri_list_add_form($form, &$form_state)
{
  return $form;

}


/*
 * The page to display items of a list, url: list/add
* */
function ccpuriri_list_page_view($list)
{
  return '';

  /*
   * 
   *  // If there is a menu link to this node, the link becomes the last part
  // of the active trail, and the link name becomes the page title.
  // Thus, we must explicitly set the page title to be the node title.
  drupal_set_title($node->title);
  $uri = entity_uri('node', $node);
  // Set the node path as the canonical URL to prevent duplicate content.
  drupal_add_html_head_link(array('rel' => 'canonical', 'href' => url($uri['path'], $uri['options'])), TRUE);
  // Set the non-aliased path as a default shortlink.
  drupal_add_html_head_link(array('rel' => 'shortlink', 'href' => url($uri['path'], array_merge($uri['options'], array('alias' => TRUE)))), TRUE);
  return node_show($node);
   * */
}

/**
 * Menu callback; presents the list editing form.
 */
function ccpuriri_list_edit($list) {
  //$type_name = node_type_get_name($node);
  drupal_set_title(t('<em>Edit </em> @title', array('@title' => $list->title)), PASS_THROUGH);
  return '';
 // return drupal_get_form($node->type . '_node_form', $node);
}


/**
 * Menu callback -- ask for confirmation of list deletion
 */
function ccpuriri_list_delete_confirm($form, &$form_state, $list) {
  $form['#list'] = $list;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['lid'] = array('#type' => 'value', '#value' => $list->lid);
  return confirm_form($form,
      t('Are you sure you want to delete %title?', array('%title' => $list->title)),
      'list/' . $list->lid,
      t('This action cannot be undone.'),
      t('Delete'),
      t('Cancel')
  );
}
