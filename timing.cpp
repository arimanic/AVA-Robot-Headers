#include "timing.h"
#include <Arduino.h>

long startTime;
long stageTime;  // the time that the current stage started at

void setStartTime(long val){
	startTime = val;
}
long getStartTime() {
	return startTime;
}
double seconds() {
	return (double)(millis() - startTime) / 1000;
}
long milliseconds() {
	return millis() - startTime;
}

void setStageTime(long val) {
	stageTime = val;
}
long getStageTime() {
	return stageTime;
}
double stageSeconds() {
	return (double)(millis() - stageTime) / 1000;
}
long stageMilliseconds() {
	return millis() - stageTime;
}