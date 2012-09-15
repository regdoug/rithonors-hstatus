<?php
/*
 * This extends views_handler_filter_in_operator to provide filtering
 * based on submission status
 */
 
/**
 * Filter by complearning submission status
 */
class hcomplearn_views_handler_filter_cl_status extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_options = array(0=>'Pending',1=>'Approved',2=>'Rejected');
    }
  }
}
