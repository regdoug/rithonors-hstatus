<?php

//NOTES:
//this is a quick todo list
// 1 - append "email sent to..." to explanation field if email sent
// 2 - create page to edit h_points_menu

/**
 * Convenience function to build complearning form
 */

function hpoints_build_clform(){
    $arg = (func_num_args() > 0)?func_get_arg(0):'';
    if($arg == 'admin' && user_access('bulk submit points')){
        return drupal_get_form('hpoints_form_bulk');
    }else{
        return drupal_get_form('hpoints_form');
    }
}

/**
 * Processes an input element from a plain textfield to an HTML5
 * "number" textfield
 * 
 * used on bulk submit form
 */

function hpoints_number($html,$elements){
    $html = str_replace('type="text"','type="number"',$html);
    return $html;
}

/**
 * Validates the credits field o the bulk submit form
 */
function hpoints_form_cl_int_validate($element, &$form_state){
    //activites has to be a positive number
	$v = trim($element['#value']);
    if(empty($v) || intval($v) < 1){
        //flags the field as incorrect
        form_error($element, t('You must have a positive integer number of credits.'));
    }
    //ensure it is actually an integer
    $integer = true;
    //probably faster than preg_match
    foreach(str_split($v) as $c){
        //if there are decimal points, they will not be numeric.
        $integer = is_numeric($c);
        if(!$integer){
            form_error($element, t('You must have a positive integer number of credits.'));
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

//TODO: rewrite this!
//needs new name too!
function hpoints_form_submit($form, &$form_state){
    //get type of submission
    //check if email needed
    //send email if necessary
    //process explanation
    //save submission
}

function hpoints_form_bulk_submit($form, &$form_state){
    //emails never needed to be sent
    //get all attached students
    //generate one submission
        //on loop change names one-by-one and save
    
    //Use ctools bulk api?
}

//====================================
//===== Private/Helper Functions =====
//====================================

/* CONTENTS (in order)
 *
 * _hpoints_newentry
 * _hpoints_savepage
 *             ..._savefinal
 *             ..._saveandredirect
 *             ..._redirect
 *             ..._page_n
 *             ..._loaddata
 */

//note the Drupal convention of making
//"private" functions start with an underscore



/*
 * Generates normal (not first or last) pages
 * 
 * some elements may be useful
 */
function _hpoints_page_n($n,&$form,$data){
    $form['page'] = array(
        '#type' => 'value',
        '#value' => $n,
    );
    $form['heading'] = array(
        '#value' => '<h3>'.t('Activity !n',array('!n'=>$n)).'</h3>',
    );
    $whitelist_nid = hpoints_get_whitelist_nid();
    if(is_numeric($whitelist_nid)){
        $form['whitelist'] = array(
            '#value' => l('Whitelist/Blacklist','node/'.$whitelist_nid),
        );
    }
    $form['type'] = array(
        '#title' => t('Type of Activity'),
        '#type' => 'select',
        '#options' => hpoints_get_type_options(),
        '#default_value' => 'other',
    );
    $form['hours'] = array(
        '#title' => t('Hours Spent'),
        '#type' => 'textfield',
        '#size' => 5,
        '#maxlength' => 2,
        '#required' => true,
        '#element_validate' => array('hpoints_form_cl_int_validate'),
        //HTML5 attributes
        '#attributes' => array('min' => '0', 'max' => '50', 'step' => '1'),
        '#post_render' => array('hpoints_number'),
    );
    $form['name'] = array(
        '#type' => 'textfield',
        '#required' => true,
        '#title' => t('Activity Name'),
    );
    $form['desc'] = array(
        '#type' => 'textarea',
        '#required' => true,
        '#title' => t('Activity Description'),
        '#description' => t('Please include why this relates to Leadership and/or Citizenship'),
    );
    $form['time'] = array(
        '#type' => 'textarea',
        '#title' => t('Dates and Times'),
        '#description' => t('If necessary, please include information about when and where the activity was performed.'),
    );
    $form['contact'] = array(
        '#type' => 'textarea',
        '#required' => true,
        '#title' => t('Contact Information'),
        '#description' => t('Who should we contact to verify this information?'),
    );
    $form['comment'] = array(
        '#type' => 'textarea',
        '#title' => t('Comments'),
    );
    $form['back'] = array(
      '#type' => 'submit',
      '#value' => t('< Prev Page'),
      '#id' => 'back',
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Next Page >'),
    );

    $form['hours']['#default_value'] = $data[$n]['hours'];
    if(isset($data[$n]['type'])){
        //this one already has a default_value, so we only want to overwrite
        //it when we have a type stored in $data.
        $form['type']['#default_value'] = $data[$n]['type'];
    }
    $fields = _hpoints_fields();
    foreach($fields as $f){
        $form[$f]['#default_value'] = $data[$n][$f];
    }
}


function _hpoints_form(&$form,$huser,$data){
    if(($msg = hpoints_submit_allowed($huser)) != 'ok'){
        return $form['info'] = array( '#value' => t('%msg',array('%msg'=>$msg)));
    }
    /*
     * This function is mostly validation to make sure the user is allowed
     * to submit a complearning submission.  Most of these checks are in
     */
    $submitmsg = variable_get('hpoints_form_submitmsg',HCOMPLEARN_SUBMIT_MSG);
    $submitwarning = '<p><strong>'.variable_get('hpoints_form_submitwarn',HCOMPLEARN_SUBMIT_WARN).'</strong></p>';

    $form['info2'] = array(
        '#value' => $submitmsg,
        '#prefix' => '<p>',
        '#suffix' => '</p>',
    );
    $form['type'] = array(
        '#type' => 'select',
        '#options' => hpoints_get_type_options();
        //TODO: finish
    );
    $form['description'] = array(
        '#type' => 'textarea',
        //TODO: finish
    );
    //TODO: AJAX elements for email?
    $form['info3'] = array(
        '#value' => $submitwarning,
        '#prefix' => '<p><strong>',
        '#suffix' => '</strong></p>',
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#disabled' => !$maysubmit,
    );
}

function hpoints_submit_allowed($huser){
    //DEBUG
    //drupal_set_message('hpoints_submit allowed: '.$huser['name'],'warning');
    if(!$huser){
        return t('Failed to load your profile.');
    }elseif($huser['continuation']['status'] > 2){
        return t('You are not active in the Honors Program');
    }else{
        return 'ok';
    }
}
