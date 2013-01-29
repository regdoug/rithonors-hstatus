<?php
/**
 * hformtools_users.inc
 * 
 * Contains template preprocessor and AJAX callbacks for the form element
 * hformtools_users
 */

function template_preprocess_hformtools_users(&$variables){
    $thispath = drupal_get_path('module','hformtools').'/users';
    
    drupal_add_js($thispath.'/form-element-users.js');
    drupal_add_js(array('hFormToolsBasePath'=>base_path().$thispath),'setting');
    
    drupal_add_css($thispath.'/form-element-users.css');
    drupal_add_css($thispath.'/form-element-users-style.css');
    
    $e = $variables['element'];
    $e['#description'] .= ' ' . t('Please enter usernames separated by spaces');
    $e['#type'] = 'textarea';
    $variables['textarea_element'] = $e;
    
    $variables['ajaxtextfield_element'] = array(
        '#type' => 'textfield',
        '#title' => $e['#title'],
        '#description' => $e['#description'],
        '#attributes' => array('class' => 'ajax'),
    );
}

function hformtools_users_ajax_groups($group){
    $names = hdata_student_list($group);
    array_unshift($names,"[$group]");
    echo json_encode($names);
    return null;
}
