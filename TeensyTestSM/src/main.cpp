#include <Arduino.h>
#include <TeensyThreads.h>

/*DEFINES*/
#define USOUT 27
#define USIN  28

#define LEDG  9
#define LEDY  10
#define LEDR  11

/*ShARED GLOBALS*/
int dist;

/* FUNCTIONS */
//Convert US distance to centimeters
float Convert(int num) {
  return num * 0.034 / 2;
}

//Send a 10ms pulse to the specified pin
void pulse(int outPin) {
  digitalWrite(outPin, LOW);
  delay(2);
  digitalWrite(outPin, HIGH);
  delay(10);
  digitalWrite(outPin, LOW);
}
/*END OF FUNCTIONS*/

/*THREAD FUNCTIONS*/
void ReadUS(void) {
  int value;

  while(1) {
    pulse(USOUT);
    value = pulseIn(USIN, HIGH);

    dist = Convert(value);

    delay(100);

    threads.yield();
  }
}

void LightLEDs(void) {
  while(1) {
    if(dist <= 5) {
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDY, LOW);
      digitalWrite(LEDG, LOW);
    }
    else if(dist >= 12) {
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDY, LOW);
      digitalWrite(LEDG, HIGH);
    }
    else {
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDY, HIGH);
      digitalWrite(LEDG, LOW);
    }

    delay(100);
    threads.yield();
  }
}
/*END OF THREAD FUNCTIONS*/


void setup() {
  pinMode(USOUT, OUTPUT);
  pinMode(USIN, INPUT);

  pinMode(LEDG, OUTPUT);
  pinMode(LEDY, OUTPUT);
  pinMode(LEDR, OUTPUT);

  threads.addThread(ReadUS);
  threads.addThread(LightLEDs);
}

void loop() {

}
