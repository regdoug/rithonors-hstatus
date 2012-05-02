<?php
$hstatus_timetosave = '6 months';

/* hstatus.pages.inc - Implements the display functions for the hStatus module */

/**
 * Function defined by hstatus_menu to generate the page.
 * 
 * All it does is start drupal's theme system
 */
function hstatus_user_page($user){
    return theme('hstatus_mystatus',$user);
}

/**
 * Complearning form
 */
function hstatus_forms_cl($arg0){
    
    if(is_numeric($arg0)){
        //activity entry
        $n = intVal($arg0);
        $form = array();
        $form['page'] = array(
            '#type' => 'value',
            '#value' => $n,
        );
        $form['heading'] = array(
            '#value' => '<h3>'.t("Activity $n").'</h3>',
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
        
        global $user;
        module_load_include('hstatus','inc','hstatus.db');
        $data = hstatus_load_cldraft($user->uid,$hstatus_timetosave);
        if($data['count'] < $n){
            //page does not exist
            //don't do anything so that execution proceeds to the first page form
        }elseif(isset($data[$n])){
            $form['name']['#default_value'] = $data[$n]['name'];
            $form['desc']['#default_value'] = $data[$n]['desc'];
            $form['lead']['#default_value'] = $data[$n]['lead'];
            $form['time']['#default_value'] = $data[$n]['time'];
            $form['contact']['#default_value'] = $data[$n]['contact'];
            $form['comment']['#default_value'] = $data[$n]['commment'];
        }
    }
    
    if($arg0 == 'last'){
        //last page
        $form = array();
        $form['page'] = array(
            '#type' => 'value',
            '#value' => 'last',
        );
        $form['information'] = array(
            '#value' => '<p>'.t("Your responses have been saved as a draft.
            They will be stored for up to $hstatus_timetosave.  
            If you are satisfied with your submission,
            you may submit the form now by clicking the button below.").'</p>',
        );
        $form['submit'] = array(
          '#type' => 'submit',
          '#value' => t('Done, Submit Now'),
        );
        return $form;
    }else{
        //first page
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
            '#element_validate' => 'hstatus_form_cl_count_validate',
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

function hstatus_form_cl_count_validate($element, &$form_state){
	$v = $element['#value'];
	if(empty($v) || !( is_numeric($v) && intVal($v) > 0 )){
		form_error($element, $t('You must have a positive number of activities');
	}
}

function hstatus_form_cl_submit($form, &$form_state)
    switch($form_state['values']['page']){
        case 'first': _hstatus_clform_newentry($form_state);break;
        case 'last': _hstatus_clform_savefinal($form_state);break;
        default: _hstatus_clform_savepage($form_state);break;
    }
}

function _hstatus_clform_newentry(&$form_state){
    $n = $form_state['values']['count'];
    $data = array('count' => $n);
    global $user;
    module_load_include('hstatus','inc','hstatus.db');
    $success = hstatus_save_cldraft($user->uid,$data);
    if($success){
        $form_state['redirect'] = 'hstatus/mystatus/1';
    }
}
function _hstatus_clform_savepage(&$form_state){
}
function _hstatus_clform_savefinal(&$form_state){
}
function _hstatus_clform_saveandredirect(&$form_state,$data,$page){
    global $user;
    module_load_include('hstatus','inc','hstatus.db');
    $success = hstatus_save_cldraft($user->uid,$data);
    if($success && $page){
        $form_state['redirect'] = "hstatus/mystatus/$page";
    }else{
        $form_state['redirect'] = 'hstatus/mystatus';
        drupal_set_message('Failed to save data','error');
    }
}
    

/**
 * hstatus_static_page
 * 
 * hstatus_test_db_page
 * 
 * Expermental or demonstrative functions
 */
 
function hstatus_static_page(){
    global $user;
    module_load_include('hstatus','inc','includes/hstatus.db'); 
    $u = hstatus_load_user($user->name,false,false,true);
    ob_start();
    include 'test2.php';
    $retVal = ob_get_contents();
    ob_end_clean();
    return $retVal;
    //return '<p>Hello!</p>';
}
function hstatus_test_db_page(){
    global $user;
    module_load_include('hstatus','inc','includes/hstatus.db');
    $u = hstatus_load_user($user->name);
    if($u){
        $retVal = '<pre>'.print_r($u,true).'</pre>';
    }else{
        $retVal = 'User failed to load';
    }
    return $retVal;
}

/**
 * Preprocess function for the theme hook 'hstatus_mystatus'.
 * 
 * It loads the database api from hstatus.db.inc and gets a user object
 */
function template_preprocess_hstatus_mystatus(&$variables){
    // this shouldn't happen unless a null value (or no value) is passed to
    // the theme function.  i.e. theme('hstatus_mystatus');
    if(is_null($variables['user'])){
        $variables['displaynone'] = true;
    }else{
        $username = $variables['user']->name;
        
        //loads the database API
        module_load_include('inc', 'hstatus', 'includes/hstatus.db');
        
        //gets a user object
        $huser = hstatus_load_user($username);
        // $huser will be false if the load failed.
        if($huser){
        
            //get all the variables first, then assign them to the $variables array
            
            $status = $huser->continuation['status'];
            switch($status){
                case 0: $status_str = 'Continuted';break;
                case 1: $status_str = 'Conditional Continuation';break;
                case 2: $status_str = 'Warning';break;
                case 3: $status_str = 'Withdrawn';break;
                case 4: $status_str = 'Graduated';break;
                case 5: $status_str = 'Withdrawn due to BS/MS';break;
                case 6: $status_str = 'Graduated with BS/MS';break;
                case 7: $status_str = 'Conditional Continuation (BS/MS)';break;
                default: $status_str = 'Unknown';
            }
            
            $points = $huser->points['total'];
            
            $cl = $huser->continuation['cl'];
            switch($cl){
                case 0: $cl_str = 'Pending'; break;
                case 1: $cl_str = 'Approved'; break;
                case 2: $cl_str = 'Rejected'; break;
                default: $cl_str = 'Unknown';
            };
            
            $fullname = ucfirst($huser->basic['name']['firstname']).' '.
                    ucfirst($huser->basic['name']['lastname']);
            
            //Guaranteed Variables
            $variables['username'] = $username;
            $variables['status'] = $status;
            $variables['status_string'] = $status_str;
            $variables['points_total'] = $points;
            $variables['complearning_status'] = $cl;
            $variables['complearning_status_string'] = $cl_str;
            
            //Optional variables
            $variables['name'] = $fullname;
            $variables['gpa'] = $huser->basic['gpa'];
            $variables['year'] = $huser->basic['year'];
            $variables['college'] = $huser->basic['college'];
            $variables['department'] = $huser->basic['department'];
            $variables['program'] = $huser->basic['program'];
            
        }else{ //the load failed.
            //signal that the display should be nothing
            $variables['displaynone'] = true;
        }
    }
}
