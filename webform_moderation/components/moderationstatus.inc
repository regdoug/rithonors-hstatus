<?php

/**
 * @file
 * Webform module moderationstatus component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_moderationstatus() {
  return array(
    'name' => 'Status',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => 0,
    'extra' => array(
      'private' => FALSE,
    ),
  );
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_moderationstatus() {
  return array(
    'webform_display_moderationstatus' => array(
      'arguments' => array('element' => NULL),
      'file' => 'components/moderationstatus.inc',
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_moderationstatus($component) {
  $form = array();
  $form['value'] = array(
    '#type' => 'hidden',
    '#default_value' => $component['value'],
    '#weight' => -10,
  );
  $form['extra']['description'] = array(); // Hide the description box.
  $form['display'] = array('#type' => 'markup'); // Hide the display options.
  return $form;
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_moderationstatus($component, $value = NULL, $filter = TRUE) {
  $element = array(
    '#type' => 'hidden',
    '#title' => $filter ? _webform_filter_xss($component['name']) : $component['name'],
    '#default_value' => $filter ? _webform_filter_values($component['value']) : $component['value'],
    '#weight' => $component['weight'],
  );

  if (isset($value[0])) {
    $element['#default_value'] = $value[0];
  }

  return $element;
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_moderationstatus($component, $value, $format = 'html') {
  $element = array(
    '#title' => t('!name', array('!name' => $component['name'])),
    '#value' => isset($value[0]) ? $value[0] : NULL,
    '#weight' => $component['weight'],
    '#format' => $format,
    '#theme' => 'webform_display_moderationstatus',
    '#theme_wrappers' => $format == 'html' ? array('webform_element', 'webform_element_wrapper') : array('webform_element_text'),
    '#post_render' => array('webform_element_wrapper'),
    '#webform_component' => $component,
  );

  // TODO: This check is unusual. It shows hidden fields in e-mails but not
  // when viewing in the browser unless you're an administrator. This should be
  // a more logical check. 
  
  //Everyone should be able to see this particular field.
  /*if ($format == 'html') {
    $element['#access'] = user_access('edit all webform submissions') || user_access('access all webform results');
  }*/

  return $element;
}

/*
function theme_webform_display_moderationstatus($element) {
	$bgcolor = '';
	$text = '';
	switch ($element['#value']){
	  case 0: $text = 'Pending'; break;
	  case 1: $text = 'Approved'; $bgcolor = '#D63333'; break;
	  case 2: $text = 'Rejected'; $bgcolor = '#33D633'; break; 
	  default : $text .= 'Unknown';
	}
	if( $element['#format'] = 'html' ){
		//do stuff
		$html = <<<HTML
$text

HTML;
		return $html;
	}else{
		return $text;
	}
}
*/

template_preprocess_webform_display_moderationstatus(&$variables){
	$variables['value'] = (is_numeric($variables['element']['#value'])) ? intval($variables['element']['#value']) : 99;
	$variables['text'] = _webform_moderation_val_to_text($variables['value']);
	$variables['format'] = $variables['element']['#format'];
}

/**
 * Implements _webform_analysis_component().
 */
function _webform_analysis_moderationstatus($component, $sids = array()) {
  $placeholders = count($sids) ? array_fill(0, count($sids), "'%s'") : array();
  $sidfilter = count($sids) ? " AND sid in (" . implode(",", $placeholders) . ")" : "";
  $query = 'SELECT data ' .
    ' FROM {webform_submitted_data} ' .
    ' WHERE nid = %d ' .
    ' AND cid = %d ' . $sidfilter;
  $submissions = 0;
  $pending = 0;
  $approved = 0;
  $rejected = 0;

  $result = db_query($query, array_merge(array($component['nid'], $component['cid']), $sids));
  while ($data = db_fetch_array($result)) {
	$data = trim($data['data'])
	$value = is_numeric($data) ? intval($data) : 99;
    switch($value){
		case 0: pending++; break;
		case 1: approved++; break;
		case 2: rejected++; break;
	}
    $submissions++;
  }

  $rows[0] = array( t('Submitted'), $submissions );
  $rows[1] = array( t('Pending'), $pending );
  $rows[2] = array( t('Percent Approved'), ($approved / ($approved+$rejected)) );
  return $rows;
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_table_moderationstatus($component, $value) {
  $val = (is_numeric($value[0]) ? intval($value[0]) : 99);
  return _webform_moderation_val_to_text($val);
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_headers_moderationstatus($component, $export_options) {
  $header = array();
  $header[0] = '';
  $header[1] = '';
  $header[2] = 'Status';
  return $header;
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_data_moderationstatus($component, $export_options, $value) {
  return (is_numeric($value[0]) ? intval($value[0]) : 99);
}

function _webform_moderation_val_to_text($intval){
  switch($intval){
	case 0: return 'Pending';
	case 1: return 'Approved';
	case 2: return 'Rejected';
	default: return 'Unknown';
  }
}
