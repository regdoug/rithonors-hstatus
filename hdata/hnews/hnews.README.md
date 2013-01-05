hNews
=====

Purpose
-------
hNews is the module by which emails can be sent to the Honors Program.

hNews was written because existing third-party modules (of which there
are many) did not have high enough performance and interoperability with
the Honors Database.

Implementation Details
----------------------
The module works by hooking into CCK fields on specified node types.  Messages
are sent via the Drupal Mime Mail module (which hNews modifies slightly through
the Mime Mail API)

Files
-----
`hnews.info`
`hnews.install`
`hnews.module`
