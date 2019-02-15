const char homePage[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>

<head>
	<meta charset="UTF-8">
	<title>Rezultati</title>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<meta name="theme-color" content="#25BE9F" />
	<style>
		button{
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

		#save {
			opacity: 1;
			cursor: allowed;
		}

		#result {
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

	<p class="timerTxt">08.152</p>


	<center>
		<div id="but">
			<button id="save">Sačuvaj</button>
			<button id="result">Rezultati</button>
		</div>
	</center>
	</div>
</body>

</html>

)=====";