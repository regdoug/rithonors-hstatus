<?php

class views_plugin_style_fieldset extends views_plugin_row {

	function option_definition() {
		$options = parent::option_definition();
		$options['initialstate'] = array('collapsed' => 'Collapsed');
		
		return $options;
	}
	
	function options_form(&$form, &$form_state) {
		parent::options_form($form, $form_state);
		
		$form['initialstate'] = array(
			'#type' => 'radios',
			'#title' => t('Initial Fieldset State'),
			'#options' => array('collapsed' => 'Collapsed',
								'null' => 'Expanded',),
			'#default_value' => $this->options['title'],
		);
	}
	
}
