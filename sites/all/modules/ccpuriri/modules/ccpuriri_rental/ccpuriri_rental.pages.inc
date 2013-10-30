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
    $build = node_view_multiple($nodes);

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

