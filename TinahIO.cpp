#include <TinahIO.h>
#include "sonar.h"
#include "PID.h"
#include "IR.h"
#include "globConsts.h"
//#include <phys253.h>
#include <Arduino.h>
#include "arrayHelpers.h"
#include <LiquidCrystal.h>

extern LiquidCrystal LCD;
extern int startbutton();
extern int stopbutton();

String params[] = { "P", "I", "D", "G", "T", "FlatSpeed ",  "RampSpeed ", "RingSpeed ", "X", "S Thresh" };
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

	LCD.clear();

	while (1) {

		printMenu++;
		if (printMenu > 400) {
			printMenu = 0;

			param = gatedKnobMap(7, 0, numVars - 1);

			if (params[param] == "T") {
				var = analogRead(6);
			}
			else if (params[param] == "FlatSpeed " || params[param] == "RingSpeed " || params[param] == "RampSpeed ") {
				var = analogRead(6) / 1023.0;
			}
			else if (params[param] == "X") {
				var = doubleMap(analogRead(6), 0, 1023, 0, 1);
			}
			else {
				var = doubleMap(analogRead(6), 0, 1023, 0, paramMax);
			}

			if (params[param] == "X") {
				LCD.clear();
				LCD.print("Select side");
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
			setSonarThresh(vars[9]);
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

void initConsts(double p, double i, double d, double g, double t, double flat, double ramp, double ring,  int x, double son) {
	double arr[numVars] = { p, i, d, g, t, flat, ramp, ring,  x, son };
	setArray(vars, arr, numVars);
	setKP(p);
	setKI(i);
	setKD(d);
	setControlGain(g);
	setFlatSpeed(flat);
	setRampSpeed(ramp);
	setRingSpeed(ring);
	setIRThresh(t);
	setSonarThresh(son);
}


double doubleMap(double x, double in_min, double in_max, double out_min, double out_max) {
	return (double)(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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

bool leftSide() {
	return vars[numVars - 2];
}

void printQRDs() {
	LCD.print(getQRD(0));
	LCD.print(getQRD(1));
	LCD.print(getQRD(2));
	LCD.print(getQRD(3));
	LCD.print(" ");
}