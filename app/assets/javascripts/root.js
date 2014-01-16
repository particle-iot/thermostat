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
                    console.log("form submitted")
                });
            }
        });

        this.renderGraph();
    },


    pollServer: function () {

    },


    renderGraph: function () {

        //fake data
        var sin = [],
            cos = [];

        for (var i = 0; i < 14; i += 0.5) {
            sin.push([i, Math.sin(i)]);
            cos.push([i, Math.cos(i)]);
        }

        var plot = $.plot("#realtime_graph", [
            { data: sin, label: "sin(x)"},
            { data: cos, label: "cos(x)"}
        ], {
            series: {
                lines: {
                    show: true
                },
                points: {
                    show: true
                }
            },
            grid: {
                hoverable: true,
                clickable: true
            },
            yaxis: {
                min: -1.2,
                max: 1.2
            }
        });

    },

    updateGraph: function () {

    }


};
var page = new Page();

// On Document Ready: Bind things to the
$(page.startup.bind(page));




