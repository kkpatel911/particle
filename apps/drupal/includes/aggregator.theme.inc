<?php

use Drupal\Component\Utility\Html;

/**
 * Implements template_preprocess_hook().
 */
$AggregatorArrayg = NULL;

function particle_preprocess_aggregator_item(&$variables, $hook) {
  // Don't go looking for a manage display tab, there is none as
  // aggregator_items are not being exposed to the field UI
  $timeStamp = $variables['elements']['#aggregator_item']->get('timestamp')->value;
  $variables['feed'] = $variables['elements']['#aggregator_item']->get('fid')->entity->title->value;
  $variables['adapted_time'] = date('M-d', $timeStamp);
}


/**
 * Implements template_preprocess_hook().
 */
function particle_preprocess_aggregator_feed(&$variables) {
  // sorts based on the key of its elements
  //$AggregatorArray = $variables['content']['items'];
  if ($variables['elements']['#view_mode'] === "utc_summary") {
    ksort($variables['content']['items']);
  }
}

/**
 * Implements hook_theme_suggestions_HOOK() for aggregator_feed suggestions
 */
function particle_theme_suggestions_aggregator_feed_alter(array &$suggestions, array $variables) {

  $node = \Drupal::routeMatch()->getParameter('node');
  if ($node) {
    $nid = $node->id();
    $bundle = $node->bundle();
    //$node->getTitle();
  }
  else {
    $nid = NULL;
    $nid2 = NULL;
    $bundle = NULL;
  }
  $suggestions[] = ('aggregator_feed__' . $bundle . "_id_" . $nid);
}

/**
 * Implements hook_theme_suggestions_HOOK() for aggregator_item suggestions
 */
function particle_theme_suggestions_aggregator_item_alter(array &$suggestions, array $variables) {


  $node = \Drupal::routeMatch()->getParameter('node');
  if ($node) {
    $nid = $node->id();
    $bundle = $node->bundle();
    //$node->getTitle();
  }
  else {
    $nid = NULL;
    $nid2 = NULL;
    $bundle = NULL;
  }
  $suggestions[] = ('aggregator_item__' . $bundle . "_id_" . $nid);

  $feed_title = $variables['elements']['#aggregator_item']->get('fid')->entity->title->value;
  $clean_feed_title = Html::getClass($feed_title);
  $suggestions[] = 'aggregator_item__' . str_replace('-', '_', $clean_feed_title);

}
