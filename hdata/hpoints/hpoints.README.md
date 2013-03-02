hStatus
=======

Purpose
-------
hStatus adds a tab to the Drupal user account page.

Implementation Details
----------------------
This module is very simple, relying on `hdata` for databse calls and only
providing one page, the "My Status" page, which is rendered through the
Drupal theme layer by `hstatus.pages.inc` and `mystatus.tpl.php`.

Files
-----
`hstatus.info`
`hstatus.module`
`hstatus.pages.inc`
`mystatus.tpl.php`
