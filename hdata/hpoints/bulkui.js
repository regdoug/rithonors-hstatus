Drupal.behaviors.hpointsLoadBulkUI = function(context){
    hbulkuiLoad(context);
};

$(function(){
    $('input.test-button').click(function(e){
        $('.hpoints-bulkui-textarea').toggle();
        //var samples = new Array('abc1234', 'rdprap');
        //hpointsAddValues(samples);
    });
    //var initial = $('.hpoints-bulkui-textarea').not('.hpoints-processed').addClass('hpoints-processed').val();
    //hpointsAddValues(initial.split(' '));
});
    

Drupal.behaviors.hpointsAttachDelete = function(context){
    $(".hpoints-bulkui-container .del",context).not('hpoints-processed').addClass("hpoints-processed").click(function(e){
        e.preventDefault()
        $(this).closest('.parent').remove();
        //testing
        $('.hpoints-bulkui-textarea').val($(".hpoints-bulkui-container .input").text());
    });
}

Drupal.theme.prototype.hpointsTags = function(username, type){
    var modulepath = Drupal.settings.hpointsBasePath;
    var classes = (type == 'input')?'input parent':'group-label';
    return $('<span>' + username + ' <a class="del"href="#"><img src="' +
        modulepath + '/close.png" width=16 height=16 ></a></span>').addClass(classes);
}

function hbulkuiLoad(context) {
    var initial = $('.hpoints-bulkui-textarea',context).not('.hpoints-processed').addClass('hpoints-processed').val();
    if(typeof(initial) == 'string'){
        var groups = initial.split('=');
        for(i in groups){
            hpointsAddValues(groups[i].split(' '));
        }
    }
    $('.hpoints-bulkui-textarea').hide();
    $(".hpoints-bulkui-container").show();
}

function hpointsAddValues(values) {
    if(values[0].indexOf('[') == 0){
        var group = $('<div></div>').addClass('group parent');
        group.append(Drupal.theme('hpointsTags',values.shift(),'group'));
        for (v in values){
            group.append(Drupal.theme('hpointsTags',values[v],'input'));
        }
        $('.hpoints-bulkui-container').append(group);
    }else{
        for (v in values){
            $(".hpoints-bulkui-container").append(Drupal.theme('hpointsTags',values[v],'input'));
        }
    }
    Drupal.attachBehaviors()
}
