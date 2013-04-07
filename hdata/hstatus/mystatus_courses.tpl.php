<?php
/**
 * @file mystatus_courses.tpl.php
 *
 * Generate a table of Honors courses
 */
?>
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
