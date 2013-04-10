<?php

/**
 * @file
 * Geocoder autocomplete widget
 *
 * @author
 * Stefan Auditor <stefan.auditor@erdfisch.de>
 */

/**
 * Implements hook_menu().
 */
function geocoder_autocomplete_autocomplete($string = '') {
  global $language;

  $matches = array();
  $params = array(
    'address' => $string,
    'language' => $language->language,
    'sensor' => 'false',
  );

  if ($string) {
    $url = GEOCODER_AUTOCOMPLETE_URL . '/' . GEOCODER_AUTOCOMPLETE_FORMAT . '?' . drupal_http_build_query($params);
    $response = drupal_http_request($url);

    if ($response->code == 200) {
      $data = json_decode($response->data);
      if ($data->status == 'OK') {
        foreach ($data->results as $result) {
          $formatted_address = '';
          if (isset($result->formatted_address)) {
            $formatted_address = check_plain($result->formatted_address);
            $matches[$formatted_address] = $formatted_address;
          }
        }
      }
    }
  }

  drupal_json_output($matches);
}
