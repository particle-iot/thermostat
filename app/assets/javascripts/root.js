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

            this.getGraphData(this.renderGraph.bind(this));
        },


        pollServer: function () {

        },

        getGraphData: function (callback) {
          $.when( 
                   $.get("actual_temp_readings.json"),
                   $.get("desired_temps.json")
               )
               .then(function (actual, desired) {
                   callback({
                       // jQuery returns something like [data payload, "success" jqr obj]
                       actual: actual[0],
                       desired: desired[0]
                   })
               });
            // var fakedata = this.makeFakeGraphData();
            // setTimeout(function () {
            //     callback(fakedata);
            // }, 250);
        },

        makeFakeGraphData: function () {
            //fake data
            var desired = [],
                actual = [];

            var starttime = (new Date()).getTime(),
                step = 60 * 1000,
                curTime = starttime;

            for (var i = 0; i < 24; i += 0.25) {
                curTime += step;
                desired.push([curTime, (Math.sin(i) * 0.75) + 72 ]);
                actual.push([curTime, (Math.sin(i) * 0.4) + 72  ]);
            }

            return {
                "desired": desired,
                "actual": actual
            }
        },


        renderGraph: function (data) {

            //TODO: calculate min/max?

            this.graph = $.plot("#realtime_graph",
                [
                    { data: data.desired, label: "desired temperature"},
                    { data: data.actual, label: "actual temperature"}
                ],
                {
                    series: {
                        lines: {
                            show: true
                        }
                    },
                    xaxes: [
                        { mode: "time" }
                    ],
                    yaxis: {
                        autoscaleMargin: 1.5
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
