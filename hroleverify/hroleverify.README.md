hRoleVerify
===========

Purpose
-------
hRoleVerify allows linking the status field of the student and faculty
tables in the Honors Program database to Drupal roles.

Implementation Details
----------------------
The module works by providing a Drupal block which is shown to users
who do not have the Drupal roles "Faculty" or "Honors."  On that block
is a short message and a link to click to have the module check permissions.

When the link is clicked, the module checks the database and adds the
appropriate role to the user.

Files
-----
`hroleverify.info`
`hroleverify.module`
