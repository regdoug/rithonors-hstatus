<?php
/**
 * Implements hook_views_handlers to register our handlers with Views
 */
function hcomplearn_views_handlers(){
    $retval['handlers'] = array(
        //the name of our handler
        'hcomplearn_views_handler_field_status' => array(
            //the parent class of our handler
            'parent' => 'views_handler_field',
            //the file our handler is located in
            'file' => 'hcomplearn_views_handler_field_status.inc',
        ),
        'hcomplearn_views_handler_filter_cl_status' => array(
            'parent' => 'views_handler_filter_in_operator',
            'file' => 'hcomplearn_views_handler_filter_cl_status.inc',
        ),
    );
    return $retval;
}

/**
 * Implements hook_views_data
 * 
 * Although this is something that could just as easily be in the hdata
 * module, I placed it here in hcomplearn because I feel that it would
 * get forgotten in hdata.
 */
function hcomplearn_views_data(){
    $group = t('Complearning');
    $base = array(
        'field' => 'id',
        'title' => t('Complearning Entries'),
        'help' => t('Current year complearning submissions'),
        'weight' => 0,
    );
    $fields = array(
        'id' => array(
            'title' => t('ID'),
            'help' => t('Submission ID'),
            'field' => array(
                'handler' => 'views_handler_field', 
                'click sortable' => false,
            ), 
        ),
        'uid' => array(
            'title' => t('Submitter'),
            'help' => t('The user who submitted this entry'),
            'relationship' => array(
                'base' => 'user',
                'base field' => 'uid',
                // 'field' => 'uid' apparently not needed.
                'handler' => 'views_handler_relationship',
                'label' => t('Submitter'),
                'title' => t('Submitter'),
                'help' => t('The user that submitted the entry.'),
            ),
        ),
        //Note the custom handler to translate the numbers to status strings.
        'status' => array(
            'title' => t('Submission Status'),
            'field' => array(
                'handler' => 'hcomplearn_views_handler_field_status', 
                'click sortable' => TRUE,
            ), 
            'filter' => array(
                'handler' => 'hcomplearn_views_handler_filter_cl_status',
            ), 
            'sort' => array(
                'handler' => 'views_handler_sort',
            ),
        ),
        'hours' => array(
            'title' => t('Total hours spent'), 
            'help' => t('Sum of the hours spent on each activity'), 
            'field' => array(
                'handler' => 'views_handler_field_numeric', 
                'click sortable' => TRUE,
            ), 
            'filter' => array(
                'handler' => 'views_handler_filter_numeric',
            ), 
            'sort' => array(
                'handler' => 'views_handler_sort',
            ),
        ),
        'types' => array(
            'title' => t('Types of activities performed'), 
            'help' => t('Types of activities as whitespace separated tags'), 
            'field' => array(
                'handler' => 'views_handler_field', 
                'click sortable' => true,
            ), 
            'sort' => array(
                'handler' => 'views_handler_sort',
            ), 
            'filter' => array(
                'handler' => 'views_handler_filter_string',
            ), 
            'argument' => array(
                'handler' => 'views_handler_argument_string',
            ),
        ),
        'submit_date' => array(
            'title' => t('Date Submitted'),
            'field' => array(
                'handler' => 'views_handler_field_date',
                'click sortable' => true,
            ),
            'sort' => array(
                'handler' => 'views_handler_sort_date',
            ),
            'filter' => array(
                'handler' => 'views_handler_filter_date',
            ),
        ),
        'review_date' => array(
            'title' => t('Date Reviewed'),
            'field' => array(
                'handler' => 'views_handler_field_date',
                'click sortable' => true,
            ),
            'sort' => array(
                'handler' => 'views_handler_sort_date',
            ),
            'filter' => array(
                'handler' => 'views_handler_filter_date',
            ),
        ),
        'reviewer_uid' => array(
            'title' => t('Reviewer'),
            'help' => t('The user who reviewed this entry'),
            'relationship' => array(
                'base' => 'user',
                'base field' => 'uid',
                // 'field' => 'uid' apparently not needed.
                'handler' => 'views_handler_relationship',
                'label' => t('Reviewer'),
                'title' => t('Reviewer'),
                'help' => t('The user that reviewed the entry.'),
            ),
        ),
    );
    $data['h_cl'] = $fields;
    $data['h_cl']['table']['base'] = $base;
    $data['h_cl']['table']['group'] = $group;
    return $data;
}
