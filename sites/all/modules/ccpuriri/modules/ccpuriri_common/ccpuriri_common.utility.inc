<?php 

function ccpuriri_country_list()
{
  return array(
      'NZ' => t('New Zealand'),
      'AU' => t('Australia'),
      'US' => t('United States'),
      'UK' => t('United Kingdom'),
  );
}


function ccpuriri_addressfield_country_config()
{

  return array(
      'NZ' => array(
          'sub_premise'=> array(
              'label'=> 'Unit',
              'enabled' => true),
          'premise'=> array(
              'label'=> 'Street Number',
              'enabled' => true),
          'thoroughfare'=> array(
              'label'=> 'Street',
              'enabled' => true),
          'postal_code'=> array(
              'label'=> 'Postal Code',
              'enabled' => true),
          'dependent_locality'=> array(
              'label'=> 'Suburb',
              'enabled' => true),
          'locality'=> array(
              'label'=> 'Town or City',
              'enabled' => true),
          'sub_administrative_area'=> array(
              'label'=> 'sub_administrative_area',
              'enabled' => false),
          'administrative_area'=> array(
              'label'=> 'administrative_area',
              'enabled' => false),
      ),

  );

}

