#ifndef globConst_h
#define globConst_h

// Things you can change
// Motor Number Outputs
#define RmotorPin 1//3
#define LmotorPin 0// 2
#define armBaseMotorPin 2// 1
#define armHingeMotorPin 3//0

// Digital IO pins
//External Interrupt Pins
#define LSonarPin 1
#define RSonarPin 2
#define distanceCounter 3

// Standard Digital IO pins
#define QRD0pin 7
#define QRD1pin 6
#define QRD2pin 5
#define QRD3pin 4

// Analog IO Pins
#define IR0pin 0
#define IR1pin 1 // should be 1 but ir 1 is not reading properly. 
#define IR2pin 2
#define armHingePotPin 4
#define armBasePotPin 5

#define paramMax 50

#define numModes 8
#define numQRD 4
#define numIR 5
#define numVars 15
#define numToys 6


#define PI 3.1415
#define wheelDiam 0.072

// Stages
#define slowStage -1
#define beforeGateStage 0
#define afterGateStage 1
#define onRampStage 2
#define afterRampStage 3
#define ringStage 4

// Distance constants 
#define beforeGateTicks 200
#define afterGateTicks 100
#define onRampTicks 200
#define afterRampTicks 100
#define zipTicks 300

// Time constants for stages (milliseconds)
#define beforeGateMillis 1000
#define afterGateMillis 1700
#define onRampMillis 2200
#define afterRampMillis 1200
#define zipMillis 3000
#endif