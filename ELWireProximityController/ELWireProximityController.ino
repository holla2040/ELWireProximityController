/* references
  https://learn.sparkfun.com/tutorials/reducing-arduino-power-consumption/all
  https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
*/

// distance in inches

#include "LowPower.h"

const int LED             = 13; 
const int trigPin         = 12; 
const int echoPin         = 11; 
const int hvEnablePin     = 10;
const int sensorPowerPin1 =  9;
const int sensorPowerPin2 =  8;
const int sensorPowerPin3 =  7;
const int sensorPowerPin4 =  6;

const int distanceLimit   = 30;
const int positiveHitLimit= 10;

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void sensorPower(bool e) {
  if (e) {
    pinMode(sensorPowerPin1,OUTPUT); 
    pinMode(sensorPowerPin2,OUTPUT); 
    pinMode(sensorPowerPin3,OUTPUT); 
    pinMode(sensorPowerPin4,OUTPUT); 
    digitalWrite(sensorPowerPin1,HIGH);
    digitalWrite(sensorPowerPin2,HIGH);
    digitalWrite(sensorPowerPin3,HIGH);
    digitalWrite(sensorPowerPin4,HIGH);
  } else {
    pinMode(sensorPowerPin1,INPUT);
    pinMode(sensorPowerPin2,INPUT);
    pinMode(sensorPowerPin3,INPUT);
    pinMode(sensorPowerPin4,INPUT);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("ELWireProximityController setup");

  pinMode(trigPin,        OUTPUT); 
  pinMode(echoPin,        INPUT_PULLUP); 
  pinMode(hvEnablePin,    OUTPUT); 
  pinMode(LED,            OUTPUT);

  digitalWrite(LED,           LOW);
  digitalWrite(hvEnablePin,   HIGH);

  sensorPower(true);

  //LowPower.idle(SLEEP_2S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
}

bool inRange() {
  // looking for positiveHitLimit
  int positives = 0;
  long duration, distance;

  for (int i = 0; i < positiveHitLimit+2; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = microsecondsToInches(duration);

/*
    Serial.print(duration);
    Serial.print(" ");
*/
    Serial.println(distance);

    if (distance < distanceLimit) {
      positives++;
      if (positives > positiveHitLimit) return true;
    }
  }
  return false;
}

void loop() {
  sensorPower(true);
  delay(200);
  if (inRange()) {
    Serial.println("IN"); 
    digitalWrite(LED,HIGH); // LED ON 
  } else {
    Serial.println("OUT"); 
    digitalWrite(LED,LOW); // LED OFF
  }
  sensorPower(false);

  delay(2000);

  //LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);  
  //delay(100);
}

