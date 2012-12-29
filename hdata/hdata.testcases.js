//hdata.testcases.js  --  Provides AJAX for testcases.inc

function hdata_testcases_jssubmit(){
    var formvalues = $('#testcases').serializeArray();
    var querystring = Drupal.settings.hdata.ajax_path;
    jQuery.each(formvalues, function(i, field){
        if(field.value){
            querystring += field.value + "/";
        }
    });
    //alert('Query String: '+querystring);
    $('#hdata-link').attr('href',querystring);
   $('#testcases-output').load(querystring, function(response, status, xhr) {
      if (status == "error") {
        var msg = "Sorry but there was an error: ";
        $("#hdata-error").html(msg + xhr.status + " " + xhr.statusText);
      }
    });
    return false;
}
    
