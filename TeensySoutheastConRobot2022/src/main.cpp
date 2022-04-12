#include <Arduino.h>
#include "TeensyThreads.h"

//#include "Locomotion.h"
//#include "Marshmallow.h"
//#include "Beads.h"

#define GOBUTTON 0

//UltraSonic Sensor pins
#define USSFO 16
#define USSFI 17
#define USSLO 18
#define USSLI 19
#define USSRO 20
#define USSRI 21
#define USS4O 22
#define USS4I 23

//Motor Pins
#define M1H 10
#define M1L 11
#define M2L 12
#define M2H 24
#define M3H 25
#define M3L 26
#define M4L 27
#define M4H 28

//Motor PWM (speed) pins
#define M1S 2
#define M2S 3
#define M3S 4
#define M4S 5

//Global shared memory
int volatile distanceF;
int volatile distanceL;
int volatile distanceR;

/*LOCOMOTION*/
void moveForward() {
  digitalWrite(M1H, HIGH);
  digitalWrite(M1L, LOW);
  digitalWrite(M2H, LOW);
  digitalWrite(M2L, HIGH);
  digitalWrite(M3H, HIGH);
  digitalWrite(M3L, LOW);
  digitalWrite(M4H, LOW);
  digitalWrite(M4L, HIGH);
}

void moveBackward() {
  digitalWrite(M1H, LOW);
  digitalWrite(M1L, HIGH);
  digitalWrite(M2H, HIGH);
  digitalWrite(M2L, LOW);
  digitalWrite(M3H, LOW);
  digitalWrite(M3L, HIGH);
  digitalWrite(M4H, HIGH);
  digitalWrite(M4L, LOW);
}

void moveCW() {
  digitalWrite(M1H, HIGH);
  digitalWrite(M1L, LOW);
  digitalWrite(M2H, HIGH);
  digitalWrite(M2L, LOW);
  digitalWrite(M3H, HIGH);
  digitalWrite(M3L, LOW);
  digitalWrite(M4H, HIGH);
  digitalWrite(M4L, LOW);
}

void moveCCW() {
  digitalWrite(M1H, LOW);
  digitalWrite(M1L, HIGH);
  digitalWrite(M2H, LOW);
  digitalWrite(M2L, HIGH);
  digitalWrite(M3H, LOW);
  digitalWrite(M3L, HIGH);
  digitalWrite(M4H, LOW);
  digitalWrite(M4L, HIGH);
}

void moveStop() {
  digitalWrite(M1H, LOW);
  digitalWrite(M1L, LOW);
  digitalWrite(M2H, LOW);
  digitalWrite(M2L, LOW);
  digitalWrite(M3H, LOW);
  digitalWrite(M3L, LOW);
  digitalWrite(M4H, LOW);
  digitalWrite(M4L, LOW);
}
/*END LOCOMOTION*/

//Convert the USS response data to cm
float Convert(int num) {
  return num * 0.034 / 2;
}

//Send a 10ms digital HIGH to outPin
void pulse(int outPin) {
  digitalWrite(outPin, LOW);
  delay(2);
  digitalWrite(outPin, HIGH);
  delay(10);
  digitalWrite(outPin, LOW);
}

/*THREAD FUNCTIONS*/
void readUSS(void) {
  while(1) {
    pulse(USSFO);
    distanceF = pulseIn(USSFI, HIGH);

    pulse(USSLO);
    distanceL = pulseIn(USSLI, HIGH);

    pulse(USSRO);
    distanceR = pulseIn(USSRI, HIGH);

    delay(50);

    Serial.println(distanceF);
    Serial.println(distanceL);
    Serial.println(distanceR);
    Serial.println();
    //threads.yield();
  }
}

//Locomotion L(pins);
//Marshmallow M(pins);
//Beads B(pins);

void setup() {
  //L.init();
  //M.init();
  //B.init();

  pinMode(USSFO, OUTPUT);
  pinMode(USSFI, INPUT);
  pinMode(USSLO, OUTPUT);
  pinMode(USSLI, INPUT);
  pinMode(USSRO, OUTPUT);
  pinMode(USSRI, INPUT);
  pinMode(USS4O, OUTPUT);
  pinMode(USS4I, INPUT);

  pinMode(M1H, OUTPUT);
  pinMode(M1L, OUTPUT);
  pinMode(M2H, OUTPUT);
  pinMode(M2L, OUTPUT);
  pinMode(M3H, OUTPUT);
  pinMode(M3L, OUTPUT);
  pinMode(M4H, OUTPUT);
  pinMode(M4L, OUTPUT);

  //pinMode(GOBUTTON, INPUT);

  //threads.addThread(readUSS);

  Serial.begin(115200);

  //threads.addThread(L.readUSS())
}

bool turn = true; //true == CW

void loop() {
  //wait for the ON button
  //bool go = digitalRead(GOBUTTON);


  //if(digitalRead(GOBUTTON)) {
    //while(1) {
      Serial.println("test");

      //go to the turn
      /*while(distanceF > 800) {
        moveForward();
        delay(50);
      }

      if (turn) {
        moveCW();
        turn = false;
      }
      else {
        moveCCW();
        turn = true;
      }
      delay(1000);

      //turn around at the end
      while(distanceF > 800) {
        moveForward();
        delay(50);
      }

      moveCW();
      delay(2000);*/
    //}
  //}
}
