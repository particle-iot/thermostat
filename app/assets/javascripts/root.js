// Place all the behaviors and hooks related to the matching controller here.
// All this logic will automatically be available in application.js.

var Page = function () {
};
Page.prototype = {
    startup: function () {
        $("#actual_temp_change_form .dial").knob({});
        $("#desired_temp_change_form .dial").knob({
            'release': function (v) {
                console.info(v);
                var form = $('#desired_temp_change_form').ajaxSubmit({ /* options */ });
                var xhr = form.data('jqxhr');
                xhr.done(function () {
                });
            }
        });
    }
};
var page = new Page();

// On Document Ready: Bind things to the
$(page.startup);



