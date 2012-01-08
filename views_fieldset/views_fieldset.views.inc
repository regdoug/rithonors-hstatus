<?php

/**
 * Declaring Plugins
 * 
 * Our plugin is called 'views_fieldset' (views_fieldset.views.inc)
 * 
 */
function views_fieldset_views_plugins(){
	$retVal = array();
	$retVal['row'] = array(
		'views_fieldset' => array(
			'title' => t('Collapsible Rows'),
			'theme' => 'views_view_row_fieldset',
			'help' => t('Displays each row as a collapsed fieldset'),
			'handler' => 'views_plugin_style_fieldset',
			'uses row plugin' => TRUE,
			'uses fields' => TRUE,
			'uses options' => TRUE,
			'type' => 'normal',
		),
	);
	return $retVal;
} 
