/*
---------------------------------------------------------------------
Author: John Adamick

This is the body of your class. This is where actual code that
  stuff will be written
---------------------------------------------------------------------
*/

/*
**NOTE**
The only dependency that the body should have is a reference
  to its header file.
  - This will include any libraries and constants defined at the top of your
    header as well.
*/
#include "SampleClass.h"

/*
**NOTE**
Every class must include a constructor(s). The purpose of a constructor is to allow
  specific variables and board components to be initialized. It does not have a
  return.
  - In this case, it will initialize our private variable c_pinNum to a value
    that will be recognized by the program later as uninitialized.
*/

/*
CONSTRUCTOR
PURPOSE: Initializes c_pinNum to the default value of -1.
INPUTS: void
*/
SampleClass::SampleClass(void) {
  c_pinNum = -1;
}

/*
CONSTRUCTOR
PURPOSE: Checks the argument pinNum to see if it is valid and either set c_pinNum
  to pinNum if it is valid or set it to the default value otherwise.
INPUTS: void
*/
SampleClass::SampleClass(int pinNum) {
  if(pinNum >= TEENSYMIN && pinNum <= TEENSYMAX) {
    pinMode(pinNum, OUTPUT);
    c_pinNum = pinNum;
  }
  else {
    Serial.print("Pin number is not available for the Teensy rev. 3.5: ");
    Serial.println(pinNum);
    Serial.println("Pin will be set to default value of -1.");
    c_pinNum = -1;
  }
}

//This is the format we will use for all functions.

/*
FUNCTION: init
PURPOSE: Set the microcontroller to initialize one pin on the Teensy rev. 3.5 to
  argument pinNum. Print an error and returns -1 if the number is out of range.
  Set the private variable c_pinNum to the input variable pinNum if successful.
INPUTS: pinNum
OUTPUT: -1 if it fails, otherwise return 0.
*/
int SampleClass::init(int pinNum) {
  if(pinNum >= TEENSYMIN && pinNum <= TEENSYMAX) {
    pinMode(pinNum, OUTPUT);
    c_pinNum = pinNum;
  }
  else {
    Serial.print("Pin number is not available for the Teensy rev. 3.5: ");
    Serial.println(pinNum);
    return -1;
  }

  return 0;
};

/*
FUNCTION: writeHigh
PURPOSE: Set the internal pin to a digital high.
  Prints an error if the pin has not been initlialized.
INPUTS: void
OUTPUTS: void
*/
void SampleClass::writeHigh(void) {
  if(c_pinNum != -1) {
    digitalWrite(c_pinNum, HIGH);
  }
  else {
    Serial.println("Pin has not been initialized for write.");
  }
}

/*
FUNCTION: writeLow
PURPOSE: Set the internal pin to a digital low.
  Prints an error if the pin has not been initlialized.
INPUTS: void
OUTPUTS: void
*/
void SampleClass::writeLow(void) {
  if(c_pinNum != -1) {
    digitalWrite(c_pinNum, LOW);
  }
  else {
    Serial.println("Pin has not been initialized for write.");
  }
}
