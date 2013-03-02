<div class="hformtools-users">
    <div class="ajaxelement form-item">
        <label><?php print t('@title:', array('@title' => $element['#title'])); ?></label>
        <div class="dynamic"></div>
        <input type="textfield" class="hformtools-ajax-field">
    </div>
    <div class="textarea">
        <?php print drupal_render($textarea_element); ?>
    </div>
</div>
