Annotations
==

hdata/hnews/hnews.module
--

```
  99	:        //TODO: make this function
 100	:        //TODO: add dependancy on hdata
 101	-        $recipients = hdata_student_list();
 102	-        if($faculty){
 103	-            $recipients += hdata_faculty_list();
```

hdata/hcomplearn/hcomplearn.module
--

```
  34	:    //TODO: write docs
  35	-
  36	-    //AJAX callback
  37	-    $items['hcomplearn/submission/%'] = array(
--
 145	://TODO: add permissions checks for approve and reject
 146	-
 147	-function hcomplearn_approve_cl_action($submission){
 148	-    $id = $submission['id'];
```

hdata/hcomplearn/hcomplearn.form.inc
--

```
  20	: //TODO: add field 'hours' and field 'type'
  21	-function hcomplearn_forms_cl(&$form_state,$page){
  22	-    if(isset($form_state['storage']['page'])
  23	-            && isset($form_state['storage']['data']['count'])){
--
 309	:        //TODO: make this configurable
 310	-        '#options' => array(
 311	-            'om' => 'OM',
 312	-            'ra' => 'RA',
--
 396	:        //TODO: make this configurable
 397	-        $maysubmitmsg = t('If you are satisfied with your submission,
 398	-            you may submit the form now by clicking the button below.');
 399	-        $submitwarning = '<p><strong>'.
```

hdata/hdata.module
--

```
  19	://WARNING:  THIS MODULE DOES NOT DO PERMISSION CHECKS!
  20	-
  21	-/* Returns a user array. $user = array('uid => 0, 'name => '') */
  22	://TODO: second argument "true" only for testing
  23	-function hdata_user_load($user){return _hdata_user_load($user,true);}
  24	-/* Saves the basic and continuation elements.  $user is a modified
  25	- * object from hdata_user_load */
--
  28	://TODO: make this a system variable
  29	-function hdata_user_cache_life(){return '1 month';}
  30	-
  31	-/* id should be uid if $draft is true */
--
 492	://TODO: implement list functions
 493	-function _hdata_student_list($college,$active){
 494	-    //if college is null, load all colleges
 495	-    //if active is false, load all statuses
```
