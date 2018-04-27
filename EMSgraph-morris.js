<!DOCTYPE html>
<html>
<head>
<title>EMS Data | Home</title>

	<link rel="stylesheet" href="css/morris.css">
  	<script src="js/jquery.min.js"></script>
  	<script src="js/raphael-min.js"></script>
  	<script src="js/morris.min.js"></script>


	<script type="text/javascript">
	    $(document).ready(function(){
	               $.get('http://ocl-data-server.herokuapp.com/read/100', function(data){
				//console.log(data.result.length)
				var rain_graph = [];
				var ldr_graph = [];
				var uv_graph = [];
    		                var mq_graph = [];
				var temp_graph =[];
				var humi_graph = [];

			for(var i=0; i<100; i++) {
					rain_graph.push({'time_stamp': data.result[i].time_stamp, 'value': data.result[i].data.rain});
					ldr_graph.push({'time_stamp': data.result[i].time_stamp, 'value': data.result[i].data.ldr});
					uv_graph.push({'time_stamp': data.result[i].time_stamp, 'value': data.result[i].data.uv});
					mq_graph.push({'time_stamp': data.result[i].time_stamp, 'value': data.result[i].data.mq});
					temp_graph.push({'time_stamp': data.result[i].time_stamp, 'value': data.result[i].data.temp});
					humi_graph.push({'time_stamp': data.result[i].time_stamp, 'value': data.result[i].data.humi});

			}

			new Morris.Line({ element: 'rain', data: rain_graph, xkey: 'time_stamp', ykeys: ['value'], labels: ['Value'] });
			new Morris.Line({ element: 'ldr', data: ldr_graph, xkey: 'time_stamp', ykeys: ['value'], labels: ['Value'] });
			new Morris.Line({ element: 'uv', data: uv_graph, xkey: 'time_stamp', ykeys: ['value'], labels: ['Value'] });
			new Morris.Line({ element: 'mq', data: mq_graph, xkey: 'time_stamp', ykeys: ['value'], labels: ['Value'] });
			new Morris.Line({ element: 'temp', data: temp_graph, xkey: 'time_stamp', ykeys: ['value'], labels: ['Value'] });
			new Morris.Line({ element: 'humi', data: humi_graph, xkey: 'time_stamp', ykeys: ['value'], labels: ['Value'] });

		  })
      
	    })
	    
	  </script>
</head>
<body>
	<div id="rain" style="height: 250px;"></div>
	<div id="ldr" style="height: 250px;"></div>
        <div id="uv" style="height: 250px;"></div>
	<div id="mq" style="height: 250px;"></div>
	<div id="temp" style="height: 250px;"></div>
	<div id="humi" style="height: 250px;"></div>



</body>
</html>
