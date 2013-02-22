<?php

function bootstrapcc_js_alter(&$javascript) {
  $javascript['misc/jquery.js']['data'] = drupal_get_path('theme', 'bootstrapcc').'/js/jquery.js';
}