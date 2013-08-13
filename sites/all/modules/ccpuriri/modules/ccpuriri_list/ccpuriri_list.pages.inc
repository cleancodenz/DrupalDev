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
 * Menu callback; presents the list editing and new list form.
 * $type = add for new and edit for editing
 */
function ccpuriri_list_edit_form($form, &$form_state, $type,$list=array()) {

  if ($type=='edit')
  {
    drupal_set_title(t('<em>Edit </em> @title', array('@title' => $list->title)), PASS_THROUGH);
  }

  $form['#optype'] = $type;
  
  $list += array(
      'title' => '',
  );
  
  $form['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => $list['title'],
      '#required' => TRUE,
//      '#access' => TRUE,
  );
  
  
    
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
  );
  
  // Only custom menus may be deleted.
  $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#access' => $type == 'edit',
  );
  
  return $form;

}

/**
 * Submit function for adding or editing a custom list.
 */
function ccpuriri_list_edit_form_submit($form, &$form_state) {
  $list = $form_state['values'];
  
  if ($form['#optype']=='add') {
    // add list
/*
    $menu['menu_name'] = 'menu-' . $menu['menu_name'];
    $link['link_title'] = $menu['title'];
    $link['link_path'] = $path . $menu['menu_name'];
    $link['router_path'] = $path . '%';
    $link['module'] = 'menu';
    $link['plid'] = db_query("SELECT mlid FROM {menu_links} WHERE link_path = :link AND module = :module", array(
        ':link' => 'admin/structure/menu',
        ':module' => 'system'
    ))
    ->fetchField();

    menu_link_save($link);
    menu_save($menu);
    */
    drupal_set_message(t('New list has been added.'));
    
  }
  else {
    /*
    // update title of the list
    
    menu_save($menu);
    $result = db_query("SELECT mlid FROM {menu_links} WHERE link_path = :path", array(':path' => $path . $menu['menu_name']), array('fetch' => PDO::FETCH_ASSOC));
    foreach ($result as $m) {
      $link = menu_link_load($m['mlid']);
      $link['link_title'] = $menu['title'];
      menu_link_save($link);
    }
    */
    drupal_set_message(t('Your list change has been saved.'));
  }
 
 // $form_state['redirect'] = $path . $menu['menu_name'];
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
