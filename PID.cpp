
#include <globConsts.h>
#include <arrayHelpers.h>
#include <Arduino.h>
#include <math.h>
#include <motor.h>
extern motorClass motor;

bool QRDs[numQRD] = { 0 }; // High means on tape
// P
double smallErr = 4;
double medErr = 8;
double largeErr = 12;
double hugeErr = 20;
int lastTurn;
double kp, ki, kd, controlGain;
double speedScale;
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

	/*if (arrayEquals(QRDs, straight4, numQRD)) {
		error = 0;
	}
	else if (arrayEquals(QRDs, sLeft4, numQRD)) {
		error = -smallErr;
		lastTurn = 1;
	}
	else if (arrayEquals(QRDs, sRight4, numQRD)) {
		error = smallErr;
		lastTurn = 0;
	}
	else if (arrayEquals(QRDs, mLeft4, numQRD)) {
		error = -medErr;
		lastTurn = 1;
	}
	else if (arrayEquals(QRDs, mRight4, numQRD)) {
		error = medErr;
		lastTurn = 0;
	}
	else if (arrayEquals(QRDs, hLeft4, numQRD)) {
		error = -largeErr;
		lastTurn = 1;
	}
	else if (arrayEquals(QRDs, hRight4, numQRD)) {
		error = largeErr;
		lastTurn = 0;
	}
	else if (arrayEquals(QRDs, hardTurn4, numQRD)) {
		if (lastTurn == 1) {
			error = -hugeErr;
		}
		else if (lastTurn == 0) {
			error = hugeErr;
		}
	}*/
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
	return ((double)kd * 200 * (error - recentError)) / ((long double)(prevDTime + curDTime));

}

void setSmallErr(double err) {
	smallErr = err;
	return;
}

void setMedErr(double err) {
	medErr = err;
	return;
}

void setLargeErr(double err) {
	largeErr = err;
	return;
}

void getQRDs() {
	// Reads all QRD sensors and stores boolean values in QRDs array
	QRDs[0] = digitalRead(QRD0pin);
	QRDs[1] = digitalRead(QRD1pin);
	QRDs[2] = digitalRead(QRD2pin);
	QRDs[3] = digitalRead(QRD3pin);
}

double getDist(int ticks) {
	double rotations = ticks / 24.0;
	double circumf = PI*wheelDiam;
	return rotations * circumf;
}

bool atCross() {
	getQRDs();
	if (QRDs[0] == 1 && QRDs[numQRD - 1] == 1) {
		return true;
	}
	return false;
}

double PID4follow()
{
	getQRDs();
	double pCon = getP4();
	double dCon = getD();
	double con = controlGain * (pCon + dCon);
	setMotors(255, 255, con);
	return con;
}

double PID2follow() {
	getQRDs();
	double pCon = getP2();
	double dCon = getD();
	double con = controlGain * (pCon + dCon);
	setMotors(255, 255, con);
	return con;
}

bool getQRD(int QRDnum) {
	// Reads the given QRD sensor and stores boolean value in QRDs array 
	// Returns true or false for the given QRD
	return QRDs[QRDnum];
}

bool getLastTurn() {
	return lastTurn;
}