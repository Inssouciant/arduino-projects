/*
  ------------------------------------------------------------
  Project: Parking Spots with Ultrasonic Sensors
  ------------------------------------------------------------
  Author : Insouciant
  Link   : https://github.com/Inssouciant
  Date   : 11.10.2025
  ------------------------------------------------------------
  Description:
  This project uses ultrasonic sensors to detect the distance
  to nearby objects and controls LED indicators that show the status 
  of a parking spot (green, yellow, red) based on distance thresholds.
  ------------------------------------------------------------
*/

const int trigPinFirst = 7;  
const int echoPinFirst = 6; 
float durationFirst, distanceFirst;

const int trigPinSecond = 8;
const int echoPinSecond = 9;
float durationSecond, distanceSecond;

const int redLEDFirst = 2;
const int yellowLEDFirst = 3;
const int greenLEDFirst = 4;

const int redLEDSecond = 11;
const int yellowLEDSecond = 12;
const int greenLEDSecond = 13;

const int checkLEDFirst = 5;
const int checkLEDSecond = 10;

const int greenLine = 13;
const int yellowLine = 9;
const int redLine = 5;

int tempFirst = 0;
int tempSecond = 0;

bool statusFirst = false;
bool statusSecond = false;

void setup() {  
  Serial.begin(9600);  

	pinMode(trigPinFirst, OUTPUT);  
	pinMode(echoPinFirst, INPUT);  
	pinMode(trigPinSecond, OUTPUT);  
	pinMode(echoPinSecond, INPUT);  

  pinMode(greenLEDFirst, OUTPUT);
  pinMode(yellowLEDFirst, OUTPUT);
  pinMode(redLEDFirst, OUTPUT);
  pinMode(greenLEDSecond, OUTPUT);
  pinMode(yellowLEDSecond, OUTPUT);
  pinMode(redLEDSecond, OUTPUT);

  pinMode(checkLEDFirst, OUTPUT);
  pinMode(checkLEDSecond, OUTPUT);
}  

void loop() {

  // Measuring distance from the first ultrasonic sensor

  // Send a short pulse from the sensor output (trigger pin)
  digitalWrite(trigPinFirst, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPinFirst, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPinFirst, LOW); 

  // Measure the time until the echo returns
  durationFirst = pulseIn(echoPinFirst, HIGH);  
  // (speed of sound = 0.0343 cm/µs, divided by 2 for round trip)
  distanceFirst = (durationFirst * 0.0343)/2;  // Convert to centimeters
  Serial.print("First distance: ");  
	Serial.println(distanceFirst);  

  // Measuring distance from the second ultrasonic sensor

  digitalWrite(trigPinSecond, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPinSecond, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPinSecond, LOW); 

  durationSecond = pulseIn(echoPinSecond, HIGH);  
  distanceSecond = (durationSecond * 0.0343)/2;  // Convert to centimeters
  Serial.print("Second distance: ");  
	Serial.println(distanceSecond); 
	
  // Control of LEDs for the first sensor based on distance

  if (distanceFirst <= redLine) {
    digitalWrite(greenLEDFirst, LOW);
    digitalWrite(yellowLEDFirst, LOW);
    digitalWrite(redLEDFirst, HIGH);
    statusFirst = true;
  } else if (distanceFirst <= yellowLine) {
    digitalWrite(greenLEDFirst, LOW);
    digitalWrite(yellowLEDFirst, HIGH);
    digitalWrite(redLEDFirst, LOW);
    statusFirst = false;
  } else if (distanceFirst <= greenLine) {
    digitalWrite(greenLEDFirst, HIGH);
    digitalWrite(yellowLEDFirst, LOW);
    digitalWrite(redLEDFirst, LOW);
    statusFirst = false;
  } else {
    digitalWrite(greenLEDFirst, LOW);
    digitalWrite(yellowLEDFirst, LOW);
    digitalWrite(redLEDFirst, LOW);
    statusFirst = false;
  }

  // Counting how long the sensor detects a nearby object (first sensor)

  if (statusFirst) {
    tempFirst = tempFirst + 1;
    if (tempFirst >= 6) {
      digitalWrite(checkLEDFirst, HIGH);
      digitalWrite(greenLEDFirst, LOW);
      digitalWrite(yellowLEDFirst, LOW);
      digitalWrite(redLEDFirst, LOW);
    } 
  } else {
    tempFirst = 0;
    digitalWrite(checkLEDFirst, LOW);
  }

  // Control of LEDs for the second sensor based on distance

  if (distanceSecond <= redLine) {
    digitalWrite(greenLEDSecond, LOW);
    digitalWrite(yellowLEDSecond, LOW);
    digitalWrite(redLEDSecond, HIGH);
    statusSecond = true;
  } else if (distanceSecond <= yellowLine) {
    digitalWrite(greenLEDSecond, LOW);
    digitalWrite(yellowLEDSecond, HIGH);
    digitalWrite(redLEDSecond, LOW);
    statusSecond = false;
  } else if (distanceSecond <= greenLine) {
    digitalWrite(greenLEDSecond, HIGH);
    digitalWrite(yellowLEDSecond, LOW);
    digitalWrite(redLEDSecond, LOW);
    statusSecond = false;
  } else {
    digitalWrite(greenLEDSecond, LOW);
    digitalWrite(yellowLEDSecond, LOW);
    digitalWrite(redLEDSecond, LOW);
    statusSecond = false;
  }

  // Counting how long the sensor detects a nearby object (second sensor)

  if (statusSecond) {
    tempSecond = tempSecond + 1;
    if (tempSecond >= 6) {
      digitalWrite(checkLEDSecond, HIGH);
      digitalWrite(greenLEDSecond, LOW);
      digitalWrite(yellowLEDSecond, LOW);
      digitalWrite(redLEDSecond, LOW);
    } 
  } else {
    tempSecond = 0;
    digitalWrite(checkLEDSecond, LOW);
  }

  // Short delay before the next measurement

  delay(500);
}
