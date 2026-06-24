#include <Arduino.h>

//Global Variables
const int StdDelay = 1800;

// Motor Pin Allocation
const int baseMotor1 = 6;   // Blue
const int baseMotor2 = 9;   // Green 
const int lowerArm1 =  3;   // Orange
const int lowerArm2 =  5;   // Yellow
const int upperArm1 = 10;   // Purple
const int upperArm2 = 11;   // Grey
const int switchPin = 13;   // with LED

// Named Motors for Ease of use
struct MOTOR {
  int pin1;
  int pin2;
};
MOTOR base  = {baseMotor1 , baseMotor2};
MOTOR lower = {lowerArm1  , lowerArm2 };
MOTOR upper = {upperArm1  , upperArm2 };

// Simple Motor Test
void testMotor(MOTOR motor) {
  // Clockwise
  digitalWrite(motor.pin1, HIGH);
  digitalWrite(motor.pin2, LOW);
  delay(500);

  // Pause
  digitalWrite(motor.pin1, LOW);
  digitalWrite(motor.pin2, LOW);
  delay(500);

  // Anticlockwise
  digitalWrite(motor.pin1, LOW);
  digitalWrite(motor.pin2, HIGH);
  delay(500);

  // Stop
  digitalWrite(motor.pin1, LOW);
  digitalWrite(motor.pin2, LOW);
}

// Run Motor at a given power for a given time ( power = -255 to 255 )
void runMotor(MOTOR motor, int power, int duration) {
  if (power > 0) {
    analogWrite(motor.pin1, power);
    digitalWrite(motor.pin2, LOW);
  } else  {
    digitalWrite(motor.pin1, LOW);
    analogWrite(motor.pin2, -power);
  }

  if (duration) {
    delay(duration);
    digitalWrite(motor.pin1, LOW);
    digitalWrite(motor.pin2, LOW);
  }
  // motor only runs for "duration" milliseconds
  // if duration = 0, motor keeps running forever
}

// Stops All Motors
void stopAll() {
  runMotor(base, 0, 0);
  runMotor(lower, 0, 0);
  runMotor(upper, 0, 0);
}

// Do nothing untill switch is pressed
void waitForSwitch() {
  // wait for switch to be released first (in case its still pressed)
  while (digitalRead(switchPin) == LOW);
  while (digitalRead(switchPin) == HIGH);
  
  runMotor(base, 0, 0);  // stop base
  delay(250);            // give base time to stop
}

// Program Code
void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(baseMotor1, OUTPUT);
  pinMode(baseMotor2, OUTPUT);
  pinMode(lowerArm1, OUTPUT);
  pinMode(lowerArm2, OUTPUT);
  pinMode(upperArm1, OUTPUT);
  pinMode(upperArm2, OUTPUT);
  Serial.println("The Setup is Complete");
}

void loop() {

  // up Code
  // runMotor(lower, -210, 600);
  
  // FINAL ROUTE
  // ===== Position 0 (Initial) ===== //
  runMotor(lower, 220, 1950);
  runMotor(upper, 180, 400);
  delay(StdDelay);
  runMotor(base, -150, 0);
  waitForSwitch();

  // ===== Position 1 (Pod One) ===== //
  runMotor(upper, -220, 130);
  runMotor(lower, -220, 550);
  delay(StdDelay);
  runMotor(base, -180, 0);
  waitForSwitch();

  // ===== Position 2 (Pod Two) ===== //
   runMotor(upper, -225, 150);
  runMotor(lower, -220, 1400);
  delay(StdDelay);
  runMotor(base, -180, 0);
  waitForSwitch();

  // ===== Position 3 (DropOff) ===== //
  runMotor(upper, 180, 280);
  delay(StdDelay);

  // Reset Position
  // please work
  runMotor(lower, -220, 1050);
  runMotor(upper, -180, 580);

  // Stop Everything - Run is Complete
  stopAll();
  Serial.println("The Run is Complete");
  while(true);
}