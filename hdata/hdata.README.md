hData
=====

Purpose
-------
hData provides a database API to other modules in the Honors Drupal Suite
which allows the modules that depend on this module to ignore the inner
structure of the Honors Database (which is subject to change at any time)

Implementation Details
----------------------
This module contains a `.install` file that defines all the database tables
used by the Honors Drupal Suite.  Some of these tables are new for Drupal
and some are legacy tables.

The API is exposed through the `.module` file.  For nearly every table,
there are load/save functions which operate on PHP associative arrays.

Additionally, for development purposes, a very basic testing page is
provided.  This will be removed in future releases.

Files
-----
`hdata.info`
`hdata.install`
`hdata.module`
