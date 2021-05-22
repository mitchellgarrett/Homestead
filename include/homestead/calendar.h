#ifndef TRIBAL_CALENDAR
#define HOMESTEAD_CALENDAR

typedef enum Season { Spring, Summer, Fall, Winter } Season;
const int DAYS_IN_SEASON;

typedef struct Calendar {
	int year;
	Season season;
	int day;
} Calendar;

Calendar* newCalendar();
void nextDay(Calendar* calendar);
void nextSeason(Calendar* calendar);
void nextYear(Calendar* calendar);
char* getSeasonName(Season season);

#endif
