<?php 

define('CCPURIRI_ADDRESSFIELD_AUTOCOMPLETE_URL', 'http://maps.google.com/maps/api/geocode');
define('CCPURIRI_ADDRESSFIELD_AUTOCOMPLETE_FORMAT', 'json');

function ccpuriri_addressfield_generate($address, $context)
{

  $settings =$context['instance']['widget']['settings'];

  $country = variable_get('ccpuriri_country', "NZ");
   
  $elements = array();

  // always having a tree structure for UI
  $elements['#tree'] = true;

  // name
  if ($settings['showname'])
  {
    ccpuriri_addressfield_name_full($elements, $address, $context);
  }
  // organizartion
  if ($settings['showorganization'])
  {
    ccpuriri_addressfield_organisation($elements, $address, $context);
  }
  $streetfunction = 'ccpuriri_addressfield_street_'.$country;

  if (function_exists($streetfunction)) {
    $streetfunction($elements, $address, $context);

  }

  return $elements;
}

/*
 * Street block, locality block, NZ
* */
function ccpuriri_addressfield_street_NZ(&$elements, $address, $context)
{

  $elements['extrernal_autocomplete'] = array(
      '#type' => 'textfield',
      '#title' => t('Auto complete'),
      '#attributes' => array('class' => array('extrernal_autocomplete')),
      '#size' => 60,
      '#weight' => 5,
      '#description' =>'If autocomplete does not work, use fields below',
      '#autocomplete_path' => 'ccpuriri_addressfield/autocomplete',
      // to not include this as a field column
      '#parents' => array(),
      // give it #id and #name as it does not have #parents
      '#id' => 'extrernal_autocomplete',
      '#name' => 'extrernal_autocomplete',
      // add js, to make sure it is added after autocomplete
      '#attached' => array(
          'js' => array(drupal_get_path('module', 'ccpuriri_addressfield') . '/ccpuriri_addressfield.js'=>
              array('group' => JS_DEFAULT, 'weight'=>100)),
      ),
  );



  // The street block.
  $elements['street_block'] = array(
      '#type' => 'ccpuriri_addressfield_container',
      '#attributes' => array('class' => array('street-block')),
      '#weight' => 10,
  );

  // first column

  $elements['street_block']['sub_premise'] = array(
      '#type' => 'textfield',
      '#title' => t('Unit'),
      '#tag' => 'div',
      '#attributes' => array('class' => array('sub_premise')),
      '#default_value' =>$address['sub_premise'],
      '#size' => 30,
      '#weight' => 10,
      '#description' =>'A unit(flat, suite etc) and/or floor. It can also include a building name',
  );


  $elements['street_block']['premise'] = array(
      '#type' => 'textfield',
      '#title' => t('Street Number'),
      '#tag' => 'div',
      '#attributes' => array('class' => array('premise')),
      '#default_value' =>$address['premise'],
      '#size' => 30,
      '#weight' => 20,
  );

  $elements['street_block']['thoroughfare'] = array(
      '#type' => 'textfield',
      '#title' => t('Street'),
      '#tag' => 'div',
      '#attributes' => array('class' => array('thoroughfare')),
      '#default_value' =>$address['thoroughfare'],
      '#size' => 50,
      '#weight' => 30,
      // The #required will be automatically set to FALSE when processing.
      '#required' => TRUE,
  );

  $elements['locality_block'] = array(
      '#type' => 'ccpuriri_addressfield_container',
      '#attributes' => array('class' => array('addressfield-container-inline', 'locality-block')),
      '#weight' => 20,
  );
  // $format['locality_block']['#attached']['css'][] = drupal_get_path('module', 'addressfield') . '/addressfield.css';
  $elements['locality_block']['dependent_locality'] = array(
      '#type' => 'textfield',
      '#title' => t('Suburb'),
      '#size' => 30,
      '#weight' => 10,
      '#prefix' => ' ',
      '#default_value' =>$address['dependent_locality'],
      '#attributes' => array('class' => array('dependent_locality')),
  );


  $elements['locality_block']['locality'] = array(
      '#type' => 'textfield',
      '#title' => t('Town or City'),
      '#size' => 30,
      '#weight' => 20,
      '#required' => TRUE,
      '#prefix' => ' ',
      '#default_value' =>$address['locality'],
      '#attributes' => array('class' => array('locality')),
  );

  $elements['locality_block']['postal_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Postal Code'),
      '#size' => 30,
      '#weight' => 30,
      // '#required' => TRUE,
      '#default_value' =>$address['postal_code'],
      '#attributes' => array('class' => array('postal-code')),
  );

  module_load_include('inc', 'ccpuriri', 'ccpuriri.utility');

  $elements['country'] = array(
      '#type' => 'select',
      '#title' => t('Country'),
      '#weight' => 30,
      '#options' => ccpuriri_country_list(),
      '#default_value' =>$address['country'],
      '#disabled'=> true,
  );

}

/*
 * name_block
* */
function ccpuriri_addressfield_name_full(&$elements, $address, $context) {
  $elements['name_block'] = array(
      '#type' => 'ccpuriri_addressfield_container',
      '#attributes' => array('class' => array('addressfield-container-inline', 'name-block')),
      '#weight' => -100,
  );
  $elements['name_block']['first_name'] = array(
      '#type' => 'textfield',
      '#title' => t('First name'),
      '#size' => 30,
      '#default_value' =>$address['first_name'],
      '#required' => TRUE,
      '#attributes' => array('class' => array('first-name')),
  );
  $elements['name_block']['last_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Last name'),
      '#size' => 30,
      '#default_value' =>$address['last_name'],
      '#required' => TRUE,
      '#prefix' => ' ',
      '#attributes' => array('class' => array('last-name')),
  );
}

/**
 *
 * Organization_block
 */
function ccpuriri_addressfield_organisation(&$elements, $address, $context) {
  $elements['organisation_block'] = array(
      '#type' => 'ccpuriri_addressfield_container',
      '#attributes' => array('class' => array('addressfield-container-inline', 'name-block')),
      '#weight' => -50,
  );
  $elements['organisation_block']['organisation_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Company'),
      '#size' => 30,
      '#default_value' =>$address['organisation_name'],
      '#attributes' => array('class' => array('organisation-name')),
  );
}

/*
 * external autocomplete
* the result of google geocoder is per result
* $result	stdClass for nz search
$result	stdClass
address_components	Array [8]
0	stdClass
long_name	1
short_name	1
types	Array [1]
0	subpremise
1	stdClass
long_name	125
short_name	125
types	Array [1]
0	street_number
2	stdClass
long_name	Maich Road
short_name	Maich Rd
types	Array [1]
0	route
3	stdClass
long_name	Manurewa
short_name	Manurewa
types	Array [2]
0	sublocality
1	political
4	stdClass
long_name	Auckland
short_name	Auckland
types	Array [2]
0	locality
1	political
5	stdClass
long_name	Auckland
short_name	Auckland
types	Array [2]
0	administrative_area_level_1
1	political
6	stdClass
long_name	New Zealand
short_name	NZ
types	Array [2]
0	country
1	political
7	stdClass
long_name	2102
short_name	2102
types	Array [1]
0	postal_code
formatted_address	1/125 Maich Road, Manurewa, Auckland 2102, New Zealand
geometry	stdClass
location	stdClass
lat	-37.0114676
lng	174.8898388
location_type	APPROXIMATE
viewport	stdClass
northeast	stdClass
lat	-37.010118619709
lng	174.89118778029
southwest	stdClass
lat	-37.012816580292
lng	174.88848981971
partial_match	true
postcode_localities	Array [0]
types	Array [1]
0	subpremise
http://maps.google.com/maps/api/geocode
*
* */
function ccpuriri_addressfield_external_autocomplete($string = '')
{
  $matches = array();
  $params = array(
      'address' => $string,
      'components' =>'country:'.variable_get('ccpuriri_country', "NZ"),
      'sensor' => 'false',
  );

  if ($string) {
    $url = CCPURIRI_ADDRESSFIELD_AUTOCOMPLETE_URL . '/' . CCPURIRI_ADDRESSFIELD_AUTOCOMPLETE_FORMAT . '?' . drupal_http_build_query($params);
    $response = drupal_http_request($url);

    if ($response->code == 200) {
      $data = json_decode($response->data);
      switch ($data->status)
      {
        // "OK" indicates that no errors occurred; the address was successfully parsed and at least one geocode was returned.
        case 'OK':
          foreach ($data->results as $result) {
            $matches+= _ccpuriri_addressfield_read_geocode($result) ;
          }
          break;
          // "ZERO_RESULTS" indicates that the geocode was successful but returned no results. This may occur if the geocode was passed a non-existent address or a latlng in a remote location.
        case 'ZERO_RESULTS'  :
          break;

          //"OVER_QUERY_LIMIT" indicates that you are over your quota.
        case 'OVER_QUERY_LIMIT'  :
          // "REQUEST_DENIED" indicates that your request was denied, generally because of lack of a sensor parameter.
        case 'REQUEST_DENIED'  :
          // "INVALID_REQUEST" generally indicates that the query (address or latlng) is missing.
        case 'INVALID_REQUEST'  :
          // UNKNOWN_ERROR indicates that the request could not be processed due to a server error. The request may succeed if you try again.
        default:
          // log the status
          watchdog('geocoder error', 'status code is '.$data->status);

          break;
      }
    }
  }

  drupal_json_output($matches);

}

function _ccpuriri_addressfield_read_geocode($result)
{
  $matches =array();

  if (isset($result->formatted_address)) {
    $formatted_address = check_plain($result->formatted_address);


    $macth =array();

    if (isset($result->address_components))
    {
      foreach ($result->address_components as $component)
      {
        if (isset($component->types) && count($component->types))
        {
          switch ($component->types[0])
          {
            case 'subpremise':
            case 'premise':
              $match['unit'] += check_plain($component->long_name) ;
              break;

            case 'street_number':
              $match['streetnumber'] =check_plain($component->long_name) ;
              break;

            case 'route':
              $match['street'] = check_plain($component->long_name);
              break;

            case 'sublocality':
              $match['suburb'] = check_plain($component->long_name);
              break;

            case 'locality':
              $match['city'] =check_plain($component->long_name);
              break;
            case 'country':
              $match['country'] =check_plain($component->short_name);

            case 'postal_code':
              $match['postalcode'] = check_plain($component->short_name);

            default:
              break;
          }

        }

      }
    }
    if ($match && isset($result->geometry) && isset($result->geometry->location))
    {
      $match['lat'] = check_plain($result->geometry->location->lat);
      $match['lng'] = check_plain($result->geometry->location->lng);
    }

    if ($match)
    {
      $matches[$formatted_address]= $match ;
    }

  }

  return $matches;
}