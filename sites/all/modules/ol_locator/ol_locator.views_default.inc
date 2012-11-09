<?php
/**
 * @file
 * ol_locator.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ol_locator_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'ol_locator_proximity_search';
  $view->description = 'Displays geocoded locations on a dynamic map for users to do proximity searches.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'OpenLayers Locator proximity search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Locations';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = 'Find a location near you. You can search using your <strong>City, Province/State</strong> or your <strong>Postal/Zip code.</strong>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = '<strong>Sorry, no results found:</strong>

1. Verify the accuracy of your postal/zip code;
2. Check the spelling of your city, province or state; or 
3. Increase the proximity distance.
';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_ol_locator_address']['id'] = 'field_ol_locator_address';
  $handler->display->display_options['fields']['field_ol_locator_address']['table'] = 'field_data_field_ol_locator_address';
  $handler->display->display_options['fields']['field_ol_locator_address']['field'] = 'field_ol_locator_address';
  $handler->display->display_options['fields']['field_ol_locator_address']['label'] = '';
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ol_locator_address']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_address']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_ol_locator_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  $handler->display->display_options['fields']['field_ol_locator_address']['field_api_classes'] = 0;
  /* Field: Content: Geofield */
  $handler->display->display_options['fields']['field_ol_locator_geofield']['id'] = 'field_ol_locator_geofield';
  $handler->display->display_options['fields']['field_ol_locator_geofield']['table'] = 'field_data_field_ol_locator_geofield';
  $handler->display->display_options['fields']['field_ol_locator_geofield']['field'] = 'field_ol_locator_geofield';
  $handler->display->display_options['fields']['field_ol_locator_geofield']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_ol_locator_geofield']['settings'] = array(
    'data' => 'full',
  );
  $handler->display->display_options['fields']['field_ol_locator_geofield']['field_api_classes'] = 0;
  /* Field: Proximity: Distance */
  $handler->display->display_options['fields']['distance']['id'] = 'distance';
  $handler->display->display_options['fields']['distance']['table'] = 'openlayers_proximity';
  $handler->display->display_options['fields']['distance']['field'] = 'distance';
  $handler->display->display_options['fields']['distance']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['external'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['distance']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['distance']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['html'] = 0;
  $handler->display->display_options['fields']['distance']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['distance']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['distance']['hide_empty'] = 1;
  $handler->display->display_options['fields']['distance']['empty_zero'] = 0;
  $handler->display->display_options['fields']['distance']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['distance']['set_precision'] = 1;
  $handler->display->display_options['fields']['distance']['precision'] = '2';
  $handler->display->display_options['fields']['distance']['format_plural'] = 0;
  $handler->display->display_options['fields']['distance']['location_provider'] = 'circle';
  /* Sort criterion: Proximity: Distance */
  $handler->display->display_options['sorts']['distance']['id'] = 'distance';
  $handler->display->display_options['sorts']['distance']['table'] = 'openlayers_proximity';
  $handler->display->display_options['sorts']['distance']['field'] = 'distance';
  $handler->display->display_options['sorts']['distance']['location_provider'] = 'circle';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ol_locator_location' => 'ol_locator_location',
  );
  /* Filter criterion: Proximity: Great-circle */
  $handler->display->display_options['filters']['circle']['id'] = 'circle';
  $handler->display->display_options['filters']['circle']['table'] = 'openlayers_proximity';
  $handler->display->display_options['filters']['circle']['field'] = 'circle';
  $handler->display->display_options['filters']['circle']['value']['value'] = '10';
  $handler->display->display_options['filters']['circle']['value']['node'] = '1';
  $handler->display->display_options['filters']['circle']['exposed'] = TRUE;
  $handler->display->display_options['filters']['circle']['expose']['operator_id'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['label'] = 'Proximity';
  $handler->display->display_options['filters']['circle']['expose']['operator'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['identifier'] = 'circle';
  $handler->display->display_options['filters']['circle']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['circle']['expose']['use_unit'] = 1;
  $handler->display->display_options['filters']['circle']['expose']['use_location'] = 1;
  $handler->display->display_options['filters']['circle']['expose']['use_node'] = 0;

  /* Display: OpenLayers Data Overlay */
  $handler = $view->new_display('openlayers', 'OpenLayers Data Overlay', 'openlayers_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_data';
  $handler->display->display_options['style_options']['data_source'] = array(
    'value' => 'wkt',
    'other_lat' => 'title',
    'other_lon' => 'title',
    'wkt' => 'field_ol_locator_geofield',
    'other_top' => 'title',
    'other_right' => 'title',
    'other_bottom' => 'title',
    'other_left' => 'title',
    'name_field' => '',
    'description_field' => '#row',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'ol_locator_proximity_search_map';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'locator';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Locator';
  $handler->display->display_options['menu']['description'] = 'Find a location near you.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_ol_locator_address' => 'field_ol_locator_address',
    'field_ol_locator_geofield' => 'field_ol_locator_geofield',
    'distance' => 'distance',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_ol_locator_address' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_ol_locator_geofield' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'distance' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Result summary */
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_ol_locator_address']['id'] = 'field_ol_locator_address';
  $handler->display->display_options['fields']['field_ol_locator_address']['table'] = 'field_data_field_ol_locator_address';
  $handler->display->display_options['fields']['field_ol_locator_address']['field'] = 'field_ol_locator_address';
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_address']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_address']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_ol_locator_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  $handler->display->display_options['fields']['field_ol_locator_address']['field_api_classes'] = 0;
  /* Field: Content: Geofield */
  $handler->display->display_options['fields']['field_ol_locator_geofield']['id'] = 'field_ol_locator_geofield';
  $handler->display->display_options['fields']['field_ol_locator_geofield']['table'] = 'field_data_field_ol_locator_geofield';
  $handler->display->display_options['fields']['field_ol_locator_geofield']['field'] = 'field_ol_locator_geofield';
  $handler->display->display_options['fields']['field_ol_locator_geofield']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_ol_locator_geofield']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_ol_locator_geofield']['settings'] = array(
    'data' => 'full',
  );
  $handler->display->display_options['fields']['field_ol_locator_geofield']['field_api_classes'] = 0;
  /* Field: Proximity: Distance */
  $handler->display->display_options['fields']['distance']['id'] = 'distance';
  $handler->display->display_options['fields']['distance']['table'] = 'openlayers_proximity';
  $handler->display->display_options['fields']['distance']['field'] = 'distance';
  $handler->display->display_options['fields']['distance']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['external'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['distance']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['distance']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['distance']['alter']['html'] = 0;
  $handler->display->display_options['fields']['distance']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['distance']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['distance']['hide_empty'] = 1;
  $handler->display->display_options['fields']['distance']['empty_zero'] = 0;
  $handler->display->display_options['fields']['distance']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['distance']['set_precision'] = 1;
  $handler->display->display_options['fields']['distance']['precision'] = '2';
  $handler->display->display_options['fields']['distance']['format_plural'] = 0;
  $handler->display->display_options['fields']['distance']['location_provider'] = 'circle';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'block_1' => 'block_1',
    'default' => 0,
  );
  $handler->display->display_options['inherit_exposed_filters'] = 1;
  $handler->display->display_options['inherit_pager'] = 1;
  $handler->display->display_options['render_pager'] = 1;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'ol_locator_proximity_search_map';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['ol_locator_proximity_search'] = $view;

  return $export;
}
