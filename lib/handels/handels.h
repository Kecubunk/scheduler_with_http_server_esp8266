#ifndef __HANDELS_H
#define __HANDELS_H
// #include "main.h"
#include <arduino.h>
#include "pseudo_RTC_arduino.h"
#include <ESP8266WebServer.h>

const char HTTP_HEAD[] PROGMEM            = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>FordEscape Scheduler.</title>";
const char HTTP_STYLE[] PROGMEM           = "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:95%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;} .l{background: url(\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgAQAAAABbAUdZAAAAAmJLR0QAAKqNIzIAAAAJcEhZcwAABAAAAAQAARkjmmsAAAAZdEVYdFNvZnR3YXJlAHd3dy5pbmtzY2FwZS5vcmeb7jwaAAAAVUlEQVR42mP431D/nwFBPGBgxCD+AwGE+JF4HEQ04yLaQcR/OHGgnuFHcoM9kGCQZ/iRJtgPJKxBhDw7kOBjh7HAYoZAIh2kLrlBHmgbUO///x//AwCFIlEZF3XpyAAAAABJRU5ErkJggg==\") no-repeat left center;background-size: 1em;}</style>";
// const char HTTP_SCRIPT[] PROGMEM          = "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>";
const char HTTP_HEAD_END[] PROGMEM        = "</head><body><div style='text-align:left;display:inline-block;min-width:260px;'>";
const char HTTP_NO_TIMERS[] PROGMEM       = "<div>Timers have not set.<br /></div>";
const char HTTP_TOO_TIMERS[] PROGMEM      = "<div>Only 5 Timers could be set.<br /></div>";
const char HTTP_PORTAL_OPTIONS[] PROGMEM  = "<form action=\"/add\" method=\"get\"><button>Add timer.</button></form><br/><form action=\"/set\" method=\"get\"><button>Settings.</button></form>";
const char HTTP_ITEM[] PROGMEM            = "<div><span>{r}</span><a class='q' href='/add?n={n}'>Delete.</a></div>";
const char HTTP_FORM_START[] PROGMEM      = "<form method='get' action='{a}'><input id='h' name='h' length=2 placeholder='Hours'><br/><input id='m' name='m' length=2 placeholder='Minutes'>";
const char HTTP_FORM_PARAM[] PROGMEM      = "<br/><input id='{i}' name='{n}' maxlength={l} placeholder='{p}' value='{v}' {c}>";
const char HTTP_FORM_END[] PROGMEM        = "<br/><button type='submit'>Save</button></form>";
const char HTTP_HOME_LINK[] PROGMEM       = "<br/><div class=\"c\"><a href=\"/\">Back</a></div>";
const char HTTP_END[] PROGMEM             = "</div></body></html>";

void handleNotFound();
void handleAdd();
void handleRoot();
void handleSettings();

#endif /* __HANDELS_H */