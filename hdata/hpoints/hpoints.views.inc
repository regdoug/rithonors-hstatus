<?php

/**
 * Implements hook_views_handlers to register our handlers with Views
 */
function hpoints_views_handlers(){
    $retval['handlers'] = array(
        //the name of our handler
        'hpoints_views_handler_field_status' => array(
            //the parent class of our handler
            'parent' => 'views_handler_field',
            //the file our handler is located in
            'file' => 'hpoints_views_handler_field_status.inc',
        ),
        'hpoints_views_handler_field_type' => array(
            'parent' => 'views_handler_field',
            'file' => 'hpoints_views_handler_field_type.inc',
        ),
        'hpoints_views_handler_filter_cl_status' => array(
            'parent' => 'views_handler_filter_in_operator',
            'file' => 'hpoints_views_handler_filter_cl_status.inc',
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
function hpoints_views_data(){
    $group = t('Honors');
    $base = array(
        'field' => 'id',
        'title' => t('Points Submissions'),
        'help' => t('Honors points submissions'),
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
        //TODO: test that this works
        'username' => array(
            'title' => t('User'),
            'help' => t('The user to whom these points belong.'),
            'relationship' => array(
                'base' => 'user',
                'base field' => 'name',
                // 'field' => 'uid' apparently not needed.
                'handler' => 'views_handler_relationship',
                'label' => t('User'),
                'title' => t('User'),
                'help' => t('This the user who owns the submission.'),
            ),
        ),
        //Note the custom handlers to translate the numbers to status strings.
        'pointID' => array(
            'title' => t('Submission Type'),
            'field' => array(
                'handler' => 'hpoints_views_handler_field_type',
                'click sortable' => TRUE,
            ),
            'sort' => array(
                'handler' => 'views_handler_sort',
            ),
        ),
        'explanation' => array(
            'title' => t('Description'),
            'help' => t('Why the points should granted.'),
            'field' => array(
                'handler' => 'views_handler_field',
            ),
        ),
        'submitted' => array(
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
        'submittedBy' => array(
            'title' => t('Submitter'),
            'help' => t('User who created this submission.  May be different than User.'),
            'relationship' => array(
                'base' => 'user',
                'base field' => 'name',
                // 'field' => 'uid' apparently not needed.
                'handler' => 'views_handler_relationship',
                'label' => t('Submitter'),
                'title' => t('Submitter'),
                'help' => t('The user that submitted the entry.'),
            ),
        ),
        'approved' => array(
            'title' => t('Submission Status'),
            'field' => array(
                'handler' => 'hpoints_views_handler_field_status',
                'click sortable' => TRUE,
            ),
            'filter' => array(
                'handler' => 'hpoints_views_handler_filter_cl_status',
            ),
            'sort' => array(
                'handler' => 'views_handler_sort',
            ),
        ),
        'approvedBy' => array(
            'title' => t('Reviewer'),
            'help' => t('The user who reviewed this submission.'),
            'relationship' => array(
                'base' => 'user',
                'base field' => 'name',
                // 'field' => 'uid' apparently not needed.
                'handler' => 'views_handler_relationship',
                'label' => t('Reviewer'),
                'title' => t('Reviewer'),
                'help' => t('The user that reviewed this submission.'),
            ),
        ),
        'approvedTime' => array(
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
        'declinedReason' => array(
            'title' => t('Reason'),
            'help' => t('Why the points were not approved.'),
            'field' => array(
                'handler' => 'views_handler_field',
            ),
        ),
        'numPoints' => array(
            'title' => t('Points Granted'),
            'help' => t('Number of credits awarded to this submission'),
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
    $data['h_students_points'] = $fields;
    $data['h_students_points']['table']['base'] = $base;
    $data['h_students_points']['table']['group'] = $group;
    return $data;
}
