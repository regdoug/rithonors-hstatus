<h2>Personal Information</h2>
<section>
<div style="display:inline-block; width:75%">
<table <?php if($status != 1) print 'style="background-color:#eee;"';?>>
    <tr>
        <td>Name</td>
        <td><?php print "$fname $lname"; ?></td>
    </tr>
    <tr>
        <td>Status</td>
        <td><?php print "$status_string"; ?></td>
    </tr>
    <tr>
        <td>Major</td>
        <td><?php print "$year $major ";//.(empty($plan))?"":"($plan $subplan)";?></td>
    </tr>
    <tr>
        <td>Entered RIT</td>
        <td><?php print "$enteredrit"; ?></td>
    </tr>
    <tr>
        <td>Entered Honors</td>
        <td><?php print "$enteredhonors"; ?></td>
    </tr>
    <tr>
        <td>Left Honors</td>
        <td><?php print "$lefthonors"; ?></td>
    </tr>
</table>
</div>
<div style="float:right;">
<img src="<?php print base_path()."facebook/portraits/$username.jpg";?>" width=150 height=200 alt="<?php print $username; ?>" />
</div>
</section>
<h2>Administrative Tasks</h2>
<p>Future content will include
<ul>
    <li>Change Status</li>
    <li>Grant Waivers</li>
    <li>Continuation?</li>
</ul></p>
<h2>Continuation Information</h2>
<p>Continuation system needs overhaul before this will be functional</p>
<h2>Comp Learning, Courses, and Points</h2>
<p>Same as MyStatus page... use theme functions?</p>
