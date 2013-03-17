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
3. hformtools - Provides new elements for forms.
4. hnews - Provides a way to send rich-text emails to Honors Program members.
4. hnotesystem - Accesses continuation notes.
5. hpoints - Provides both individual and bulk points submission forms.
5. hstatus - Adds the "MyStatus" page to Drupal user accounts.
6. hstudent - Provides Student Search and Student History functionality.
7. hvite - The Honors invitation module.

Module Dependencies
-------------------
1. Drupal 6
2. CCK (content)
3. Chaos Tools (ctools)
4. Colorbox (colorbox) *The colorbox library must also be installed*
4. Date (date)
4. jQuery UI (jquery_ui)
4. jQuery Update (jquery_update)
5. Mime Mail (mimemail)
6. Views (views)
7. Views Bulk Operations (views_bulk_operations)
