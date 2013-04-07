<?php
/**
 * @file mystatus_points.tpl.php
 *
 * Generate a table of points/waivers
 */
?>
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

if(is_array($submissions)){
    foreach($submissions as $value)
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
