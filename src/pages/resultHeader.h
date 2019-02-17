const char resultHeader[] PROGMEM = R"=====(

	<!DOCTYPE html>
<html >
<head>
  <meta charset="UTF-8">
  <title>Rezultati</title>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0, user-scalable=0">
  <meta name="theme-color" content="#25BE9F" />
  <style>
    #dayBt {
      background:rgb(240, 248, 255, 0.25);
    }
    #allBt {
      background: none;
    }
    #day {
      display: block;
    }
    #all {
      display: none;
    }
  table {
      border-spacing: 1;
      border-collapse: collapse;
      background: transparent;
      border-radius: 8px;
      overflow: hidden;
      max-width: 800px;
      width: 100%;
      margin: 0 auto;
      position: relative;
    }
    table * {
      position: relative;
    }
    table td, table th {
      padding-left: 8px;
    }
    table thead tr {
      height: 30px;
      background:rgb(240, 248, 255, 0.25);
      color: aliceblue;
      font-size: 16px;
    }
    table tbody tr {
      height: 30px;
      border-bottom: 1px solid #E3F1D5;
      color: aliceblue;
    }
    table tbody tr:last-child {
      border: 0;
    }
    
    table td, table th {
      text-align: right;
    }
    table td.l, table th.l {
      text-align: left;
    }
    table td.c, table th.c {
      text-align: center;
    }
    table td.r, table th.r {
      text-align: right;
      padding-right: 8px;
    }
    
    table th.left {
      text-align: center;
      width: 50%;
    }
    table th.right {
      text-align: center;
      width: 50%;
    }
    
    
    body {
      background: linear-gradient(to right, #25c481, #25b7c4);
      font: 400 14px 'Calibri','Arial';
      padding: 20px;
    }
    
    
    
    h1{
      font-size: 30px;
      color: #fff;
      text-transform: uppercase;
      font-weight: 300;
      text-align: center;
      margin-bottom: 15px;
    }
    
    blockquote {
      color: white;
      text-align: center;
    }

    input[type=submit] {
			background-color: rgb(240, 248, 255, 0.25);
			border-radius: 8px;
			border: none;
			color: white;
			padding: 5px 11px;
			text-align: center;
			text-decoration: none;
			display: inline-block;
			font-size: 16px;
			margin: 4px 2px;
			cursor: pointer;
			min-height: 10px;
			min-width: 40px;
		}
    </style>

  
  
</head>

<body>
  <form action="/"> <input type="submit" value="Početna" /> </form>
  <h1>Rezultati</h1>
  <div>
    <table><thead><th id="dayBt" class="left" onclick='showToday(event)'>Danas</th> <th id="allBt" class="right" onclick='showAll(event)'>Svih vremena</th> </thead></table>
  </div>

  <div style="height: 10px;"></div>

  <script>
      function showToday() {
        var day = document.getElementById("day");
        var all = document.getElementById("all");
        day.style.display = 'block';
        all.style.display = 'none';
        var dayBt = document.getElementById("dayBt");
        var allBt = document.getElementById("allBt");
        dayBt.style.background = "rgb(240, 248, 255, 0.25)";
        allBt.style.background = 'none';

        
      }

      function showAll() {
        var day = document.getElementById("day");
        var all = document.getElementById("all");
        day.style.display = 'none';
        all.style.display = 'block';
        var dayBt = document.getElementById("dayBt");
        var allBt = document.getElementById("allBt");
        dayBt.style.background = 'none';
        allBt.style.background = "rgb(240, 248, 255, 0.25)";
      }
  </script>

  <div id ="day">
      <table>
      <thead>
        <tr>
          <th>#</th>
          <th class="l">Ime</th>
          <th>Vreme</th>
          <th class="c">Kasni</th>
        </tr>
      <thead>
      <tbody>

)=====";