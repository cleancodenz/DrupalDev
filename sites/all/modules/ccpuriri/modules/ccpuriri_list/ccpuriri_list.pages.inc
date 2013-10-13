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
 * The page to display items of a list, url: list/1
* */
function ccpuriri_list_page_view($list)
{
  
  // menu_tree_set_path('ccpuririlistnavigation','list/%');
  
  return 'dddddd';

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
function ccpuriri_list_edit_form($form, &$form_state, $type,$list=NULL) {

  $cancleurl='list';
  
  if($type=='add')
  {
    $list =(object)array('title' => '',);
  }
  
  if ($type=='edit')
  {
    drupal_set_title(t('<em>Edit </em> @title', array('@title' => $list->title)), PASS_THROUGH);

    // save the list
    $form_state['#list'] = $list;
    
    $cancleurl ='list/'.$list->lid;
    
    
  }
  
  $form['#optype'] = $type;
  
  $form['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => $list->title,
      '#required' => TRUE,
//      '#access' => TRUE,
  );
      
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
  );
  

  $form['actions']['cancel'] = array(
      '#type' => '',
      '#title' => t('Cancel'),
      '#href' => $cancleurl,
  );
 
  
 
  return $form;

}

/**
 * Submit function for adding or editing a custom list.
 */
function ccpuriri_list_edit_form_submit($form, &$form_state) {
  $list = $form_state['values'];
  
  global $user;
  
  if ($form['#optype']=='add') {
    
    _ccpuriri_list_add_list($list['title'],$user->uid);
    
    $form_state['redirect'] = 'list';
    
    drupal_set_message(t('New list has been added.'));
    
    
  }
  else {
    $updatelist = new stdClass();
    
    $updatelist->title = $list['title'];
    $updatelist->lid =$form_state['#list']->lid;
    $updatelist->uid = $user->uid;
    
    ccpuriri_list_save($updatelist);

    $form_state['redirect'] = 'list/'.$updatelist->lid;
    
    drupal_set_message(t('Your list change has been saved.'));
  }
 
}


/**
 * Validate function for adding or editing a custom list.
 */
function ccpuriri_list_edit_form_validate($form, &$form_state) {
  $list = $form_state['values'];

  global $user;
  
  $noduplicate = false;
  
  if ($form['#optype']=='add') {
        
    $noduplicate =  _ccpuriri_list_title_noduplicate(
        $list['title'],$user->uid,0);
    
    }else{
    $noduplicate =  _ccpuriri_list_title_noduplicate(
        $list['title'],$user->uid, $form_state['#list']->lid);
      
  }
  
  
  if (!$noduplicate)
  {
    form_set_error('info', t('List already exists.'));
  }
  
}


/**
 * Menu callback -- ask for confirmation of list deletion
 */
function ccpuriri_list_delete_confirm($form, &$form_state, $list) {
  $form_state['#list'] = $list;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['lid'] = array('#type' => 'value', '#value' => $list->lid);
  // as we do not display title
  $question = t('Are you sure you want to delete %title?', array('%title' => $list->title));
  
  $form['question'] = array(
      '#type' => 'item',
      '#markup' => $question,

  );
  
  return confirm_form($form,
      $question,
      'list/' . $list->lid,
      t('This action cannot be undone.'),
      t('Delete'),
      t('Cancel')
  );
}

/**
 * Validate function for deleting a custom list.
 */
function ccpuriri_list_delete_confirm_validate($form, &$form_state) {
 // normally these conditions are impossible, here just to protect
 
  $list= $form_state['#list'] ;
  if (!isset($list) || !isset($list->lid))
  {
    form_set_error('info', t('Trying to delete a list which does not exist.'));
  }
  
  if ($list->is_shared)
  {
    form_set_error('info', t('Can not delete this system list.'));
  }
  
  if ($list->items_count>0)
  {
    form_set_error('info', t('Can not delete a list which is not empty.'));
  }
  
}

function ccpuriri_list_delete_confirm_submit($form, &$form_state) {
 // to delete the list
  $list= $form_state['#list'] ;
  
  ccpuriri_list_delete($list);
  
  $form_state['redirect'] = 'list';
  
  drupal_set_message( t('List %title has been deleted', array('%title' => $list->title)));
    
}


function _ccpuriri_list_title_noduplicate($title,$uid, $lid)
{
  $query = db_select('ccpuriri_list','l');
   
  $query->condition('l.title', $title);
  
      
  if($lid!=0)
  {
    // existing list
   $query->condition(db_and()->condition('l.lid',$lid,'!='));
       
  }
  
  
  $query->condition(db_or()->condition('l.uid', 0)->condition('l.uid',$uid));
  
  $query->addExpression('COUNT(l.lid)', 'lcount');
  $lcount =$query->execute()->fetchField();
     
  return !($lcount>=1) ;
  
}




function _ccpuriri_list_add_list($title,$uid){
 
    // add list
    $newlist = new stdClass();
    $newlist->title = $title;
    $newlist->uid = $uid;
    ccpuriri_list_save($newlist);
      

    /*
    // create menu item as well
    $menuname = 'ccpuririlistnavigation';
  
    $plid = ccpuriri_list_root_menu_link_id();
    
    $listitem = array(
        'menu_name' => $menuname,
        'weight' => 1000,
        'link_title' => 'My listsss', // use router title to activate call back, can not be empty as well 
        'link_path' => 'list/'.$newlist->lid,
        'description' => 'User customized list',
        'module' => 'ccpuriri_list',
        'options'=>array(
            'alter'=> true, // to use link list/%
     //       'icon'=>'icon-reorder',
     //       'html'=>true,
        ),
        'plid'=>$plid, 
    );
  
    menu_link_save($listitem);
  
    // to get the weight of the list
    
    $userlists[$newlist->lid]= $newlist;
    
    
    // uasort
    uasort($userlists,'_ccpuriri_list_sort_by_title');
    */
    // update the weight of all items of this user
    
 
    
   
 
  
}