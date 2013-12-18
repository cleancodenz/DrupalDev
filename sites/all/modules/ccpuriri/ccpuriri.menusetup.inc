<?php 

/*
 * Add home item to ccpuriri main menu
*
* */
function _ccpuriri_menu_home_add(){

  $startTime=  microtime(TRUE);

  // first add home to it
  $home_item = array(
      'menu_name' => 'ccpuririmainnavigation',
      'weight' => 10,
      'link_title' => t('Home'),
      'link_path' => '<front>',
      'router_path' => '',
      'module' => 'ccpuriri',
      'description' => 'Home on main menu',
      'options'=>array(
          'icon'=>'home',
          'html'=>true,
      ),
      'external' => 1,
      'expanded' => 0,

  );

  menu_link_save($home_item);


  watchdog('ccpuriri',
      'Home menu item is added to main navigation, time elapsed is %timeElpased ms',
      array('%timeElpased' =>
          round((microtime(TRUE) - $startTime) * 1000,2)

      ),
      WATCHDOG_DEBUG);
}

/*
 * Add rental item to ccpuriri main menu
*
* */
function _ccpuriri_menu_rental_add(){

  $startTime=  microtime(TRUE);

  //Add rental

  $rental_item = array(
      'menu_name' => 'ccpuririmainnavigation',
      'weight' => 30,
      'link_title' => t('Rentals'),
      'link_path' => 'rental',
      'router_path' => 'rental',
      'description' => 'Rental menu item on main menu',
      'options'=>array(
          'icon'=>'th',
          'html'=>true,
      ),

  );

  menu_link_save($rental_item);

  //Add rental add

  $rental_add = array(
      'menu_name' => 'ccpuririmainnavigation',
      'link_title' => t('Add'),
      'link_path' => 'rental/add',
      'router_path' => 'rental/add',
      'plid' => $rental_item['mlid'],
  );

  menu_link_save($rental_add);

  //Add rental view
  $rental_view = array(
      'menu_name' => 'ccpuririmainnavigation',
      'link_title' => 'My rental', // conform with router to trigger callback
      'link_path' => 'rental/%',
      'router_path' => 'rental/%',
      'plid' => $rental_item['mlid'],

  );

  menu_link_save($rental_view);

  //Add rental edit
  $rental_edit = array(
      'menu_name' => 'ccpuririmainnavigation',
      'link_title' =>  t('Edit'),
      'link_path' => 'rental/%/edit',
      'router_path' => 'rental/%/edit',
      'plid' => $rental_view['mlid'],
  );


  menu_link_save($rental_edit);

 
  
   // named tag #address 
 
  $rental_address = array(
        'menu_name' => 'ccpuririmainnavigation',
        'weight' => 10,
        'link_title' => 'Address',
        'link_path' => '#address',
        'customized'=>true,
        'description' => 'Address of Rental',
        'access' =>true,
        'plid' => $rental_view['mlid'],
        'options'=>array(
            'alter'=>true,
        ),

    );
  
    menu_link_save($rental_address);
  
    // named tag #contacts
    $rental_contact = array(
        'menu_name' => 'ccpuririmainnavigation',
        'weight' => 20,
        'link_title' => 'Contacts',
        'link_path' => '#contacts',
        'customized'=>true,
        'description' => 'Contacts of Rental',
        'plid' => $rental_view['mlid'],
        'options'=>array(
            'alter'=>true,
        ),
 
    );
  
  menu_link_save($rental_contact);
  
  watchdog('ccpuriri',
      'Rental menu items are added to main navigation, time elapsed is %timeElpased ms',
      array('%timeElpased' =>
          round((microtime(TRUE) - $startTime) * 1000,2)

      ),
      WATCHDOG_DEBUG);
}

/*
 * Add list item to ccpuriri main menu
*
* */
function _ccpuriri_menu_list_add(){

  $startTime=  microtime(TRUE);

  $menuname = 'ccpuririmainnavigation';

  //Add list

  $list_item = array(
      'menu_name' => $menuname,
      'weight' => 20,
      'link_title' => t('My Lists'),
      'link_path' => 'list',
      'router_path' => 'list',
      'description' => 'My lists menu item on main menu',
      'options'=>array(
          'icon'=>'indent-left',
          'html'=>true,
      ),
  );

  menu_link_save($list_item);

  //Add list add

  $list_add = array(
      'menu_name' => $menuname,
      'link_title' => t('Add'),
      'link_path' => 'list/add',
      'router_path' => 'list/add',
      'plid' => $list_item['mlid'],
       
  );

  menu_link_save($list_add);

  //Add list view
  $list_view = array(
      'menu_name' => $menuname,
      'link_title' => 'My listsss',
      'link_path' => 'list/%',
      'router_path' => 'list/%',
      'options'=>array(
          'html'=>true, // turn on html title
      ),
      'plid' => $list_item['mlid'],

  );


  menu_link_save($list_view);


  //Add list edit
  $list_edit = array(
      'menu_name' => $menuname,
      'link_title' => t('Edit'),
      'link_path' => 'list/%/edit',
      'router_path' => 'list/%/edit',
      'plid' => $list_view['mlid'],
  );


  menu_link_save($list_edit);

  //Add list delete
  $list_delete = array(
      'menu_name' => $menuname,
      'link_title' => t('Delete'),
      'link_path' => 'list/%/delete',
      'router_path' => 'list/%/delete',
      'plid' => $list_view['mlid'],
  );


  menu_link_save($list_delete);


  // add the shared list to ccpuririlistnavigation
  $lists = ccpuriri_list_load_shared();



  $i=-100;

  foreach($lists as $key=>$list)
  {

    $sharedlistitem = array(
        'menu_name' => $menuname,
        'weight' => $i +10,
        'link_title' => 'My listsss', // use router title to activate call back
        'link_path' => 'list/'.$list->lid,
        'description' => 'Shared list '.$list->title.' menu item on navigation menu',
        'options'=>array(
            'icon'=>'tag',
            'html'=>true,
        ),
        'plid' => $list_item['mlid'],
    );

    menu_link_save($sharedlistitem);
    $i =$i+10;
  }



  watchdog('ccpuriri',
      'List menu items are added to main navigation, time elapsed is %timeElpased ms',
      array('%timeElpased' =>
          round((microtime(TRUE) - $startTime) * 1000,2)

      ),
      WATCHDOG_DEBUG);
}





