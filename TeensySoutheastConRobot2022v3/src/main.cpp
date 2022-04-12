#include <Arduino.h>
#include "TeensyThreads.h"
#include "Adafruit_NeoPixel.h"
#include "PWMServo.h"

//#include "Locomotion.h"
//#include "Marshmallow.h"
//#include "Beads.h"

//Start button
#define GOBUTTON 1

//NepPixel Pins
#define NUMPIXELS 8
#define NPPINF 57
#define NPPINB 33

Adafruit_NeoPixel pixelsF(NUMPIXELS, NPPINF, NEO_KHZ800 + NEO_RGB);
Adafruit_NeoPixel pixelsB(NUMPIXELS, NPPINB, NEO_KHZ800 + NEO_RGB);

//Seven segment display pins
#define SSDA 48
#define SSDB 50
#define SSDC 41
#define SSDD 40
#define SSDE 53
#define SSDF 44
#define SSDG 51

#define SSD1 45
#define SSD2 49
#define SSD3 43
#define SSD4 42

//Speaker notes and pins
#define SPEAKER 32

#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494

#define REST 0

//Marshmallow stuff
PWMServo MarshServo;
//#define MARSHPIN 46
#define MARSHOUT 135
#define MARSHIN 45
#define MARSHREST 90

#define MARSHALLEY 250
#define MARSHID 250

int marshVal;

//Bead system servos
PWMServo Base;       // 0-180
PWMServo Claw;       // 90-180
PWMServo ClawHeight; // 110-170
PWMServo Reach;      // 30-150

//UltraSonic Sensor pins
#define USSFO 16
#define USSFI 17
#define USSLO 18
#define USSLI 19
#define USSRO 20
#define USSRI 21
#define USSBO 22
#define USSBI 23

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

//Time for rotations
#define SLOWSPEED 56
#define MAXSPEED 255
#define TURNSPEED 255

#define TURNTIME 950
#define TIME (TURNTIME * 255 / TURNSPEED)
#define DIFF 750

#define TURNFRONTDISTANCE 900
#define TURNSIDEDISTANCE 2600
#define TURNSHORT 1000
#define TURNLONG 2600
#define TURNCOMP 800

//Global shared memory
int volatile distanceF;
int volatile distanceL;
int volatile distanceR;
int volatile distanceB;

int volatile lfR;
int volatile lfL;

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

void moveLeftOnly() {
  digitalWrite(M1H, HIGH);
  digitalWrite(M1L, LOW);
  digitalWrite(M2H, LOW);
  digitalWrite(M2L, LOW);
  digitalWrite(M3H, HIGH);
  digitalWrite(M3L, LOW);
  digitalWrite(M4H, LOW);
  digitalWrite(M4L, LOW);
}

void moveRightOnly() {
  digitalWrite(M1H, LOW);
  digitalWrite(M1L, LOW);
  digitalWrite(M2H, LOW);
  digitalWrite(M2L, HIGH);
  digitalWrite(M3H, LOW);
  digitalWrite(M3L, LOW);
  digitalWrite(M4H, LOW);
  digitalWrite(M4L, HIGH);
}

void orientRightFW() {
  analogWrite(M1S, 3 * SLOWSPEED / 2);
  analogWrite(M2S, SLOWSPEED / 2);
  analogWrite(M3S, 3 * SLOWSPEED / 2);
  analogWrite(M4S, SLOWSPEED / 2);

  moveForward();
}

void orientLeftFW() {
  analogWrite(M1S, SLOWSPEED / 2);
  analogWrite(M2S, 3 * SLOWSPEED / 2);
  analogWrite(M3S, SLOWSPEED / 2);
  analogWrite(M4S, 3 * SLOWSPEED / 2);

  moveForward();
}

void orientLeftBW() {
  analogWrite(M1S, 3 * SLOWSPEED / 2);
  analogWrite(M2S, SLOWSPEED / 2);
  analogWrite(M3S, 3 * SLOWSPEED / 2);
  analogWrite(M4S, SLOWSPEED / 2);

  moveBackward();
}

void orientRightBW() {
  analogWrite(M1S, SLOWSPEED / 2);
  analogWrite(M2S, 3 * SLOWSPEED / 2);
  analogWrite(M3S, SLOWSPEED / 2);
  analogWrite(M4S, 3 * SLOWSPEED / 2);

  moveBackward();
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

void speedMax(void) {
  analogWrite(M1S, MAXSPEED);
  analogWrite(M2S, MAXSPEED);
  analogWrite(M3S, MAXSPEED);
  analogWrite(M4S, MAXSPEED);
}

void speedHalf(void) {
  analogWrite(M1S, SLOWSPEED);
  analogWrite(M2S, SLOWSPEED);
  analogWrite(M3S, SLOWSPEED);
  analogWrite(M4S, SLOWSPEED);
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

/*BEADS*/
void openClaw(void) {
  for (unsigned short i = 90; i < 180; i++) {
    Claw.write(i);
    delay(100);
  }
}

void closeClaw(void) {
  for (unsigned short i = 180; i < 90; i--) {
    Claw.write(i);
    delay(100);
  }
}

void raiseArm(void) {
  for (short i = 0; i < 120; i++) {
    Reach.write(30 + i);
    ClawHeight.write(170 - i/2);
    delay(100);
  }
}

void lowerArm(void) {
  for (short i = 0; i < 120; i++) {
    Reach.write(150-i);
    ClawHeight.write(110+i/2);
    delay(100);
  }
}

void Marshmallow() {
  // Run robot locomotion routine
  moveStop();
  delay(500);

  // turn the robot 45 degrees
  speedMax();
  moveCCW();
  delay(375);
  moveStop();
  delay(500);
  // move forward for specific amount of time
  speedHalf();
  moveForward();
  delay(1000); // needs calibrated
  moveStop();
  delay(500);

//push the linear actuator routine
  MarshServo.write(MARSHOUT);
  delay(500);
  MarshServo.write(MARSHIN);
  delay(500);
  MarshServo.write(MARSHREST);
  delay(500);

  // move robot backwards to original position at the beginning of marshmallow routine
  // turn backwards 45 degrees
  moveBackward();
  delay(500);
  moveStop();
  delay(500);

  moveCW();
  delay(375);
  moveStop();
  delay(500);
  // continue down straight path
  exit(1);
}

/*THREAD FUNCTIONS*/
void readMeasurements(void) {
  while(1) {
    pulse(USSFO);
    distanceF = pulseIn(USSFI, HIGH);

    pulse(USSLO);
    distanceL = pulseIn(USSLI, HIGH);

    pulse(USSRO);
    distanceR = pulseIn(USSRI, HIGH);

    pulse(USSBO);
    distanceB = pulseIn(USSBI, HIGH);

    lfR = analogRead(A1);
    lfL = analogRead(A0);
    marshVal = analogRead(A12);

    delay(60);
  }
}

void npLights(void) {
  pixelsF.begin();
  pixelsB.begin();

  while(1) {
    for(short i = 7; i > 0; i -= 2) {
      pixelsF.setPixelColor(i, pixelsF.Color(0, 0, 255));
      pixelsF.setPixelColor(i - 1, pixelsF.Color(255, 255, 255));

      pixelsB.setPixelColor(i, pixelsB.Color(0, 0, 255));
      pixelsB.setPixelColor(i - 1, pixelsB.Color(255, 255, 255));

      pixelsF.show();
      pixelsB.show();
      delay(450);

      if(i == 1) {
        pixelsF.clear();
        pixelsB.clear();
        delay(450);
      }
    }
  }
}

int melody[] = {
  NOTE_A4,4,  NOTE_C4,4,  NOTE_E4,8,
  NOTE_G4,8,  NOTE_B4,8,  NOTE_B4,4,
  NOTE_E4,8,  NOTE_C4,8,  NOTE_E4,8,
};

void sing() {
  pixelsF.begin();
  pixelsB.begin();

  int i;
  int tempo =   400;
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  int wholenote = (50000 * 4) / tempo;
  int divider = 0, noteDuration = 0;

  while(1) {
    // iterate over the notes of the melody
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
      for(i = 7; i > 0; i -= 2) {
        divider = melody[thisNote + 1];
        if (divider > 0)
          noteDuration = (wholenote) / divider;

        else if (divider < 0) {
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 8;
        }

        tone(SPEAKER, melody[thisNote], noteDuration*0.9);
        delay(noteDuration);

        noTone(SPEAKER);
        int pauseBetweenNotes = noteDuration * 1.10;
        delay(pauseBetweenNotes);

        pixelsB.setPixelColor(8 - i, pixelsB.Color(0, 0, 255));
        pixelsB.setPixelColor(7 - i, pixelsB.Color(255, 255, 255));

        pixelsF.setPixelColor(i, pixelsF.Color(0, 0, 255));
        pixelsF.setPixelColor(i - 1, pixelsF.Color(255, 255, 255));

        pixelsF.show();
        pixelsB.show();
        pixelsF.clear();
        pixelsB.clear();
      }
    }
  }
}

void printIEEE(void) {
  digitalWrite(SSD1, HIGH);
  digitalWrite(SSD2, LOW);
  digitalWrite(SSD3, LOW);
  digitalWrite(SSD4, LOW);

  digitalWrite(SSDA, HIGH);
  digitalWrite(SSDB, HIGH);
  digitalWrite(SSDC, HIGH);
  digitalWrite(SSDD, HIGH);
  digitalWrite(SSDE, LOW);
  digitalWrite(SSDF, LOW);
  digitalWrite(SSDG, HIGH);

  delay(1);

  digitalWrite(SSD1, LOW);
  digitalWrite(SSD2, HIGH);
  digitalWrite(SSD3, HIGH);
  digitalWrite(SSD4, HIGH);

  digitalWrite(SSDA, LOW);
  digitalWrite(SSDB, HIGH);
  digitalWrite(SSDC, HIGH);
  digitalWrite(SSDD, LOW);
  digitalWrite(SSDE, LOW);
  digitalWrite(SSDF, LOW);
  digitalWrite(SSDG, LOW);

  delay(1);
}

void print2022(){

  digitalWrite(SSD1, HIGH);
  digitalWrite(SSD2, LOW);
  digitalWrite(SSD3, HIGH);
  digitalWrite(SSD4, HIGH);

  digitalWrite(SSDA, LOW);
  digitalWrite(SSDB, LOW);
  digitalWrite(SSDC, HIGH);
  digitalWrite(SSDD, LOW);
  digitalWrite(SSDE, LOW);
  digitalWrite(SSDF, HIGH);
  digitalWrite(SSDG, LOW);

  delay(1);

  digitalWrite(SSD1, LOW);
  digitalWrite(SSD2, HIGH);
  digitalWrite(SSD3, LOW);
  digitalWrite(SSD4, LOW);

  digitalWrite(SSDA, LOW);
  digitalWrite(SSDB, LOW);
  digitalWrite(SSDC, LOW);
  digitalWrite(SSDD, LOW);
  digitalWrite(SSDE, LOW);
  digitalWrite(SSDF, LOW);
  digitalWrite(SSDG, HIGH);

  delay(1);
}

void SevSeg(void) {
  while(1) {
    digitalWrite(SSD1, HIGH);
    digitalWrite(SSD2, HIGH);
    digitalWrite(SSD3, HIGH);
    digitalWrite(SSD4, HIGH);

    digitalWrite(SSDA, LOW);
    digitalWrite(SSDB, LOW);
    digitalWrite(SSDC, LOW);
    digitalWrite(SSDD, LOW);
    digitalWrite(SSDE, LOW);
    digitalWrite(SSDF, LOW);
    digitalWrite(SSDG, HIGH);
  }
}

void setup() {
  pinMode(USSFO, OUTPUT);
  pinMode(USSFI, INPUT);
  pinMode(USSLO, OUTPUT);
  pinMode(USSLI, INPUT);
  pinMode(USSRO, OUTPUT);
  pinMode(USSRI, INPUT);
  pinMode(USSBO, OUTPUT);
  pinMode(USSBI, INPUT);

  pinMode(M1H, OUTPUT);
  pinMode(M1L, OUTPUT);
  pinMode(M2H, OUTPUT);
  pinMode(M2L, OUTPUT);
  pinMode(M3H, OUTPUT);
  pinMode(M3L, OUTPUT);
  pinMode(M4H, OUTPUT);
  pinMode(M4L, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  pinMode(GOBUTTON, INPUT);
  pinMode(4, OUTPUT);

  Base.attach(A16);
  ClawHeight.attach(A17);
  Reach.attach(A18);
  Claw.attach(A19);

  pinMode(A12, INPUT);
  //MarshServo.attach(A24);

  pinMode(SSDA, OUTPUT);
  pinMode(SSDB, OUTPUT);
  pinMode(SSDC, OUTPUT);
  pinMode(SSDD, OUTPUT);
  pinMode(SSDE, OUTPUT);
  pinMode(SSDF, OUTPUT);
  pinMode(SSDG, OUTPUT);

  pinMode(SSD1, OUTPUT);
  pinMode(SSD2, OUTPUT);
  pinMode(SSD3, OUTPUT);
  pinMode(SSD4, OUTPUT);

  pixelsF.clear();
  pixelsB.clear();

  threads.addThread(readMeasurements);
  threads.addThread(sing);

  //MarshServo.write(MARSHREST);

  Serial.begin(115200);
}

void loop() {
  //wait for the ON button
  int button = digitalRead(GOBUTTON);
  int lastTurn;
  int test = 0;
  bool firstTurn = true;

  if(button) {
    if (test == 1) {
      while(1) {
        Serial.println(lfL);
        Serial.println(lfR);
        Serial.println((float)Convert(distanceF)/2.54);
        Serial.println(distanceF);
        Serial.println();

        delay(500);
      }
    }
    else if(test == 2) {
      speedHalf();
      lastTurn = -1;
      while((distanceF > TURNFRONTDISTANCE + 50)) {
        if(lfL > DIFF) {
          orientRightFW();
          lastTurn = 1;
        }
        else if(lfR > DIFF) {
          orientLeftFW();
          lastTurn = 0;
        }
        else {
          if(lastTurn == 1) {
            orientLeftFW();
            delay(TURNCOMP);
          }
          else if(lastTurn == 0) {
            orientRightFW();
            delay(TURNCOMP);
          }

          speedHalf();
          moveForward();
          lastTurn = -1;
        }

        delay(25);
      }

      moveStop();
      delay(700);

      //Turn 90°
      speedMax();
      moveCCW();
      delay(TIME-75);

      moveStop();
      delay(700);

      speedHalf();
      moveForward();
      delay(1000);

      moveStop();
      delay(500);
      if(lfL > DIFF-100) {
        speedMax();
        moveCW();
        delay(200);
        moveStop();
        delay(500);
      }

      exit(1);
    }
    else if(test == 3) {
      while(distanceF > TURNFRONTDISTANCE || distanceR > TURNSIDEDISTANCE) {
        if(distanceL > TURNLONG && marshVal < MARSHID)
        //  Marshmallow();

        if(lfL > DIFF) {
          orientRightFW();
          lastTurn = 1;
        }
        else if(lfR > DIFF) {
          orientLeftFW();
          lastTurn = 0;

          if(firstTurn) {
            delay(700);
            while(lfL > DIFF) {}
            firstTurn = false;
          }
        }
        else {
          if(lastTurn == 1) {
            orientLeftFW();
            delay(TURNCOMP);
          }
          else if(lastTurn == 0) {
            orientRightFW();
            delay(TURNCOMP);
          }

          speedHalf();
          moveForward();
          lastTurn = -1;
        }

        moveForward();

        delay(25);
      }
    }
// ROUTINE START
    while(1) {
      //Move to the 90° turn
      speedHalf();
      lastTurn = -1;
      while((distanceF > TURNFRONTDISTANCE + 0)) {
      //while(lfL < DIFF || lfR < DIFF) {
        if(lfL > DIFF) {
          orientRightFW();
          lastTurn = 1;
        }
        else if(lfR > DIFF) {
          orientLeftFW();
          lastTurn = 0;
        }
        else {
          if(lastTurn == 1) {
            orientLeftFW();
            delay(TURNCOMP);
          }
          else if(lastTurn == 0) {
            orientRightFW();
            delay(TURNCOMP);
          }

          speedHalf();
          moveForward();
          lastTurn = -1;
        }

        delay(10);
      }

      moveStop();
      delay(700);

      //turning point adjustment
      speedHalf();
      while(lfL < DIFF || lfR < DIFF)
        moveForward();

      moveStop();
      delay(700);

      while(lfL > DIFF || lfR > DIFF)
        moveBackward();

      moveStop();
      delay(700);
      //end turning point adjustment

////////////////////////////////////////////


      moveBackward();
      delay(250);
      moveStop();

///////////////////////////////////////////

      //Turn 90°
      speedMax();
      moveCW();
      delay(TIME+30);

      moveStop();
      delay(700);

      /*speedMax();
      //while((distanceF < TURNLONG) || (distanceL > TURNSHORT) || (distanceR < TURNLONG) || (distanceB > TURNSHORT)) {
      while((distanceL > TURNSHORT) || (distanceB > TURNSHORT)) {
        moveCW();
        delay(100);
        moveStop();
        delay(700);
      }

      exit(1);*/

      speedHalf();
      moveForward();
      delay(1000);

      /*moveStop();
      delay(500);
      if(lfL > DIFF-200) {
        speedMax();
        moveCCW();
        delay(50);
        moveStop();
        delay(500);
      }*/

      //go to end
      while(distanceF > TURNFRONTDISTANCE || distanceR > TURNSIDEDISTANCE) {
        if(lfL > DIFF) {
          orientRightFW();
          lastTurn = 1;
        }
        else if(lfR > DIFF) {
          orientLeftFW();
          lastTurn = 0;

          if(firstTurn) {
            delay(700);
            while(lfL > DIFF) {}
            firstTurn = false;
          }
        }
        else {
          if(lastTurn == 1) {
            orientLeftFW();
            delay(TURNCOMP);
          }
          else if(lastTurn == 0) {
            orientRightFW();
            delay(TURNCOMP);
          }

          speedHalf();
          moveForward();
          lastTurn = -1;
        }

        moveForward();

        delay(25);
      }

      moveStop();
      delay(700);

      speedHalf();
      moveBackward();
      delay(1000); // was 1000

      /*moveStop();
      delay(500);
      if(lfR > DIFF) {
        speedMax();
        moveCW();
        delay(50);
        moveStop();
        delay(500);
      }*/

      //Move backwards until the 90° turn
      while(distanceB > TURNFRONTDISTANCE + 100) {
        if(lfL > DIFF) {
          orientRightBW();
          lastTurn = 1;
        }
        else if(lfR > DIFF) {
          orientLeftBW();
          lastTurn = 0;
        }
        else {
          if(lastTurn == 1) {
            orientLeftBW();
            delay(TURNCOMP);
          }
          else if(lastTurn == 0) {
            orientRightBW();
            delay(TURNCOMP);
          }

          speedHalf();
          moveBackward();
          lastTurn = -1;
        }

        delay(50);
      }

      moveStop();
      delay(500);

      speedMax();
      moveCCW();
      delay(TIME - 75);

      moveStop();
      delay(700);

      speedHalf();
      moveBackward();
      delay(850);
      moveStop();
      delay(500);
      /*
      if(lfR > DIFF) {
        speedMax();
        moveCW();
        delay(200);
        moveStop();
        delay(500);
      }*/

      speedHalf();
      while(distanceB > TURNFRONTDISTANCE - 200) {
        if(lfL > DIFF) {
          orientRightBW();
          lastTurn = 1;
        }
        else if(lfR > DIFF) {
          orientLeftBW();
          lastTurn = 0;
        }
        else {
          if(lastTurn == 1) {
            orientLeftBW();
            delay(TURNCOMP-100);
          }
          else if(lastTurn == 0) {
            orientRightBW();
            delay(TURNCOMP);
          }

          speedHalf();
          moveBackward();
          lastTurn = -1;
        }

        delay(25);
      }

      moveStop();
      delay(700);
      exit(1);

      /*speedMax();
      moveCW();
      delay(TIME * 2);

      speedHalf();
      while(lfL > DIFF || lfR > DIFF)
        moveForward();*/
    }
  }
}
