#include "handels.h"

extern RTC rtc;
extern ESP8266WebServer server;
     xTime_t Time;
xEventTime_t Event;

String rendListEvents();
String rendHead      ();
String rendTime      (xTime_t time);
String toStringIp    (IPAddress ip);
  void redirectHome  ();


void handleNotFound(){
	String page = "File Not Found\n\nURI: ";
	page += server.uri() + "\nMethod: ";
	page += (server.method() == HTTP_GET)?"GET":"POST";
	page += "\nArguments: ";
	page += server.args();
	page += "\n";
	for (uint8_t i=0; i<server.args(); i++){
		page += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", page);
}

void handleAdd(){
	if (server.args() != 0) {
// remove event and redirect to home page
		if (server.hasArg("n")) {
			rtc.deleteEvent(server.arg("n").toInt());
// adding event and redirect to home page
		} else if (server.hasArg("h") & server.hasArg("m")) {
			Event.hours = (unsigned int)server.arg("h").toInt();
			Event.minutes = (unsigned int)server.arg("m").toInt();
			rtc.setEvent(Event);
		}
		redirectHome();
	} else { // rendering ADD page
		String page = rendHead();
		page += F("<h3>Adding a timer.</h3>");
		page += rendListEvents();
		if (rtc.getEvents() == AMOUNT_OF_EVENTS){
			page += FPSTR(HTTP_TOO_TIMERS);
		} else {
			// represent adding Timer
			page += F("<div>Fill up hours and minutes.</div>");
			page += FPSTR(HTTP_FORM_START);
			page.replace("{a}", "add");
			page += FPSTR(HTTP_FORM_END);
		}
		page += FPSTR(HTTP_HOME_LINK);
		page += FPSTR(HTTP_END);
		server.sendHeader("Content-Length", String(page.length()));
		server.send(200, "text/html", page);
	}
}

void handleSettings(){
	if (server.args() != 0) { // save time and redirect to home page
		// TODO check date
		Time.hours = (unsigned int)server.arg("h").toInt();
		Time.minutes = (unsigned int)server.arg("m").toInt();
		Time.seconds = (unsigned int)server.arg("s").toInt();
		rtc.setTime(Time);
		redirectHome();
	} else { // rendering SET_TIME page
		String page = rendHead();
		page += F("<h3>Setting Time.</h3>");
		page += rendTime(rtc.getTime());
		page += FPSTR(HTTP_FORM_START);
		page.replace("{a}", "set");

		String item = FPSTR(HTTP_FORM_PARAM);
		item.replace("{i}", "s");
		item.replace("{n}", "s");
		item.replace("{p}", "Seconds");
		item.replace("{l}", "2");
		item.replace("{v}", "");
		page += item;

		page += FPSTR(HTTP_FORM_END);
		page += FPSTR(HTTP_HOME_LINK);
		page += FPSTR(HTTP_END);
		server.sendHeader("Content-Length", String(page.length()));
		server.send(200, "text/html", page);
	}
}

void handleRoot() {
	String page = rendHead();
	page += F("<h3>FordEscape Scheduler.</h3>");
	page += rendTime(rtc.getTime());
	page += rendListEvents();
	page += FPSTR(HTTP_PORTAL_OPTIONS);
	page += FPSTR(HTTP_END);
	server.sendHeader("Content-Length", String(page.length()));
	server.send(200, "text/html", page);
}

String rendListEvents(){
	String page;
	page = F("<div>List of set Timers below:</div>");
	if(rtc.getEvents() != 0){
		String item;
		for (unsigned int i=0; i<AMOUNT_OF_EVENTS; i++){
			Event = rtc.getEvent(i);
			if (Event.active == true){
				item = FPSTR(HTTP_ITEM);
				String eventStr = "Timer set on ";
				eventStr += (String)Event.hours + String(":");
				eventStr += (String)Event.minutes;
				item.replace("{r}", eventStr);
				item.replace("{n}", (String)i);
				page += item;	
			}		
		}
	} else {
		page += FPSTR(HTTP_NO_TIMERS);
	}
	return page;
}

String rendHead(){
	String page = FPSTR(HTTP_HEAD);
		    // page += FPSTR(HTTP_SCRIPT);
	       page += FPSTR(HTTP_STYLE);
		    page += FPSTR(HTTP_HEAD_END);
	return page;
}

String rendTime(xTime_t time){
	String page = F("<div>Time in controller is ");
		   page += (String)time.hours + ":";
	       page += (String)time.minutes + "  ";
		   page += (String)time.seconds;
		   page += F(" seconds.</div>");
	return page;
}

void redirectHome(){
	server.sendHeader("Location", String("http://") + toStringIp(server.client().localIP()), true);
    server.send ( 302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.client().stop(); // Stop is needed because we sent no content length
}

String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}