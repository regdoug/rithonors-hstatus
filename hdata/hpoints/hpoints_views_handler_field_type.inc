<?php
/**
 * Render a (numeric) complearning status field as a status string
 *
 * @ingroup views_field_handlers
 */
//TODO: change number values for points.
//  we'll also need one for points type. (this means another file)
class hpoints_views_handler_field_type extends views_handler_field {
    function render($values) {
        $value = intval($values->{$this->field_alias});
        //TODO: load h_points_menu table into $types
        if($types[$value]){
            return($types[$value]);
        }else{
            return number_format($value,0);
        }
    }
    function allow_advanced_render() {
        return false;
    }
}
