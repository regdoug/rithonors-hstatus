<?php //hnotesystem_note.tpl.php 
if(!($format && $note)){
    echo 'Not Found';
    return;
}
$student_name = ($student_name)?$student_name:$note['username'];

if($format == 'long'):
?>
<h2><?php print t('@student | $title',array('@student' => $student_name,'@title' => $title)); ?></h2>
<aside>
    <?php print t('Note @id (@year) posted by @author on @date',
    array('@id' => $id, '@year' => $note['year'], '@author' => $note['author'], '@date' => strftime('%F',$note['date']))); ?>
</aside>
<p><?php print t('@body',array('@body' => $note['body'])); ?></p>

<?php
elseif($format == 'short'):
//TODO: make stylesheet
?>

<span class="hnote-row">
    <span class="hnote-cell hnote-author-cell"><?php print t('@author @date (@year)', 
    array('@year' => $note['year'], '@author' => $note['author'], '@date' => strftime('%F',$note['date']))); ?></span>
    <span class="hnote-cell hnote-title-cell"><?php print t('@title', array('@title' => $title)); ?></span>
    <span class="hnote-cell hnote-link-cell">
        <?php 
        $linkoptions = array('query' => array('destination' => drupal_get_destination()));
        print l('View',$viewlink,$linkoptions).' '.
            l('Edit',$editlink,$linkoptions).' '.
            l('Delete',$deletelink,$linkoptions);
        ?>
    </span>
</span>

<?php
endif;
?>
