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

#define trigPin 31
#define echoPin 2

// Standard Digital IO pins
#define QRD0pin 4
#define QRD1pin 5
#define QRD2pin 6
#define QRD3pin 7

// Analog IO Pins
#define IR0pin A0
#define IR1pin A1
#define IR2pin A2
#define IR3pin A3
#define IR4pin A4

#define armHingePotPin A5
#define armBasePotPin A6

#define paramMax 50

#define numQRD 4
#define numIR 5
#define numVars 9
#define numToys 6
#define overflowsNeeded (61 + 9.0/255.0);

#define PI 3.1415
#define wheelDiam 0.072

// Distance constants 
#define gateDist 1
#define startRampDist 1.4
#define endRampDist 6
#define zipDist 1

#endif