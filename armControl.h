#ifndef armControl_h
#define armControl_h

#define upperBaseBound 4.8
#define lowerBaseBound 3.5
#define upperHingeBound 3.6
#define lowerHingeBound 1.7
#define hingeCollision 3.10

#define toyZero 0
#define baseZero 4.5
#define hingeZero 2.0
#define servoZero 90

#define toyOne 1
#define baseOne 4.5
#define hingeOne 2.0
#define servoOne 90

#define toyTwo 2
#define baseTwo 4.5
#define hingeTwo 2.0
#define servoTwo 90

#define toyThree 3
#define baseThree 4.5
#define hingeThree 2.0
#define servoThree 90

#define toyFour 4
#define baseFour 4.5
#define hingeFour 2.0
#define servoFour 90

#define toyFive 5
#define baseFive 4.5
#define hingeFive 2.0
#define servoFive 90

#define drivePos 6
#define baseD upperBaseBound
#define hingeD lowerHingeBound
#define servoD 90

#define zipPos 7
#define baseZ upperBaseBound
#define hingeZ upperHingeBound
#define servoZ 90


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
void moveBaseServoPos(int pos);
void activateArmServo();
void resetArmServo();

void moveArm(int pos);

#endif // armControl_h
