#include "robotDebug.h"
#include <LiquidCrystal.h>
#include "PID.h"
#include "motor.h"
#include "IR.h"
#include "globConsts.h"
#include "ringControl.h"
#include "ServoTINAH.h"
#include "TinahIO.h"
#include "armControl.h"
#include <Arduino.h>
#include "phys253pins.h"
#include "timing.h"
#include "sonar.h"

extern bool stopbutton();
extern bool startbutton();

extern int printCount;

extern motorClass motor;
extern LiquidCrystal LCD;

extern ServoTINAH RCServo0;
extern ServoTINAH RCServo1;
extern ServoTINAH RCServo2;

void sonarTest() {
	while (1) {
		outPulse();
		LCD.clear();
		LCD.print(" ");
		LCD.print(getOffTime());
		LCD.setCursor(0, 1);
	}
}

void armDebug() {
	int pos;
	int servo;
	while (1) {
		printCount++;
		pos = gatedKnobMap(6, 0, 9);
		servo = map(analogRead(7), 0, 1023, -2, 182);
		if (printCount > 400) {
			printCount = 0;

			LCD.clear();
			LCD.print(pos);
			LCD.print(" ");
			LCD.print(servo);
			LCD.print(" ");
			LCD.print(getRelLowerPos(pos));
			LCD.print(" ");
			LCD.print(getRelUpperPos(pos));

			LCD.setCursor(0, 1);
			LCD.print(atUpperPos(pos));
			LCD.print(" ");
			LCD.print(atLowerPos(pos));

		}
		moveLowerArm(pos);
		moveUpperArm(pos);
		moveBaseServo(servo);

	}
}

void irDebug() {
	while (1) {
		if (stopbutton()) {
			while (stopbutton()) {
			}
			menu();
		}
		moveArm(irPos);
		//moveBaseServo(gatedKnobMap(7, 0, 180));

		printCount++;
		if (printCount > 400) {
			printCount = 0;
			LCD.clear();
			LCD.print(analogRead(IR0pin));
			LCD.print(" ");
			LCD.print(analogRead(IR1pin));
			LCD.print(" ");
			LCD.print(analogRead(IR2pin));
			LCD.print(" ");

			LCD.setCursor(0, 1);
			LCD.print(gateStop());
		}

		if (stopbutton()) {
			while (stopbutton()) {
			}
			menu();
		}
	}
}

void ringDebug() {
	extern bool toyFallen[];
	setCrossPos(-1);
	setTargetPos(0);
	int nextPos = getTargetPos();
	stageSpeed(ringStage);
	setStartTime(millis() - 55000L);
	while (1) {
		toysInWater(seconds());
		nextPos = getTargetPos();
		resetArmServo();

		if (moveToPos(nextPos) && nextPos != -1) {
			moveArm(nextPos);
			activateArmServo();

			delay(3000);
			stepMotors(100);
			//turnAround();
			// do the arm thing and then set the target to the next toy
			setTargetPos(findNextToy(getCrossPos(), seconds()));
		}


		printCount++;
		if (printCount > 500) {
			printCount = 0;
			LCD.clear();
			printQRDs();
			LCD.print(nextPos);
			LCD.print(" ");
			LCD.print(getCrossPos());
			LCD.print(" ");
			LCD.print(seconds());
			LCD.print(" ");

			LCD.setCursor(0, 1);
			for (int i = 0; i < numToys; i++) {
				LCD.print(toyFallen[i]);
			}
		}

		if (startbutton()) {  // push start to reset the timer

			setStartTime((double)millis() - 57000);
			setCrossPos(-1);
			setTargetPos(0);
			toysInWater(seconds());
			while (startbutton()) {
				Serial.print(seconds());
			}
		}

		if (stopbutton()) {
			while (stopbutton()) {

			}
			menu();
		}
	}
}

void PIDdebug() {
	long testMillis = 0;
	int testStage = 0;
	setStageTime(millis());
	while (1) {
		stageSpeed(testStage);
		printCount++;
		testMillis = gatedKnobMap(7, 0, 5000);
		testStage = gatedKnobMap(6, 0, 5);

		if (stageMilliseconds() < testMillis) {
			setStopFlag(0);
			PID4follow();
		}
		else {
			revStop();
		}

		if (stopbutton()) {
			while (stopbutton()) {

			}
			menu();
		}

		if (startbutton()) {
			setStageTime(millis());
		}

		if (printCount > 400) {
			getQRDs();
			LCD.clear();
			printQRDs();
			LCD.print(stageMilliseconds());
			LCD.setCursor(0, 1);
			LCD.print(testMillis);
			LCD.print(" ");
			LCD.print(testStage);
			LCD.print(" ");
			LCD.print(getSpeedScale());

		}
	}
}

void armCalibrate() {
	double lowerVoltage;
	double upperVoltage;
	int servoVal;
	int tempServo;
	int servo0 = 0;
	int servo1 = 0;
	int servo2 = 0;
	int menuCounter = 0;

	while (1) {
		printCount++;
		lowerVoltage = gatedKnobMap(6,lowerBaseBound, upperBaseBound);
		upperVoltage = gatedKnobMap(7, lowerHingeBound, upperHingeBound);
		servoVal = gatedKnobMap(6, 0, 180);

		switch (menuCounter % 5) {
		case 0:
			moveUpperArm(upperVoltage);
			moveLowerArm(lowerVoltage);

			if (printCount > 400) {
				printCount = 0;
				LCD.clear();
				LCD.print("L");
				LCD.print(lowerVoltage);
				LCD.print(" ");
				LCD.print(getBaseMotorPot());
				LCD.print(" ");
				LCD.print(getRelLowerPos(lowerVoltage));

				LCD.setCursor(0, 1);
				LCD.print("U");
				LCD.print(upperVoltage);
				LCD.print(" ");
				LCD.print(getHingeMotorPot());
				LCD.print(" ");
				LCD.print(getRelUpperPos(upperVoltage));
			}
			break;

		case 1:
			RCServo0.write(servo0);
			tempServo = constrainNum(servoVal, 0, 180);
			if (startbutton()) {
				while (startbutton()) {
				}
				servo0 = tempServo;
			}
			if (printCount > 400) {
				printCount = 0;
				LCD.clear();
				LCD.print("Servo 0 was ");
				LCD.print(servo0);
				LCD.setCursor(0, 1);
				LCD.print(tempServo);
			}
			break;

		case 2:
			RCServo1.write(servo1);
			tempServo = constrainNum(servoVal, 0, 180);
			if (startbutton()) {
				while (startbutton()) {
				}
				servo1 = tempServo;
			}
			if (printCount > 400) {
				printCount = 0;
				LCD.clear();
				LCD.print("Servo 1 was ");
				LCD.print(servo1);
				LCD.setCursor(0, 1);
				LCD.print(tempServo);
			}
			break;

		case 3:
			RCServo2.write(servo2);
			tempServo = constrainNum(servoVal, 0, 180);
			if (startbutton()) {
				while (startbutton()) {
				}
				servo2 = tempServo;
			}
			if (printCount > 400) {
				printCount = 0;
				LCD.clear();
				LCD.print("Servo 2 was ");
				LCD.print(servo2);
				LCD.setCursor(0, 1);
				LCD.print(tempServo);
			}
			break;

		case 4:
			while (stopbutton()) {

			}
			menu();
			menuCounter++;
			break;

		}

		if (stopbutton()) {
			while (stopbutton()) {
			}
			menuCounter++;
		}
	}
}

void motorDebug() {
	int x = 0;
	int y = 0;
	setSpeedScale(1);
	while (1) {
		x = gatedKnobMap(7, -255, 255);
		y = gatedKnobMap(6, -255, 255);
		setMotors(x, y, 0);
		LCD.clear();
		LCD.print(x);
		LCD.print(" ");
		LCD.print(y);
	}
}

void ziplineDebug() {
	moveArm(drivePos);
	if (atBothPos(drivePos)) {
		while (1) {
			printCount++;

			moveArm(zipPos);

			if (printCount > 400) {
				LCD.clear();
				printQRDs();
			}
		}
	}
}
