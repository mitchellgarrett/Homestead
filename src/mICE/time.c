#include <mICE/time.h>

#include <time.h>

time_t start_time;
time_t prev_time;
time_t curr_time;

void initTime() {
	time(&start_time);
	prev_time = curr_time = start_time;
}

void updateTime() {
	prev_time = curr_time;
	time(&curr_time);
}

double getTime() {
	return difftime(curr_time, start_time);
}

double deltaTime() {
	return difftime(curr_time, prev_time);
}