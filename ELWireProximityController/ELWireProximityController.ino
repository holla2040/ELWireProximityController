/* references
  https://learn.sparkfun.com/tutorials/reducing-arduino-power-consumption/all
  https://learn.adafruit.com/distance-measurement-ultrasound-hcsr04
*/

#include "LowPower.h"

const int LED     = 13; 
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

// #define DEBUG

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println("ELWireProximityController setup");
ajlsdkjf;
#endif
  pinMode(LED,OUTPUT);
  LowPower.idle(SLEEP_2S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
}

void loop() {
/*
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
*/
  digitalWrite(LED,!digitalRead(LED));
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
}

