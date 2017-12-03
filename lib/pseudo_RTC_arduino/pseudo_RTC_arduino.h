#ifndef __PSEUDO_RTC_H
#define __PSEUDO_RTC_H

#include <arduino.h>

#define AMOUNT_OF_EVENTS      5
// typedef enum { SUN = 0x00u,
// 	MON, TUE, WED, THU, FRI, SAT
// } xDays_e;

// typedef enum { JAN = 0x00u,
// 	FEB, MAR, APR, MAY, JUN, JUL, AUG, SEPT, OCT, NOV, DEC
// } xMonth_e;

// typedef enum { 
// 	"Sun." = 0x00u,
// 	"Mon.",
// 	"Tue.",
// 	"Wed.",
// 	"Thu.",
// 	"Fri.",
// 	"Sat."
// } xDays_e;

typedef struct {
	int seconds;
	int minutes;
	int hours;
} xTime_t;

typedef struct {
	int days;
	int month;
	int year;
} xDate_t;

typedef struct {
	int hours;
	int minutes;
	bool active;
} xEventTime_t;



class RTC {
public:
	RTC(): timeNow(0), timeLast(0), dailyErrorBehind(0), 
		availableEvents(0), correctedToday(1) {
		currentTime.seconds = 0;
		currentTime.minutes = 0;
		currentTime.hours = 0;
		currentDate.days = 3;
		currentDate.month = 0;
		currentDate.year = 0;
	};
	void handleTime();

	/// ????????
	unsigned int getSeconds();

	xDate_t getDate();
	xTime_t getTime();
	// String getDayAsStr();
	// String getMonthAsStr();
	// unsigned int getYear();

	void setTime(xTime_t& newTime);
	void setDate(xDate_t& newDate);

	void setEvent(xEventTime_t& newEvent);
	xEventTime_t getEvent(int number);
	// void deActivateEvent(int number);
	void deleteEvent(int number);
	unsigned int getEvents();

private:
	xEventTime_t events[AMOUNT_OF_EVENTS] = 
			{{6,25,false},{0,0,false},{0,0,false},
			{0,0,false},{0,0,false}};
	unsigned int availableEvents = 0;
	xDate_t currentDate;
	xTime_t currentTime;
	unsigned int startingHour = 0;
	unsigned long timeNow;
	unsigned long timeLast;
	int dailyErrorFast; // set the average number of milliseconds your 
						//microcontroller's time is fast on a daily basis
	int dailyErrorBehind; // set the average number of milliseconds your 
						//microcontroller's time is behind on a daily basis
	int correctedToday; // do not change this variable, one means that 
						//the time has already been corrected today for 
						//the error in your boards crystal. This is true 
						//for the first day because you just set the time 
						//when you uploaded the sketch.
};

#endif /*  __PSEUDO_RTC_H  */