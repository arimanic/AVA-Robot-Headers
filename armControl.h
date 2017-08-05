#ifndef armControl_h
#define armControl_h

#define upperBaseBound 4.5
#define lowerBaseBound 3.5
#define upperHingeBound 3.6
#define lowerHingeBound 1.7
#define hingeCollision 3.10

#define toyZero 0
#define baseZero upperBaseBound
#define hingeZero upperHingeBound
#define servoZero 90
#define endServoZero 0

#define toyOne 1
#define baseOne upperBaseBound
#define hingeOne upperHingeBound
#define servoOne 90
#define endServoOne 0

#define toyTwo 2
#define baseTwo upperBaseBound
#define hingeTwo upperHingeBound
#define servoTwo 90
#define endServoTwo 0

#define toyThree 3
#define baseThree upperBaseBound
#define hingeThree upperHingeBound
#define servoThree 90
#define endServoThree 0

#define toyFour 4
#define baseFour upperBaseBound
#define hingeFour upperHingeBound
#define servoFour 90
#define endServoFour 0

#define toyFive 5
#define baseFive upperBaseBound
#define hingeFive upperHingeBound
#define servoFive 90
#define endServoFive 0

#define drivePos 6
#define baseD 3.5
#define hingeD 2.0
#define servoD 90
#define endServoD 0

#define zipPos 7
#define baseZ upperBaseBound
#define hingeZ upperHingeBound
#define servoZ 90
#define endServoZ 0

#define irPos 8
#define baseIR 3.84
#define hingeIR 2.9
#define servoIR 90
#define endServoIR 0

#define gatePos 9
#define baseGate upperBaseBound
#define hingeGate 2.67
#define servoGate 90
#define endServoGate 0


// define a threshold for measurement error. It is unlikely to read the pot when it is at the exact value defined above.
// instead try to catch it when it is close;
#define voltageRange 0.15;
#define fineCorrRange 0.10

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

#endif // armControl_h
