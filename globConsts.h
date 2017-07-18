#ifndef globConst_h
#define globConst_h

// Things you can change
// Motor Number Outputs
#define RmotorPin 0
#define LmotorPin 1
#define armBaseMotorPin 2
#define armHingeMotorPin 3

// Digital IO pins
//External Interrupt Pins
#define LSonarPin 1
#define RSonarPin 2
#define distanceCounter 3
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

#define paramMax 150

#define numQRD 4
#define numIR 5
#define numVars 6
#define numToys 6

#define PI 3.1415
#define wheelDiam 0.072

// define a numerical value for each arm position
// define the voltage reading of the upper and lower Pot for each position.
// There are 4 positions: Driving   (D)
//                        Collecting (C)
//                        Fishing   (F)
//                        Zipline   (Z)
#define drivePos 0
#define baseD 0
#define hingeD 5

#define collectPos 1
#define baseC 0
#define hingeC 5

#define fishPos 2
#define baseF 0
#define hingeF 5

#define zipPos 3
#define baseZ 5
#define hingeZ 0

#endif