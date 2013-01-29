Annotations
==

hdata/hnews/hnews.module
--

```
 175	:    //TODO: (Maybe) make a way for users to opt out of certain types of mailings.
 176	-    array_walk($recipients,'_hnews_to_email');
 177	-    
 178	-    //load the node and send it
--
 193	:    //TODO: (Maybe) add a way to have users input a preferred email address
 194	:    //NOTE: This is probably a must for faculty... not so much students.
 195	-    $element .= '@rit.edu';
 196	-}
 197	-
```

hdata/hpoints/hpoints.module
--

```
  47	:    //TODO: needs two pages (as tabs) one for types
  48	-    $items['admin/settings/hpoints'] = array(
  49	-        'title' => 'hPoints Settings',
  50	-        'description' => 'Adjust the points form settings.',
```

hdata/hpoints/hpoints.form.inc
--

```
   3	://NOTES:
   4	-//this is a quick todo list
   5	-// 2 - create page to edit h_points_menu (this would be in hpoints.admin.inc)
   6	-
--
  95	:        //OPTION: Use ctools bulk api?
  96	-        foreach($users as $student){
  97	-            $s = array('username' => $student);
  98	-            if(hdata_user_is_active_student($s)){
```

hdata/hpoints/hpoints.admin.inc
--

```
   7	:    //TODO: add better descriptive text
   8	:    //TODO: create a "real" form instead of a system settings form
   9	-    //    for the type options: make it a separate tab.
  10	-    // !! we could use ctools AJAX!  We've already gots deps on it.
  11	-    $form['hpoints_form_type_options'] = array(
```

hdata/hpoints/hpoints.views.inc
--

```
  51	:        //TODO: test that this works
  52	-        'username' => array(
  53	-            'title' => t('User'),
  54	-            'help' => t('The user to whom these points belong.'),
```

hdata/hcomplearn/hcomplearn.form.inc
--

```
   2	://TODO: hcomplearn should use hformtools
   3	-//  This means replacing the "faked" HTML5 number fields with fields of
   4	-//  type 'hformtools_html5_number'
   5	-//  Other changes may also be in order.
```

hdata/hdata.module
--

```
  48	://TODO: make this a system variable
  49	-function hdata_user_cache_life(){return '1 month';}
  50	-
  51	-/* id should be uid if $draft is true */
--
 425	:    //OPTION:  cache??
 426	-    $rs = db_query("SELECT id, title, description,sorting as weight, enabled, send_email
 427	-            FROM {h_points_menu} WHERE %d OR enabled=1",$enabled?0:1);
 428	-    $list = array();
```
