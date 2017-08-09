#include <Arduino.h>
#include "globConsts.h"
#include "ServoTINAH.h"
#include "motor.h"
#include "armControl.h"
#include "TinahIO.h"

// Arm movement is controlled by these functions.
// Movement is split into upper arm, lower arm, and base servo
// The upper and lower arms are controlled by motor feedback loops. 
// On each iteration the loop reads the displacement from the desired position and produces a 
// motor speed towards the desired position. The speed is proportional to the displacement.

// define a numerical value for each arm position
// define the voltage reading of the upper and lower Pot for each position.
// There are 4 positions: Driving   (D)
//                        Collecting (C)
//                        Fishing   (F)
//                        Zipline   (Z)



int armSpeed = 800; // > 0.07 , 4000 < 0.07
int fineCorrSpeed = 15000;
bool armSafe;
double relLowerPos;
double relUpperPos;

extern motorClass motor;

extern ServoTINAH RCServo0;
extern ServoTINAH RCServo1;
extern ServoTINAH RCServo2;


void setArmSpeed(int speed) {
	armSpeed = speed;
}
void setFineArmSpeed(int speed) {
	fineCorrSpeed = speed;
}
void setArmSafe(bool safe) {
	armSafe = safe;
}

int getArmSpeed() {
	return armSpeed;
}
int getFineArmSpeed() {
	return fineCorrSpeed;
}
double getBaseMotorPot() {
	//Read the analog voltage value of the Potentiometer at the base of the arm
	// 0 - 5
	return analogRead(armBasePotPin)*5.0 / 1024.0;
}
double getHingeMotorPot() {
	//Read the analog voltage value of the Potentiometer at the hinge of the arm
	// 0 -5
	return analogRead(armHingePotPin)*5.0 / 1024.0;
}
double getRelLowerPos(double voltage) {
	return getBaseMotorPot() - voltage;
}
double getRelLowerPos(int pos) {
	// Determines if the lower portion of the arm is at the position passed as pos
	// returns a negative number if the position is low. Positive number if high. 0 if at the right spot
	double voltRead = getBaseMotorPot();

	switch (pos) {
	case toyZero:
		return voltRead - baseZero;
	case toyOne:
		return voltRead - baseOne;
	case toyTwo:
		return voltRead - baseTwo;
	case toyThree:
		return voltRead - baseThree;
	case toyFour:
		return voltRead - baseFour;
	case toyFive:
		return voltRead - baseFive;
	case drivePos:
		return voltRead - baseD;
	case zipPos:
		return voltRead - baseZ;
	case irPos:
		return voltRead - baseIR;
	case gatePos:
		return voltRead - baseGate;
	}
}
double getRelUpperPos(double voltage) {
	return getHingeMotorPot() - voltage;
}
double getRelUpperPos(int pos) {
	// Determines if the upper portion of the arm is at the position passed as pos
	// returns a negative number if the position is low. Positive number if high. 0 if at the right spot
	double voltRead = getHingeMotorPot();
	switch (pos) {
	case toyZero:
		return voltRead - hingeZero;
	case toyOne:
		return voltRead - hingeOne;
	case toyTwo:
		return voltRead - hingeTwo;
	case toyThree:
		return voltRead - hingeThree;
	case toyFour:
		return voltRead - hingeFour;
	case toyFive:
		return voltRead - hingeFive;

	case drivePos:
		return voltRead - hingeD;
	case zipPos:
		return voltRead - hingeZ;
	case irPos:
		return voltRead - hingeIR;
	case gatePos:
		return voltRead - hingeGate;

	}
}
bool getArmSafe() {
	return armSafe;
}

bool atLowerPos(int pos) {
	//Determine if the lower portion of the arm are in the position passed
	double relLower = getRelLowerPos(pos);
	return abs(relLower) <= voltageRange;
}
bool atUpperPos(int pos) {
	//Determine if the upper portion of the arm are in the position passed
	double relUpper = getRelUpperPos(pos);
	return abs(relUpper) <= voltageRange;
}

bool atUpperPos(double voltage) {
	double relUpper = getRelUpperPos(voltage);
	return abs(relUpper) <= voltageRange;
}

bool atLowerPos(double voltage) {
	//Determine if the lower portion of the arm are in the position passed
	double relLower = getRelLowerPos(voltage);
	return abs(relLower) <= voltageRange;
}
bool atBothPos(int pos) {
	// Determines if the upper and lower portions of the arm are at the position passed as pos within the error range defined as voltageRange
	return atUpperPos(pos) && atLowerPos(pos);
}

void moveLowerArm(int pos) {

	double newRelLowerPos = getRelLowerPos(pos);
	if (newRelLowerPos - relLowerPos < 0.02 && atLowerPos(pos)) {
		motor.stop(armBaseMotorPin);
	}
	else {
		relLowerPos = newRelLowerPos;
		if (abs(relLowerPos) > fineCorrRange) {
			motor.speed(armBaseMotorPin, -armSpeed * relLowerPos);
		}
		else if (abs(relLowerPos) <= fineCorrRange) {
			motor.speed(armBaseMotorPin, -fineCorrSpeed * relLowerPos);
		}
	}
	return;
}
void moveLowerArm(double voltage) {

	if (atLowerPos(voltage)) {
		motor.stop(armBaseMotorPin);
	} else if (abs(getRelLowerPos(voltage)) > fineCorrRange) {
		motor.speed(armBaseMotorPin, -armSpeed * getRelLowerPos(voltage));
	}
	else if (abs(getRelLowerPos(voltage)) <= fineCorrRange) {
		motor.speed(armBaseMotorPin, -fineCorrSpeed * getRelLowerPos(voltage));
	}
	else {
		motor.stop(armBaseMotorPin);
	}
	return;
}
void moveUpperArm(int pos) {
	double newRelUpperPos = getRelUpperPos(pos);
	if (newRelUpperPos - relUpperPos < 0.02 && atUpperPos(pos)) {
		motor.stop(armHingeMotorPin);
	}
	else {
		relUpperPos = newRelUpperPos;
		if (abs(relUpperPos) > fineCorrRange) {
			motor.speed(armHingeMotorPin, -armSpeed * relUpperPos);
		}
		else if (abs(relUpperPos) <= fineCorrRange) {
			motor.speed(armHingeMotorPin, -fineCorrSpeed * relUpperPos);
		}
	}
	return;
}
void moveUpperArm(double voltage) {
	if (atUpperPos(voltage)) {
		motor.stop(armHingeMotorPin);
	} else 	if (abs(getRelUpperPos(voltage)) > fineCorrRange) {
		motor.speed(armHingeMotorPin, -armSpeed * getRelUpperPos(voltage));
	}
	else if (abs(getRelUpperPos(voltage)) <= fineCorrRange) {
		motor.speed(armHingeMotorPin, -fineCorrSpeed * getRelUpperPos(voltage));
	}
	else {
		motor.stop(armHingeMotorPin);
	}
	return;
}
void moveBaseServo(int val) {
	// Moves the base servo to the desired position. 90 is pointed forward
	if (val > 179) {
		val = 179;
	}
	else if (val < 0) {
		val = 0;
	}

	RCServo0.write(val);
	return;
}
void moveBaseServoPos(int pos) {
	switch (pos) {
		case toyZero:
			RCServo0.write(servoZero);
			break;
		case toyOne:
			RCServo0.write(servoOne);
			break;
		case toyTwo:
			RCServo0.write(servoTwo);
			break;
		case toyThree:
			RCServo0.write(servoThree);
			break;
		case toyFour:
			RCServo0.write(servoFour);
			break;
		case toyFive:
			RCServo0.write(servoFive);
			break;

		case drivePos:
			RCServo0.write(servoD);
			break;
		case zipPos:
			RCServo0.write(servoZ);
			break;
		case irPos:
			if (leftSide()) {
				RCServo0.write(servoIR - 5);
			}
			else {
				RCServo0.write(servoIR + 5);
			}
			break;
		case gatePos:
			RCServo0.write(servoGate);
			break;
	}
}
void activateArmServo() {
	RCServo1.write(100);

}
void resetArmServo() {
	RCServo1.write(180);
}
void moveEndServo(int pos) {
	switch (pos) {
		case toyZero:
			RCServo2.write(endServoZero);
			break;
		case toyOne:
			RCServo2.write(endServoOne);
			break;
		case toyTwo:
			RCServo2.write(endServoTwo);
			break;
		case toyThree:
			RCServo2.write(endServoThree);
			break;
		case toyFour:
			RCServo2.write(endServoFour);
			break;
		case toyFive:
			RCServo2.write(endServoFive);
			break;
		case drivePos:
			RCServo2.write(endServoD);
			break;
		case zipPos:
			RCServo2.write(endServoZ);
			break;
		case irPos:
			RCServo2.write(endServoIR);
			break;
		case gatePos:
			RCServo2.write(endServoGate);
			break;
		}
}

void moveArm(int pos) {
	if (!atUpperPos(upperHingeBound) && !armSafe) {
		moveUpperArm(upperHingeBound);
		motor.speed(armBaseMotorPin, 0);
		moveBaseServoPos(pos);
	}
	else {
		armSafe = true;
		moveLowerArm(pos);
		moveUpperArm(pos);
		moveBaseServoPos(pos);
		moveEndServo(pos);
	}
}
void stableLift() {
	if (!atLowerPos(zipPos)) {
		moveLowerArm(zipPos);
	}
	else {
		moveUpperArm(zipPos);
		double angle = getHingeMotorPot();
		double potMap = doubleMap(angle, hingeFive, baseZ, endServoFive, endServoZ);
		RCServo2.write(potMap);

	}
}