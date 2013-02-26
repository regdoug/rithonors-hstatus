<?php
/*
 * Available Variables:
 *   $student_name - name of student
 *   $student_email - who the message is from
 *   $reference_name - name of reference
 *   $reference_email - email address of reference
 *   $points_submission - description of activity
 */
$text = <<<TEXT
<p>Dear @reference,</p>

<p>@student (@student_email) has submitted a request to the Honors Program
requesting that the following activity be counted for Honors credit.  
@student listed you as a reference.  Please email the Honors Office
at <a href="mailto:honors@rit.edu">honors@rit.edu</a> to confirm the
accuracy of this report.</p>

<blockquote>
@points_submission
</blockquote>
TEXT;
print t($text,array('@student'=>$student_name,'@student_email'=>$student_email,
        '@reference'=>$reference_name,'@points_submission'=>$points_submission));
?>
