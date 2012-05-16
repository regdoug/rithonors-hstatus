<?php

//works better than constants
function _hstatus_timetosave(){return '6 months';}

/**
 * hstatus_build_form
 * 
 * Convenience function to build form pages
 */

function hstatus_build_form($form = ''){
    switch($form){
        case 'cl':
            return drupal_get_form('hstatus_forms_cl',(func_num_args() > 1)?func_get_arg(1):'first');
        default:
            return "The requested form '$form' could not be loaded.";
    }
}

/**
 * Complearning form
 */
function hstatus_forms_cl(&$form_state,$page){
    //get data from database
    global $user;
    module_load_include('inc','hstatus','hstatus.db');
    $data = hstatus_load_cldraft($user->uid,_hstatus_timetosave());
    
    //if we are coming from another page, we need to get it from the
    //storage rather than from the args
    $page = (isset($form_state['storage']['page']))?$form_state['storage']['page']:$page;
    
    $n = intval($page);
    //if $page is a string, $n will be 0
    if($n > 0){
        $form = array();
        $form['page'] = array(
            '#type' => 'value',
            '#value' => $n,
        );
        $form['heading'] = array(
            '#value' => '<h3>'.t('Activity !n',array('!n'=>$n)).'</h3>',
        );

        $form['name'] = array(
            '#type' => 'textarea',
            '#required' => true,
            '#title' => t('Activity Name'),
        );
        $form['desc'] = array(
            '#type' => 'textarea',
            '#required' => true,
            '#title' => t('Activity Description'),
        );
        $form['lead'] = array(
            '#type' => 'textarea',
            '#required' => true,
            '#title' => t('Leadership/Citizenship'),
        );
        $form['time'] = array(
            '#type' => 'textarea',
            '#required' => true,
            '#title' => t('Time Commitment'),
        );
        $form['contact'] = array(
            '#type' => 'textarea',
            '#required' => true,
            '#title' => t('Contact Information'),
        );
        $form['comment'] = array(
            '#type' => 'textarea',
            '#title' => t('Comments'),
        );
        $form['submit'] = array(
          '#type' => 'submit',
          '#value' => t('Next Page >'),
        );
        
        
        if(isset($data['count']) && $data['count'] < $n){
            //page does not exist
            //don't do anything so that execution proceeds to the first page form
        }elseif(isset($data[$n])){
            $form['name']['#default_value'] = $data[$n]['name'];
            $form['desc']['#default_value'] = $data[$n]['desc'];
            $form['lead']['#default_value'] = $data[$n]['lead'];
            $form['time']['#default_value'] = $data[$n]['time'];
            $form['contact']['#default_value'] = $data[$n]['contact'];
            $form['comment']['#default_value'] = $data[$n]['commment'];
            return $form;
        }else{
            return $form;
        }
    }
    
    if($page == 'last'){
        //last page
        $form = array();
        $form['page'] = array(
            '#type' => 'value',
            '#value' => 'last',
        );
        $form['information'] = array(
            '#value' => '<p>'.t("Your responses have been saved as a draft.
            They will be stored for up to "._hstatus_timetosave()."
            If you are satisfied with your submission,
            you may submit the form now by clicking the button below.").'</p>',
        );
        $form['submit'] = array(
          '#type' => 'submit',
          '#value' => t('Done, Submit Now'),
        );
        return $form;
    }else{
        //first page -- acts as a catch-all, rather than returning a 404
        $form = array();
        $form['page'] = array(
            '#type' => 'value',
            '#value' => 'first',
        );
        $form['count'] = array(
            '#type' => 'textfield',
            '#title' => t('Activities'),
            '#description' => t('Number of activities that compose this submission.'),
            '#required' => true,
            '#element_validate' => array('hstatus_form_cl_count_validate'),
            '#default_value' => (isset($data['count']))?$data['count']:1,
            //HTML5 attributes
            '#attributes' => array('type' => 'number', 'min' => '1'),
        );
        $form['submit'] = array(
          '#type' => 'submit',
          '#value' => t('Next Page >'),
        );
    }
    return $form;
}

/*
 * hstatus_form_cl_count_validate
 * 
 * Validates the count field on the first page of the form
 */
function hstatus_form_cl_count_validate($element, &$form_state){
    //activites has to be a positive number
	$v = trim($element['#value']);
    if(empty($v) || intval($v) < 1){
        //flags the field as incorrect
        form_error($element, t('You must have a positive integer number of activities.'));
    }
    //ensure it is actually an integer
    $integer = true;
    //probably faster than preg_match
    foreach(str_split($v) as $c){
        //if there are decimal points, they will not be numeric.
        $integer = is_numeric($c);
        if(!$integer){
            form_error($element, t('You must have a positive integer number of activities.'));
            return;
        }
    }
}

/*
 * hstatus_forms_cl_submit
 * 
 * Called whenever the form is submitted.
 * This function does not actually handle the data but instead passes
 * it on to helper functions.
 */

function hstatus_forms_cl_submit($form, &$form_state){
    $page = $form_state['values']['page'];
    
    if(is_numeric($page)){
        _hstatus_clform_savepage($form_state);
    }elseif($page == 'first'){
        _hstatus_clform_newentry($form_state);
    }elseif($page == 'last'){
        _hstatus_clform_savefinal($form_state);
    }else{
        _hstatus_clform_redirect($form_state,false);
    }
}

//====================================
//===== Private/Helper Functions =====
//====================================

//note the Drupal convention of making 
//"private" functions start with an underscore

/*
 * Helper function for the first page
 */
function _hstatus_clform_newentry(&$form_state){
    global $user;
    module_load_include('inc','hstatus','hstatus.db');
    $data = hstatus_load_cldraft($user->uid,_hstatus_timetosave());
    
    $n = $form_state['values']['count'];
    
    if($data){
        $data['count'] = $n;
    }else{
        $data = array('count' => $n);
    }
    _hstatus_clform_saveandredirect($form_state,$data,1);
}

/*
 * Helper for all pages except first and last
 */

function _hstatus_clform_savepage(&$form_state){
    global $user;
    module_load_include('inc','hstatus','hstatus.db');
    $data = hstatus_load_cldraft($user->uid,_hstatus_timetosave());
    //DEBUG
    drupal_set_message('Loading data: '.($data)?'Success.':'Failure.');
    $vals = $form_state['values']; //note that PHP arrays are NOT assigned by reference
    $n = $vals['page'];
    unset($vals['page']);
    $data[$n] = $vals;
    $nextpage = ($n < $data['count'])?$n+1:'last';
    _hstatus_clform_saveandredirect($form_state,$data,$nextpage);
}

/*
 * Helper for last page
 */
function _hstatus_clform_savefinal(&$form_state){
    global $user;
    module_load_include('inc','hstatus','hstatus.db');
    if(hstatus_clsubmit($user->uid)){
        drupal_set_message(t('Complementary Learning sucessfully submitted.'));
        unset($form_state['storage']);
        unset($form_state['rebuild']);
        $form_state['redirect'] = '<front>';
    }else{
        drupal_set_message(t('Failed to submit Complementary Learning.'),'error');
        _hstatus_clform_redirect($form_state,'last',false);
    }
}

/*
 * Saves the $data passed to it and calls the redirect helper
 * with $page if it is successful.  If unsucessful, the redirect
 * helper is called with false.
 */

function _hstatus_clform_saveandredirect(&$form_state,$data,$page){
    global $user;
    module_load_include('inc','hstatus','hstatus.db');
    $success = hstatus_save_cldraft($user->uid,$data);
    $page = ($success)?$page:false;
    _hstatus_clform_redirect($form_state,$page);
} 

/*
 * The redirect helper.
 * 
 * Not actually a true redirect because the page doesn't change, but
 * will reload the form to the $page requested.  If $page is false,
 * the current page of the form is reloaded.
 */

function _hstatus_clform_redirect(&$form_state,$page,$message=true){
    if($page){
        $form_state['storage']['page'] = $page;
        if($message){drupal_set_message(t('Data saved successfully'));}
    }else{
        $form_state['redirect'] = false;
        if($message){drupal_set_message(t('Failed to save data.'),'error');}
    }
}
