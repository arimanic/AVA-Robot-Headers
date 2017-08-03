#ifndef PID_h
#define PID_h

void setSmallErr(int err);
void setMedErr(int err);
void setLargeErr(int err);
void setHugeErr(int err);
void setKP(double val);
void setKI(double val);
void setKD(double val);
void setControlGain(double val);
void setSpeedScale(double val);
void setRampSpeed(double val);
void setFlatSpeed(double val);
void setRingSpeed(double val);
void setStopFlag(bool val);

int getSmallErr();
int getMedErr();
int getLargeErr();
int getHugeErr();
double getKP();
double getKI();
double getKD();
double getControlGain();
double getSpeedScale();
double getRampSpeed();
double getFlatSpeed();
double getRingSpeed();


bool getLastTurn();

void setMotors(double L, double R, double ctrl);

void getQRDs();
bool getQRD(int QRDnum);

bool atCross();

double getP4();
double getP2();
double getD();

double PID4follow();
double PID2follow();
void stepMotors(long time);
double getDist(int ticks);

void crossTurn();
void revStop();
void turnAround();
void stageSpeed(int stage);

#endif

