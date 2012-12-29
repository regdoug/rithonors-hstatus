<?php
/*
 * hcomplearn.admin.inc
 */

function hcomplearn_admin_settings(){
    $form['hcomplearn_date_open'] = array(
        '#type' => 'date',
        '#title' => t('Submissions Start On'),
        '#description' => t('On this date at 12:00AM, the complearning from will open'),
        '#default_value' => variable_get('hcomplearn_date_open',null),
    );
    $form['hcomplearn_date_close'] = array(
        '#type' => 'date',
        '#title' => t('Submissions End On'),
        '#description' => t('On this date at 11:59PM, the complearning from will close'),
        '#default_value' => variable_get('hcomplearn_date_close',null),
    );
    $form['hcomplearn_form_type_options'] = array(
        '#type' => 'textarea',
        '#title' => t('Activity Types'),
        '#description' => t('Students will be allowed to chose from these types when submitting their complearning.  Format is "machine_key | Human Readable Name"'),
        '#default_value' => variable_get('hcomplearn_form_type_options',_hcomplearn_default_type_options()),
        '#element_validate' => array('hcomplearn_admin_settings_form_type_options_validate'),
        '#required' => true,
    );
    $form['submitmessages'] = array(
        '#type' => 'fieldset',
        '#title' => 'Submission Messages',
        '#description' => t('The following messages will be shown on the final page of the submission form.'),
    );
    $form['submitmessages']['hcomplearn_form_submitmsg'] = array(
        '#type' => 'textarea',
        '#title' => 'Message',
        '#description' => t('What do you want to tell students before they submit their complearning?'),
        '#default_value' => variable_get('hcomplearn_form_submitmsg',HCOMPLEARN_SUBMIT_MSG),
    );
    $form['submitmessages']['hcomplearn_form_submitwarn'] = array(
        '#type' => 'textarea',
        '#title' => 'Warning',
        '#description' => t('The warning is to tell the student that they may only recieve one chance to submit.'),
        '#default_value' => variable_get('hcomplearn_form_submitwarn',HCOMPLEARN_SUBMIT_WARN),
    );
        
    return system_settings_form($form);
}

function hcomplearn_admin_settings_validate($form, &$form_state) {
    $open = $form_state['values']['hcomplearn_date_open'];
    $close = $form_state['values']['hcomplearn_date_close'];
    $opentime = strtotime("{$open['year']}-{$open['month']}-{$open['day']}");
    $closetime = strtotime("{$close['year']}-{$close['month']}-{$close['day']}");
    if($closetime <= $opentime){
        form_set_error('hcomplearn_date_close',t('Close date must be after open date.'));
    }
}

function hcomplearn_admin_settings_form_type_options_validate($element, &$form_state) {
    if (empty($element['#value'])) {
        form_error($element, t('You must enter at least one option.'));
    }else{
        $lines = explode("\r\n",$element['#value']);
        foreach($lines as $line){
            if(!empty($line) && !preg_match('/^\\w+\\s*\\|.*$/',trim($line))){
                form_error($element, t('Error on line: %line. Please follow the format "machine_key | Human Readable Name" for type options',array('%line'=>$line)));
                break;
            }
        }
    }
}
