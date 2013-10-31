<?php 

/**
 * Generate a listing of rental nodes.
 */
function _ccpuriri_rental_list_page() {
  $select = db_select('node', 'n')
  ->fields('n', array('nid', 'sticky', 'created'))
  ->condition('type', 'ccpuriri_rental')
  ->condition('promote', 1)
  ->condition('status', 1)
  ->orderBy('sticky', 'DESC')
  ->orderBy('created', 'DESC')
  ->extend('PagerDefault')
  ->limit(variable_get('default_nodes_main', 10))
  ->addTag('node_access');

  $nids = $select->execute()->fetchCol();

  if (!empty($nids)) {
    $nodes = node_load_multiple($nids);
    $build =  _ccpuriri_rental_view_multiple($nodes);

    // 'rss.xml' is a path, not a file, registered in node_menu().
    drupal_add_feed('rss.xml', variable_get('site_name', 'Drupal') . ' ' . t('RSS'));
    $build['pager'] = array(
        '#theme' => 'pager',
        '#weight' => 5,
    );
    drupal_set_title('');
  }
  else {

    $default_message = '<p>' . t('No rental content has been created yet.') . '</p>';


    $build['default_message'] = array(
        '#markup' => $default_message,
        '#prefix' => '<div id="first-time">',
        '#suffix' => '</div>',
    );
  }
  return $build;
}

/**
 * Constructs a drupal_render() style array from an array of loaded rentals.
 *
 * @param $nodes
 *   An array of nodes as returned by node_load_multiple().
 *
 * @return
 *   An array in the format expected by drupal_render().
 */
function _ccpuriri_rental_view_multiple($nodes) {
  $view_mode = 'teaser';
  $weight = 0; // first node weight
  $langcode = NULL ;// default language
  
  /*in our render array we control the rendering field by field, 
    as some field we might not want to render here, but the process needs to be followded,
    except the list, we might want to insert search or sorting functionalities to the list
    
   field_attach_prepare_view('node', $nodes, $view_mode, $langcode);
  entity_prepare_view('node', $nodes, $langcode);
  $build = array();
  foreach ($nodes as $node) {
    $build['nodes'][$node->nid] = node_view($node, $view_mode, $langcode);
    $build['nodes'][$node->nid]['#weight'] = $weight;
    $weight++;
  }
  $build['nodes']['#sorted'] = TRUE;
  return $build;
  
  
  */
  
  // considering performance, run prepare view for all the fields
  // no single field version here 
  field_attach_prepare_view('node', $nodes, $view_mode, $langcode);
  
  entity_prepare_view('node', $nodes, $langcode);
    
  $build = array();
  foreach ($nodes as $node) {
    $build['nodes'][$node->nid] = _ccpuriri_rental_list_view($node, $langcode);
    $build['nodes'][$node->nid]['#weight'] = $weight;
    $weight++;
  }
  $build['nodes']['#sorted'] = TRUE;
  return $build;
}


/**
 * Generates an array for rendering the given node in ccpuriri_rental_list_view mode.
 *
 * @param $node
 *   A node object.
 * @param $langcode
 *   (optional) A language code to use for rendering. Defaults to the global
 *   content language of the current request.
 *
 * @return
 *   An array as expected by drupal_render().
 */
function  _ccpuriri_rental_list_view($node,  $langcode = NULL) {
  
  $view_mode = 'ccpuriri_rental_list_view';
  
  if (!isset($langcode)) {
    $langcode = $GLOBALS['language_content']->language;
  }

  // Populate $node->content with a render() array.
  _ccpuriri_rental_build_list_item_content($node, $langcode);

  $build = $node->content;
  // We don't need duplicate rendering info in node->content.
  unset($node->content);

  $build += array(
      '#theme' => 'node',
      '#node' => $node,
      '#view_mode' => $view_mode,
      '#language' => $langcode,
  );

  // list view no contextual links
  // Add contextual links for this node, except when the node is already being
  // displayed on its own page. Modules may alter this behavior (for example,
  // to restrict contextual links to certain view modes) by implementing
  // hook_node_view_alter().
  //if (!empty($node->nid) && !($view_mode == 'full' && node_is_page($node))) {
  //  $build['#contextual_links']['node'] = array('node', array($node->nid));
  // }

  // Allow modules to modify the structured node.
  $type = 'node';
  drupal_alter(array('node_view', 'entity_view'), $build, $type);

  return $build;
}


/**
 * Builds a structured array representing the rental's list item content.
 *
 * The content built for the node (field values, comments, file attachments or
 * other node components) will vary depending on the $view_mode parameter.
 *
 * the view mode for it is only 'ccpuriri_rental_list_view'
 * @param $node
 *   A node object.
 * @param $langcode
 *   (optional) A language code to use for rendering. Defaults to the global
 *   content language of the current request.
 */
function _ccpuriri_rental_build_list_item_content($node,  $langcode = NULL) {

  $view_mode = 'ccpuriri_rental_list_view';
  
 
  // Remove previously built content, if exists.
  $node->content = array();

  // Allow modules to change the view mode.
  $context = array(
      'entity_type' => 'node',
      'entity' => $node,
      'langcode' => $langcode,
  );
  drupal_alter('entity_view_mode', $view_mode, $context);

  // The 'view' hook can be implemented to overwrite the default function
  // to display nodes.
  if (node_hook($node, 'view')) {
    $node = node_invoke($node, 'view', $view_mode, $langcode);
  }

  // Build fields content.
  // In case of a multiple view, node_view_multiple() already ran the
  // 'prepare_view' step. An internal flag prevents the operation from running
  // twice.
 // field_attach_prepare_view('node', array($node->nid => $node), $view_mode, $langcode);
 // entity_prepare_view('node', array($node->nid => $node), $langcode);

  $node->content += field_attach_view('node', $node, $view_mode, $langcode);

  // takes out all original links
  /*
  // Always display a read more link on teasers because we have no way to know
  // when a teaser view is different than a full view.
  $links = array();
  $node->content['links'] = array(
      '#theme' => 'links__node',
      '#pre_render' => array('drupal_pre_render_links'),
      '#attributes' => array('class' => array('links', 'inline')),
  );
  
  if ($view_mode == 'teaser') {
    $node_title_stripped = strip_tags($node->title);
    $links['node-readmore'] = array(
        'title' => t('Read more<span class="element-invisible"> about @title</span>', array('@title' => $node_title_stripped)),
        'href' => 'node/' . $node->nid,
        'html' => TRUE,
        'attributes' => array('rel' => 'tag', 'title' => $node_title_stripped),
    );
  }
  $node->content['links']['node'] = array(
      '#theme' => 'links__node__node',
      '#links' => $links,
      '#attributes' => array('class' => array('links', 'inline')),
  );
 */
  
  // Allow modules to make their own additions to the node.
  module_invoke_all('node_view', $node, $view_mode, $langcode);
  module_invoke_all('entity_view', $node, 'node', $view_mode, $langcode);

  // Make sure the current view mode is stored if no module has already
  // populated the related key.
  $node->content += array('#view_mode' => $view_mode);
}


