#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "src/Result.hpp"
#include "src/LinkedList.h"
#include "src/Taster.hpp"

const char* ssid = "AONS Speed climbing";
const char* password = "";

ESP8266WebServer server(80);
DNSServer dnsServer;

Taster foot(5);
Taster hand(4);
Taster readyBt(14);
bool ready = false;

void setup()
{
	Serial.begin(115200);

	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(IPAddress(10, 10, 10, 10), IPAddress(10, 10, 10, 10), IPAddress(255, 255, 255, 0));
	WiFi.softAP(ssid);

	dnsServer.reset(new DNSServer());
	dnsServer.start(53, "*", WiFi.softAPIP());

	server.on("/", handleRoot);
	server.begin();
	Serial.println("Ready!\n\n");

}
void loop()
{
	while (!readyBt.on() && !ready) server.handleClient();;
	if (!foot.on())
	{
		Serial.println("Put your foot on START!");
		while (!foot.on()) server.handleClient();
	}
	while(foot.on()) server.handleClient();

	unsigned long start = millis();
	while(!hand.on()) server.handleClient();
	Serial.print("Your time is  ");
	Serial.println(millis() - start);
	Serial.print("\n\n");
	while (!readyBt.on()) server.handleClient();
}

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}