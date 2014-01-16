// Place all the behaviors and hooks related to the matching controller here.
// All this logic will automatically be available in application.js.

(function ($) {

    var Page = function () {
        //
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

            var starttime = (new Date()).getTime(),
                step = 60 * 1000,
                //endtime = starttime + (step * 60),
                curTime = starttime;


            //fake data
            var sin = [],
                cos = [];

            for (var i = 0; i < 24; i += 0.25) {
                curTime += step;
                sin.push([curTime, (Math.sin(i) + 72) ]);
                cos.push([curTime, ((Math.sin(i) * 0.50) + 72)  ]);
            }

            this.graph = $.plot("#realtime_graph", [
                { data: sin, label: "desired temperature"},
                { data: cos, label: "actual temperature"}
            ], {
                series: {
                    lines: {
                        show: true
                    }
                },
                xaxes: [ { mode: "time" } ],
                yaxis: {
                    min: 65,
                    max: 80
                }
            });

        },

        updateGraph: function () {
            // call this.graph.setupGrid() -- if the axes change

            //
            // this.graph.setData([ newData ]);
            // this.graph.draw();
        }


    };


    // -----
    //
    // -----


    var page = new Page();

    // On Document Ready: Bind things to the
    $(page.startup.bind(page));


})(jQuery);