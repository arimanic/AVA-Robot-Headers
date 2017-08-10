#ifndef armControl_h
#define armControl_h

#define upperBaseBound 4.5
#define lowerBaseBound 3.35
#define upperHingeBound 3.25
#define lowerHingeBound 1.7
#define hingeCollision 3.10
#define upperEndServo 0
#define lowerEndServo 85

#define toyZero 0
#define baseZero 3.91
#define hingeZero 2.71
#define servoZero 0
#define endServoZero 142

#define toyOne 1
#define baseOne 3.91
#define hingeOne 2.71
#define servoOne 0
#define endServoOne 142

#define toyTwo 2
#define baseTwo 3.91
#define hingeTwo 2.71
#define servoTwo 0
#define endServoTwo 142

#define toyThree 3
#define baseThree 3.91
#define hingeThree 2.71
#define servoThree 0
#define endServoThree 142

#define toyFour 4
#define baseFour 3.91
#define hingeFour 2.71
#define servoFour 0
#define endServoFour 142

#define toyFive 5
#define baseFive 3.91
#define hingeFive 2.71
#define servoFive 0
#define endServoFive 142

#define drivePos 6
#define baseD 3.5
#define hingeD 1.8
#define servoD 90
#define endServoD 180

#define zipPos 7
#define baseZ lowerBaseBound
#define hingeZ upperHingeBound
#define servoZ 90
#define endServoZ 18

#define irPos 8
#define baseIR 3.35
#define hingeIR 2.10
#define servoIR 90
#define endServoIR 135

#define gatePos 9
#define baseGate upperBaseBound
#define hingeGate 3.0
#define servoGate 90
#define endServoGate 150


// define a threshold for measurement error. It is unlikely to read the pot when it is at the exact value defined above.
// instead try to catch it when it is close;
#define voltageRange 0.05;
#define fineCorrRange 0.25

// define a scaling factor for the movement speed of the arm. motor speed = armSpeed*displacement

void setArmSpeed(int speed);
void setFineArmSpeed(int speed);
void setArmSafe(bool safe);

int getArmSpeed();
int getFineArmSpeed();
double getBaseMotorPot();
double getHingeMotorPot();

double getRelLowerPos(int pos);
double getRelUpperPos(int pos);
double getRelLowerPos(double voltage);
double getRelUpperPos(double voltage);

bool getArmSafe();

bool atLowerPos(int pos);
bool atUpperPos(int pos);
bool atUpperPos(double voltage);
bool atLowerPos(double voltage);
bool atBothPos(int pos);

void moveLowerArm(int pos);
void moveUpperArm(int pos);
void moveLowerArm(double voltage);
void moveUpperArm(double voltage);
void moveBaseServo(int val);
void moveBaseServoPos(int pos);
void activateArmServo();
void resetArmServo();
void moveEndServo(int pos);

void moveArm(int pos);
void stableLift();
#endif // armControl_h
