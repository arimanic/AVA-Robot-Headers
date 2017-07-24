#include <sonar.h>
#include <Arduino.h>
#include <globConsts.h>

double sonarThresh;
double offTime;
extern long overflowCount;
/*
void sonar() {
	offTime = overflowCount;
	digitalWrite(trigPin, LOW);  // Added this line
								 // delayMicroseconds(2); // Added this line
	digitalWrite(trigPin, HIGH);
	//  delayMicroseconds(1000); - Removed this line
	//  delayMicroseconds(10); // Added this line
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = (duration / 2) / 29.1;
	if (distance >= 200 || distance <= 0) {
		LCD.print("Out of range");
	}
	else {
		LCD.print(distance);
		LCD.print(" cm");
	}
	//delay(500);
}*/

void outPulse() {

	offTime = overflowCount;
	digitalWrite(trigPin, LOW);
	// delay
	digitalWrite(trigPin, HIGH);
	// delay
	digitalWrite(trigPin, LOW);

}

double getSonarThresh() {
	return sonarThresh;
}

double getOffTime() {
	return offTime;
}