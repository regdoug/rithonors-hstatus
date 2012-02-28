<?php
/**
 * Displays the moderation status (Webform Moderation)
 * 
 * Variables
 *   - $format - 'html', 'email', etc
 *   - $value - the integer form of the value
 *   - $text - the text form of the value
 * 
 * Values:
 *  0 => Pending
 *  1 => Approved
 *  2 => Rejected
 * 99 => Unknown
 */
?>
<?php print $text; ?>
<?php
//Determine which color (if any) to output
switch ($value){
  case 1: $bgcolor = '#D63333'; break;
  case 2: $bgcolor = '#33D633'; break;
}
?>
<?php if ($format == 'html' && isset($bgcolor)): ?>
<style type="text/css">
.webform_submission_info, .webform_submission {
	     background-color: <?php print $bgcolor; ?>;
 -webkit-box-shadow: 0px 0px 4px 1px #ffffff; /* Saf3-4, iOS 4.0.2 - 4.2, Android 2.3+ */
    -moz-box-shadow: 0px 0px 4px 1px #ffffff; /* FF3.5 - 3.6 */
         box-shadow: 0px 0px 4px 1px #ffffff; /* Opera 10.5, IE9, FF4+, Chrome 6+, iOS 5 */
}
</style>
<?php endif; ?>

