//Program to test four UltraSonic sensors

#include <Arduino.h>

using namespace std;

#define USD1 12
#define USA1 13
//#define USD2 16
//#define USA2 17
//#define USD3 18
//#define USA3 19
//#define USD4 20
//#define USA4 21
/*
int pulse(int outPin, int inPin) {
  digitalWrite(outPin, LOW);
  delay(2);
  digitalWrite(outPin, HIGH);
  delay(10);
  digitalWrite(outPin, LOW);

  //return pulseIn(inPin, HIGH);
  return analogRead(inPin);
}*/

void setup() {
  pinMode(USD1, OUTPUT);
  pinMode(USA1, INPUT);

  //pinMode(USD2, OUTPUT);
  //pinMode(USA2, INPUT);

  //pinMode(USD3, OUTPUT);
  //pinMode(USA3, INPUT);

  //pinMode(USD4, OUTPUT);
  //pinMode(USA4, INPUT);

  Serial.begin(115200);
}

void loop() {
  int readUS1;
  int readUS2;
  int readUS3;
  int readUS4;

  Serial.flush();

  digitalWrite(USD1, LOW);
  delay(2);
  digitalWrite(USD1, HIGH);
  delay(10);
  digitalWrite(USD1, LOW);

  readUS1 = pulseIn(USA1, HIGH);
  readUS1 *= 0.034 / 2;

  //readUS1 = pulse(USD1, USA1);
  //cout << "US1: \t" << readUS1 << endl;
  Serial.print("US1: \t");
  Serial.print(readUS1);
  //Serial.print("\n");

  /*pulse(USD2);
  readUS1 = analogRead(USA2);
  //cout << "US2: \t" << readUS2 << endl;
  Serial.print("US2: \t");
  Serial.print(readUS2);
  Serial.print("\n");

  pulse(USD3);
  readUS3 = analogRead(USA3);
  //cout << "US3: \t" << readUS3 << endl;
  Serial.print("US3: \t");
  Serial.print(readUS3);
  Serial.print("\n");

  pulse(USD4);
  readUS4 = analogRead(USA4);
  //cout << "US4: \t" << readUS4 << endl;
  Serial.print("US4: \t");
  Serial.print(readUS4);*/
  Serial.print("\n\n");

  delay(1000);
}
