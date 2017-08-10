#include <IR.h>
#include <Arduino.h>
#include "globConsts.h"

int readCount = 0;

double prevSum0 = 0;
double prevSum1 = 0;
double prevSum2 = 0;

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
	int numLoops = 20;
	double sum0 = 0;
	double sum1 = 0;
	double sum2 = 0;

	double totSum0 = 0;
	double totSum1 = 0;
	double totSum2 = 0;

	for (int i = 0; i < numLoops; i++) {
		getIRs();
		sum0 += IRs[0];
		sum1 += IRs[1];
		sum2 += IRs[2];
	}
	totSum0 = (sum0 + prevSum0) / (2*numLoops);
	totSum1 = (sum1 + prevSum1) / (2 * numLoops);
	totSum2 = (sum2 + prevSum2) / (2 * numLoops);

	prevSum0 = sum0;
	prevSum1 = sum1;
	prevSum2 = sum2;

	Serial.print(totSum0);
	Serial.print(" ");
	Serial.print(totSum1);
	Serial.print(" ");
	Serial.println(totSum2);
		
	return totSum0 > irThresh || totSum1 > irThresh || totSum2 > irThresh;
}

/*bool gateStop() {
	getIRs();
	for (int i = 0; i < numIR; i++) {
		if (IRs[i] >= irThresh) {
			delayMicroseconds(1);
			getIR(i);
			if (IRs[i]) {
				return true;
			}
		}
	}
	return false;
}*/

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