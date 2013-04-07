<?php
//TODO: hcomplearn should use hformtools
//  This means replacing the "faked" HTML5 number fields with fields of
//  type 'hformtools_html5_number'
//  Other changes may also be in order.

/**
 * Convenience function to build complearning form
 */

function hcomplearn_build_clform(){
    $isopen = hcomplearn_form_is_open();
    if($isopen['result']){
        return drupal_get_form('hcomplearn_forms_cl',(func_num_args() > 0)?func_get_arg(0):'first',$isopen['close']);
    }else{
        if(time()<$isopen['open']){
            return t('The form will open for submissions on @date',array('@date'=>strftime('%B %e, %Y',$isopen['open'])));
        }else{
            return t('Sorry, the form stopped accepting submissions on @date',array('@date'=>strftime('%B %e, %Y',$isopen['close'])));
        }
    }
}

/**
 * Complearning form
 *
 * $form_state['storage'] is used to store three things:
 *  1. the $data array      ['data']
 *  2. the page to load     ['page']
 *  3. the activity count   ['count']
 */

function hcomplearn_forms_cl(&$form_state,$page,$closetime){
    if(isset($form_state['storage']['page'])
            && isset($form_state['storage']['data']['count'])){
        $data = $form_state['storage']['data'];
        $page = $form_state['storage']['page'];
    }else{
        $data = _hcomplearn_loaddata();
        $form_state['storage']['data'] = $data;
        $form_state['storage']['page'] = $page;
    }

    //ensure that data is loaded if we are going to a page other than 'first'
    if(isset($data['count']) && intval($data['count']) > 0){
        $form_state['storage']['count'] = $data['count'];
    }else{
        //DEBUG, but possibly useful anyway...
        if($page != 'first')drupal_set_message(t('Number of activities unknown.  Going to first page'));
        $page = 'first';
    }

    $form = array();
    $form['closedate'] = array(
        '#value' => t('This form will close on @date',array('@date'=>strftime('%B %e, %Y',$closetime))),
    );
    $n = intval($page);

    //if $page is a string, $n will be 0
    if($n > 0){
        //$form = array();
        _hcomplearn_page_n($n,$form,$data);
        return $form;
    }

    if($page == 'last'){
        //last page
        global $user;
        $huser = hdata_user_load(array('uid'=>$user->uid,'name'=>$user->name));
        _hcomplearn_page_last($form,$huser,$data);
    }else{
        //first page -- acts as a catch-all, rather than returning a 404
        $form['page'] = array(
            '#type' => 'value',
            '#value' => 'first',
        );
        $form['count'] = array(
            '#type' => 'textfield',
            '#title' => t('Activities'),
            '#description' => t('Number of activities that compose this submission.'),
            '#required' => true,
            '#element_validate' => array('hcomplearn_form_cl_int_validate'),
            '#default_value' => (isset($data['count']))?$data['count']:1,
            //HTML5 attributes
            '#attributes' => array('min' => '1'),
            '#post_render' => array('hcomplearn_number'),
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
    }
    return $form;
}

/**
 * Processes an input element from a plain textfield to an HTML5
 * "number" textfield
 */

function hcomplearn_number($html,$elements){
    $html = str_replace('type="text"','type="number"',$html);
    return $html;
}

/**
 * Validates the count field on the first page of the form
 */
function hcomplearn_form_cl_int_validate($element, &$form_state){
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
 * hcomplearn_forms_cl_submit
 *
 * Called whenever the form is submitted.
 * This function does not actually handle the data but instead passes
 * it on to helper functions.
 */

function hcomplearn_forms_cl_submit($form, &$form_state){
    $page = $form_state['values']['page'];
    $back = ($form_state['clicked_button']['#id'] == 'back');

    if(is_numeric($page)){
        _hcomplearn_savepage($form_state,$back);
    }elseif($page == 'first'){
        _hcomplearn_newentry($form_state);
    }elseif($page == 'last'){
        if($back){
            _hcomplearn_redirect($form_state,$form_state['storage']['count'],false);
        }else{
            _hcomplearn_savefinal($form_state);
        }
    }else{
        _hcomplearn_redirect($form_state,false,false);
    }
}

//====================================
//===== Private/Helper Functions =====
//====================================

/* CONTENTS (in order)
 *
 * _hcomplearn_newentry
 * _hcomplearn_savepage
 *             ..._savefinal
 *             ..._saveandredirect
 *             ..._redirect
 *             ..._page_n
 *             ..._loaddata
 */

//note the Drupal convention of making
//"private" functions start with an underscore

/*
 * Helper function for the first page
 */
function _hcomplearn_newentry(&$form_state){
    global $user;
    if(isset($form_state['storage']['data']['count'])){
        $data = $form_state['storage']['data'];
    }else{
        $data = _hcomplearn_loaddata();
    }

    $n = $form_state['values']['count'];
    $form_state['storage']['count'] = $n;
    $data['count'] = $n;

    _hcomplearn_saveandredirect($form_state,$data,1);
}

/*
 * Helper for all pages except first and last
 */

function _hcomplearn_savepage(&$form_state,$back=false){

    $data = $form_state['storage']['data'];
    if(!isset($data['count'])){
        $data = _hcomplearn_loaddata();
    }

    $vals = $form_state['values']; //note that PHP arrays are NOT assigned by reference
    $n = $vals['page'];
    unset($vals['page']);

    $data[$n] = $vals;

    $nextpage = $back?'<':'>';
    _hcomplearn_saveandredirect($form_state,$data,$nextpage);
}

/*
 * Helper for last page
 */
function _hcomplearn_savefinal(&$form_state){
    global $user;
    //sending true to hdata_cl_load tells it to load a draft
    $sub = hdata_cl_load($user->uid,true);
    $d = $sub['data'];
    //strips out unnecessary information in the data field.
    //This is necessary b/c the form is lazy and stores all the
    //form build keys and suchlike
    for($i = 0; $i < $d['count']; $i++){
        foreach ($d[$i] as $key => $val) {
            $whitelist = _hcomplearn_fields();
            if(!in_array($key,$whitelist)){
                unset($d[$i][$key]);
            }
        }
    }
    //when we pretend that the draft we just loaded is a submission
    //(by passing false) hdata_cl_save automagically converts and saves
    //it as a full-fledged submission.
    if(hdata_cl_save($sub,false)){
        drupal_set_message(t('Complementary Learning sucessfully submitted.'));
        unset($form_state['storage']);
        unset($form_state['rebuild']);
        $form_state['redirect'] = '<front>';
    }else{
        drupal_set_message(t('Failed to submit Complementary Learning.'),'error');
        _hcomplearn_redirect($form_state,'last',false);
    }
}

/*
 * Saves the $data passed to it and calls the redirect helper
 * with $page if it is successful.  If unsucessful, the redirect
 * helper is called with false.
 */

function _hcomplearn_saveandredirect(&$form_state,$data,$page){
    global $user;
    $sub = hdata_cl_load($user->uid,true);
    $sub['data'] = $data;
    $success = hdata_cl_save($sub,true);
    if($success)$form_state['storage']['data'] = $data;
    $page = ($success)?$page:false;
    _hcomplearn_redirect($form_state,$page);
}

/*
 * The redirect helper.
 *
 * Not actually a true redirect because the page doesn't change, but
 * will reload the form to the $page requested.  If $page is false,
 * the current page of the form is reloaded.
 */

function _hcomplearn_redirect(&$form_state,$page='>',$message=true){
    if($page == '>' || $page == '<'){
        $n = $form_state['storage']['page'];
        if(is_numeric($n)){
            if($page == '>'){
                $page = ($n < $form_state['storage']['count'])?$n+1:'last';
            }else{
                $page = ($n > 1)?$n-1:'first';
            }
        }else{
            $page = false;
        }
    }

    //message could be better.
    if($page){
        $form_state['storage']['page'] = $page;
        if($message){drupal_set_message(t('Data saved successfully'));}
    }else{
        $form_state['redirect'] = false;
        if($message){drupal_set_message(t('Failed to save data.').$page,'error');}
    }
}

//helper function for validation and default values
function _hcomplearn_fields(){
    //remember to change this if the field names change
    return array('type','hours','name','desc','time','contact','comment');
}

/*
 * Generates normal (not first or last) pages
 */
function _hcomplearn_page_n($n,&$form,$data){
    $form['page'] = array(
        '#type' => 'value',
        '#value' => $n,
    );
    $form['heading'] = array(
        '#value' => '<h3>'.t('Activity !n',array('!n'=>$n)).'</h3>',
    );
    $whitelist_nid = hcomplearn_get_whitelist_nid();
    if(is_numeric($whitelist_nid)){
        $form['whitelist'] = array(
            '#value' => l('Whitelist/Blacklist','node/'.$whitelist_nid),
        );
    }
    $form['type'] = array(
        '#title' => t('Type of Activity'),
        '#type' => 'select',
        '#options' => hcomplearn_get_type_options(),
        '#default_value' => 'other',
    );
    $form['hours'] = array(
        '#title' => t('Hours Spent'),
        '#type' => 'textfield',
        '#size' => 5,
        '#maxlength' => 2,
        '#required' => true,
        '#element_validate' => array('hcomplearn_form_cl_int_validate'),
        //HTML5 attributes
        '#attributes' => array('min' => '0', 'max' => '50', 'step' => '1'),
        '#post_render' => array('hcomplearn_number'),
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
    $fields = _hcomplearn_fields();
    foreach($fields as $f){
        $form[$f]['#default_value'] = $data[$n][$f];
    }
}

function _hcomplearn_page_last(&$form,$huser,$data){
    /*
     * This function is mostly validation to make sure the user is allowed
     * to submit a complearning submission.  Most of these checks are in
     */

    // Loop through the data array to get total hours
    $hours = 0;
    for($i = 1; $i <= $data['count']; $i++){
        $hours += $data[$i]['hours'];
    }
    if($hours < hcomplearn_minhours()) {
        drupal_set_message(t('You need more than !h hours',array('!h'=>$hours)),'warning');
        $maysubmitmsg = $maysubmit = false;
    }elseif(($submitwarning = hcomplearn_submit_allowed($huser)) != 'ok'){
        $maysubmitmsg = $maysubmit = false;
    }else{
        $maysubmitmsg = variable_get('hcomplearn_form_submitmsg',HCOMPLEARN_SUBMIT_MSG);
        $submitwarning = '<p><strong>'.variable_get('hcomplearn_form_submitwarn',HCOMPLEARN_SUBMIT_WARN).'</strong></p>';
        $maysubmit = true;
    }
    $genericmessage = t('Your responses have been saved as a draft.
        They will be stored for up to @time.',
        array('@time' => hcomplearn_timetosave() ) );
    
    $form['page'] = array(
        '#type' => 'value',
        '#value' => 'last',
    );
    $form['info1'] = array(
        '#value' => $genericmessage,
        '#prefix' => '<p>',
        '#suffix' => '</p>',
        '#weight' => -15,
    );
    $form['info2'] = array(
        '#value' => $maysubmitmsg,
        '#prefix' => '<p>',
        '#suffix' => '</p>',
        '#weight' => -13,
    );
    $form['info3'] = array(
        '#value' => $submitwarning,
        '#prefix' => '<p><strong>',
        '#suffix' => '</strong></p>',
        '#weight' => -11,
    );
    $form['submission-fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t('Preview Submission'),
        '#collapsible' => true,
        '#collapsed' => true,
    );
    $form['submission-fieldset']['submission'] = array(
        '#value' => theme('hcomplearn_cl_activities',array('data' => $data)),
    );
    $form['back'] = array(
      '#type' => 'submit',
      '#value' => t('< Prev Page'),
      '#id' => 'back',
      '#weight' => 10,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Done, Submit Now'),
      '#disabled' => !$maysubmit,
      '#weight' => 10,
    );
}

function hcomplearn_submit_allowed($huser){
    if(!$huser){
        return t('Failed to load your profile.');
    }elseif($huser['continuation']['comp_learn'] == 1){
        return t('You have already completed Comp Learning for this year.');
    }elseif($huser['continuation']['status'] > 2){
        return t('You are not active in the Honors Program');
    }elseif(isset($huser['submissions']['complearn']) && is_array($huser['submissions']['complearn'])){
        foreach($huser['submissions']['complearn'] as $sub){
            if($sub['status'] == 0){
                return t('You already have a pending submission.');
            }elseif($sub['status'] == 1 && $sub['submit_time'] > strtotime('-'.hcomplearn_timetosave())){
                return t('You have already completed Comp Learning for this year.');
            }
        }
    }else{
        return 'ok';
    }
}


//this gets done often enough that it needs it's own helper function
function _hcomplearn_loaddata(){
    global $user;
    $sub = hdata_cl_load($user->uid,true);
    return $sub['data'];
}
