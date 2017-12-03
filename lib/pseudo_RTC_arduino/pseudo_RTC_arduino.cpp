#include "pseudo_RTC_arduino.h"


void RTC::handleTime() {
	timeNow = millis()/1000; // the number of milliseconds that have passed since boot
	currentTime.seconds = timeNow - timeLast;
//the number of seconds that have passed since the last time 60 seconds was reached.
if (currentTime.seconds == 60) {
	timeLast = timeNow;
	currentTime.minutes += 1; 
}
//if one minute has passed, start counting milliseconds from zero again and add one minute to the clock.
if (currentTime.minutes == 60){
	currentTime.minutes = 0;
	currentTime.hours += 1; 
}
// if one hour has passed, start counting minutes from zero and add one hour to the clock
if (currentTime.hours == 24){
	currentTime.hours = 0;
	currentDate.days += 1;
}
//if 24 hours have passed, add one day
if (currentTime.hours ==(24 - startingHour) && correctedToday == 0){
	delay(dailyErrorFast*1000);
	currentTime.seconds += dailyErrorBehind;
	correctedToday = 1; 
}

//every time 24 hours have passed since the initial starting time and it has not been reset this day before, add milliseconds or delay the program with some milliseconds.
//Change these varialbes according to the error of your board.
// The only way to find out how far off your boards internal clock is, is by uploading this sketch at exactly the same time as the real time, letting it run for a few days
// and then determining how many seconds slow/fast your boards internal clock is on a daily average. (24 hours).
if (currentTime.hours == 24 - startingHour + 2) {
	correctedToday = 0; 
}

}

unsigned int RTC::getSeconds(){
	return currentTime.seconds;
}


void RTC::setTime(xTime_t& newTime){
	currentTime.hours = newTime.hours;
	currentTime.minutes = newTime.minutes;
	timeLast = ((millis()/1000) - newTime.seconds);
	startingHour = newTime.hours;
	correctedToday = 1;
}

xTime_t RTC::getTime(){
	return currentTime;
}

xDate_t RTC::getDate(){
	return currentDate;
}

void RTC::setDate(xDate_t& newDate){
	currentDate.days = newDate.days;
	currentDate.month = newDate.month;
	currentDate.year = newDate.year;
}

void RTC::setEvent(xEventTime_t& newEvent){
	if (getEvents() != AMOUNT_OF_EVENTS) {
		for (unsigned int i=0; i<AMOUNT_OF_EVENTS; i++){
			if (events[i].active == false){
				events[i].minutes = newEvent.minutes;
				events[i].hours   = newEvent.hours;
				events[i].active  = true;
				availableEvents++;	
				break;		
			}
		}
	}
}

void RTC::deleteEvent(int number){
	events[number].active = false;
	availableEvents--;
}

xEventTime_t RTC::getEvent(int number){
	return events[number];
}

unsigned int RTC::getEvents(){
	return availableEvents;
}