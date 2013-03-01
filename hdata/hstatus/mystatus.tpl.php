<?php
/**
 * mystatus.tpl.php
 * Copyright 2012 The Honors Program at RIT
 *
 * ===================
 * Available Variables
 * ===================
 * ALWAYS DEFINED
 * $username
 * $status - Continuation Status (as an integer)
 * $status_string - Continuation Status (plain text)
 * $points_total - integer total honors points
 * $complearning_status - integer status
 * $complearning_status_string - plaintext status
 *
 * SOMETIMES NULL
 * $college - college e.g. KGCOE
 * $department - e.g. Electrical Engineering
 * $program - e.g. 'BS', 'BS/MS'
 * $name - full name
 * $gpa - plain text representation of gpa
 * $year - user's year level
 * $courses - array of courses taken
 *    - each element is an array with keys 'num','name','term','grade','points','instructor'
 * $points username, explanation,
 *  	pointID as type,
 * 		submitted as submitted_time,
		submittedBy as submitted_by,
		approved as status,
		approvedBy as reviewer,
		approvedTime as reviewed_time,
		declinedReason as reason,
		numPoints as credits
 * 
 * TODO
 * -figure out how "other points" will work
 * -figure out how complearning submissions will work
 */
 

if($displaynone):
?>
<h2>You are not in the Honors Database</h2>
<?php else: ?>

<div style="float:right;">
<img src="<?php print base_path()."facebook/portraits/$username.jpg";?>" width=150 height=200 alt="<?php print $username; ?>" />
</div>

<h2>Continuation Status </h2>
 <p>Your continuation status is 
<?php
//provide a background color for select statuses
switch($status){
    case 0: $color = '#A2EB81';break;//green
    case 1: $color = '#D0EB81';break;//green-yellow
    case 2: $color = '#E7EB81';break;//yellow
    case 3: $color = '#EB8181';break;//red
}
//print opening tag  
if(isset($color)){
    print "<span style=\"background-color:$color\" >";
}
?>

<strong><?php print $status_string; ?></strong>

<?php if(isset($color)){ print '</span>'; }/*print closing tag.*/ ?>
</p>

<section>

<h2><?php t('Honor Status for @user',array('@user'=>$username)); ?></h2>

<div id="student-information" style="display:inline-block;width:575px;">
<table>
    <thead>
        <tr><td>Full Name</td>
        <td>College</td>
        <td>Department</td>
        <td></td>
        <td>GPA</td></tr>
    </thead>
    <tbody>
        <tr><td><?php print $name;?></td>
        <td><?php print $college;?></td>
        <td><?php print $department;?></td>
        <td><?php print $program;?></td>
        <td><?php print substr(strval($gpa),0,1) .'.'.substr(strval($gpa),1);?></td></tr>
    </tbody>
</table>

<h2> Honors Points</h2>
<strong>Total Points: <?php print (int)$points_total; ?></strong>
<h3> Honors Courses</h3>
<table>
    <thead>
	<tr><td>Course Name</td>
	<td>Number</td>
	<td>Term Taken</td>
	<td>Instructor</td>
	<td>Grade</td>
	<td>Points</td>
	</tr>
    </thead>
    <tbody>
<?php
if(is_array($courses)){
    foreach($courses as $value)
    {
	echo '<tr><td>'.$value['name']. '</td>
		<td>' .$value['num'] .'</td>
		<td>' .$value['term'] .'</td>
		<td>' .$value['instructor'] .'</td>
		<td>' .$value['grade'] .'</td>
		<td>' .$value['credits'] .'</td></tr>';	
    }
}
?>
    </tbody>
</table>

<h3>Other Activities</h3>
<table>
			<thead>
				<tr>
					<td>Explanation</td>
					<td>Status</td>
					<td>Points</td>
					<td>Date Submitted</td>
				</tr>
			</thead>
			<tbody>
<?php

if(is_array($courses)){
    foreach($courses as $value)
    {
	echo '<tr>
			<td>' .$value['explanation'] .'</td>
			<td>' .$value['status'] .'</td>
			<td>' .$value['credits'] .'</td>
			<td>' .$value['submitted_time'] .'</td>
		  </tr>';
    }
}

?>
</tbody>
</table>

<!-- temporary -->
<h3><a href="https://www-staging.rit.edu/academicaffairs/honors/">Point Request Form</a></h3>

<h2>Comp Learning Submissions</h2>

<p>Your complearning has been <strong><?php print $complearning_status_string; ?></strong></p>
<p>For requirements, please see the <a href="http://www-staging.rit.edu/academicaffairs/honors/service-requirements">comp learning page</a>.</p>
<h4>Submissions</h4>
<table>
	<thead>
		<tr>
			<td>ID</td>
			<td>Status</td>
			<td>Hours</td>
			<td>Submit Date</td>
			<td>Review Date</td>
		
		</tr>
	</thead>
	<tbody>
	<?php
	echo 
		'<tr><td>'.$sumissions['complearn']['id'] .'</td>
		<td>'.$sumissions['complearn']['status'] .'</td>
		<td>'.$sumissions['complearn']['hours'] .'</td>
		<td>'.$sumissions['complearn']['submit_date'] .'</td>
		<td>'.$sumissions['complearn']['review_date'] .'</td>
		</tr>';
		?>
	</tbody>
</table>
</div> <!-- End #student-information -->
</section> <!-- End Main Section -->
<h2>Questions?</h2>

<h3>Continuation Review</h3>
<p>Email any questions to <a href="mailto:honors@rit.edu">
honors@rit.edu</a></p>

<h3>Comp Learning</h3>
<p><a href="http://www-staging.rit.edu/academicaffairs/honors/service-requirements">info about comp learning requirements</a></p>
<p>Email any questions to <a href="mailto:CompLearning@mail.honors.rit.edu">CompLearning@mail.honors.rit.edu</a></p>

<h3>General Requirements</h3>
<p><a href=http://www-staging.rit.edu/academicaffairs/honors/academic-requirements>info about honors requirements</a></p>
<p>Email any questions to <a href="mailto:Council@mail.honors.rit.edu">Council@mail.honors.rit.edu</a></p>

<h3>Honors Courses</h3>
<p><a href="http://www-staging.rit.edu/academicaffairs/honors/courseslist">A Listing of the currently offered honors courses</a></p>
<pre>
<?php print_r($huser); /*DEBUG*/ ?>
</pre>
<aside><p>Generated by the hStatus module</p></aside>

<?php endif; ?>

