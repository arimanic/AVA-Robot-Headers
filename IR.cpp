#include <IR.h>
#include <Arduino.h>
#include "globConsts.h"
double IRs[numIR] = { 0 };
int irThresh;
long IRtimer;

void setIRTimer(long time) {
	IRtimer = time;
}

long getIRTimer() {
	return IRtimer;
}

long timeLeft(long time) {
	return IRtimer + 5000L - time;
}

void setIRThresh(int thresh) {
	irThresh = thresh;
	return;
}

int getIRThresh() {
	return irThresh;
}

// Function for stopping at the 10/1kHz gate
// returns true if any of the IR sensors read a value higher than the threshold set in the menu
bool gateStop() {
	bool a = false;
	bool b = false;
	getIRs();
	for (int i = 0; i < numIR; i++) {
		if (IRs[i] >= irThresh) {
			a = true;
			break;
		}
	}
	delay(30);
	getIRs();
	for (int j = 0; j < numIR; j++) {
		if (IRs[j] >= irThresh) {
			b = true;
			break;
		}

	}
	return a && b;
}

void getIRs() {
	// Reads all IR sensors and stores values in IRs array	
	IRs[0] = analogRead(IR0pin);
	IRs[1] = analogRead(IR1pin);
	IRs[2] = analogRead(IR2pin);
}

int getIR(int IRNum) {
	// Reads the given IR sensor, stores the value in IRs array and returns the value
	IRs[IRNum] = analogRead(IRNum);
	return IRs[IRNum];
}