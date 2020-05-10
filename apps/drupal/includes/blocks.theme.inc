<?php

/**
 * @file
 * Functions to support theming blocks in the Particle theme.
 */

use Drupal\particle\Particle;
use Drupal\media\Entity\Media;
use Drupal\media_entity\MediaInterface;
use Drupal\file\Entity\File;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function particle_theme_suggestions_block_alter(array &$suggestions, array $variables) {
  // Provide suggestion for block templates by custom block type.
  if (!empty($variables['elements']['content']['#block_content'])) {
    $block = $variables['elements']['content']['#block_content'];
    // Add `block--BLOCK-TYPE.html.twig`.
    $suggestions[] = 'block__' . $block->bundle();
    $view_mode = $variables['elements']['#configuration']['view_mode'];
    if (!empty($view_mode)) {
      // Add `block--BLOCK-TYPE--VIEW-MODE.html.twig`.
      $suggestions[] = 'block__' . $block->bundle() . '__' . $view_mode;
    }
  }


  foreach ($suggestions as &$suggestion) {
    $suggestion = str_replace('themag_st_', 'themag_', $suggestion);
  }
  
  $node = \Drupal::routeMatch()->getParameter('node');
    if ($node) {
    $nid = $node->id();
    $nid2 = $node->toUrl()->toString();
    //$node->getTitle();
    } else {
    $nid = null;
    $nid2 = null;
    }
  $word= 'node';
  if(strpos($nid2, $word) !== false){
    $suggestions[] = ('block__' . "_id_" . $nid . "_label_" . preg_replace('/\s+/', '_', $variables['elements']['#configuration']['label']));
  } else{
    $suggestions[] = ('block__'. str_replace('-', '_', ltrim($nid2, '/')) . "_id_" . $nid . "_label_" . preg_replace('/\s+/', '_', $variables['elements']['#configuration']['label']));
  }




}

/**
 * Implements hook_preprocess_block().
 */
function particle_preprocess_block__system_branding_block(&$variables) {
  $logo_default = theme_get_setting('logo.use_default');
  $logo_url = theme_get_setting('logo.url');

  $logo_svg_theme = drupal_get_path('theme', Particle::THEME_NAME) . '/logo.svg';
  $logo_svg_assets = Particle::ASSETS_PATH . '/logo.svg';
  $logo_svg_inline = file_exists($logo_svg_assets) ? $logo_svg_assets : $logo_svg_theme;

  // Set the logo to PL if default.
  if ($logo_default) {
    $variables['logo_svg_inline'] = $logo_svg_inline;
    // Send to img if Logo is not an default.
  }
  else {
    $variables['logo_img_src'] = $logo_url;
  }
}


function particle_preprocess_block(&$variables) {
 
  if ($variables['plugin_id'] == 'entity_browser_block:employee_blocks') {
   
      $content = $variables['elements']['content'];
    
      $mediaId=$content[0]['#block_content']->get('field_employee_picture')->target_id;
      for ($index = 0; $index <= sizeof($content)-1; $index++) {
        $mediaIdtwo=$content[$index]['#block_content']->get('field_employee_picture')->target_id;
        $media_entity_loadtwo = Media::load($mediaIdtwo);
        $uritwo = $media_entity_loadtwo->field_image->entity->getFileUri();
        $variables['employeeimages'][$index] = $uritwo;
        $variables['field_employee_department'][$index] = $content[$index]['#block_content']->get('field_employee_department')->value;
        $variables['field_employee_email'][$index] = $content[$index]['#block_content']->get('field_employee_email')->value;
        $variables['field_employee_title'][$index] = $content[$index]['#block_content']->get('field_employee_title')->value;
        $variables['field_employee_first_name'][$index] = $content[$index]['#block_content']->get('field_employee_first_name')->value;
        $variables['field_employee_last_name'][$index] = $content[$index]['#block_content']->get('field_employee_last_name')->value;
        $variables['field_employee_office_location'][$index] = $content[$index]['#block_content']->get('field_employee_office_location')->value;
        $variables['field_employee_telephone'][$index] = $content[$index]['#block_content']->get('field_employee_telephone')->value;

      }
  }

}



