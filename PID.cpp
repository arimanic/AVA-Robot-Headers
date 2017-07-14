
#include <globConsts.h>
#include <arrayHelpers.h>
#include <Arduino.h>
bool QRDs[numQRD] = { 0 }; // High means on tape
// P
int smallErr = 4;
int medErr = 8;
int largeErr = 12;
int lastTurn;

// D
int lastError, error, recentError;
int prevDTime = 0;
int curDTime = 0;

// 4QRD arrays
bool straight4[numQRD] = { 0, 1, 1, 0 };
bool sLeft4[numQRD] = { 0, 1, 0, 0 };
bool sRight4[numQRD] = { 0, 0, 1, 0 };
bool mLeft4[numQRD] = { 1, 1, 0, 0 };
bool mRight4[numQRD] = { 0, 0, 1, 1 };
bool hLeft4[numQRD] = { 1, 0, 0, 0 };
bool hRight4[numQRD] = { 0, 0, 0, 1 };
bool hardTurn4[numQRD] = { 0, 0, 0, 0 };
bool cross[numQRD] = { 1, 0, 0, 1 }; // middle two entries do not matter

// 2QRD arrays
bool straight2[numQRD] = { 1, 1 };
bool sLeft2[numQRD] = { 1, 0 };
bool sRight2[numQRD] = { 0, 1 };
bool hardTurn2[numQRD] = { 0, 0 };
bool QRDs2[2] = { 0 };




int getP4(int kp) {
	// To make the car turn right P is positive.
	// If P is negative the car turns left
	// Sets the error to be used by D control
	if (arrayEquals(QRDs, straight4, numQRD)) {
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
			error = -largeErr - smallErr;
		}
		else if (lastTurn == 0) {
			error = largeErr + smallErr;
		}
	}
	return kp * error;
}

int getP2(int kp) {
	// To make the car turn right P is positive.
	// If P is negative the car turns left
	arraySubset(QRDs, 1, 2, QRDs2);
	if (arrayEquals(QRDs2, straight2, numQRD)) {
		error = 0;
	}
	else if (arrayEquals(QRDs2, sLeft2, numQRD)) {
		error = -smallErr;
		lastTurn = 1;
	}
	else if (arrayEquals(QRDs2, sRight2, numQRD)) {
		error = smallErr;
		lastTurn = 0;
	}
	else if (arrayEquals(QRDs2, hardTurn2, numQRD)) {
		if (lastTurn == 1) {
			error = -medErr;
		}
		else if (lastTurn == 0) {
			error = medErr;
		}
	}
	return kp * error;
}

double getD(int kd) {
	// To make the car turn right D is positive.
	// If D is negative the car turns left
	// error is set by getPx()

	if (lastError != error) {
		recentError = lastError;
		prevDTime = curDTime;
		curDTime = 0;
	}
	curDTime++;
	lastError = error;
	return ((double)kd * (error - recentError)) / ((double)(prevDTime + curDTime));

}

void setSmallErr(int err) {
	smallErr = err;
	return;
}

void setMedErr(int err) {
	medErr = err;
	return;
}

void setLargeErr(int err) {
	largeErr = err;
	return;
}

void getQRDs() {
	// Reads all QRD sensors and stores boolean values in QRDs array
	for (int i = 0; i < numQRD; i++) {
		QRDs[i] = digitalRead(i);
	}
}

bool atCross() {
	getQRDs();
	if (QRDs[0] == 1 && QRDs[numQRD - 1] == 1) {
		return true;
	}
	return false;
}

double PID4follow(int kp, int ki, int kd, double controlGain) {
	getQRDs();
	int pCon = getP4(kp);
	int dCon = getD(kd);

	return controlGain * (pCon + dCon);

}

double PID2follow(int kp, int ki, int kd, double controlGain) {

	getQRDs();
	int pCon = getP2(kp);
	int dCon = getD(kd);

	return controlGain * (pCon + dCon);
}

bool getQRD(int QRDnum) {
	// Reads the given QRD sensor and stores boolean value in QRDs array 
	// Returns true or false for the given QRD
	QRDs[QRDnum] = digitalRead(QRDnum);
	return QRDs[QRDnum];
}