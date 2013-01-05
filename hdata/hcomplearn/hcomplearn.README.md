hComplearn
==========

Purpose
-------
To manage the submission and review of Complementary Learning (complearning),
an Honors Program requirement.

Implementation Details
----------------------
This module uses hdata for nearly all database calls.

For the submission of complearning, a custom form using the Drupal Form API (FAPI)
is provided by the module.  This form implements access controls based on
the Honors Database and upon open and close dates on the module settings page.
SQL injection is guarded against by adhering to the FAPI guidelines.  It
may at this time be possible to perform an XSS attack against the form. This
will be addressed in future releases.

The third-party Drupal module Views Bulk Operations (VBO), is used to facilitate
the reviewing phase.  For this purpose, the hcomplearn module exposes parts of
the Honors Database to Views throught the Views API.  Many of the files in this
module are involved in this process.

Files
-----
`clactivity.tpl.php` - Template used to theme submissions for display
`hcomplearn.admin.inc` - System Settings form
`hcomplearn.form.inc` - Complementary Learning form
`hcomplearn.info`
`hcomplearn.module` - Main file
`hcomplearn.views.inc` - Exposes database tables
`hcomplearn_views_handler_field_status.inc` - Tells views how to display the status field
`hcomplearn_views_handler_filter_cl_status.inc` - Tells views how to sort the status field
