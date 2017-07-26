#ifndef armControl_h
#define armControl_h

double getBaseMotorPot();
double getHingeMotorPot();

double getRelLowerPos(int pos);
double getRelUpperPos(int pos);

bool atLowerPos(int pos);
bool atUpperPos(int pos);
bool atBothPos(int pos);

void moveLowerArm(int pos);
void moveUpperArm(int pos);
void moveBaseServo(int val);


#endif // armControl_h
