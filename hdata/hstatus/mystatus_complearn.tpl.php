<?php
/**
 * @file mystatus_complearn.tpl.php
 * 
 * Generate a table of complearning submissions
 */
?>
<table>
	<thead>
		<tr>
			<td>Status</td>
			<td>Hours</td>
			<td>Submit Date</td>
			<td>Review Date</td>
		
		</tr>
	</thead>
	<tbody>
	<?php
	foreach($submissions as $cl){
	    echo 
		'<td>'.$cl['status'] .'</td>
		<td>'.$cl['hours'] .'</td>
		<td>'.$cl['submit_date'] .'</td>
		<td>'.$cl['review_date'] .'</td>
		</tr>';
	}
		?>
	</tbody>
</table>
