<?php
	require( '../includes/page_start.inc.php' );
	$v_user = $_SESSION['userName'];

	require( BASE_DIR_HONORS . 'includes/scripts/check_login.php' );
	require( BASE_DIR_HONORS . 'includes/scripts/change_cl_system.inc.php' );
	
	
	if( isset($_POST['pointSubmit']) )
	{
		if( !is_numeric( $_POST['pointID'] ) ) die('The selected point menu item must be in the form of an integer.');
		$pointID = $_POST['pointID'];
		$explanation = $_POST['studentExplanation'];
		$explanation = mysql_real_escape_string( $explanation );
		
		// Insert the point request into the database
		$query = 'INSERT INTO students_points
					(username, pointID, explanation, submitted, submittedBy)
					VALUES ( "'.$v_user.'", '.$pointID.', "'.$explanation.'", NOW(), "'.$v_user.'" );';
		$result = mysql_query( $query ) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
		
		//------------Send a confirmation email---------------
		require( BASE_DIR_SWIFTMAILER3 . "Swift.php" );
		require( BASE_DIR_SWIFTMAILER3 . "Swift/Connection/SMTP.php" );
		
		//Create a message
		$message =& new Swift_Message( "Honors Point Request Received" );
		
		$query = 'SELECT title FROM points_menu WHERE id='.$pointID.';';
		$result = mysql_query( $query );
		$menuItem = mysql_fetch_assoc( $result );
		$v_plain_part = $_SESSION['firstName'].',

This email confirms that we have received your Honors Point request.  The Honors Office will review your submission in the near future.  You will receive another email once your request has been reviewed.  If your request is accepted, that email will also contain the number of points you were awarded.  You may also check your My Status page on the Honors website for the status of your request:
https://honors.rit.edu/mystatus/

For reference, your submission was as follows:
--------
Activity: '.$menuItem['title'].'

Explanation:
'.stripslashes($explanation).'
--------

Regards,
RIT Honors Program';
		
		//Add the message
		$message->attach( new Swift_Message_Part( $v_plain_part ));
		
		//Add recipients
		$recipients =& new Swift_RecipientList();
		$recipients->addTo( $v_user.'@rit.edu', $_SESSION['firstName'].' '.$_SESSION['lastName'] );
		//Add addCc()
		$recipients->addCc( 'honors@rit.edu', 'RIT Honors Program' );
		
		//Create a second message to the professor, if necessary
		if ( $_POST['profEmail'] != '' ) { 
			$message2 =& new Swift_Message( "Honors Point Request Received" );
			
			$message2_body = "Dear " . $_POST['profName'] . ", 

" . $_SESSION['firstName'] . " " . $_SESSION['lastName'] . " has recently submitted their research or scholarship project for Honors points. Before we can evaluate their work, we ask that their advising professor confirm their efforts. If you could, please send a brief evaluation of this student’s work to honors@rit.edu, including the following points:

-  A description of the project
-  An estimate of the number of hours worked by the student
-  Your overall estimation of the student’s work and progress in the field
 
If you have any questions about the process or Honors in general, please feel free to contact us at honors@rit.edu.

Thank you.";
			
			//Add the message
			$message2->attach( new Swift_Message_Part( $message2_body ));
			
			//Add recipients
			$recipients2 =& new Swift_RecipientList();
			$recipients2->addTo( $_POST['profEmail'], $_POST['profName'] );
			//Add addCc()
			$recipients2->addCc( 'honors@rit.edu', 'RIT Honors Program' );
		
		}
		
		//Open a connection to RIT's SMTP server
		$swift =& new Swift(new Swift_Connection_SMTP("smtp-server.rit.edu"));
		
		//Send the email(s)
		$emailSent = $swift->send($message, $recipients, new Swift_Address('honors@rit.edu', 'RIT Honors Program') );
		if ( isset( $message2 ) ) {
			$emailSent = $swift->send($message2, $recipients2, new Swift_Address('honors@rit.edu', 'RIT Honors Program') );
		}
		
		//Disconnect from the SMTP server
		$swift->disconnect();

		

		header('Location: ./my_status.php');
		exit();
	}
	
	
	
	$v_title = TITLE . 'Honors Program | Students | My Status';
	$v_css = CSS_HONORS;
	$v_icon = HONORS_ICON;
	
	$v_subnavigation = "<a href='my_status.php#comp_learning'>Comp Learning</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='my_status.php#gpa'>GPA</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='my_status.php#points'>Honors Points</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='my_status.php#questions'>Questions?</a>";
	
	$v_javascript = '<script src="' . BASE_URL_PROTOTYPE . '" type="text/javascript"></script>
	<script type="text/javascript">
		function updatePointForm()
		{
			id = $F("pointID");
			if( id == -1 )
			{
				$("menuDescription").update();
				$("menuDescription").hide();
				$("studentExplanationBlock").hide();
				$("pointSubmit").hide();
				$("emailBlock").hide();
			} else {
				new Ajax.Request("'.BASE_URL_CONTINUATION.'points/pointQuery.php",
				{
					method:"get",
					parameters: {getItem: id, nl2br: true},
					onSuccess: function(transport){
						var data = transport.responseText.evalJSON();
						$("menuDescription").update(data.description);
						$("menuDescription").show();
						$("studentExplanationBlock").show();
						$("pointSubmit").show();
						$("studentExplanation").focus();
						
						// display email form if the submission is for scholarship/research
						if ( data.id == 1 ) {
							$("emailBlock").show();
						}
						else {
							$("emailBlock").hide();
						}
					},
				});	
			}
		}
	</script>';
	
	
	require( HEADER_HONORS );
	
	require( HONORS_NAVBAR );
	
?>	
	<div id="content">
		<h1>My Status</h1>
		
		<h2>Continuation Status</h2>
		<div class='paragraph' style="border-left: 2px solid #a4883b; padding-left: 10px">
<?php
		//first check to see if the student has graduated or has been withdrawn
		$v_query = "SELECT *
						FROM students
						WHERE username = '$v_user'
						LIMIT 1";
		$v_result = mysql_query($v_query) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
		if ( $v_result && mysql_affected_rows() > 0 ){
			$v_row = mysql_fetch_array( $v_result );
			switch ( $v_row['active'] ) {
				case 0:
						echo "You have graduated from the Honors Program.\n";
						break;
				case -1:
						echo "You have been withdrawn from the Honors Program.\n";
						break;
				case -2:
						echo "You have left RIT.\n";
						break;
				case 1:
						//continued
						$v_active_student = true;
						break;
				default:
						echo "You are not an active member of the Honors Program.\n";					
			}
		}
			
		if ( $v_active_student ) {
		echo"<strong> NOTE:</strong> During the week of March 16th continuation review will occur. Please be advised that the status reported on this page is likely to fluctuate. Your status is not final until you receive a continuation email.<br /><br />\n";
			$v_query = "SELECT *
							FROM continuation
							WHERE username = '$v_user'
							LIMIT 1";
			$v_result = mysql_query($v_query) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
			if ( $v_result && mysql_affected_rows() > 0 ){
				$v_row = mysql_fetch_array( $v_result );
				if ( $v_row['status'] != '' ) {
					switch ( $v_row['status'] ) {
						case 0: echo "You have been marked as <strong>continued</strong> for this academic year.\n"; break;
						case 1: echo "You have been marked as <strong>conditionally continued</strong> until June review.\n"; break;
						case 3: echo "You have been marked as <strong>withdrawn</strong> from the Honors Program.\n"; break;
						case 4: echo "You have been marked as <strong>graduated</strong> from the Honors Program.\n"; break;
						case 5: echo "You have been marked as <strong>withdrawn</strong> from the Honors Program.\n"; break;
						case 6: echo "You have been marked as <strong>graduated</strong> from the Honors Program.\n"; break;
						case 7: echo "You have been marked as <strong>conditionally graduated</strong> from the Honors Program.\n"; break;
					}
				}
				else {
					echo "Your continuation status for this academic year has not yet been set.\n";
				}
			}
			else {			
				echo "Your continuation status for this academic year has not yet been set.\n";
			}
		}
								

?>		
		</div>
		
		<a name='gpa'></a>
		<h2>GPA</h2>
		<div class='paragraph' style="border-left: 2px solid #a4883b; padding-left: 10px">
			<?php
				$v_query = "SELECT yearenteredrit, yearlevel, students_gpa.gpa
										FROM students
										LEFT JOIN students_gpa ON students.username=students_gpa.username
										WHERE students.username='$v_user'";
				$v_result = mysql_query($v_query) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
				$v_num = mysql_affected_rows();
				if ($v_num > 0) {
					$v_row = mysql_fetch_assoc($v_result);
					$v_gpa = $v_row['gpa']/1000;
					echo "Current GPA: <strong>$v_gpa</strong><br />\n";
					
					/////////////////////////////////////////////////////
					// don't display if not an active student
					/////////////////////////////////////////////////////
					if ( $v_active_student ) { 
					
						//figure out what the current school year is (i.e. the year it began in)
						if(date('m') >= 9) {
							$v_schoolYear = date('Y');
						} else {
							$v_schoolYear = date('Y')-1;
						}
						
						echo "Year Level: <strong>".$v_row['yearlevel']."</strong><br /><br />\n";
						
						
						//if student has a good enough gpa, let them know that
						if($v_row['gpa'] >= 3600 ||
								($v_row['gpa']>=3500 && $v_row['yearenteredrit']==$v_schoolYear-2) ||
								($v_row['gpa']>=3400 && $v_row['yearenteredrit']==$v_schoolYear-1) ||
								($v_row['gpa']>=3200 && $v_row['yearenteredrit']==$v_schoolYear)) {
							echo "Your GPA satisfies the honors GPA requirements for your year level.\n";
						//if the student is below the minimum for their year, give them a warning
						}else {
							echo "Your GPA does not satisfy the honors GPA requirements for your year level.\n";
						}
						
					/////////////////////////////////////////////////////
					// END don't display if not an active student
					/////////////////////////////////////////////////////
					} 
				}
				
			?>
		</div>
		
		<a name='points'></a>
		<h2>Honors Points</h2>
		<div class='paragraph' style="border-left: 2px solid #a4883b; padding-left: 10px">
			<h3>Courses Taken</h3>
			<?php
				$credits = 0;
				echo "<table style='padding:0px; border-spacing:0px; font-size:.9em;'>\n";
				echo "\t\t\t\t<tr style='font-weight:bold;'>
					<td style='width:100px;'>Course #</td>
					<td style='width:200px;'>Honors Course Name</td>
					<td style='width:50px;'>Grade</td>
					<td style='width:50px;'>Points</td>
					<td style='width:150px;'>Professor</td>
					<td style='width:100px;'>Quarter</td>
					
				</tr>\n";
				//Courses
				$v_query = "SELECT * 
								FROM students_courses
								WHERE username='$v_user' AND honors='Y'
								ORDER BY quarter, course;";
				$v_result = mysql_query($v_query) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
				$v_num = mysql_affected_rows();
				if ($v_num > 0) {
					while($v_row = mysql_fetch_assoc($v_result)) {
						if( $v_row['grade'] != ''
							&& $v_row['grade'] != 'F'
							&& $v_row['grade'] != 'W' )
							$pointsTotal += $v_row['credits'];
						echo "\t\t\t\t<tr>
							<td>".$v_row['course']."</td>
							<td>".$v_row['name']."</td>
							<td>".$v_row['grade']."</td>
							<td>".$v_row['credits']."</td>
							<td>".$v_row['professor']."</td>
							<td>".$v_row['quarter']."</td>
						</tr>\n";
					}
				}
				echo "</table>\n";
				
				//Honors Points Activities
				echo '<br /><h3>Other Activities</h3>';
				
				echo "<table style='padding:0px; border-spacing:0px;'>\n";
				echo "\t\t\t\t<tr style='font-weight:bold;'>
					<td style='width:150px;'>Title</td>
					<td style='width:125px;'>Status</td>
					<td style='width:50px;'>Points</td>
					<td style='width:100px;'>Date Submitted</td>
				</tr>\n";
				
				//Point Waivers
				$v_query = "SELECT * 
								FROM students_waivers
								WHERE username='$v_user'
								ORDER BY date, description;";
				$v_result = mysql_query($v_query) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
				$v_num = mysql_affected_rows();
				if ($v_num > 0) {
					while($v_row = mysql_fetch_assoc($v_result)) {
						$pointsTotal += $v_row['credits'];
						echo "\t\t\t\t<tr>
							<td>".$v_row['description']."</td>
							<td>Granted</td>
							<td>".$v_row['credits']."</td>
							<td>".date('j M Y', strtotime($v_row['date']))."</td>
						</tr>\n";
					}
				}
				
				//Point Activities
				$v_query = "SELECT students_points.*, points_menu.title 
								FROM students_points
								JOIN points_menu ON students_points.pointID = points_menu.id
								WHERE username='$v_user'
								ORDER BY approved, submitted;";
				$v_result = mysql_query($v_query) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
				$v_num = mysql_affected_rows();
				if ($v_num > 0) {
					while( $v_row = mysql_fetch_assoc($v_result) )
					{
						if( $v_row['approved'] == 1 )
							$pointsTotal += $v_row['numPoints'];
						switch($v_row['approved'])
						{
							case 0:
								$status = 'Pending Approval';
								break;
							case 1:
								$status = 'Accepted';
								break;
							case -1:
								$status = 'Declined - <a href="'.BASE_URL_POINTS.'view/?id='.$v_row['id'].'" target="_blank">reason</a>';
								break;
						}
						$numPoints = ($v_row['numPoints'] < 1 ? '&mdash;' : $v_row['numPoints']);
						echo "\t\t\t\t<tr>
							<td><a href=\"".BASE_URL_POINTS."view/?id=".$v_row['id']."\" target=\"_blank\">".$v_row['title']."</a></td>
							<td>".$status."</td>
							<td>".$numPoints."</td>
							<td>".date('j M Y', strtotime($v_row['submitted']))."</td>
						</tr>\n";
					}
				} else {
					echo '<tr><td colspan="4">No point-bearing activities have been submitted at this time.</td></tr>';
				}
				
				echo "</table>\n";
				
				echo '<br />Honors points completed: <strong>'.$pointsTotal.'</strong>';
				
			
			$query = 'SELECT * FROM points_menu WHERE sorting>0 AND id<>8 ORDER BY sorting;';
			$result = mysql_query( $query );
			while( $row = mysql_fetch_assoc($result) )
			{
				$pointsMenu[$row['id']] = $row;
			}
			
			?>
			
			<br /><br />
			<h3>Point Request Form</h3>
			<br />
			<form id="pointForm" method="post" action="./my_status.php">
				<p>
				<select id="pointID" name="pointID" onchange="updatePointForm();">
					<option value="-1">Select an item</option>
<?php
					foreach( $pointsMenu as $menuItem )
					{
						echo '<option value="'.$menuItem['id'].'">';
						echo $menuItem['title'];
						echo '</option>';
					}
?>
				</select>
				<blockquote>
				<div id="menuDescription"></div>
				
				<div id="studentExplanationBlock" style="display: none;">
					<br /><br />
					<label for="studentExplanation"><strong>After reading the guidance above, briefly explain your submission:</strong></label>
					<br /><br />
					<textarea id="studentExplanation" name="studentExplanation" cols="55" rows="8"></textarea>
					<br /><br />
				</div>
				
				<!--only display this block for scholarship/research (done with jQuery above)-->
				<div id='emailBlock' style='display:none;'>
					<label for='profName'>Professor name:</label>
					<input type='text' name='profName' id='profName' /><br/>
					<label for='profEmail'>Professor email:</label>
					<input type='text' name='profEmail' id='profEmail' />
				</div>
				
				<input type="submit" id="pointSubmit" name="pointSubmit" value="Submit point request" style="display: none;" />
				</blockquote>
				</p>
			</form>
			
			
			
			
		</div>
		

<?php 
/////////////////////////////////////////////////////
// don't display if not an active student
/////////////////////////////////////////////////////
if ( $v_active_student ) { 
		
		// determine what the user's CL system is
		$v_query = "SELECT yearenteredrit, complearningsystem, yearenteredhonors 
						FROM students 
						WHERE username LIKE '%{$v_user}%'";
		$v_result = mysql_query($v_query) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
		$v_num = mysql_num_rows( $v_result );
		if ($v_num > 0) {
			$v_row = mysql_fetch_assoc($v_result);
			$v_yearEntered = $v_row['yearenteredhonors'];
			$v_system = $v_row['complearningsystem'];
			
		} else {
			echo "There was a problem accessing your account.  Please contact the <a href='mailto:technology@honors.rit.edu'>honors technology committee</a>.\n";
		}
		
?>

		<h2>Comp Learning Submissions</h2>
		<div class='paragraph' style="border-left: 2px solid #a4883b; padding-left: 10px">
			For requirements, please see the <a href="<?=BASE_URL_COMP_LEARNING;?>">comp learning page</a>.
			<br /><br />
			<?php
			
				// if user is on the new system, print out his approved submissions
				if($v_system=='1') {
					$v_query = "SELECT * 
									FROM complearning 
									WHERE dce LIKE '%{$v_user}%' 
										AND reviewed = '1'
										AND submitted_date >= '" . CUTOFF_DATE . "'";
					$v_result = mysql_query($v_query) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
					$v_num = mysql_affected_rows();
					if ($v_num > 0) {
						while ($v_row = mysql_fetch_assoc($v_result)) {
							$v_id = $v_row['id'];
							$v_title = $v_row['title'];
							$v_date = $v_row['date'];
							$v_reflect = $v_row['reflection'];
							$v_submitted_date = date('F jS, Y', strtotime($v_row['submitted_date']));
							$v_reviewed_date = date('F jS, Y', strtotime($v_row['reviewed_date']));
							
							echo "<strong>$v_title</strong><br />\n";
							echo "<em>Date:</em> $v_date<br />\n";
							echo "<div style='height: 150px; overflow: scroll; padding: 10px; margin: 5px 0px; border: 1px solid #999999;'>".nl2br($v_reflect)."</div>\n";
							echo "<em>Submitted:</em> $v_submitted_date<br />\n";
							echo "<em>Reviewed:</em> $v_reviewed_date<br />\n";
							
						}
						
						
						echo "<br /><br /><strong>You have completed your comp learning requirement for this academic year.</strong>
							However, you may continue to submit activities that you have completed, and they will be stored here for future portfolio display.<br />\n";
					} else {
						echo "You currently don't have any completed comp learning activites that have been approved.\n";
					}
					
					$v_query = "SELECT * 
											FROM complearning 
											WHERE dce LIKE '%{$v_user}%' 
												AND reviewed IS NULL
												AND submitted_date >= '" . CUTOFF_DATE . "'";
					$v_result = mysql_query($v_query) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
					$v_num = mysql_affected_rows();
					if ( $v_num == 1 )
					{
						echo "<br /><br />You have 1 submission waiting to be reviewed.\n";
					} else {
						echo "<br /><br />You have $v_num submissions waiting to be reviewed.\n";
					}
					
				// if user is on the old system, print out just his 12 pt submissions
				} else {
				
					$v_query = "SELECT * 
											FROM twelvepoint 
											WHERE dce LIKE '%{$v_user}%' 
												AND reviewed = '1'
												AND submitted_date >= '" . CUTOFF_DATE . "'";
					$v_result = mysql_query($v_query) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
					$v_num = mysql_affected_rows();
					if ($v_num > 0) {
						while ($v_row = mysql_fetch_assoc($v_result)) {
							$v_id = $v_row['id'];
							$v_title = $v_row['title'];
							$v_date = $v_row['date'];
							$v_reflect = $v_row['reflection'];
							$v_hours = $v_row['hours'];
							$v_volunteer = $v_row['volunteer'];
							$v_submitted_date = date('F jS, Y', strtotime($v_row['submitted_date']));
							$v_vcard = $v_row['vcard'];
							$v_points = $v_row['points'];
							$v_totalPoints += $v_points;
							$v_totalVolunteer += $v_vcard;
							$v_reviewed_date = date('F jS, Y', strtotime($v_row['reviewed_date']));
							
							echo "<strong>$v_title</strong><br />\n";
							echo "<em>Date:</em> $v_date<br />\n";
							echo "<div style='margin-left:10px;'>$v_reflect</div>\n";
							echo "<em>Hours:</em> $v_hours<br />\n";
							echo "<em>Volunteer?:</em> $v_volunteer<br />\n";
							echo "<em>Submitted:</em> $v_submitted_date<br />\n";	
							echo "<em>Reviewed:</em> $v_reviewed_date<br />\n";		
							echo "<br />\n";
							echo "You were awarded $v_points for this activity.<br />\n";
							if($v_vcard == 1) {
								echo "You were awarded volunteer credit for this activity.<br />\n";
							}
							echo "<br />\n";
						}
						
						echo "You have earned a total of $v_totalPoints of comp learning credit.<br />\n";
						echo "<br /><br />\n";
						if($v_totalPoints >= 12) {
							echo "You have earned enough points to satisfy your comp learning requirement.<br />\n";
						} else {
							echo "<strong>You must complete twelve points to satisfy your comp learning requirement.</strong><br />\n";
						}
						if($v_totalVolunteer > 0) {
							echo "You have participated in a volunteer activity and thus completed the volunteer aspect of the comp learning requirement.<br />\n";
						} else {
							echo "<strong>You must complete a volunteer activity to complete the volunteer aspect of the comp learning requirement.</strong><br />\n";
						}
						echo "<br /><br />\n";
						if($v_totalPoints >= 12 && $v_totalVolunteer > 0) {
							echo "<strong>You have completed your comp learning requirement for this academic year.</strong><br />\n";
						}
						
					} else { 
						echo "You currently don't have any completed comp learning activites that have been approved.\n";
						
					}
					
					$v_query = "SELECT * 
											FROM twelvepoint 
											WHERE dce LIKE '%{$v_user}%' 
												AND reviewed IS NULL
												AND submitted_date >= '" . CUTOFF_DATE . "'";
					$v_result = mysql_query($v_query) or die("Database access error on line " . __LINE__ . " of " . basename(__FILE__) . ": " . mysql_error() . " (error #" . mysql_errno() . ").");
					$v_num = mysql_affected_rows();
					if ( $v_num == 1 )
					{
						echo "<br /><br />You have 1 submission waiting to be reviewed.\n";
					} else {
						echo "<br /><br />You have $v_num submissions waiting to be reviewed.\n";
					}
				}
			
			?>
			
		</div>
<?php 
/////////////////////////////////////////////////////
// END don't display if not an active student
/////////////////////////////////////////////////////
} 
?>
		
		<a name='questions'></a>
		<h2>Questions?</h2>
		<div class='paragraph'>
			<strong>Continuation Review</strong><br />
			Email any questions to <a href='mailto:honors@rit.edu'>honors@rit.edu</a>.<br />
			<br />
			<strong>Comp Learning</strong><br />
			<a href='<?=BASE_URL_COMP_LEARNING?>'>Info about comp learning requirements</a><br />
			Email any questions to <a href='mailto:complearning@honors.rit.edu'>CompLearning@honors.rit.edu</a><br />
			<br />
			<strong>General Requirements</strong><br />
			<a href='<?=BASE_URL_HONORS?>requirements.php'>Info about honors requirements</a><br />
			Email questions to <a href='mailto:council@honors.rit.edu'>Council@honors.rit.edu</a><br />
			<br />
			<strong>Honors Courses</strong><br />
			<a href='<?=BASE_URL_HONORS?>courses/'>A Listing of the currently offered honors courses</a><br />
		</div>
		

	</div>
<?php
	require( FOOTER_HONORS );
?>