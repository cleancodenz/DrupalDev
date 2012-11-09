<?php
/**
 * @file
 * ol_locator.openlayers_maps.inc
 */

/**
 * Implements hook_openlayers_maps().
 */
function ol_locator_openlayers_maps() {
  $export = array();

  $openlayers_maps = new stdClass;
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'ol_locator_node_map';
  $openlayers_maps->title = 'OpenLayers Locator Node Map';
  $openlayers_maps->description = 'This is the default map that is displayed on the \'Location\' node that comes with the OpenLayers Locator module.';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '400px',
    'image_path' => '',
    'css_path' => '',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '0,0',
        'zoom' => '2',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_fullscreen' => array(
        'activated' => 0,
      ),
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_panzoombar' => array(
        'zoomWorldIcon' => 0,
        'panIcons' => 1,
      ),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => 'geofield_formatter',
        'point_zoom_level' => '15',
      ),
    ),
    'default_layer' => 'osm_mapnik',
    'layers' => array(
      'osm_mapnik' => 'osm_mapnik',
      'geofield_formatter' => 'geofield_formatter',
    ),
    'layer_weight' => array(
      'geofield_formatter' => '0',
      'ol_locator_proximity_search_openlayers_1' => '0',
      'openlayers_geojson_picture_this' => '0',
    ),
    'layer_styles' => array(
      'openlayers_geojson_picture_this' => '0',
      'ol_locator_proximity_search_openlayers_1' => 'default_marker_red',
      'geofield_formatter' => 'default_marker_red',
    ),
    'layer_styles_select' => array(
      'openlayers_geojson_picture_this' => '0',
      'ol_locator_proximity_search_openlayers_1' => '0',
      'geofield_formatter' => '0',
    ),
    'layer_activated' => array(
      'geofield_formatter' => 'geofield_formatter',
      'openlayers_geojson_picture_this' => 0,
      'ol_locator_proximity_search_openlayers_1' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'ol_locator_proximity_search_openlayers_1' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default',
      'temporary' => 'default',
    ),
  );
  $export['ol_locator_node_map'] = $openlayers_maps;

  $openlayers_maps = new stdClass;
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'ol_locator_proximity_search_map';
  $openlayers_maps->title = 'OpenLayers Locator Proximity Search Map';
  $openlayers_maps->description = 'This is the default proxmity search map that comes with the OpenLayers Locator module.';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '400px',
    'image_path' => '',
    'css_path' => '',
    'proxy_host' => '',
    'hide_empty_map' => 1,
    'center' => array(
      'initial' => array(
        'centerpoint' => '0,0',
        'zoom' => '2',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_fullscreen' => array(
        'activated' => 0,
      ),
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_panzoombar' => array(
        'zoomWorldIcon' => 0,
        'panIcons' => 1,
      ),
      'openlayers_behavior_popup' => array(
        'layers' => array(
          'ol_locator_proximity_search_openlayers_1' => 'ol_locator_proximity_search_openlayers_1',
          'geofield_formatter' => 0,
        ),
      ),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => 'ol_locator_proximity_search_openlayers_1',
        'point_zoom_level' => '15',
      ),
    ),
    'default_layer' => 'osm_mapnik',
    'layers' => array(
      'osm_mapnik' => 'osm_mapnik',
      'geofield_formatter' => 'geofield_formatter',
      'ol_locator_proximity_search_openlayers_1' => 'ol_locator_proximity_search_openlayers_1',
    ),
    'layer_weight' => array(
      'geofield_formatter' => '0',
      'ol_locator_proximity_search_openlayers_1' => '0',
      'openlayers_geojson_picture_this' => '0',
    ),
    'layer_styles' => array(
      'openlayers_geojson_picture_this' => '0',
      'ol_locator_proximity_search_openlayers_1' => 'default_marker_red',
      'geofield_formatter' => 'default_marker_red',
    ),
    'layer_styles_select' => array(
      'openlayers_geojson_picture_this' => '0',
      'ol_locator_proximity_search_openlayers_1' => '0',
      'geofield_formatter' => '0',
    ),
    'layer_activated' => array(
      'ol_locator_proximity_search_openlayers_1' => 'ol_locator_proximity_search_openlayers_1',
      'geofield_formatter' => 'geofield_formatter',
      'openlayers_geojson_picture_this' => 0,
    ),
    'layer_switcher' => array(
      'ol_locator_proximity_search_openlayers_1' => 0,
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default',
      'temporary' => 'default',
    ),
  );
  $export['ol_locator_proximity_search_map'] = $openlayers_maps;

  return $export;
}
