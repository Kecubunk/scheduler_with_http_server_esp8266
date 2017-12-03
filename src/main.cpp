#include <arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "main.h"
#include "pseudo_RTC_arduino.h"
#include "handels.h"

ESP8266WebServer server(80);
RTC rtc;

void setup() {
	bool sdf = true; 
	Serial.begin(9600); 
	WiFi.mode(WIFI_AP);
	WiFi.softAP("Hello_IOT", "12345678");
	// server.on("/", std::bind(&handleRoot));
	server.on("/", handleRoot);
	server.on("/add", handleAdd);
	server.on("/set", handleSettings);
	server.onNotFound(handleNotFound); 
	server.begin();
	
}

void loop() {
	server.handleClient();
	rtc.handleTime();
	yield();
}