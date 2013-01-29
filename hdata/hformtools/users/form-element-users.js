Drupal.behaviors.hftUsersLoad = function (context) {
    var initial = $('.hformtools-users textarea',context).not('.hformtools-processed').addClass('hformtools-processed').val();
    if(typeof(initial) == 'string'){
        var groups = initial.split('=');
        for(i in groups){
            hFormToolsAddValues(groups[i].split(' '));
        }
    }
    $('.hformtools-users input[type=textfield]').bind('keydown', function(e) {
        if (e.which === 13) { // keycode 13 is enter
            e.preventDefault(); // don't submit form
            var value = $(this).val();
            if( !(typeof(value) == 'string' && value.length && value.length >= 2) ) return;
            
            if(value == value.toUpperCase()){
                hFormToolsLoadGroup(value);
            }else{
                hFormToolsAddValues(value);
            }
            $(this).val('');
        }
    });
    $('.hformtools-users').closest('form').bind('submit',function(e){
        $('.hformtools-users textarea').val($(".hformtools-users .dynamic .user").text());
    });
        
    $('.hformtools-users .textarea').hide();
    $(".hformtools-users .ajaxelement").show();
}

Drupal.behaviors.hftUsersBindDelete = function (context){
    $(".hformtools-users .del",context).not('hformtools-processed').addClass("hformtools-processed").click(function(e){
        e.preventDefault()
        $(this).closest('.parent').remove();
    });
}

Drupal.theme.prototype.hFormToolsUsers = function(username, type){
    if(username == "") return "";
    var modulepath = Drupal.settings.hFormToolsBasePath;
    var classes = "";
    switch(type){
        case 'user': classes = 'user parent';break;
        case 'group': classes = 'group group-label';break;
        default: return "";
    }
    return $('<span>' + username + ' <a class="del"href="#"><img src="' +
        modulepath + '/close.png" width=16 height=16 ></a></span>').addClass(classes);
}

function hFormToolsAddValues(values) {
    if(typeof(values) == 'string'){
        $(".hformtools-users .dynamic").append(Drupal.theme('hFormToolsUsers',values,'user'));
    }else if(values[0].indexOf('[') == 0){
        var group = $('<div></div>').addClass('group parent');
        group.append(Drupal.theme('hFormToolsUsers',values.shift(),'group'));
        for (v in values){
            group.append(Drupal.theme('hFormToolsUsers',values[v],'user'));
        }
        $('.hformtools-users .dynamic').append(group);
    }else{
        for (v in values){
            $(".hformtools-users .dynamic").append(Drupal.theme('hFormToolsUsers',values[v],'user'));
        }
    }
    Drupal.attachBehaviors()
}

function hFormToolsLoadGroup(group) {
    var tmpname = "tmp" + (new Date().getTime());
    $('<div></div>').addClass('group tmp '+tmpname).appendTo('.hformtools-users > container');
    $.ajax({
        url: Drupal.settings.basePath + 'hformtools/ajax/users/group/'+group,
        dataType: 'json',
        success: function(jsonArray, status, jqXHR){
            if(jsonArray.length && jsonArray.length > 1){
                hFormToolsAddValues(jsonArray);
            }
        },
        complete: function (jqXHR, status) { 
            //alert("AJAX status "+status);
            $("."+tmpname).remove(); 
        },
    });
}
