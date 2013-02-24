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
  97	:        //OPTION: Use ctools bulk api?
  98	-        foreach($users as $student){
  99	-            if(!empty($student)){
 100	-                if(hdata_user_is_active_student($student)){
--
 191	:    //DEBUG:
 192	-    $form['debug_lastsub'] = array(
 193	-        '#prefix' => '<pre>',
 194	-        '#suffix' => '</pre>',
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
  45	://TODO: make this a system variable
  46	-function hdata_user_cache_life(){return '1 month';}
  47	-
  48	-/* id should be uid if $draft is true */
--
  86	://DEBUG: Remove before beta testing
  87	-function hdata_menu(){
  88	-    return array(
  89	-        'testhdata' => array(
--
 440	:    //OPTION:  cache??
 441	-    $rs = db_query("SELECT id, title, description,sorting as weight, enabled, send_email
 442	-            FROM {h_points_menu} WHERE %d OR enabled=1",$enabled?0:1);
 443	-    $list = array();
```

hdata/hformtools/hformtools.module
--

```
 100	:    //DEBUG:  Remove for beta release
 101	-    $menu['hformtools/test'] = array(
 102	-        'title' => 'Test hFormTools',
 103	-        'page callback' => 'drupal_get_form',
```
