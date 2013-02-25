<?php

function bootstrapcc_js_alter(&$javascript) {
  
  $javascript['misc/jquery.js']['data'] = drupal_get_path('theme', 'bootstrapcc').'/jquery/jquery-1.9.1.js';
}