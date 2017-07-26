#include "timing.h"
#include <Arduino.h>

double startTime;

void setStartTime(double val){
	startTime = val;
}

double getStartTime() {
	return startTime;
}

double seconds() {
	return (millis() - startTime) / 1000;
}
