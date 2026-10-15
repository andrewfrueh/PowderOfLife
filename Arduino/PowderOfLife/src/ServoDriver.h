/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Servo Driver
  
  ===========================

  Controls a basic servo motor with standard Arduino PWM output.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */



// TODO
// straight mapping to 180 degrees
// more?

// ServoDriver has dependency on Servo library, so we include it by default
#include <Servo.h>
// Check if the library is installed
// #if defined(Servo_h)
//   #include "ServoDriver.h"
// #else
#ifndef Servo_h
  #error "POL ServoDriver is dependent on the standard Servo library. Please install it first."
#endif




class ServoDriver : public Driver {
  private:
    int outputPin;
    Servo servoObject;
    byte outputRangeMin; 
    byte outputRangeMax;
  public:
    ServoDriver();
    //
    void work();
    void setPin(int newPin);
    void setRange(byte newMin, byte newMax);
};


// constructor
ServoDriver::ServoDriver() {
  //SetLerpProperties(SERVODRIVER_LERP_SPEED, SERVODRIVER_LERP_ACCEL);
  setNormal(normalMode::custom, normalClip::clip, 0.0, 1.0);
  setRange(0,180);
}

void ServoDriver::setPin(int newPin){
  outputPin = newPin;
  servoObject.attach(outputPin);
}

void ServoDriver::work() {
  setInternalValue(getInput().getValue());
  int pos = Toolkit::mapf( getValue(), 0, 1, outputRangeMin, outputRangeMax);
  // Be sure to clamp the output
  pos = Toolkit::constraini(pos, outputRangeMin, outputRangeMax);
  servoObject.write(pos);
}

void ServoDriver::setRange(byte newMin, byte newMax){
  outputRangeMin = newMin;
  outputRangeMax = newMax;
}

// EOF
