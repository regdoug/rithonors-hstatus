Annotations
==

hdata/hnews/hnews.module
--

```
 164	:    //TODO: (Maybe) make a way for users to opt out of certain types of mailings.
 165	-    array_walk($recipients,'_hnews_to_email');
 166	-    
 167	-    //load the node and send it
--
 180	:    //TODO: (Maybe) add a way to have users input a preferred email address
 181	-    $element .= '@rit.edu';
 182	-}
 183	-
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
