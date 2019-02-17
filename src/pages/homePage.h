const char homePage[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>

<head>
	<meta charset="UTF-8">
	<title>AONS Speed climbing</title>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<meta name="theme-color" content="#25BE9F" />
	<style>
		input {
			background-color: rgb(240, 248, 255, 0.25);
			border-radius: 8px;
			border: none;
			color: white;
			padding: 15px 32px;
			text-align: center;
			text-decoration: none;
			display: inline-block;
			font-size: 16px;
			margin: 4px 2px;
			cursor: pointer;
			min-height: 10px;
			min-width: 40px;
		}

		input[type="submit"]:disabled {
			opacity: 0.6;
			cursor: not-allowed;
		}

		a {
			color: aliceblue;
			text-decoration: none;
		}

		a:focus {
			outline: none !important;
		}

		a:hover {
			text-decoration: none !important;
		}

		body {
			background: linear-gradient(to right, #25c481, #25b7c4);
			font: 400 14px 'Calibri', 'Arial';
			padding: 0px;
		}


		p.timerTxt {
			margin-top: 10%;
			margin-bottom: 10%;
			position: relative;
			color: aliceblue;
			font-size: 16vw;
			text-align: center;

		}
	</style>

</head>

<body>

	<p id="mile" class="timerTxt">08.152</p>
	<center>
		<div style="display: inline-block">
			<form action="/save"> <input id="saveBt" type="submit" value="Sačuvaj" disabled /> </form>
		</div>
		<div style="display: inline-block">
			<form action="/result"> <input id="resultBt" type="submit" value="Rezultati" /> </form>
		</div>
	</center>
	</div>

	<script>
		var myTimedAction;
		var millis;
		var seted = false;

		var x = setInterval(function() {loadData("data",controlTimer)}, 100);
   		function loadData(url, callback){
   		var xhttp = new XMLHttpRequest();
   		xhttp.onreadystatechange = function(){
   		 if(this.readyState == 4 && this.status == 200){
   		 callback.apply(xhttp);
   		 }
   		};
   		xhttp.open("GET", url, true);
   		xhttp.send();
   		}
		
   		function controlTimer(){
			var myObj = JSON.parse(this.responseText);
			if(myObj.finish == 1 && myObj.time == 0){
				document.getElementById("mile").innerHTML = "--.---";

				document.getElementById('saveBt').disabled = true;
				document.getElementById('resultBt').disabled = false;
			}
			if(myObj.finish == 0 && myObj.time == 0){
				document.getElementById("mile").innerHTML = "00.000";

				document.getElementById('saveBt').disabled = true;
				document.getElementById('resultBt').disabled = true;
			}
			if(myObj.finish == 0 && myObj.time != 0){
				if (seted == false) {
					millis = myObj.time;
					myTimedAction = setInterval(timerRun, 17);
					seted = true;

					document.getElementById('saveBt').disabled = true;
					document.getElementById('resultBt').disabled = true;
				}
			}
			if(myObj.finish == 1 && myObj.time != 0){
				clearInterval(myTimedAction);
				seted = false;
				millis = myObj.time;
				parseTime();

				document.getElementById('saveBt').disabled = false;
				document.getElementById('resultBt').disabled = false;
			}
   		}
		function timerRun() {
			millis += 17;
			parseTime();
		}
		
		function parseTime(){
			var milliseconds = parseInt((millis % 1000)),
  			  seconds = parseInt((millis / 1000) % 60),
  			  minutes = parseInt((millis / (1000 * 60)) % 60);

  			minutes = (minutes < 10) ? "0" + minutes : minutes;
  			seconds = (seconds < 10) ? "0" + seconds : seconds;
			milliseconds = (milliseconds < 10) ? "0" + milliseconds : milliseconds;
            milliseconds = (milliseconds < 100) ? "0" + milliseconds : milliseconds;

  			var ret = "";
            if (minutes > 0){
            	ret += minutes + ":";
                }
            ret += seconds + "." + milliseconds;
			document.getElementById("mile").innerHTML = ret;
            }

	</script>

</body>

</html>

)=====";