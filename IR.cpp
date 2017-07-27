#include <IR.h>
#include <Arduino.h>
#include <globConsts.h>
double IRs[numIR] = { 0 };
int irThresh;

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
	getIRs();
	for (int i = 0; i < numIR; i++) {
		if (IRs[i] >= irThresh) {
			return true;
		}
	}
	return false;
}

void getIRs() {
	// Reads all IR sensors and stores values in IRs array
	for (int IRindex = 0; IRindex < numIR; IRindex++) {
		IRs[IRindex] = analogRead(IRindex);
	}
}

int getIR(int IRNum) {
	// Reads the given IR sensor, stores the value in IRs array and returns the value
	IRs[IRNum] = analogRead(IRNum);
	return IRs[IRNum];
}