// Place all the behaviors and hooks related to the matching controller here.
// All this logic will automatically be available in application.js.

// On Document Ready: Bind things to the
$(function() {
  $("#actual_temp_change_form .dial").knob({});
  $("#desired_temp_change_form .dial").knob({
    'release' : function (v) {
      console.info(v);
      var form = $('#desired_temp_change_form').ajaxSubmit({ /* options */ });
      var xhr = form.data('jqxhr');
      xhr.done(function() {});
    }
  })
});
