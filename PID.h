#ifndef PID_h
#define PID_h

void setKP(double val);
void setKI(double val);
void setKD(double val);
void setControlGain(double val);
void setSpeedScale(double val);
void setRampSpeed(double val);
void setFlatSpeed(double val);

double getKP();
double getKI();
double getKD();
double getControlGain();
double getSpeedScale();
double getRampSpeed();
double getFlatSpeed();


bool getLastTurn();

void setMotors(double L, double R, double ctrl);

void setSmallErr(double err);
void setMedErr(double err);
void setLargeErr(double err);

void getQRDs();
bool getQRD(int QRDnum);

bool atCross();

double getP4();
double getP2();

double getD();

double PID4follow();
double PID2follow();

double getDist(int ticks);

#endif

