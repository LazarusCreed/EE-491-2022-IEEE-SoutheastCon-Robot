#include <Arduino.h>

#define H1 19
#define H2 20
#define H3 21
#define H4 22

#define SPEED1 2
#define SPEED2 3

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
  analogWrite(SPEED1, 255);
  analogWrite(SPEED2, 255);
}

void speedHalf(void) {
  analogWrite(SPEED1, 128);
  analogWrite(SPEED2, 128);
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
  int i;

  moveForward();
  for(i = 0; i < 255; i++) {
    analogWrite(SPEED1, i);
    analogWrite(SPEED2, i);
    delay(20);
  }

  delay(500);

  for(i = 255; i > 0; i--) {
    analogWrite(SPEED1, i);
    analogWrite(SPEED2, i);
    delay(20);
  }

  delay(500);
}
