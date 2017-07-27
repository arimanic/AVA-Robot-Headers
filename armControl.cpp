#include <Arduino.h>
#include "globConsts.h"
#include "ServoTINAH.h"
#include "motor.h"

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

#define upperBaseBound 3.6
#define lowerBaseBound 4.8
#define upperHingeBound 3.4
#define lowerHingeBound 1.7
#define hingeCollision 3.10

#define drivePos 0
#define baseD upperBaseBound
#define hingeD lowerHingeBound

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define fishPos 2
#define baseF 4.3
#define hingeF 2.0

#define zipPos 3
#define baseZ upperBaseBound
#define hingeZ upperHingeBound

/*
#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75
*/
// define a threshold for measurement error. It is unlikely to read the pot when it is at the exact value defined above.
// instead try to catch it when it is close;
#define voltageRange 0.1
#define fineCorrRange 0.15
// define a scaling factor for the movement speed of the arm. motor speed = armSpeed*displacement
#define armSpeed 700 // > 0.07 , 4000 < 0.07
#define fineCorrSpeed 3000

extern motorClass motor;

extern ServoTINAH RCServo0; 
extern ServoTINAH RCServo1;
extern ServoTINAH RCServo2;


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

double getRelLowerPos(int pos) {
	// Determines if the lower portion of the arm is at the position passed as pos
	// returns a negative number if the position is low. Positive number if high. 0 if at the right spot
	double voltRead = getBaseMotorPot();

	switch (pos) {
	case drivePos:
		return voltRead - baseD;
	case collectPos:
		return voltRead - baseC;
	case fishPos:
		return voltRead - baseF;
	case zipPos:
		return voltRead - baseZ;
	}
}

double getRelUpperPos(int pos) {
	// Determines if the upper portion of the arm is at the position passed as pos
	// returns a negative number if the position is low. Positive number if high. 0 if at the right spot
	double voltRead = getHingeMotorPot();
	switch (pos) {
	case drivePos:
		return voltRead - hingeD;
	case collectPos:
		return voltRead - hingeC;
	case fishPos:
		return voltRead - hingeF;
	case zipPos:
		return voltRead - hingeZ;
	}
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

bool atBothPos(int pos) {
	// Determines if the upper and lower portions of the arm are at the position passed as pos within the error range defined as voltageRange
	return atUpperPos(pos) && atLowerPos(pos);
}

void moveLowerArm(int pos) {
	if (getRelLowerPos(pos) > fineCorrRange){
		motor.speed(armBaseMotorPin, armSpeed * getRelLowerPos(pos));
	} else if (getRelLowerPos(pos) <= fineCorrRange) {
		motor.speed(armBaseMotorPin, fineCorrSpeed * getRelLowerPos(pos));
	}
	else {
		motor.stop(armBaseMotorPin);
	}
	return;
}

void moveUpperArm(int pos) {
	if (getRelUpperPos(pos) > fineCorrRange) {
		motor.speed(armHingeMotorPin, armSpeed * getRelUpperPos(pos));
	}
	else if (getRelUpperPos(pos) <= fineCorrRange) {
		motor.speed(armHingeMotorPin, fineCorrSpeed * getRelUpperPos(pos));
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