const char saveTop[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>

<head>
	<meta charset="UTF-8">
	<title>Responsive Table</title>
	<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0, user-scalable=0">
	<meta name="theme-color" content="#25BE9F" />
	<style>
		body {
			background: linear-gradient(to right, #25c481, #25b7c4);
			font: 400 14px 'Calibri', 'Arial';
			padding: 20px;
		}

		h1 {
			font-size: 30px;
			color: aliceblue;
			text-transform: uppercase;
			font-weight: 300;
			text-align: center;
			margin-bottom: 15px;
		}

		blockquote {
			color: white;
			text-align: center;
		}

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
			min-height: 10px;
			min-width: 40px;
		}

		input[type=text] {
			text-align: left;
		}

		input[type=submint] {
			cursor: pointer;
		}

		::placeholder {
			color: aliceblue;
			opacity: 0.7;
			/* Firefox */
		}

		:-ms-input-placeholder {
			/* Internet Explorer 10-11 */
			color: aliceblue;
			opacity: 0.7;
		}

		::-ms-input-placeholder {
			/* Microsoft Edge */
			color: aliceblue;
			opacity: 0.7;
		}
	</style>

	<script>
		
	</script>
</head>

<body>
	<h1>Sačuvaj rezultat</h1>

	<center>
		<form action="/saveAndGo">
			<input type="text" id="fname" name="name" placeholder="Zovem se..." autocomplete="off" required="" 
			oninvalid="this.setCustomValidity('Unesi svoje ime!')"
			oninput="setCustomValidity('')">
			<br>
			<input type="text" id="lname" name="time" placeholder="

)=====";