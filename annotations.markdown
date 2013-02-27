Annotations
==

.git/objects/2d/e1bb1aec8e76aba9b5d7f2962caecbc7ac6c46
--

```
Binary file .git/objects/2d/e1bb1aec8e76aba9b5d7f2962caecbc7ac6c46 matches
```

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

hdata/hvite/hvite.module
--

```
 164	:	//QUESTION:  why a form?  why not a regular page?
 165	-	//return drupal_get_form('hvite_eventlist_form');
 166	-	return '<p>Under Development</p>';
 167	-}
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
  88	://DEBUG: Remove before beta testing
  89	-function hdata_menu(){
  90	-    return array(
  91	-        'testhdata' => array(
--
 438	:    //OPTION:  cache??
 439	-    $rs = db_query("SELECT id, title, description,sorting as weight, enabled, send_email
 440	-            FROM {h_points_menu} WHERE %d OR enabled=1",$enabled?0:1);
 441	-    $list = array();
```

hdata/hformtools/hformtools.module
--

```
 100	:    //DEBUG:  Remove for beta release
 101	-    $menu['hformtools/test'] = array(
 102	-        'title' => 'Test hFormTools',
 103	-        'page callback' => 'drupal_get_form',
```

hdata/hnotesystem/hnotesystem.module
--

```
   9	://NOTE: deleted block stuff.  I don't think it is needed. Reggie 2/27
  10	-
  11	-/**
  12	-* This will allow you to restrict certain actions of the module to certain roles
--
  22	://TODO: add real help
  23	-function hnotesystem_help($path, $arg)
  24	-{
  25	-	switch($path) {
--
 105	:			//TODO: create theme functions
 106	-		}
 107	-	}
 108	-	else
--
 123	:	//NOTE: see how to create links below
 124	-	$content = l('Create Note','hnotesystem/form/create').'<br />';
 125	-	$content .= l('Edit Note','hnotesystem/form/edit').'<br />';
 126	-	$content .= l('Delete Note','hnotesystem/form/delete').'<br />';
--
 134	://QUESTION: Why would $idOrName ever be a name?
 135	-function _hnotesystem_gen_form($type, $idOrName)
 136	-{
 137	-	global $user;
--
 142	:	//QUESTION:  I'm not quite sure what this accomplishes.  Odds are the
 143	-	//  user will have no clue what the id is.
 144	-	//
 145	-	//  I've just blocked the form from generating if the param type is wrong.
--
 158	:			//COMMENT: Nothing to put here after deleting a note!
 159	:			//QUESTION:  Why not have an "Are you sure" message?
 160	-			$form['confirm_msg'] = array(
 161	-				'#value' => t('Are you sure you want to delete Note @id "@title"',
 162	-						array('@id'=>$idOrName,'@title'=>$note['title'])),
--
 204	:			//Q: Should these fields be auto-generated?
 205	:			//ANS: yes, probably
 206	-			$form['date'] = array(
 207	-				'#type' => 'date',
 208	-				'#title' => t('Date'),
--
 220	:		//Q: What is cont_id?
 221	:		//ANS: the school year in which the note was created
 222	-		
 223	-	}
 224	-	
--
 264	:	//NOTE: always use $form_state['values'].  It has been checked to
 265	-	//  ensure that hacking attempts are squelched.
 266	-	$note = _hnotesystem_form_to_note($form_state['values']);
 267	-	// $note['id'] is left blank so a new note is created.
--
 275	://NOTE: form_state['storage'] is really inteded for multi-page forms
 276	-function hnotesystem_edit_note_form(&$form_state, $param = "")
 277	-{
 278	-	return _hnotesystem_gen_form("edit", $param);
```
