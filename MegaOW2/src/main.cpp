#include <Arduino.h>
#include <Servo.h>

#define CW   1900
#define STOP 1475
#define CCW  900

#define FR A3
#define FL A1
#define BR A4
#define BL A2

#define BUTTONF      5
#define BUTTONB      4
#define BUTTONL      3
#define BUTTONR      2
#define BUTTONRCW    1
#define BUTTONRCCW   0

Servo servoFR;
Servo servoFL;
Servo servoBR;
Servo servoBL;

bool written;
bool testbool;

void writeAll(int num) {
  servoFR.writeMicroseconds(num);
  servoFL.writeMicroseconds(num);
  servoBR.writeMicroseconds(num);
  servoBL.writeMicroseconds(num);
}

void goForward(void) {
  servoFR.writeMicroseconds(CW);
  servoFL.writeMicroseconds(CCW);
  servoBR.writeMicroseconds(CW);
  servoBL.writeMicroseconds(CCW);
}

void goBackward(void) {
  servoFR.writeMicroseconds(CCW);
  servoFL.writeMicroseconds(CW);
  servoBR.writeMicroseconds(CCW);
  servoBL.writeMicroseconds(CW);
}

void goLeft(void) {
  servoFR.writeMicroseconds(CW);
  servoFL.writeMicroseconds(CW);
  servoBR.writeMicroseconds(CCW);
  servoBL.writeMicroseconds(CCW);
}

void goRight(void) {
  servoFR.writeMicroseconds(CCW);
  servoFL.writeMicroseconds(CCW);
  servoBR.writeMicroseconds(CW);
  servoBL.writeMicroseconds(CW);
}

void rotateCW(void) {
  servoFR.writeMicroseconds(CCW);
  servoFL.writeMicroseconds(CCW);
  servoBR.writeMicroseconds(CCW);
  servoBL.writeMicroseconds(CCW);
}

void rotateCCW(void) {
  servoFR.writeMicroseconds(CW);
  servoFL.writeMicroseconds(CW);
  servoBR.writeMicroseconds(CW);
  servoBL.writeMicroseconds(CW);
}

void ONEgoForward(void) {
  servoFR.writeMicroseconds(CW);
}

void ONEgoBackward(void) {
  servoFR.writeMicroseconds(CCW);
}

void ONEstop(void) {
  servoFR.writeMicroseconds(STOP);
}

void TWOgoForward(void) {
  servoBR.writeMicroseconds(CW);
  servoBL.writeMicroseconds(CCW);
}

void TWOgoBackward(void) {
  servoBR.writeMicroseconds(CCW);
  servoBL.writeMicroseconds(CW);
}

void TWOstop(void) {
  servoBR.writeMicroseconds(STOP);
  servoBL.writeMicroseconds(STOP);
}

void setup() {
  pinMode(BUTTONF, INPUT);
  pinMode(BUTTONB, INPUT);
  pinMode(BUTTONL, INPUT);
  pinMode(BUTTONR, INPUT);
  pinMode(BUTTONRCW, INPUT);
  pinMode(BUTTONRCCW, INPUT);

  servoFR.attach(FR);
  servoFL.attach(FL);
  servoBR.attach(BR);
  servoBL.attach(BL);

  Serial.begin(115200);

  //written = false;

  //writeAll(STOP);
  ONEstop();

}
bool buttonWritten;

void loop() {
  //buttonWritten = digitalRead(BUTTONF);
  //Serial.println(buttonWritten);

  //if(buttonWritten == 1) {
    //if(written == false) {
      TWOgoForward();
      //ONEgoForward();
      delay(1000);
      //written = true;
      //written = true;
    //}
  //}
  /*
  else if(digitalRead(BUTTONB) == HIGH) {
    if(written == false) {
      goBackward();

      written = true;
    }
  }
  else if(digitalRead(BUTTONL) == HIGH) {
    if(written == false) {
      goLeft();

      written = true;
    }
  }
  else if(digitalRead(BUTTONR) == HIGH) {
    if(written == false) {
      goRight();

      written = true;
    }
  }
  else if(digitalRead(BUTTONRCW) == HIGH) {
    if(written == false) {
      rotateCW();

      written = true;
    }
  }
  else if(digitalRead(BUTTONRCCW) == HIGH) {
    if(written == false) {
      rotateCCW();

      written = true;
    }
  }*/
  //else {
    //writeAll(STOP);
    TWOstop();
    //if(written == true) {
      //ONEstop();

      //written = false;
    //}
  //}
    delay(1000);
    //ONEgoBackward();
    TWOgoBackward();
    delay(1000);
    //writeAll(STOP);
    TWOstop();
    //ONEstop();
    delay(1000);
}
