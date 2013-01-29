<?php
/* clactivity.tpl.php
 * This template is the default format for comp learning activities 
 */
 
/*
 * $submission
 *      id          -- maps to id
 *      body        -- maps to explanation
 *     'username'   -- maps to username
 *     'author'     -- maps to submittedBy
 *     'submit_date -- maps to submitted
 *     'type'       -- maps to pointID
 *     'status'     -- maps to approved
 *     'reviewer'   -- maps to approvedBy
 *      review_date -- maps to approvedTime
 *      reason      -- maps to declinedReason
 *      credits     -- maps to numPoints
 */

switch($submission['status']){
    case -1: $color = //red
    case 1: $color = //green
    default: $color = '';
}
?>
<div style="<?php print $color; ?>">

<h1><?php print t('%type for @name',array('%type'=> $submission['type'], '@name'=>$submission['username'])); ?></h1>
<h2><?php print t('Submitted by @name on @date.',array('@name'=>$submission['author'],'@date'=>$submission['submit_date'])); ?></h2>

<fieldset>
    <legend>Description</legend>
    <?php print t($activity['body']); ?>
</fieldset>

<?php if ($color): ?>
<fieldset>
    <legend>Status</legend>
    <p><?php print t('@activity',array('@activity'=>$activity)); ?></p>
    <aside><?php print t('Reviewed by %user on @date',array('%user'=>$activity['reviewer'],
            '@date'=>strftime('%B %e, %G',strtotime($activity['review_date'])))); ?></aside>
</fieldset>
<?php else: ?>
<fieldset>
    <legend>Status</legend>
    <?php print 'Pending'; ?>
</fieldset>
<?php endif; //End of color?>
</div>

