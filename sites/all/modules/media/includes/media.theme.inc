<?php

/**
 * @file
 * Media Theming
 *
 * Theming functions for the Media module.
 */


/**
 * Display a media file list.
 *
 * @param array $element
 *   The form element.
 * @return string
 */
function theme_media_file_list($element) {
  // Add the CSS for our display.
  return '<div class="media-file-list">' . theme('form_element', $element, $element['#children']) . '</div>';
}



/**
 * Theme a thumbnail.
 * @param $variables
 *   array items being passed in
 */
function theme_media_admin_thumbnail($variables) {
  $path = drupal_get_path('module', 'media');
  $file = $variables['file'];
  $style_name = $variables['style_name'];
  if (isset($file)) {
    $file_url = file_create_url($file->uri);
  }
  else {
    return '';
  }
  $output = '';
  // Display a thumbnail for images.
  if (strstr($file->filemime, 'image')) {
    $thumbnail = theme('image_style',
      array(
        'style_name' => 'thumbnail',
        'path' => $file->uri,
        'alt' => t('Thumbnail for !filename.', array('!filename' => $file->filename)),
      )
    );
  }
  // Display the 'unknown' icon for other file types.
  else {
    $thumbnail = theme('image',
      array(
        'path' => $path . '/images/file-unknown.png',
        'alt' => t('Thumbnail for !filename.', array('!filename' => $file->filename)),
        'attributes' => array('class' => 'file-unknown'),
      ));
  }
  $output .= l($thumbnail,
    $file_url,
    array(
      'html' => TRUE,
      'attributes' => array('class' => 'media-thumbnail'),
    ));
  return $output;
}

/**
 * Add messages to the page.
 */
function template_preprocess_media_dialog_page(&$variables) {
  $variables['messages'] = theme('status_messages');
}

/**
 * Adds a wrapper around a preview of a media file.
 * @param unknown_type $element
 * @return unknown_type
 */
function theme_media_thumbnail($variables) {
  $label = '';
  $element = $variables['element'];
  $destination = drupal_get_destination();

  // Wrappers to go around the thumbnail
  $prefix = '<div class="media-item" title="' . $element['#name'] . '"><div class="media-thumbnail">';
  $suffix = '</div></div>';

  // Arguments for the thumbnail link
  $thumb = $element['#children'];
  $target = 'file/' . $element['#file']->fid . '/edit';
  $options = array('query' => $destination, 'html' => TRUE, 'attributes' => array('title' => t('Click to edit details')));

  // Element should be a field renderable array... This is a little wonky - admitted.
  if (!empty($element['#show_names']) && $element['#name']) {
    $label = '<div class="label-wrapper"><label class="media-filename">' . $element['#name'] . '</label></div>';
  }

  // How can I attach CSS here?
  //$element['#attached']['css'][] = drupal_get_path('module', 'media') . '/css/media.css';
  drupal_add_css(drupal_get_path('module', 'media') . '/css/media.css');

  $output = $prefix;
  if (!empty($element['#add_link'])) {
    $output .= l($thumb, $target, $options);
  }
  else {
    $output .= $thumb;
  }
  $output .= $label . $suffix;
  return $output;
}

function template_preprocess_media_thumbnail(&$variables) {
  // Set the name for the thumbnail to be the filename.  This is done here so
  // that other modules can hijack the name displayed if it should not be the
  // filename.
  $variables['element']['#name'] = isset($variables['element']['#file']->filename) ? check_plain($variables['element']['#file']->filename) : NULL;
}

/**
 * Field formatter for displaying a file as a large icon.
 */
function theme_media_formatter_large_icon($variables) {
  $file = $variables['file'];
  $icon_dir = media_variable_get('icon_base_directory') . '/' . media_variable_get('icon_set');
  $icon = file_icon_path($file, $icon_dir);
  $variables['path'] = $icon;
  // theme_image() requires the 'alt' attribute passed as its own variable.
  // @see http://drupal.org/node/999338
  if (!isset($variables['alt']) && isset($variables['attributes']['alt'])) {
    $variables['alt'] = $variables['attributes']['alt'];
  }
  return theme('image', $variables);
}
