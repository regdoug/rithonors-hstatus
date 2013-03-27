<?php
/*
 * hcomplearn.admin.inc
 */

function hpoints_admin_settings(){
    //TODO: add better descriptive text
    //TODO: create a "real" form instead of a system settings form
    //    for the type options: make it a separate tab.
    // !! we could use ctools AJAX!  We've already gots deps on it.
    $form['submitmessages'] = array(
        '#type' => 'fieldset',
        '#title' => 'Submission Messages',
        '#description' => t('The following messages will be shown on the submission form.'),
    );
    $form['submitmessages']['hpoints_form_submitmsg'] = array(
        '#type' => 'textarea',
        '#title' => 'Message',
        '#description' => t('This text will appear at the top of the points form.'),
        '#default_value' => variable_get('hpoints_form_submitmsg',HPOINTS_SUBMIT_MSG),
    );
    $form['submitmessages']['hpoints_form_submitwarn'] = array(
        '#type' => 'textarea',
        '#title' => 'Warning',
        '#description' => t('This text will appear just before the submit button on the points form.'),
        '#default_value' => variable_get('hpoints_form_submitwarn',HPOINTS_SUBMIT_WARN),
    );
    $form['submitmessages']['hpoints_form_emailmsg'] = array(
        '#type' => 'textarea',
        '#title' => 'Message',
        '#description' => t('This text will appear at the top of the reference information form.'),
        '#default_value' => variable_get('hpoints_email_msg',HPOINTS_EMAIL_MSG),
    );
        
    return system_settings_form($form);
}

/*function hpoints_admin_settings_validate($form, &$form_state) {
    $open = $form_state['values']['hpoints_date_open'];
    $close = $form_state['values']['hpoints_date_close'];
    $opentime = strtotime("{$open['year']}-{$open['month']}-{$open['day']}");
    $closetime = strtotime("{$close['year']}-{$close['month']}-{$close['day']}");
    if($closetime <= $opentime){
        form_set_error('hpoints_date_close',t('Close date must be after open date.'));
    }
}*/

function hpoints_admin_settings_form_type_options_validate($element, &$form_state) {
    if (empty($element['#value'])) {
        form_error($element, t('You must enter at least one option.'));
    }else{
        $lines = explode("\r\n",$element['#value']);
        foreach($lines as $line){
            if(!empty($line) && !preg_match('/^[1-9]+[0-9]*\\s*\\|.*$/',trim($line))){
                form_error($element, t('Error on line: %line. Please follow the format "integer_id | Human Readable Name" for type options',array('%line'=>$line)));
                break;
            }
        }
    }
}
