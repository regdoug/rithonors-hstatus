<?php

/* hstatus.pages.inc - Implements the display functions for the hStatus module */

function hstatus_user_page($user){
    return theme('hstatus_mystatus',$user);
}

function template_preprocess_hstatus_mystatus(&$variables){
    if(is_null($variables['user'])){
        $variables['username'] = 'none';
    }else{
        $username = $variables['user']->name;
        $status = _bogus_api_get_status($username);
        switch($status){
            default: $status_str = 'Not yet implemented';
        }
        $points = _bogus_api_get_points($username);
        $cl = _bogus_api_get_cl($username);
        switch($cl){
            case 0: $cl_str = 'Pending'; break;
            case 1: $cl_str = 'Approved'; break;
            case 2: $cl_str = 'Rejected'; break;
            default: $cl_str = 'Unknown';
        };
        
        //Guaranteed Variables
        $variables['username'] = $username;
        $variables['status'] = $status;
        $variables['status_string'] = $status_str;
        $variables['points_total'] = $points;
        $variables['complearning_status'] = $cl;
        $variables['complearning_status_string'] = $cl_str;
    }
}

function _bogus_api_get_status($uname){ return 0; }
function _bogus_api_get_points($uname){ return 0; }
function _bogus_api_get_cl($uname){ return -1; }
