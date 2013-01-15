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

hdata/hdata.module
--

```
  48	://TODO: make this a system variable
  49	-function hdata_user_cache_life(){return '1 month';}
  50	-
  51	-/* id should be uid if $draft is true */
```
