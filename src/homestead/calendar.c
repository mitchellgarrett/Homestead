#include <homestead/calendar.h>
#include <malloc.h>

const int DAYS_IN_SEASON = 15;
char* season_names[] = { "Spring", "Summer", "Fall", "Winter" };

Calendar* newCalendar() {
	Calendar* calendar = (Calendar*)malloc(sizeof(Calendar));
	calendar->year = 1;
	calendar->season = Spring;
	calendar->day = 1;
	return calendar;
}

void nextDay(Calendar* calendar) {
	calendar->day++;
	if (calendar->day >= DAYS_IN_SEASON) {
		calendar->day = 1;
		nextSeason(calendar);
	}
}

void nextSeason(Calendar* calendar) {
	calendar->season++;
	if (calendar->season >= Winter) {
		calendar->season = Spring;
		nextYear(calendar);
	}
}

void nextYear(Calendar* calendar) {
	calendar->year++;
}

char* getSeasonName(Season season) {
	return season_names[season];
}