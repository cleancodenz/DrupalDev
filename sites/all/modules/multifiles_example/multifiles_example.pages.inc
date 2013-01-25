<?php

/**
 * @file
 * Page/form showing image styles in use.
 */

/**
 * Form for uploading and displaying an image using selected style.
 *
 * This page provides a form that allows the user to upload an image and choose
 * a style from the list of defined image styles to use when displaying the
 * the image. This serves as an example of integrating image styles with your
 * module and as a way to demonstrate that the styles and effects defined by
 * this module are available via Drupal's image handling system.
 *
 * @see theme_image_style()
 *
 * @ingroup image_example
 */
function multifiles_example_form($form, &$form_state) {

  // in case of ajax, form_state is already populated, as drupal_process_form already run before this.

  $form['allfiles'] = array(
      '#type' => 'container',
      '#tree' => true,
  );

 

  $filecount =0;
  
  // first loading
  if (!$fileslist = variable_get('multifiles_example_files', FALSE))
  {
    $fileslist =array('files'=>array(),'count'=>0);
  }
      
  // load existing list
  foreach($fileslist['files'] as $key=>$value)
  {
    // Use the #managed_file FAPI element to upload an image file.
    $form['allfiles']['file_'.$filecount] = array(
        '#title' => t('Image '.$filecount),
        '#type' => 'managed_file',
        '#upload_location' => 'public://multifiles_example_images/',
        '#default_value' =>$value,
        '#upload_validators' => array(
            'file_validate_extensions' => array('gif png jpg jpeg'),
            // Pass the maximum file size in bytes
            'file_validate_size' => array(1000000),
        ),
    );
  
    $filecount++;
  
  }
  
  
 // always attach a new upload control
  
    // Use the #managed_file FAPI element to upload an image file.
    $form['allfiles']['file_'.$filecount] = array(
        '#title' => t('Image '.$filecount),
        '#type' => 'managed_file',
        '#upload_location' => 'public://multifiles_example_images/',
        '#upload_validators' => array(
            'file_validate_extensions' => array('gif png jpg jpeg'),
            // Pass the maximum file size in bytes
            'file_validate_size' => array(1000000),
        ),

    );

 

  // Submit Button.
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
  );

  return $form;
}

/**
 * Verifies that the user supplied an image with the form..
 *
 * @ingroup image_example
 */
function multifiles_example_form_validate($form, &$form_state) {
  if (!isset($form_state['values']))
  {
    $form_state['values']['dump']='';

  }
  // if (!isset($form_state['values']['image_example_image_fid']) || !is_numeric($form_state['values']['image_example_image_fid'])) {
  //  form_set_error('image_example_image_fid', t('Please select an image to upload.'));
  // }
}

/**
 * Form Builder; Display a form for uploading an image.
 *
 * @ingroup image_example
 */
function multifiles_example_form_submit($form, &$form_state) {

  // to get the current list

  if ($fileslist = variable_get('multifiles_example_files', FALSE))
  {

    //have to find out deleted ones
    $i=0;
    foreach($fileslist['files'] as $fileindex=>$fileidvalue)
    {
      if ($form_state['values']['allfiles']['file_'.$i] ==0)
      {
        // deleted
        $file =  file_load($fileidvalue) ;
        if ($file) {
          // When a module is managing a file, it must manage the usage count.
          // Here we decrement the usage count with file_usage_delete().
          file_usage_delete($file, 'multifiles_example', 'sample_image', 1);

          // The file_delete() function takes a file object and checks to see if
          // the file is being used by any other modules. If it is the delete
          // operation is cancelled, otherwise the file is deleted.
          file_delete($file);
        }
      }
      $i++;
    }

  }
  // now save files
   
  $newlist= array('files'=>array(),'count'=>0);
  foreach ($form_state['values']['allfiles'] as $key =>$value)
  {
    if ($value!=0)
    {
      // file exists
      $file = file_load($value);
      if ($file->status==0)
      {
        $file->status = FILE_STATUS_PERMANENT;
        file_save($file);

        // When a module is managing a file, it must manage the usage count.
        // Here we increment the usage count with file_usage_add().
        file_usage_add($file, 'multifiles_example', 'sample_image', 1);
      }

      $newlist['files'][$file->fid]= $file->fid;
      $newlist['count'] = $newlist['count']+1;

    }

  }

  if($newlist['count']>0)
  {
    variable_set('multifiles_example_files', $newlist);
  }
  else
  {
    variable_set('multifiles_example_files', false);
  }
  
  $form_state['redirect']='multifiles_example';
  
}





/**
 * Theme function displays an image rendered using the specified style.
 *
 * @ingroup image_example

 function theme_image_example_image($variables) {
 $image = $variables['image'];
 $style = $variables['style'];

 // theme_image_style() is the primary method for displaying images using
 // one of the defined styles. The $variables array passed to the theme
 // contains the following two important values:
 //   'style_name': the name of the image style to use when displaying the
 //   image.
 //   'path': the $file->uri of the image to display.
 // When given a style and an image path the function will first determine
 // if a derivative image already exists, in which case the existing image
 // will be displayed. If the derivative image does not already exist the
 // function returns an <img> tag with a specially crafted callback URL
 // as the src attribute for the tag. When accessed, the callback URL will
 // generate the derivative image and serve it to the browser.
 $output = theme('image_style', array('style_name' => $style, 'path' => $image->uri, 'getsize' => FALSE));
 $output .= '<p>' . t('This image is being displayed using the image style %style_name.', array('%style_name' => $style)) . '</p>';
 return $output;
 }
 */