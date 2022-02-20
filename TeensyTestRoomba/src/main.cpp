#include <Arduino.h>
#include <TeensyThreads.h>

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
volatile int distanceF;
volatile int distanceL;
volatile int distanceR;

/*LOCOMOTION*/
void moveForward() {
  digitalWrite(M1H, HIGH);
  digitalWrite(M1L, LOW);
  //digitalWrite(M2H, HIGH);
  //digitalWrite(M2L, LOW);
  //digitalWrite(M3H, HIGH);
  //digitalWrite(M3L, LOW);
  //digitalWrite(M4H, HIGH);
  //digitalWrite(M4L, LOW);
}

void moveCW() {
  digitalWrite(M1H, HIGH);
  digitalWrite(M1L, LOW);
  digitalWrite(M2H, LOW);
  digitalWrite(M2L, HIGH);
  digitalWrite(M3H, HIGH);
  digitalWrite(M3L, LOW);
  digitalWrite(M4H, LOW);
  digitalWrite(M4L, HIGH);
}

void moveCCW() {
  digitalWrite(M1H, LOW);
  digitalWrite(M1L, HIGH);
  digitalWrite(M2H, HIGH);
  digitalWrite(M2L, LOW);
  digitalWrite(M3H, LOW);
  digitalWrite(M3L, HIGH);
  digitalWrite(M4H, HIGH);
  digitalWrite(M4L, LOW);
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
  Serial.println("testP");
  pulse(USSFO);
  //distanceF = Convert(digitalRead(USSFI));
  distanceF = pulseIn(USSFI, HIGH);
  pulse(USSLO);
  //distanceF = Convert(digitalRead(USSLI));
  distanceF = pulseIn(USSLI, HIGH);
  pulse(USSRO);
  //distanceF = Convert(digitalRead(USSRI));
  distanceF = pulseIn(USSRI, HIGH);

  delay(100);

  threads.yield();
}

//Initialization loop runs once
void setup() {
  /*distanceF = 0;
  distanceL = 0;
  distanceR = 0;*/

  pinMode(USSFO, OUTPUT);
  pinMode(USSFI, INPUT);
  pinMode(USSLO, OUTPUT);
  pinMode(USSLI, INPUT);
  pinMode(USSRO, OUTPUT);
  pinMode(USSRI, INPUT);
  pinMode(USS4O, OUTPUT);
  pinMode(USS4I, INPUT);

  Serial.begin(115200);

  Serial.println(threads.addThread(readUSS));


}

//Logic for dumb Roomba
void loop() {
  //readUSS();
  Serial.println(distanceF);
  Serial.println(distanceL);
  Serial.println(distanceR);
  if(distanceF > 15) {
    //moveForward();
    Serial.println("forward");
  }
  else {
    if(distanceL > distanceR) {
      //moveCCW();
      Serial.println("ccw");
    }
    else {
      //moveCW();
      Serial.println("cw");
    }
  }

  delay(500);
  //threads.yield();
}
