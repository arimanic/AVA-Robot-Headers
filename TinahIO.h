#ifndef tinah_io
#define tinah_io

void menu();
void printParams();
void printQRDs();

void initConsts(double p, double i, double d, double g, double t, double flat, double ramp, double ring, int x, double son);
double doubleMap(double x, double in_min, double in_max, double out_min, double out_max);
int gatedKnobMap(int port, int outMin, int outMax);
bool leftSide();

#endif
