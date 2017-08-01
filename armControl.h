#ifndef armControl_h
#define armControl_h

#define upperBaseBound 4.8
#define lowerBaseBound 3.5
#define upperHingeBound 3.6
#define lowerHingeBound 1.7
#define hingeCollision 3.10

#define drivePos 0
#define baseD upperBaseBound
#define hingeD lowerHingeBound

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define fishPos 2
#define baseF 4.3
#define hingeF 2.0

#define zipPos 3
#define baseZ upperBaseBound
#define hingeZ upperHingeBound

/*
#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75

#define collectPos 1
#define baseC 4.0
#define hingeC 1.75
*/
// define a threshold for measurement error. It is unlikely to read the pot when it is at the exact value defined above.
// instead try to catch it when it is close;
#define voltageRange 0.1
#define fineCorrRange 0.15
// define a scaling factor for the movement speed of the arm. motor speed = armSpeed*displacement

void setArmSpeed(int speed);
void setFineArmSpeed(int speed);

int getArmSpeed();
int getFineArmSpeed();
double getBaseMotorPot();
double getHingeMotorPot();

double getRelLowerPos(int pos);
double getRelUpperPos(int pos);
double getRelLowerPos(double voltage);
double getRelUpperPos(double voltage);

bool atLowerPos(int pos);
bool atUpperPos(int pos);
bool atBothPos(int pos);

void moveLowerArm(int pos);
void moveUpperArm(int pos);
void moveLowerArm(double voltage);
void moveUpperArm(double voltage);
void moveBaseServo(int val);


#endif // armControl_h
