Drupal.behaviors.hFormToolsBulkUsersLoad = hBulkUsersLoad;
Drupal.behaviors.hFormToolsBulkUsersAttachDelete = hBulkUsersAttachDelete;

Drupal.theme.prototype.hpointsTags = function(username, type){
    var modulepath = Drupal.settings.hpointsBasePath;
    var classes = (type == 'input')?'input parent':'group-label';
    return $('<span>' + username + ' <a class="del"href="#"><img src="' +
        modulepath + '/close.png" width=16 height=16 ></a></span>').addClass(classes);
}

function hBulkUsersAttachDelete(context){
    $(".hformtools-users .del",context).not('hpoints-processed').addClass("hpoints-processed").click(function(e){
        e.preventDefault()
        $(this).closest('.parent').remove();
        //testing
        $('.hformtools-users textarea').val($(".hformtools-users .dynamic .input").text());
    });
}

function hBulkUsersLoad(context) {
    var initial = $('.hformtools-users textarea',context).not('.hpoints-processed').addClass('hpoints-processed').val();
    if(typeof(initial) == 'string'){
        var groups = initial.split('=');
        for(i in groups){
            hpointsAddValues(groups[i].split(' '));
        }
    }
    $('.hformtools-users').delegate('input:text', 'keypress', function(e) {
        if (e.which === 13) { // keycode 13 is enter
            e.preventDefault(); // don't submit form
            var value = $(this).val();
            if(value && value === value.toUpperCase()){
                hFormToolsLoadGroup(value);
            }else{
                hpointsAddValues(value);
            }
            $(this).val('');
        }
    });
    $('.hformtools-users textarea').hide();
    $(".hformtools-users > .container").show();
}

function hFormToolsAddValues(values) {
    if(typeof(values) == 'string'){
        $(".hformtools-users > .container").append(Drupal.theme('hpointsTags',values,'input'));
    if(values[0].indexOf('[') == 0){
        var group = $('<div></div>').addClass('group parent');
        group.append(Drupal.theme('hpointsTags',values.shift(),'group'));
        for (v in values){
            group.append(Drupal.theme('hpointsTags',values[v],'input'));
        }
        $('.hformtools-users > .container').append(group);
    }else{
        for (v in values){
            $(".hformtools-users > .container").append(Drupal.theme('hpointsTags',values[v],'input'));
        }
    }
    Drupal.attachBehaviors()
}

function hFormToolsLoadGroup(group) {
    //TODO:
    //add temporary "loading" group
    //load group from hformtools/ajax/users/group/XXXXX  (as JSON)
    //validate JSON  (is an array and has more than one element)
    //use hFormToolsAddValues to add group
    //done
}
