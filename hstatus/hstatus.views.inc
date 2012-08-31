<?php
/**
 * Implements hook_views_data (I think)
 */
function hstatus_views_data(){
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
        //TODO: implement custom handler to translate the numbers.
        'status' => array(
            'title' => t('Submission Status'),
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
