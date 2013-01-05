<?php
/**
 * Render a (numeric) complearning status field as a status string
 *
 * @ingroup views_field_handlers
 */
//TODO: change number values for points.
//  we'll also need one for points type. (this means another file)
class hpoints_views_handler_field_status extends views_handler_field {
    function render($values) {
        $value = intval($values->{$this->field_alias});
        switch ($value) {
            case 0: return 'Pending';
            case 1: return 'Approved';
            case 2: return 'Rejected';
            default: return strval($value);
        }
    }
    function allow_advanced_render() {
        return false;
    }
}
        
