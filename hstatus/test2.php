<!DOCTYPE html>
<html lang="en">
<head>
<meta charset=utf-8>
<meta name="viewport" content="width=620">
<title>HTML5 Demo: geolocation</title>
<link rel="stylesheet" href="css/html5demos.css">
<script src="js/h5utils.js"></script></head>
<body>
<section id="user">
    <?php
    if($user):
    ?>
    <header>
        <h1><?php print $user->name; ?></h1>
    </header>
    <article>
        <h1>$user object</h1>
        <?php print_r($user); ?>
    </article>
    <article>
        <h1>$u object</h1>
        <?php if($u): ?>
            <?php print_r($u); ?>
        <?php endif; ?>
    </article>
    <?php else: ?>
        <aside style="color:red;">Can't find user data</aside>
    <?php endif; ?>
</section>
<!--
<section id="wrapper">
    <header>
      <h1>geolocation</h1>
    </header>
<meta name="viewport" content="width=620" />

<script type="text/javascript" src="http://maps.google.com/maps/api/js?sensor=false"></script>
    <article>
      <p>Finding your location: <span id="status">checking...</span></p>
    </article>
<script>
function success(position) {
  var s = document.querySelector('#status');
  
  if (s.className == 'success') {
    // not sure why we're hitting this twice in FF, I think it's to do with a cached result coming back    
    return;
  }
  
  s.innerHTML = "found you!";
  s.className = 'success';
  
  var mapcanvas = document.createElement('div');
  mapcanvas.id = 'mapcanvas';
  mapcanvas.style.height = '400px';
  mapcanvas.style.width = '560px';
    
  document.querySelector('article').appendChild(mapcanvas);
  
  var latlng = new google.maps.LatLng(position.coords.latitude, position.coords.longitude);
  var myOptions = {
    zoom: 15,
    center: latlng,
    mapTypeControl: false,
    navigationControlOptions: {style: google.maps.NavigationControlStyle.SMALL},
    mapTypeId: google.maps.MapTypeId.ROADMAP
  };
  var map = new google.maps.Map(document.getElementById("mapcanvas"), myOptions);
  
  var marker = new google.maps.Marker({
      position: latlng, 
      map: map, 
      title:"You are here! (at least within a "+position.coords.accuracy+" meter radius)"
  });
}

function error(msg) {
  var s = document.querySelector('#status');
  s.innerHTML = typeof msg == 'string' ? msg : "failed";
  s.className = 'fail';
  
  // console.log(arguments);
}

if (navigator.geolocation) {
  navigator.geolocation.getCurrentPosition(success, error);
} else {
  error('not supported');
}

</script><a id="html5badge" href="http://www.w3.org/html/logo/">
<img src="http://www.w3.org/html/logo/badge/html5-badge-h-connectivity-device-graphics-multimedia-performance-semantics-storage.png" width="325" height="64" alt="HTML5 Powered with Connectivity / Realtime, Device Access, Graphics, 3D & Effects, Multimedia, Performance & Integration, Semantics, and Offline & Storage" title="HTML5 Powered with Connectivity / Realtime, Device Access, Graphics, 3D & Effects, Multimedia, Performance & Integration, Semantics, and Offline & Storage">
</a>
    <footer><a href="/">HTML5 demos</a>/<a id="built" href="http://twitter.com/rem">@rem built this</a>/<a href="#view-source">view source</a></footer> 
</section>
<script src="js/prettify.packed.js"></script>
-->
</body>
</html>
