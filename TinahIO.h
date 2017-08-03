#ifndef tinah_io
#define tinah_io

void menu();
void printParams();
void printQRDs();

void initConsts(double p, double i, double d, double g, double IR, double flat, double ramp, double ring, int smallErr, int medErr, int largeErr, int hugeErr, double armSpeed, double fineArmSpeed, int side);
void setPIDG(double p, double i, double d, double g);
void setSpeeds(double flat, double ramp, double ring);
void setErrors(int smallErr, int medErr, int largeErr, int hugeErr);
void setArmSpeeds(double armSpeed, double fineArmSpeed);

double doubleMap(double x, double in_min, double in_max, double out_min, double out_max);
double gatedKnobMap(int port, double outMin, double outMax);
int gatedKnobMap(int port, int outMin, int outMax);
double knobToVolt(int knob);
double constrainNum(double val, double min, double max);

void setSide(int val);
bool leftSide();
int getSide();

#endif
