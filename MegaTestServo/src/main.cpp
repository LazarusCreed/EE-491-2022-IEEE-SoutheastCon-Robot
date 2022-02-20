#include <Arduino.h>
#include <Servo.h>

#define CW   1900
#define STOP 1475
#define CCW  900

#define PIN A0

Servo s;

void setup() {
  pinMode(A0, INPUT);

  s.attach(A0);
}

void loop() {
  // put your main code here, to run repeatedly:
  /* s.writeMicroseconds(CW);
  delay(500);
  s.writeMicroseconds(STOP);
  delay(500);
  s.writeMicroseconds(CCW);
  delay(500);
  s.writeMicroseconds(STOP);
  delay(500); */
  s.write(0);
  delay(500);
  s.write(360);
  delay(500);
}
