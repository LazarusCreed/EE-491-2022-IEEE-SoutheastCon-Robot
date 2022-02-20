#include <Arduino.h>

#define H1 26
#define H2 27
#define H3 28
#define H4 29

#define SPEED1 8
#define SPEED2 9

void moveForward(void) {
  digitalWrite(H1, HIGH);
  digitalWrite(H2, LOW);
  digitalWrite(H3, HIGH);
  digitalWrite(H4, LOW);
}

void moveBackward(void) {
  digitalWrite(H1, LOW);
  digitalWrite(H2, HIGH);
  digitalWrite(H3, LOW);
  digitalWrite(H4, HIGH);
}

void moveStop(void) {
  digitalWrite(H1, LOW);
  digitalWrite(H2, LOW);
  digitalWrite(H3, LOW);
  digitalWrite(H4, LOW);
}

void speedMax(void) {
  analogWrite(18, 255);
  analogWrite(23, 255);
}

void speedHalf(void) {
  analogWrite(18, 128);
  analogWrite(23, 128);
}

void setup() {
  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(H3, OUTPUT);
  pinMode(H4, OUTPUT);

  pinMode(SPEED1, OUTPUT);
  pinMode(SPEED2, OUTPUT);
}

void loop() {
  speedHalf();
  moveForward();
  delay(500);

  speedMax();
  moveForward();
  delay(500);
  /*
  speedHalf();
  moveForward();
  delay(500);

  moveStop();
  delay(500);

  speedHalf();
  moveBackward();
  delay(500);

  speedMax();
  moveBackward();
  delay(500);

  speedHalf();
  moveBackward();
  delay(500);

  moveStop();
  delay(500);
  */
}
