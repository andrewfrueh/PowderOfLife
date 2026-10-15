/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Motor Driver

  ===========================

  Controls a basic DC motor driver board (two pins: digital direction, PWM speed).

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

  ==================================================================================================== */

// TODO
// There's a problem with input = -1
// WHY?????



class MotorDriver : public Driver {
  private:
    int outputDirPin; // digital
    int outputSpeedPin; // analog
    byte outputRangeMin;
    byte outputRangeMax;
    bool reverseDirection;
    //
    //bool useCenterOffset = false;
    float centerOffsetPoint;
    //int outputSpeed;
  protected:
    //Neuron* inputNeurons[1];
  public:
    MotorDriver();
    //
    void work();
    void setPin(int newDirPin, int newSpeedPin);
    void setRange(byte newMin, byte newMax);
    void setReverse(bool newRev); // invert direction
    void setCenter(float newCenter);
};


// constructor
MotorDriver::MotorDriver() {
  // Using normalize with 0.5 to 1.0 so it reverses.
  setNormal(normalMode::custom, normalClip::overflow, centerOffsetPoint, 1.0);
  // And then this output range will ultimately clip the output, so overflow above is safe to use
  setRange(ANALOG_OUTPUT_MIN, ANALOG_OUTPUT_MAX);
  // Reverse is false by default
  setReverse(false);
  // Center
  setCenter(0.0);
}

void MotorDriver::work() {

  updateInput();

  // Get speed from input
  //float outputSpeed = Toolkit::constrainf(getValue(), -POL_NORMALIZE_MAX, POL_NORMALIZE_MAX);

  
  // Handle -/+ value to change direction
  bool outputDir = (reverseDirection ? getValue() * -1 : getValue()) < 0.0 ? false : true;

  // map output for speed
  int outputSpeed;
  outputSpeed = Toolkit::mapf(Toolkit::absf(getValue()), POL_NORMALIZE_MIN, POL_NORMALIZE_MAX, outputRangeMin, outputRangeMax);
  outputSpeed = Toolkit::constrainf(outputSpeed, ANALOG_OUTPUT_MIN, ANALOG_OUTPUT_MAX);

  // write to outputs
  digitalWrite(outputDirPin, outputDir);
  analogWrite(outputSpeedPin, outputSpeed);

}


void MotorDriver::setPin(int newDirPin, int newSpeedPin) {
  outputDirPin = newDirPin;
  outputSpeedPin = newSpeedPin;
  pinMode(outputDirPin, OUTPUT); // digital
  pinMode(outputSpeedPin, OUTPUT); // analog
}

void MotorDriver::setRange(byte newMin, byte newMax) {
  outputRangeMin = newMin;
  outputRangeMax = newMax;
}

void MotorDriver::setReverse(bool newRev) {
  reverseDirection = newRev;
}

void MotorDriver::setCenter(float newCenter){
  centerOffsetPoint = newCenter;
}




//EOF
