
#include "globConsts.h"
#include "arrayHelpers.h"
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <math.h>
#include "motor.h"
#include "TinahIO.h"

extern LiquidCrystal LCD;
extern motorClass motor;
extern int wheelTicks;
bool stopFlag;

bool QRDs[numQRD] = { 0 }; // High means on tape
// P
double smallErr;
double medErr;
double largeErr;
double hugeErr;

int lastTurn;
double kp, ki, kd, controlGain;
double speedScale;
double flatSpeed;
double rampSpeed;
double ringSpeed;
double slowSpeed = 0.20;
// D
double lastError, error, recentError;
long prevDTime = 0;
long curDTime = 0;

// 4QRD

#define straight4  6 // { 0, 1, 1, 0 };
#define sLeft4  2 // { 0, 1, 0, 0 };
#define sRight4  4 // { 0, 0, 1, 0 };
#define mLeft4  3 // { 1, 1, 0, 0 };
#define mRight4  12 //{ 0, 0, 1, 1 };
#define hLeft4  1 //{ 1, 0, 0, 0 };
#define hRight4  8 //{ 0, 0, 0, 1 };
#define hardTurn4  0 //{ 0, 0, 0, 0 };

int cross = 9; //{ 1, 0, 0, 1 }; // middle two entries do not matter

// 2QRD arrays
#define straight2  3 //{ 1, 1 };
#define sLeft2  1 //{ 1, 0 };
#define sRight2  2 //{ 0, 1 };
#define hardTurn2  0 //{ 0, 0 };
bool QRDs2[2] = { 0 };

// Setters and Getters //

void setSmallErr(int err) {
	smallErr = err;
}
void setMedErr(int err) {
	medErr = err;
}
void setLargeErr(int err) {
	largeErr = err;
}
void setHugeErr(int err) {
	hugeErr = err;
}
void setKP(double val) {
	kp = val;
	return;
}
void setKI(double val) {
	ki = val;
	return;
}
void setKD(double val) {
	kd = val;
	return;
}
void setControlGain(double val) {
	controlGain = val;
	return;
}
void setSpeedScale(double val) {
	speedScale = val;
	return;
}
void setFlatSpeed(double val) {
	flatSpeed = val;
}
void setRampSpeed(double val) {
	rampSpeed = val;
}
void setRingSpeed(double val) {
	ringSpeed = val;
}
void setStopFlag(bool val) {
	stopFlag = val;
}

int getSmallErr() {
	return smallErr;
}
int getMedErr() {
	return medErr;
}
int getLargeErr() {
	return largeErr;
}
int getHugeErr() {
	return hugeErr;
}
double getKP() {
	return kp;
}
double getKI() {
	return ki;
}
double getKD() {
	return kd;
}
double getControlGain() {
	return controlGain;
}
double getSpeedScale() {
	return speedScale;
}
double getFlatSpeed() {
	return flatSpeed;
}
double getRampSpeed() {
	return rampSpeed;
}
double getRingSpeed() {
	return ringSpeed;
}

void setMotors(double L, double R, double ctrl) {
	// Calculates and sets motor speed and control
	motor.speed(RmotorPin, (R + ctrl)*speedScale);
	motor.speed(LmotorPin, (L - ctrl)*speedScale);
}

double getP4() {
	// To make the car turn left P is positive.
	// If P is negative the car turns right
	// Sets the error to be used by D control

	int bin4 = arr2bin4(QRDs);

	switch (bin4) {
	case straight4:
		error = 0;
		break;

	case sLeft4:
		error = -smallErr;
		lastTurn = 1;
		break;

	case sRight4:
		error = smallErr;
		lastTurn = 0;
		break;

	case mLeft4:
		error = -medErr;
		lastTurn = 1;
		break;

	case mRight4:
		error = medErr;
		lastTurn = 0;
		break;

	case hLeft4:
		error = -largeErr;
		lastTurn = 1;
		break;

	case hRight4:
		error = largeErr;
		lastTurn = 0;
		break;

	case hardTurn4:
		if (lastTurn == 1) {
			error = -hugeErr;
		}
		else if (lastTurn == 0) {
			error = hugeErr;
		}
		break;

	default:
		break;
	}

	return kp * error;
}
double getP2() {
	// To make the car turn right P is positive.
	// If P is negative the car turns left
	arraySubset(QRDs, 1, 2, QRDs2);

	int bin2 = arr2bin2(QRDs2);

	switch (bin2) {
	case straight2:
		error = 0;
		break;

	case sLeft2:
		error = -smallErr;
		lastTurn = 1;
		break;

	case sRight2:
		error = smallErr;
		lastTurn = 0;
		break;

	case hardTurn2:
		if (lastTurn == 1) {
			error = -medErr;
		}
		else if (lastTurn == 0) {
			error = medErr;
		}
		break;

	default:
		break;
	}
	return kp * error;
}
double getD() {
	// To make the car turn left D is positive.
	// If D is negative the car turns right
	// error is set by getPx()

	if (lastError != error) {
		recentError = lastError;
		prevDTime = curDTime;
		curDTime = 0;
	}
	curDTime++;
	lastError = error;

	//if (abs(error) < abs(recentError)) {
	return ((double)kd * (error - recentError)) / ((long double)(prevDTime + curDTime));
	//	}
	//	return 0;
}

void getQRDs() {
	// Reads all QRD sensors and stores boolean values in QRDs array
	QRDs[0] = digitalRead(QRD0pin);
	QRDs[1] = digitalRead(QRD1pin);
	QRDs[2] = digitalRead(QRD2pin);
	QRDs[3] = digitalRead(QRD3pin);

}
bool getQRD(int QRDnum) {
	// Reads the given QRD sensor and stores boolean value in QRDs array 
	// Returns true or false for the given QRD

	return QRDs[QRDnum];
}
double getDist(int ticks) {
	double rotations = ticks / 24.0;
	double circumf = PI*wheelDiam;
	return rotations * circumf * 2 / 3;
}
bool getLastTurn() {
	return lastTurn;
}
// Control Functions //

bool atCross() {
	getQRDs();
	int binary = arr2bin4(QRDs);
	switch (binary) {
	case 7: // 0111
		break;
		/*case 9: // 1001
			break;
		case 11: // 1011
			break;
		case 13: // 1101
			break;*/
	case 14: // 1110
		break;
	case 15: // 1111
		break;
	default:
		return false;

	}

	return true;
}

double PID4follow()
{
	stopFlag = 0;
	getQRDs();
	double pCon = getP4();
	double dCon = getD();
	double con = controlGain * (pCon - dCon);
	setMotors(255, 255, con);
	return con;
}
double PID2follow() {
	stopFlag = 0;
	getQRDs();
	double pCon = getP2();
	double dCon = getD();
	double con = controlGain * (pCon - dCon);
	setMotors(255, 255, con);
	return con;
}

void stepMotors(long time) {
	long startStep = millis();
	while (millis() - startStep < time) {
		if (!leftSide()) {
			setMotors(-255, 100, 0);
		}
		else {
			setMotors(100, -255, 0);
		}

		setMotors(0, 0, 0);
	}
}
void PID4step(long time) {
	long startTime = millis();
	while (millis() - startTime < time) {
		PID4follow();
	}
}
void crossTurn() {
	// Step forward until both middle QRDs are 0 (off tape)
	while (QRDs[1] || QRDs[2]) {
		LCD.clear();
		printQRDs();
		getQRDs();
		stepMotors(150);
	}
	// Turn until at least one middle QRD finds tape
	if (leftSide()) {
		while (!(QRDs[1] || QRDs[2])) {
			getQRDs();
			LCD.clear();
			printQRDs();
			setMotors(-255, 200, 0);
		}
	}
	else {
		long turnTime = millis();
		while (!(QRDs[1] || QRDs[2])) {
			getQRDs();
			LCD.clear();
			printQRDs();
			setMotors(-255, 200, 0);
		}
		
	}
	setMotors(0, 0, 0);
}


void revStop() {
	long startingTime = millis();
	while (millis() - startingTime < 50 * getSpeedScale() && !stopFlag) {
		motor.speed(RmotorPin, -255);
		motor.speed(LmotorPin, -255);
	}
	stopFlag = 1;
	motor.speed(RmotorPin, 0);
	motor.speed(LmotorPin, 0);

}
//uses while. may get stuck here
void turnAround(long turnTime) {
	long turnStart = millis();

	while (millis() - turnStart < turnTime) {
		setMotors(255, -255, 0);
	}

	setMotors(0, 0, 0);
}
void stageSpeed(int stage) {
	switch (stage) {
	case beforeGateStage:
		speedScale = flatSpeed;
		break;

	case afterGateStage:
		speedScale = 0.5;
		break;

	case onRampStage:
		speedScale = rampSpeed;
		break;

	case afterRampStage:
		speedScale = 0.5;
		break;

	case ringStage:
		speedScale = ringSpeed;
		break;

	case slowStage:
		speedScale = slowSpeed;
		break;

	}
}