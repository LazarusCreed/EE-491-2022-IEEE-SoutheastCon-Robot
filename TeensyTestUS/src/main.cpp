//Program to test four UltraSonic sensors

#include <Arduino.h>
#include <iostream>

using namespace std;

//number of tests to run for test 2
#define NUMTESTS 200
#define NUMTRIALS 10

#define USD1 14
#define USA1 15
#define USD2 16
#define USA2 17
#define USD3 18
#define USA3 19
#define USD4 20
#define USA4 21

void pulse(int outPin) {
  digitalWrite(outPin, LOW);
  delay(2);
  digitalWrite(outPin, HIGH);
  delay(10);
  digitalWrite(outPin, LOW);
}

float Convert(int num) {
  return num * 0.034 / 2;
}

float CalcAvg(int num[]) {
  float avg = 0;

  for(int i = 0; i < NUMTESTS; i++) {
    avg += num[i];
  }

  return avg / NUMTESTS;
}

float CalcSD(int data[]) {
  float sum = 0.0, mean, standardDeviation = 0.0;
  int i;

  for(i = 0; i < NUMTESTS; ++i) {
    sum += data[i];
  }

  mean = sum / NUMTESTS;

  for(i = 0; i < NUMTESTS; ++i) {
    standardDeviation += pow(data[i] - mean, 2);
  }

  return sqrt(standardDeviation / NUMTESTS);
}

void setup() {
  pinMode(USD1, OUTPUT);
  pinMode(USA1, INPUT);

  pinMode(USD2, OUTPUT);
  pinMode(USA2, INPUT);

  pinMode(USD3, OUTPUT);
  pinMode(USA3, INPUT);

  pinMode(USD4, OUTPUT);
  pinMode(USA4, INPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.flush();

  int readUS1;
  int readUS2;
  int readUS3;
  int readUS4;

  int i;

  int valUS1[NUMTESTS] = {};
  int valUS2[NUMTESTS] = {};
  int valUS3[NUMTESTS] = {};
  int valUS4[NUMTESTS] = {};

  float avgUS1 = 0;
  float avgUS2 = 0;
  float avgUS3 = 0;
  float avgUS4 = 0;

  float sdUS1 = 0;
  float sdUS2 = 0;
  float sdUS3 = 0;
  float sdUS4 = 0;

  float avgUS1_ar[NUMTRIALS] = {};
  float avgUS2_ar[NUMTRIALS] = {};
  float avgUS3_ar[NUMTRIALS] = {};
  float avgUS4_ar[NUMTRIALS] = {};

  float sdUS1_ar[NUMTRIALS] = {};
  float sdUS2_ar[NUMTRIALS] = {};
  float sdUS3_ar[NUMTRIALS] = {};
  float sdUS4_ar[NUMTRIALS] = {};


  for(int j = 0; j < NUMTRIALS; j++) {
    for(i = 0; i < NUMTESTS; i++) {
      pulse(USD1);
      valUS1[i] = pulseIn(USA1, HIGH);

      delay(1);
    }

    for(i = 0; i < NUMTESTS; i++) {
      pulse(USD2);
      valUS2[i] = pulseIn(USA2, HIGH);

      delay(1);
    }

    for(i = 0; i < NUMTESTS; i++) {
      pulse(USD3);
      valUS3[i] = pulseIn(USA3, HIGH);

      delay(1);
    }

    for(i = 0; i < NUMTESTS; i++) {
      pulse(USD4);
      valUS4[i] = pulseIn(USA4, HIGH);

      delay(1);
    }

    avgUS1_ar[j] = CalcAvg(valUS1);
    avgUS2_ar[j] = CalcAvg(valUS2);
    avgUS3_ar[j] = CalcAvg(valUS3);
    avgUS4_ar[j] = CalcAvg(valUS4);

    sdUS1_ar[j] = CalcSD(valUS1);
    sdUS2_ar[j] = CalcSD(valUS2);
    sdUS3_ar[j] = CalcSD(valUS3);
    sdUS4_ar[j] = CalcSD(valUS4);
  }

  Serial.print("avgUS5,avgUS6,avgUS7,avgUS8\n");
  for(i = 0; i < NUMTRIALS; i++) {
    Serial.print(avgUS1_ar[i]);
    Serial.print(",");
    Serial.print(avgUS2_ar[i]);
    Serial.print(",");
    Serial.print(avgUS3_ar[i]);
    Serial.print(",");
    Serial.print(avgUS4_ar[i]);
    Serial.print("\n");
  }

  Serial.print("cnvUS5,cnvUS6,cnvUS7,cnvUS8\n");
  for(i = 0; i < NUMTRIALS; i++) {
    Serial.print(Convert(avgUS1_ar[i]));
    Serial.print(",");
    Serial.print(Convert(avgUS2_ar[i]));
    Serial.print(",");
    Serial.print(Convert(avgUS3_ar[i]));
    Serial.print(",");
    Serial.print(Convert(avgUS4_ar[i]));
    Serial.print("\n");
  }

  Serial.print("sdUS5,sdUS6,sdUS7,sdUS8\n");
  for(i = 0; i < NUMTRIALS; i++) {
    Serial.print(sdUS1_ar[i]);
    Serial.print(",");
    Serial.print(sdUS2_ar[i]);
    Serial.print(",");
    Serial.print(sdUS3_ar[i]);
    Serial.print(",");
    Serial.print(sdUS4_ar[i]);
    Serial.print("\n");
  }

  exit(0);
}
