/* references
  https://learn.sparkfun.com/tutorials/reducing-arduino-power-consumption/all
  https://learn.adafruit.com/distance-measurement-ultrasound-hcsr04
*/

#include "LowPower.h"

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void setup() {
  Serial.begin(115200);
  Serial.println("ELWireProximityController setup");
}

void loop() {
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);   // need to turn off uart also
}

