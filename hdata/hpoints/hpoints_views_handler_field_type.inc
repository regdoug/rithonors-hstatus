<?php
/**
 * Render a (numeric) complearning status field as a status string
 *
 * @ingroup views_field_handlers
 */
class hpoints_views_handler_field_type extends views_handler_field {
    function render($values) {
        $value = intval($values->{$this->field_alias});
        $types = hdata_points_type_list();
        if($types[$value]){
            return($types[$value]['title']);
        }else{
            return number_format($value,0);
        }
    }
    function allow_advanced_render() {
        return false;
    }
}
