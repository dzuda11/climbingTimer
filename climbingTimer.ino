#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <FS.h>

#include "src/Result.hpp"
#include "src/LinkedList.h"
#include "src/Taster.hpp"
#include "src/Laser.hpp"

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

const char *filePath = "everList.txt";

ESP8266WebServer server(80);

LinkedList<Result> everList;
LinkedList<Result> todayList;

Laser hand(5);
Laser foot(4);
Taster readyBt(14);

//RGBLED footLED on 12  D6
//RGBLED handLED on 13  D7

bool finish = true;
unsigned long data = 0;

void setup()
{
	Serial.begin(115200);

	// if(!SPIFFS.begin())
	// 	Serial.println("faled to mount spiffs");
	if (readyBt.hold(3000))
		//clearEverFile();
	//loadEverList();

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
		checkAndWrite(name, todayList);
		if(checkAndWrite(name, everList))
			// saveToFile();
		
		data = 0;
	}

	server.send(200, "text/html", saveAndGo);
}

bool checkAndWrite(String name, LinkedList<Result> &list)
{
	bool ret = false;
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
		ret = true;
	}
	else if (list.get(index).getRecord() > data)
	{
		list.remove(index);
		list.add(Result(name, data));
		list.sort(&Result::compare);
		ret = true;
	}
	return ret;
}

/// Function below will compile but SPIFFS doesn't work on my ESP

void clearEverFile()
{
	SPIFFS.remove(filePath);
}

void loadEverList()
{
	File f = SPIFFS.open(filePath, "r");
	if (f)
	{
		everList.clear();
		String s, t;
		while((s=f.readStringUntil('\n')) != "" )
		{
			t = f.readStringUntil('\n');
			char ta[11];
			t.toCharArray(ta, 11);
			Serial.print(s + "  "); Serial.println(strtoul(ta, NULL, 10));
			everList.add(Result(s, strtoul(ta, NULL, 10)));
		}
		f.close();
	}
	else
	{
		Serial.println("Failed to load everList");
	}
}

void saveToFile()
{
	File f = SPIFFS.open(filePath, "w");
	if (f)
	{
		for (unsigned int i = 0; i < everList.size(); i++)
		{
			f.println(everList.get(i).getName());
			f.println(String(everList.get(i).getRecord()));
		}
	}
	else
	{
		Serial.println("Failed to write everList to file");
	}

}