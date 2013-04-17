Annotations
==

.git/objects/2d/e1bb1aec8e76aba9b5d7f2962caecbc7ac6c46
--

```
Binary file .git/objects/2d/e1bb1aec8e76aba9b5d7f2962caecbc7ac6c46 matches
```

hdata/hstudent/hstudent.module
--

```
  12	:	//TODO: users with no View permissions will not get links on the search page
  13	:	//TODO: checking active/inactive permissions
  14	-}
  15	-
  16	-/*
--
 125	:		//DEBUG:
 126	-		//drupal_set_message("t_p_h_r called, firstname=".$student_info['basic']['name']['firstname']);
 127	-		
 128	-		if($student_info['basic']['legacy']){
--
 152	:	//DEBUG:
 153	-	// drupal_set_message("leaving t_p_h_r: vars=".print_r($variables, TRUE));
 154	-}
 155	-
```

hdata/hnews/hnews.module
--

```
 179	:    //TODO: (Maybe) make a way for users to opt out of certain types of mailings.
 180	-    array_walk($recipients,'_hnews_to_email');
 181	-    
 182	-    //load the node and send it
--
 197	:    //TODO: (Maybe) add a way to have users input a preferred email address
 198	:    //NOTE: This is probably a must for faculty... not so much students.
 199	-    $element .= '@rit.edu';
 200	-}
 201	-
```

hdata/hpoints/hpoints.module
--

```
  48	:    //TODO: needs two pages (as tabs) one for types
  49	-    $items['admin/settings/hpoints'] = array(
  50	-        'title' => 'hPoints Settings',
  51	-        'description' => 'Adjust the points form settings.',
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
  11	-    $form['submitmessages'] = array(
```

hdata/hpoints/hpoints.views.inc
--

```
  51	:        //TODO: test that this works
  52	-        'username' => array(
  53	-            'title' => t('User'),
  54	-            'help' => t('The user to whom these points belong.'),
```

hdata/hcomplearn/hcomplearn.module
--

```
 232	://TODO: these accept/reject VBO interfaces will probably be the same
 233	-// for hcomplearn, hpoints, (the future) happlications, etc.  They
 234	-// probably should end up being merged.
 235	-function hcomplearn_reject_cl_action_form($context){
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
  48	-/** Loads a faculty member from the CCK fields of the 'contact' node type */
--
  54	://TODO: make this a system variable
  55	-function hdata_faculty_cache_life() {return '1 month';}
  56	-
  57	-/* id should be uid if $draft is true */
--
 105	://DEBUG: Remove before beta testing
 106	-function hdata_menu(){
 107	-    return array(
 108	-        'testhdata' => array(
--
 469	:    //OPTION:  cache??
 470	-    $rs = db_query("SELECT id, title, description,sorting as weight, enabled, send_email
 471	-            FROM {h_points_menu} WHERE %d OR enabled=1",$enabled?0:1);
 472	-    $list = array();
--
 953	:    //TODO: make setting for name of fields involved
 954	-    //D7: will need to be revamped
 955	-    $field = content_fields('field_username');
 956	-    $field_info = content_database_info($to_field);
--
1027	:    //DEBUG:
1028	-    drupal_set_message('basic_info: uid='.$userinfo['uid'].' name='.$userinfo['name']);
1029	-    $return['username'] = $userinfo['name'];
1030	-    $return['uid'] = @$userinfo['uid'];
--
1038	:    //DEBUG:
1039	-	drupal_set_message($return['name'].' is a student');
1040	-	return $return;
1041	-    }else{
--
1046	:    //DEBUG:
1047	-	    drupal_set_message($return['name'].' is a faculty member');
1048	-	    return $return;
1049	-	}
--
1053	:    //DEBUG:
1054	-    drupal_set_message($return['username'].' was not found');
1055	-    return $return;
1056	-}
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
 104	:			//TODO: create theme functions
 105	-		}
 106	-	}
 107	-	else
--
 122	:	//NOTE: see how to create links below
 123	-	$content = l('Create Note','hnotesystem/form/create').'<br />';
 124	-	$content .= l('Edit Note','hnotesystem/form/edit').'<br />';
 125	-	$content .= l('Delete Note','hnotesystem/form/delete').'<br />';
--
 133	://QUESTION: Why would $idOrName ever be a name?
 134	-function _hnotesystem_gen_form($type, $idOrName)
 135	-{
 136	-	global $user;
--
 141	:	//QUESTION:  I'm not quite sure what this accomplishes.  Odds are the
 142	-	//  user will have no clue what the id is.
 143	-	//
 144	-	//  I've just blocked the form from generating if the param type is wrong.
--
 157	:			//COMMENT: Nothing to put here after deleting a note!
 158	:			//QUESTION:  Why not have an "Are you sure" message?
 159	-			$form['confirm_msg'] = array(
 160	-				'#value' => t('Are you sure you want to delete Note @id "@title"',
 161	-						array('@id'=>$idOrName,'@title'=>$note['title'])),
--
 203	:			//Q: Should these fields be auto-generated?
 204	:			//ANS: yes, probably
 205	-			$form['date'] = array(
 206	-				'#type' => 'date',
 207	-				'#title' => t('Date'),
--
 219	:		//Q: What is cont_id?
 220	:		//ANS: the school year in which the note was created
 221	-		
 222	-	}
 223	-	
--
 263	:	//NOTE: always use $form_state['values'].  It has been checked to
 264	-	//  ensure that hacking attempts are squelched.
 265	-	$note = _hnotesystem_form_to_note($form_state['values']);
 266	-	// $note['id'] is left blank so a new note is created.
--
 274	://NOTE: form_state['storage'] is really inteded for multi-page forms
 275	-function hnotesystem_edit_note_form(&$form_state, $param = "")
 276	-{
 277	-	return _hnotesystem_gen_form("edit", $param);
```

hdata/hstatus/hstatus.pages.inc
--

```
  94	:            //TODO: create theme functions for courses, points and submissions
  95	-            $variables['courses']= $huser['courses'];
  96	-            $variables['points']=$huser['points'];
  97	-            $variables['submissions']=$huser['submissions'];
```
