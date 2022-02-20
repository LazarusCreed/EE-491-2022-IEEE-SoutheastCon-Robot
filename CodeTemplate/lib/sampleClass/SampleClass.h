/*
---------------------------------------------------------------------
Author: John Adamick

This is the header for your class. This will contain all integration
  for your module. The goal for this is to have code that can be
  easily integrated into any Arduino/Teensy and be easily learned
  and used in the main file.

This sample class will be used to initialize a given pin for a digital
  write and have functions to write a digital high or low.
---------------------------------------------------------------------
*/

/*
**DESCRIPTION**
You can define any CONSTANT global values that will be prevelant
  throughout your code.
**DEFINITION**
const
  Used before the variable type to state that the value will not be changed.
*/
const int TEENSYMIN = 0;
const int TEENSYMAX = 57;

/*
**DESCRIPTION**
This will compile the Arduino library if it is previously
  defined.
  - The purpose of this is to save resources if the main code
    isn't using an Arduino. In our case, this will always compile,
    but it's good practice especially since we want our code to
    be useable by others with microcontrollers that could potentially
    have lower on-board storage.
*/
#ifdef ARDUINO
#include <Arduino.h>
#endif

/*
**DESCRIPTION**
This is the definition of your class. You will need this to contain
  all of your code under one name.
  - The purpose of a header file is to OUTLINE what functions and
    data members will be included in your class.
*/
class SampleClass {
  /*
  **DESCRIPTION**
  This is a declaration to state whether a data member is
    public or private. Private members are not accessable
    by the main where this class is being implemented.
    Therefore, any functions that will be used by anybody
    wanting to implement this class must be written under the
    "public" declaration.
      - The purpose of this is for privacy and security.
      - By default, all members of a "class" are declared as
        private (as opposed to a "struct" where all members
        are public), so the only purpose of re-declaring
        "private" here is for good coding practice.

    Format of functions in header:
    returnType functionName(arguments);
      - returnType: type of variable to be returned
        - void: no return
      - functionName: name of the function. Must be consistent
          with the body file.
      - arguments: data to be passed in from other places.
        - i.e. a variable defined in the private section of
            your class.
        - [type] [variable name]
  */
  private:
    //This variable and anything else defined here will not be
    //  accessable outside of the header and body.
    int c_pinNum;
  public:
    /*
    These functions will be useable by the code implementing
      this class.
    Short descriptions should be added here.
    */

    //This is the basic constructor.
    SampleClass(void);

    //This is a constructor that initializes c_pinNum.
    SampleClass(int pinNum);

    //Used to initialize the pin needed for this class if not originally specified.
    int init(int pinNum);

    //Will write a digital high to c_pinNum.
    void writeHigh(void);

    //Will write a digital low to c_pinNum.
    void writeLow(void);
};
