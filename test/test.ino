#include "Result.hpp"
#include "LinkedList.h"

void setup()
{
	Serial.begin(9600);
	Result a("Mile", 5);
	Result b("Nikola", 2);
	Result c("Sara", 1);
	Result d("Spasoje", 6);
	Result e("milisav", 9);

	LinkedList<Result> l;
	l.add(a);
	l.add(b);
	l.add(c);
	l.add(d);
	l.add(e);
	l.sort(&Result::compare);

	for (uint8_t i = 0; i < l.size(); i++)
	{
		Serial.println(l.get(i).getName());
	}

}
void loop()
{

}

/////////////

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char *ssid = "Mambole";
const char *password = "everest8848";
ESP8266WebServer server(80); //instantiate server at port 80 (http port)

String page = "";
String text = "";
double data;

void setup(void)
{
	
	delay(1000);
	Serial.begin(115200);
	WiFi.begin(ssid, password); //begin WiFi connection
	Serial.println("");

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	server.on("/data.txt", []() {
		text = (String)data;
		server.send(200, "text/html", text);
	});
	server.on("/", []() {
		page = "<h1>Sensor to Node MCU Web Server</h1><h1>Data:</h1> <h1 id=\"data\">"
			   "</h1>\r\n";
		page += "<script>\r\n";
		page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
		page += "function loadData(url, callback){\r\n";
		page += "var xhttp = new XMLHttpRequest();\r\n";
		page += "xhttp.onreadystatechange = function(){\r\n";
		page += " if(this.readyState == 4 && this.status == 200){\r\n";
		page += " callback.apply(xhttp);\r\n";
		page += " }\r\n";
		page += "};\r\n";
		page += "xhttp.open(\"GET\", url, true);\r\n";
		page += "xhttp.send();\r\n";
		page += "}\r\n";
		page += "function updateData(){\r\n";
		page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
		page += "}\r\n";
		page += "</script>\r\n";
		server.send(200, "text/html", page);
	});

	server.begin();
	Serial.println("Web server started!");
}

void loop(void)
{
	data = millis();
	//delay(1000);
	server.handleClient();
}