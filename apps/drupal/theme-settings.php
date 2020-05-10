<?php

/**
 * @file
 * Advanced theme settings.
 */

use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function particle_form_system_theme_settings_alter(&$form, FormStateInterface &$form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes. See issue #943212.
  if (isset($form_id)) {
    return;
  }
  // ------------------------
  // Social Media Pages
  // ------------------------
  $form['social']['social_media_pages'] = array(
    '#type' => 'details',
    '#title' => t('Social Media Pages'),
    '#open' => TRUE,
  );

  $social_media_pages = array (
    'facebook' => 'Facebook',
    'twitter' => 'Twitter',
    'google-plus' => 'Google+',
    'youtube' => 'YouTube',
    'instagram' => 'Instagram',
    'pinterest' => 'Pinterest',
    'tumblr' => 'Tumblr',
    'linked-in' => 'LinkedIn',
    'snapchat' => 'Snapchat',
  );

  foreach ($social_media_pages as $sm_page => $sm_name) {

    $form['social']['social_media_pages'][$sm_page] = array(
      '#type' => 'details',
      '#title' => t($sm_name),
      '#open' => FALSE,
    );

    $form['social']['social_media_pages'][$sm_page]['themag_' . $sm_page] = array (
      '#type' => 'url',
      '#title'  => t($sm_name),
      '#description' => t('Enter the URL of your ' . $sm_name . ' profile.'),
      '#attributes' => array('placeholder' => 'http://'),
      '#default_value' => theme_get_setting('themag_' . $sm_page),
    );

    $form['social']['social_media_pages'][$sm_page]['themag_' . $sm_page . '_link_title'] = array(
      '#type' => 'textfield',
      '#title'  => t('Link title'),
      '#description' => t('Enter the link title eg. Follow us on ... You can leave this field blank if you don\'t want use link title.'),
      '#default_value' => theme_get_setting('themag_' . $sm_page . '_link_title'),
    );
  }
 
}


