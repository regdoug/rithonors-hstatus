<?php
/**
 * Render a (numeric) complearning status field as a status string
 *
 * @ingroup views_field_handlers
 */
class hcomplearn_views_handler_field_status extends views_handler_field {
    function render($values) {
        $value = intval($values->{$this->field_alias});
        return hcomplearn_status_string($value);
    }
    function allow_advanced_render() {
        return false;
    }
}
