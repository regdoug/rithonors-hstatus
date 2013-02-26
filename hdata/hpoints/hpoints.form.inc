<?php

//NOTES:
//this is a quick todo list
// 2 - create page to edit h_points_menu (this would be in hpoints.admin.inc)

/**
 * Determines whether the bulk form should be shown and selects the correct
 * form building function.
 * 
 * TODO: It might be better to move this logic to hpoints_menu
 */
function hpoints_build_form(){
    $arg = (func_num_args() > 0)?func_get_arg(0):'';
    if($arg == 'admin' && 1 && user_access('bulk submit points')){
        return drupal_get_form('hpoints_form_bulk');
    }else{
        return drupal_get_form('hpoints_form');
    }
}

/**
 * Validates a number as an integer
 */
function hpoints_form_int_validate($element, &$form_state){
    //activites has to be a positive number
	$v = trim($element['#value']);
    if(empty($v) || intval($v) < 1){
        //flags the field as incorrect
        form_error($element, t('%element must be a positive integer.',array('%element'=>$element['#title'])));
    }
    //ensure it is actually an integer
    $integer = true;
    //probably faster than preg_match
    foreach(str_split($v) as $c){
        //if there are decimal points, they will not be numeric.
        $integer = is_numeric($c);
        if(!$integer){
            form_error($element, t('%element must be a positive integer.',array('%element'=>$element['#title'])));
            return;
        }
    }
}

/*
 * hpoints_forms_cl_submit
 *
 * Called whenever the form is submitted.
 * This function does not actually handle the data but instead passes
 * it on to helper functions.
 */

function hpoints_form_submit($form, &$form_state){
    global $user;
    if(!isset($user->name)){
        $u = user_load($user->uid);
    }
    if($form_state['storage']['email']){
        $huser = hdata_user_load(array('uid'=>$u->uid,'name'=>$u->name));
        $sub = $form_state['storage']['submission'];
        _hpoints_send_email($form_state['values']['name'],$form_state['values']['email'],
            implode(' ',$huser['basic']['name']),$sub);
        $sub['explanation'] .= PHP_EOL.'Email sent to '.$form_state['values']['email'];
        hdata_points_save($sub);
        unset($form_state['storage']);
    }else{
        $type = intval($form_state['values']['type']);
        $explanation = check_plain($form_state['values']['description']);
        $sub = array('username'=>$u->name,'type'=>$type,'explanation'=>$explanation);
        $sub = hdata_points_save($sub);
        
        if(hpoints_type_needs_email($type)){
            $form_state['storage']['email'] = true;
            $form_state['storage']['submission'] = $sub;
        }
    }
}

function hpoints_form_bulk_submit($form, &$form_state){
    global $user;
    if(!isset($user->name)){
        $user = user_load(array('uid' => $user->uid));
    }
    
    $submission_tmpl = array(
        'explanation'   => $form_state['values']['description'],
        'type'          => $form_state['values']['type'],
        'submitted_by'  => $user->name,
        'reviewer'      => $user->name,
        'reviewed_time' => strftime('%F %H:%M:%S'),
        'credits'       => $form_state['values']['points'],
        'status'        => 1,
    );
    $user_str = preg_replace('[^a-z0-9\\s]','',$form_state['values']['users']);
    $users = explode(' ',$user_str);
    if(is_array($users)){
        //OPTION: Use ctools bulk api?
        foreach($users as $student){
            if(!empty($student)){
                if(hdata_user_is_active_student($student)){
                    $sub = $submission_tmpl + array('username' => trim($student));
                    $form_state['storage']['testing']['sub'] = $sub;
                    hdata_points_save($sub);
                }else{
                    drupal_set_message(t('%user is not an active student.',array('%user' => $student)),'warning');
                }
            }
        }
    }else{
        form_set_error($form['users'],'Invalid Recipient Usernames');
    }
}

function hpoints_form(&$form_state){
    global $user;
    $huser = hdata_user_load(array('uid'=>$user->uid,'name'=>$user->name));
    
    $form = array();
    if(($msg = hpoints_submit_allowed($huser)) != 'ok'){
        $form['error'] = array( '#value' => t('%msg',array('%msg'=>$msg)));
        return $form;
    }
    $submitmsg = variable_get('hpoints_form_submitmsg',HPOINTS_SUBMIT_MSG);
    $form['info'] = array(
        '#value' => $submitmsg,
        '#prefix' => '<p>',
        '#suffix' => '</p>',
    );
    
    if($form_state['storage']['email']){
        _hpoints_form_email($form,$huser);
    }else{
        _hpoints_form($form,$huser);
    }
    return $form;
}
        

function _hpoints_form(&$form,$huser){
    $submitwarning = '<p><strong>'.variable_get('hpoints_form_submitwarn',HPOINTS_SUBMIT_WARN).'</strong></p>';
    
    $form['type'] = array(
        '#title' => t('Activity Type'),
        '#type' => 'select',
        '#options' => hpoints_get_type_options(),
    );
    $form['description'] = array(
        '#title' => t('Description'),
        '#description' => t('Please describe what you did and why you deserve to earn points.'),
        '#type' => 'textarea',
    );
    $form['info3'] = array(
        '#value' => $submitwarning,
        '#prefix' => '<p><strong>',
        '#suffix' => '</strong></p>',
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
    );
}

function _hpoints_form_email (&$form,$huser){
    $msg = variable_get('hpoints_form_emailmsg',HPOINTS_EMAIL_MSG);
    $form['info2'] = array(
        '#value' => $msg,
    );
    $form['name'] = array(
        '#title' => t('Reference'),
        '#description' => t('Enter the name of your reference'),
        '#type' => 'textfield',
    );
    $form['email'] = array(
        '#title' => t('Email'),
        '#description' => t('Enter the email address of the your reference'),
        '#type' => 'hformtools_html5_email',
        '#required' => true,
    );
    $form['message'] = array(
        '#title' => t('Message'),
        '#description' => t('Enter a short message to accompany this email'),
        '#type' => 'textarea',
    );
    $form['submit'] = array(
        '#value' => t('Send Email'),
        '#type' => 'submit',
    );
}

function hpoints_form_bulk (&$form_state){
    //DEBUG:
    $form['debug_lastsub'] = array(
        '#prefix' => '<pre>',
        '#suffix' => '</pre>',
        '#value' => print_r($form_state['storage']['testing']['sub'],true),
    );
    $form['users'] = array(
        '#title' => t('Recipients'),
        '#description' => t('Enter the usernames of the students who will recieve the points'),
        '#type' => 'hformtools_users',
    );
    $form['type'] = array(
        '#title' => t('Activity Type'),
        '#type' => 'select',
        '#options' => hpoints_get_type_options(),
    );
    $form['description'] = array(
        '#title' => t('Description'),
        '#description' => t('Describe the reason that points are being granted'),
        '#type' => 'textarea',
    );
    $form['points'] = array(
        '#title' => t('Credits Awarded'),
        '#type' => 'hformtools_html5_number',
        '#size' => 5,
        '#maxlength' => 2,
        '#required' => true,
        '#element_validate' => array('hpoints_form_int_validate'),
        //HTML5 attributes
        '#min' => 1,
        '#max' => 10,
        '#step' => 1,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
    );
    return $form;
}

function hpoints_submit_allowed($huser){
    if(!$huser){
        return t('Failed to load your profile.');
    }elseif($huser['continuation']['status'] > 2){
        return t('You are not active in the Honors Program');
    }else{
        return 'ok';
    }
}

function _hpoints_send_email($name,$to,$studentname,$submission){
    $from = "{$submission['username']}@rit.edu";
    $formatted_submission = theme('hpoints_submission',$submission);
    $formatted_message = theme('hpoints_reference_email',$studentname,$from,$name,$to,$formatted_submission);
    mimemail($from,$to,'Honors Points Submission',$formatted_message);
}
