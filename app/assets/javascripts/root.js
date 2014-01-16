// Place all the behaviors and hooks related to the matching controller here.
// All this logic will automatically be available in application.js.


//var Helpers = {
//   trigger_web_event: function(type, value) {
//     var jqxhr = $.post( "web_event", {})
//       .done(function() {
//         alert( "second success" );
//       })
//       .fail(function() {
//         alert( "error" );
//       })
//       .always(function() {
//         alert( "finished" );
//     jqxhr.always(function() {
//       alert( "second finished" );
//     });
//   }
// };
// 
// Bind things to the 
$(function() {
  $(".dial").knob({
    'release' : function (v) {
      console.info(v);
    }
  })
});
