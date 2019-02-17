#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "src/Result.hpp"
#include "src/LinkedList.h"
#include "src/Taster.hpp"

#include "src/pages/resultHeader.h"
#include "src/pages/homePage.h"
#include "src/pages/resultMiddle.h"
#include "src/pages/resultFooter.h"
#include "src/pages/resultItem.h"
#include "src/pages/saveTop.h"
#include "src/pages/saveEnd.h"
#include "src/pages/saveAndGo.h"

const char *ssid = "AONS Speed climbing";
const char *password = "";

ESP8266WebServer server(80);

LinkedList<Result> everList;
LinkedList<Result> todayList;

Taster hand(5);
Taster foot(4);
Taster readyBt(14);

//RGBLED footLED(12, 13, 15);
//RGBLED handLED(16, 5, 4);

bool finish = true;
unsigned long data = 0;

void setup()
{
	Serial.begin(115200);

	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(IPAddress(10, 10, 10, 10), IPAddress(10, 10, 10, 10), IPAddress(255, 255, 255, 0));
	WiFi.softAP(ssid);
	server.on("/", handleRoot);
	server.on("/result", handleResult);
	server.on("/data", handleData);
	server.on("/save", handleSave);
	server.on("/saveAndGo", handleSaveAndGo);
	server.begin();
	Serial.println("Ready!\n\n");
}
void loop()
{
	while (!readyBt.on())
		server.handleClient();
	finish = false;
	if (!foot.on())
	{
		Serial.println("Put your foot on START! # footLED red");
		while (!foot.on())
			server.handleClient();
	}
	Serial.println("Foot is on the START# footLED yellow");
	Serial.println("# handLED yellow");
	while (foot.on())
		server.handleClient();

	unsigned long start = millis();
	while (!hand.on())
	{
		data = millis() - start;
		server.handleClient();
	}
	Serial.print("Your time is  ");
	Serial.println(data);
	finish = true;
	Serial.print("#leds green\n\n");
	while (!readyBt.on())
		server.handleClient();
	data = 0;
}

void handleRoot()
{
	server.send(200, "text/html", homePage);
}

void handleData()
{
	// {"finish":1, "time":2560}
	String str = "{\"finish\":" + String(finish) + ", \"time\":" + String(data) + "}";
	server.send(200, "text/html", str);
}

void handleResult()
{
	server.send(200, "text/html", generateResults());
}

String generateResults()
{

	String ret = resultHeader;

	ret += itemsList(todayList);
	ret += resultMiddle;
	ret += itemsList(everList);

	ret += resultFooter;
	return ret;
}

String itemsList(LinkedList<Result> &list)
{
	String ret = "";
	for (unsigned int i = 0; i < list.size(); i++)
	{
		String item = resultItem;
		item.replace("{n}", String(i + 1));
		item.replace("{name}", list.get(i).getName());
		item.replace("{time}", Result::recordString(list.get(i).getRecord()));
		unsigned long diff = list.get(i).getRecord() - list.get(0).getRecord();
		if (diff != 0)
		{
			if (diff < 60000)
				item.replace("{diff}", "-" + Result::recordString(diff));
			else
				item.replace("{diff}", "mnogo");
		}
		else
		{
			item.replace("{diff}", "");
		}
		ret += item;
	}
	return ret;
}

void handleSave()
{
	server.send(200, "text/html", saveTop + Result::recordString(data) + saveEnd);
}

void handleSaveAndGo()
{
	String name = "";
	if (server.args() > 0)
	{
		for (uint8_t i = 0; i < server.args(); i++)
		{
			if (server.argName(i) == "name")
			{
				name = server.arg(i);
			}
		}
		checkAndWrite (name, todayList);
		checkAndWrite (name, everList);
		data = 0;
	}

	server.send(200, "text/html", saveAndGo);
}

void checkAndWrite (String name, LinkedList<Result> &list)
{
	unsigned int index = -1;
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list.get(i).getName() == name)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		list.add(Result(name, data));
		list.sort(&Result::compare);
	}
	else if (list.get(index).getRecord() > data)
	{
		list.remove(index);
		list.add(Result(name, data));
		list.sort(&Result::compare);
	}
}