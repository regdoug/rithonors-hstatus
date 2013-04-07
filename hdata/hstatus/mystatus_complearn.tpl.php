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
			<td>ID</td>
			<td>Status</td>
			<td>Hours</td>
			<td>Submit Date</td>
			<td>Review Date</td>

		</tr>
	</thead>
	<tbody>
	<?php
	foreach($submissions as $cl){
		if ($cl['legacy']){
			$idstring=$cl['id'];
		}
		else{
			$idstring=l($cl['id'], "hcomplearn/submission/{$cl['id']}", array('attributes'=>array('class'=>'colorbox-load')));
		}
		if ($cl['submit_date']==0){
			$sub_date="";
		}
		else{
			$sub_date=strftime("%x %I:%M:%S %p",$cl['submit_date']);
		}
		if ($cl['review_date']==0){
			$rev_date="";
		}
		else{
			$rev_date=strftime("%x %I:%M:%S %p",$cl['review_date']);
		}
		echo
			'<tr><td>'.$idstring .'</td>
			<td>'.hcomplearn_status_string($cl['status']) .'</td>
			<td>'.$cl['hours'] .'</td>
			<td>'.$sub_date .'</td>
			<td>'.$rev_date .'</td>
			</tr>';
	}
		?>
	</tbody>
</table>
