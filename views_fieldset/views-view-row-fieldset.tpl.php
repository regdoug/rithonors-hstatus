<?php
//Created by Reginald Pierce, RIT Honors Tech Committee
$first = true;
?>
<fieldset class="collapsible <?php print $options['initialstate']; ?>">
<?php foreach ($fields as $id => $field): ?>
  <?php if($first): //Make the first one a legend
           $first = false; ?>
    <legend>
      <?php print $field->content; ?>
    </legend>
  <?php else: ?>
	  <?php if (!empty($field->separator)): ?>
		<?php print $field->separator; ?>
	  <?php endif; ?>

	  <<?php print $field->inline_html;?> class="views-field-<?php print $field->class; ?>">
		<?php if ($field->label): ?>
		  <label class="views-label-<?php print $field->class; ?>">
			<?php print $field->label; ?>:
		  </label>
		<?php endif; ?>
		  <?php
		  // $field->element_type is either SPAN or DIV depending upon whether or not
		  // the field is a 'block' element type or 'inline' element type.
		  ?>
		  <<?php print $field->element_type; ?> class="field-content"><?php print $field->content; ?></<?php print $field->element_type; ?>>
	  </<?php print $field->inline_html;?>>
  <?php endif; ?>
<?php endforeach; ?>
</fieldset>
