#include <TinahIO.h>
#include "sonar.h"
#include "PID.h"
#include "IR.h"
#include "globConsts.h"
//#include <phys253.h>
#include <Arduino.h>
#include "arrayHelpers.h"
#include <LiquidCrystal.h>
#include "armControl.h"

extern LiquidCrystal LCD;
extern int startbutton();
extern int stopbutton();
int side; // 0 if turn to right. 1 if turn to left

String params[] = { "P ", "I ", "D ", "G ", "IR ", "FlatSpeed ",  "RampSpeed ", "RingSpeed ", "Sml error ", "Med err ", "Lrg err ", "Huge err ", "Arm Spd ", "Fine Arm ", "Side " };
double vars[numVars] = { 0 };

void menu() {
	int param, printMenu;
	double var;
	setMotors(0, 0, 0);

	// Load in preloaded variables
	vars[0] = getKP();
	vars[1] = getKI();
	vars[2] = getKD();
	vars[3] = getControlGain();
	vars[4] = getIRThresh();
	vars[5] = getFlatSpeed();
	vars[6] = getRampSpeed();
	vars[7] = getRingSpeed();
	vars[8] = getSmallErr();
	vars[9] = getMedErr();
	vars[10] = getLargeErr();
	vars[11] = getHugeErr();
	vars[12] = getArmSpeed();
	vars[13] = getFineArmSpeed();
	vars[14] = getSide();

	LCD.clear();

	while (1) {

		printMenu++;
		if (printMenu > 400) {
			printMenu = 0;

			param = gatedKnobMap(7, 0, numVars - 1);

			if (params[param] == "IR ") {
				var = analogRead(6);
			}
			else if (params[param] == "FlatSpeed " || params[param] == "RingSpeed " || params[param] == "RampSpeed ") {
				var = analogRead(6) / 1023.0;
			}
			else if (params[param] == "Side ") {
				var = gatedKnobMap(6, 0, 1);
			}
			else if (params[param] == "Arm Spd " || params[param] == "Fine Arm ") {
				var = doubleMap(analogRead(6), 0, 1023, 0, 20000);
			}
			else {
				var = doubleMap(analogRead(6), 0, 1023, 0, paramMax);
			}

			if (params[param] == "Side ") {
				LCD.clear();
				LCD.print("Select turn");
				LCD.setCursor(0, 1);
				if (var == 1) {
					LCD.print("R");
				}
				else {
					LCD.print("L");
				}

			}
			else {
				LCD.clear();
				LCD.print(params[param]);
				LCD.print(var);
				if (params[param] == "T") {
					LCD.print(" Rs");
					LCD.print(digitalRead(QRD1pin));
					LCD.print(" Ls");
					LCD.print(digitalRead(QRD2pin));
					LCD.setCursor(0, 1);
					LCD.print(" Last = ");
					LCD.print(vars[param]);
				}
				else {
					LCD.setCursor(0, 1);
					LCD.print(" Last = ");
					LCD.print(vars[param]);
				}
			}
		}

		// Exit the menu and save parameters
		if (stopbutton()) {
			while (stopbutton()) {
			}
			setKP(vars[0]);
			setKI(vars[1]);
			setKD(vars[2]);
			setControlGain(vars[3]);
			setIRThresh(vars[4]);
			setFlatSpeed(vars[5]);
			setRampSpeed(vars[6]);
			setRingSpeed(vars[7]);
			setSmallErr(vars[8]);
			setMedErr(vars[9]);
			setLargeErr(vars[10]);
			setHugeErr(vars[11]);
			setArmSpeed(vars[12]);
			setFineArmSpeed(vars[13]);
			setSide(vars[14]);
			LCD.clear();
			return;

		}

		// Save the current variable
		if (startbutton()) {
			while (startbutton()) {
			}
			vars[param] = var;
		}
	}
}
void printParams() {
	// Print all parameters to screen
	//!!! change these to get functions.
	//P
	LCD.clear();
	LCD.print(params[0]);
	LCD.print(getKP());
	LCD.print(" ");

	// I
	LCD.print(params[1]);
	LCD.print(getKI());
	LCD.print(" ");

	// D
	LCD.setCursor(0, 1);
	LCD.print(params[2]);
	LCD.print(getKD());
	LCD.print(" ");

	// controlGain
	LCD.print(params[3]);
	LCD.print(getControlGain());
	LCD.print(" ");

	/*  // irThresh
	LCD.print(params[4]);
	LCD.print(getIRThresh());
	LCD.print(" ");

	// speedScale
	LCD.print(params[5]);
	LCD.print(getSpeedScale());
	LCD.print(" "); */
}
void printQRDs() {
	LCD.print(getQRD(0));
	LCD.print(getQRD(1));
	LCD.print(getQRD(2));
	LCD.print(getQRD(3));
	LCD.print(" ");
}

void initConsts(double p, double i, double d, double g, double IR, double flat, double ramp, double ring, int smallErr, int medErr, int largeErr, int hugeErr, double armSpeed, double fineArmSpeed, int side) {
	setKP(p);
	setKI(i);
	setKD(d);
	setControlGain(g);
	setFlatSpeed(flat);
	setRampSpeed(ramp);
	setRingSpeed(ring);
	setIRThresh(IR);
	setSmallErr(smallErr);
	setMedErr(medErr);
	setLargeErr(largeErr);
	setHugeErr(hugeErr);
	setArmSpeed(armSpeed);
	setFineArmSpeed(fineArmSpeed);
}
void setPIDG(double p, double i, double d, double g) {
	setKP(p);
	setKI(i);
	setKD(d);
	setControlGain(g);
}
void setSpeeds(double flat, double ramp, double ring) {
	setFlatSpeed(flat);
	setRampSpeed(ramp);
	setRingSpeed(ring);
}
void setErrors(int smallErr, int medErr, int largeErr, int hugeErr) {
	setSmallErr(smallErr);
	setMedErr(medErr);
	setLargeErr(largeErr);
	setHugeErr(hugeErr);
}
void setArmSpeeds(double armSpeed, double fineArmSpeed) {
	setArmSpeed(armSpeed);
	setFineArmSpeed(fineArmSpeed);
}

double doubleMap(double x, double in_min, double in_max, double out_min, double out_max) {
	return (double)(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
double gatedKnobMap(int port, double outMin, double outMax) {
	double out = doubleMap(analogRead(port), 50, 950, outMin, outMax);
	if (out > outMax) {
		out = outMax;
	}
	else if (out < outMin) {
		out = outMin;
	}

	return out;
}
int gatedKnobMap(int port, int outMin, int outMax) {
	int out = map(analogRead(port), 50, 950, outMin, outMax);
	if (out > outMax) {
		out = outMax;
	}
	else if (out < outMin) {
		out = outMin;
	}

	return out;
}
double knobToVolt(int knob) {
	return analogRead(knob)*5.0 / 1024.0;
}
double constrainNum(double val, double min, double max) {
	if (val < min) {
		return min;
	}
	if (val > max) {
		return max;
	}
	return val;
}

void setSide(int val) {
	side = val;
}
int getSide() {
	return side;
}
bool leftSide() {
	return side;
}
