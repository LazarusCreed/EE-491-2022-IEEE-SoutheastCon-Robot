/*
---------------------------------------------------------------------
Author: John Adamick

This project will lay-out how code will be formated for our project.
Your code will be implemented in a class/library that can be easily
  implemented into our robot's main code.

There should be no code written in this section that will actually
  integrate your module into reusable functions.
  - ALL INTEGRATION FOR YOUR MODULE SHOULD BE WRITTEN INTO A CLASS
    - See SampleClass
  - The purpose of this main.cpp file is to apply your class to
    logic.
---------------------------------------------------------------------
*/

/*
**GRAMMAR AND PUNCTUATION**
  - All words should be spelled correctly.
  - All written items should be in complete sentences and/or paragraphs.
  - All written items should use correct grammar.
  - All written items should include correct punctuation.

**FORMATTING**
  Class           -   Pascal Case
  Constant        -   Upper Case
  Enum Type       -   Pascal Case
  Enum Values     -   Pascal Case
  Event           -   Pascal Case
  Functions       -   Camel Case
  Interface       -   Pascal Case
  Method          -   Pascal Case
  Namespace       -   Pascal Case
  Parameter       -   Camel Case
  Property        -   Pascal Case
  Global Variable -   Pascal Case
    NOTE: All global variables should begin with "g_".
  Local Variable  -   Camel Case
    NOTE: Variables should never differ only by case.

**NAMING GUIDELINES**
  Classes
    - Use a noun or noun phrase to name a class.
    - Use Pascal Case.
    - Do not use an underscore.
    - Avoid using abbreviations.
    - Variables that are private to the class should begin wtih "c_".
*/

/*
All files listed at the top of each programming file is a
  dependency. These must be added at the top of c++ files with
  a "#include" if you want to use their functionality.
*/

/*
**DESCRIPTION**
This is the standard Arduino library.
  - Always include this in your main if your code will be integrated
    into an Arduino or Teensy.
*/
#include <Arduino.h>

/*
**DESRIPTION**
This is your class.
  - Obviously this will need to be renamed to reflect your module.
  - Including this will allow the code in this file to access your
    functions that you will make in your class.
PLEASE REVIEW THE CLASS AND HEADER FILES.
*/
#include <SampleClass.h>

// This class declaration will also call the constructor to initialize it.
SampleClass g_Sample(6);

/*
This section of the code will only ever run one time. This is useful for
  one-time code calls such as initializations.
Since our code includes an initialization during construction, we do not need
  to put anything here.
*/

/*
PURPOSE: none
*/
void setup() {
}

/*
This section of the code will run forever unless an exit function is called.
Ths section is used for writing code that will actually perform your work.
*/

/*
PURPOSE: This will toggle the pin initialized in g_Sample on and off every second.
*/
void loop() {
  g_Sample.writeHigh();
  delay(1000);
  g_Sample.writeLow();
  delay(1000);
}
