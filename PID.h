#ifndef PID_h
#define PID_h
#include <phys253.h>
void setSmallErr(int err);

void setMedErr(int err);

void setLargeErr(int err);

void getQRDs(bool arrQRD[]);

bool getQRD(int QRDnum);

bool atCross();

int getP4(int kp);

int getP2(int kp);

double getD(int kd);

double PID4follow(int kp, int ki, int kd, double controlGain);

double PID2follow(int kp, int ki, int kd, double controlGain);
#endif

