<?php
/* clactivity.tpl.php
 * This template is the default format for comp learning activities 
 */
?>

<h2><?php print t('%name (!hours hours)',array('%name'=>$activity['name'],'!hours'=>$activity['hours'])); ?></h2>

<fieldset>
    <legend>Description</legend>
    <?php print t($activity['desc']); ?>
</fieldset>

<?php if ($activity['time']): ?>
<fieldset>
    <legend>Dates and Times</legend>
    <?php print t($activity['time']); ?>
</fieldset>
<?php endif; ?>

<fieldset>
    <legend>Contact Person</legend>
    <?php print t($activity['contact']); ?>
</fieldset>

<?php if ($activity['comment']): ?>
<fieldset>
    <legend>Comments</legend>
    <?php print t($activity['comment']); ?>
</fieldset>
<?php endif; ?>
