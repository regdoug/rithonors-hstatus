Annotations
==

hdata/hnews/hnews.module
--

```
 154	:        //TODO: make this function
 155	:        //TODO: add dependancy on hdata
 156	-        $recipients = hdata_student_list();
 157	-        if($faculty){
 158	-            $recipients += hdata_faculty_list();
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
  38	://DEBUG:  this function is only for debugging
  39	-function hdata_init(){
  40	-    //menu_rebuild();
  41	-}
--
  52	://WARNING:  THIS MODULE DOES NOT DO PERMISSION CHECKS!
  53	-
  54	-/* Returns a user array. $userinfo = array('uid => 0, 'name => '') */
  55	-function hdata_user_load($userinfo,$reset=false){
  56	:    //DEBUG: check the calling function
  57	-    $trace=debug_backtrace();
  58	-    $caller=array_shift($trace);
  59	-    $caller=array_shift($trace);
--
  72	://TODO: make this a system variable
  73	-function hdata_user_cache_life(){return '1 month';}
  74	-
  75	-/* id should be uid if $draft is true */
--
 672	://TODO: implement list functions
 673	-function _hdata_student_list($college,$active = true){
 674	-    //if college is null, load all colleges
 675	-    //if active is false, load all statuses
```
