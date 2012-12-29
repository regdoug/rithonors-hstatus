<?php
/*
 * hdata.testcases.inc
 * 
 * This file contains functions to test hdata, which, since it is a backend
 * module is rather difficult to accurately test.
 */
 
function hdata_testcases_page(){
    global $base_path;
    $settings = array('ajax_path' => $base_path . 'testhdata/ajax/');
    drupal_add_js(array('hdata' => $settings),'setting');
    drupal_add_js(drupal_get_path('module','hdata').'/hdata.testcases.js','module','header',false,false,false);
    return <<<PAGE
<h1>hData &ldquo;Load&rdquo; Tests</h1>
<form id="testcases">
<select name="function">
    <option value="hdata_user_load">hdata_user_load(username,reset)</option>
    <option value="hdata_student_list">hdata_student_list(college,active)</option>
    <option value="hdata_faculty_list">hdata_faculty_list(college)</option>
    <option value="hdata_load_notes">hdata_load_notes(username)</option>
    <option value="hdata_load_note">hdata_load_note(id)</option>
    <option value="hdata_user_is_active_student">hdata_user_is_active_student(username)</option>
</select>
Arguments:<br>
<input name="arg1">
<input name="arg2">
<input name="arg3">
<input type="button" name="submit" value="Test" onclick="hdata_testcases_jssubmit();"/>
</form>
<a id="hdata-link" href="#">Results</a>
<div id="testcases-output"></div>
<div id="hdata-error"></div>
PAGE;
}

function hdata_testcases_ajax(){
    if(func_num_args() < 1){
        echo "Too few arguments";
    }
    $argv = func_get_args();
    $fcn = array_shift($argv);
    //handle functions that need a "userinfo" array
    if($fcn == 'hdata_user_load' || $fcn == 'hdata_user_is_active_student'){
        $argv[0] = array('name' => $argv[0]);
    }
    
    if(function_exists($fcn)){
        echo '<pre>';
        echo "About to call $fcn with the following arguments\n";
        print_r($argv);
        $retVal = call_user_func_array($fcn,$argv);
        echo "\nResults\n\n";
        if(is_array($retVal))
            print_r($retVal);
        else
            var_dump($retVal);
        echo '</pre>';
    }
    return null;
}
