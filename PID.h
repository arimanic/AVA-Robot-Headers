#ifndef PID_h
#define PID_h

void setKP(int val);
void setKI(int val);
void setKD(int val);
void setControlGain(int val);
void setSpeedScale(double val);

int getKP();
int getKI();
int getKD();
int getControlGain();
double getSpeedScale();

void setMotors(double L, double R, int ctrl);

void setSmallErr(int err);
void setMedErr(int err);
void setLargeErr(int err);

void getQRDs(bool arrQRD[]);
bool getQRD(int QRDnum);

bool atCross();

int getP4();
int getP2();

double getD();

double PID4follow();
double PID2follow();

double getDist(int ticks);
#endif

