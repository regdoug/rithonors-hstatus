<?php

class views_plugin_style_fieldset extends views_plugin_row {

	function option_definition() {
		$options = parent::option_definition();
		$options['title'] = array('default' => '');
		
		return $options;
	}
	
	function options_form(&$form, &$form_state) {
		parent::options_form($form, $form_state);
		$title_options = array();
		$title_options['default'] = '';
		
		$fields = $this->display->handler->get_option('fields');
		foreach ($fields as $field => $info) {
		  //$handler = views_get_handler($info['table'], $info['field'], 'field');
		  $title_options[$info['field']] = $info['field'];
		}
		
		$form['title'] = array(
			'#type' => 'select',
			'#title' => t('Title Field'),
			'#options' => $title_options,
			'#default_value' => $this->options['title'],
		);
	}
	
}
