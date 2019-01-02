/* references
  https://learn.sparkfun.com/tutorials/reducing-arduino-power-consumption/all
  https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
*/

// distance in inches
// using 4 arduino digital output for sensor power control, why 4?
// to lower Vds on voltage

#define DEBUG

const int LED             = 13; 
const int trigPin         = 12; 
const int echoPin         = 11; 
const int hvEnablePin     = 4;
const int sensorPowerPin1 =  9;
const int sensorPowerPin2 =  8;
const int sensorPowerPin3 =  7;
const int sensorPowerPin4 =  6;

const int distanceLimit   = 50;

long microsecondsToInches(long microseconds) {
   return (microseconds/2) / 74;
}

void sensorPower(bool e) {
  if (e) {
    pinMode(echoPin,INPUT_PULLUP); 
    pinMode(sensorPowerPin1,OUTPUT); 
    pinMode(sensorPowerPin2,OUTPUT); 
    pinMode(sensorPowerPin3,OUTPUT); 
    pinMode(sensorPowerPin4,OUTPUT); 
    digitalWrite(sensorPowerPin1,HIGH);
    digitalWrite(sensorPowerPin2,HIGH);
    digitalWrite(sensorPowerPin3,HIGH);
    digitalWrite(sensorPowerPin4,HIGH);
  } else {
    pinMode(echoPin,OUTPUT); 
    digitalWrite(echoPin, LOW);
    digitalWrite(trigPin, LOW);
    digitalWrite(sensorPowerPin1,LOW);
    digitalWrite(sensorPowerPin2,LOW);
    digitalWrite(sensorPowerPin3,LOW);
    digitalWrite(sensorPowerPin4,LOW);
/*
    pinMode(sensorPowerPin1,INPUT);
    pinMode(sensorPowerPin2,INPUT);
    pinMode(sensorPowerPin3,INPUT);
    pinMode(sensorPowerPin4,INPUT);
*/
  }
}

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  delay(10);
  Serial.println("\nELWireProximityController setup");
#endif

  pinMode(trigPin,        OUTPUT); 
  pinMode(echoPin,        INPUT_PULLUP); 
  pinMode(hvEnablePin,    OUTPUT); 
  pinMode(LED,            OUTPUT);

  digitalWrite(LED,           LOW);
  digitalWrite(hvEnablePin,   HIGH);

  sensorPower(true);
}

long getDuration() {
    const int maxdur = 20000;
    long duration;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration =  pulseIn(echoPin, HIGH, maxdur);
    if (duration == 0) duration = maxdur;
#ifdef DEBUG
    Serial.println(duration);
#endif
    delay(15); // this is needed for sensor to reset
    return duration;
}

bool inRange() {
  long distance,duration = 0;
  const int avecount = 5;

  getDuration();
  getDuration();

  for (int i = 0; i < avecount; i++) {
    long v;
    v = getDuration();
    duration += v;
  }

#ifdef DEBUG
  Serial.println(duration);
  Serial.println();
#endif

  duration /= avecount;
  distance = microsecondsToInches(duration);

#ifdef DEBUG
  Serial.print(distance);
  Serial.print(" ");
  Serial.println(float(distance)/12.0);
#endif

  if (distance < distanceLimit) {
    return true;
  }
  return false;
}

void loop() {
  if (inRange()) {
#ifdef DEBUG
    Serial.println("IN"); 
#endif
    digitalWrite(LED,HIGH); // LED ON 
  } else {
#ifdef DEBUG
    Serial.println("OUT"); 
#endif
    digitalWrite(LED,HIGH); // quick blink
    delay(1);
    digitalWrite(LED,LOW); 
  }
}

