Honors Drupal Suite
===================

Purpose
-------
These Drupal 6 modules provide functionality essential to the operation
of the Honors Program website which cannot be duplicated by third-party
modules, either due to the complexity of task which must be perfomed, by
the performance restrictions of third-party modules, or due to interoperability
requirements with the Honors Program student database.

Included Modules
----------------
1. hroleverify - Interfaces with the Honors database to automatically add
        Drupal roles to users
2. hdata - Database API module.  Used by all following modules:
3. hcomplearn - Provides a form for submission and review of complementary learning.
4. hnews - Provides a way to send rich-text emails to Honors Program members
5. hstatus - Adds the "MyStatus" page to Drupal user accounts.

Module Dependencies
-------------------
1. Drupal 6
2. CCK (content)
3. Chaos Tools (ctools)
4. Colorbox (colorbox) *The colorbox library must also be installed*
5. Mime Mail (mimemail)
6. Views (views)
7. Views Bulk Operations (views_bulk_operations)
