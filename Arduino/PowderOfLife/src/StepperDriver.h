/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Stepper Driver
  
  ===========================

  Controls a basic stepper motor driver board (two pins: digital direction, digital step).
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2026
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */



// What is this? delete!
//#define STEPPER_DRIVER_MAPPING_BREAK 0.01

class StepperDriver : public Driver {
  private:
    // TODO
    int outputDirPin; // digital
    int outputStepPin; // analog
    byte motorMicrostepLevel;// must be 1, 2, 4, 8, 16
    const int motorPhysicalStepsPerRotation = 200;
    int motorStepsPerRotation;
    const int minimumPulseDelay = 5; // in MICROSECONDS
    Timer stepTimer;
    float stepTimeMin = 0.00002; // full:0.003f; quarter:0.0005?; sixteenth:0.00002
    float stepTimeMax = 0.01;
    float stepTimes[5] = { 0.003f, 0.003f, 0.0005f, 0.0005f, 0.00001f }; // TODO, 'full' and 'sixteenth' are good, but need to test for other modes

    //int maxStepsPerFrame;
    //int stepsPerFrame;
    //int stepsThisFrame;
    long stepCurrentPosition = 0;
    long stepTargetPosition = 0;
    byte stepMode;
  public:
    StepperDriver();
    //
    //enum StepperDriverMode : byte { servo, speed }; // TODO, should be "range" and "rate" to match the encoder
    //enum StepperDriverMicrostepLevel : byte { full = 1, half = 2, quarter = 4, eighth = 8, sixteenth = 16 };
    enum modes : byte { range, rate};
    enum microsteps : byte { full = 1, half = 2, quarter = 4, eighth = 8, sixteenth = 16 };
    //
    void work();
    void workFast();
    void setMicrostep(microsteps newStep);
    void setMode(modes newMode);
    void stepOnce(int dir = 1);
    void setPin(int newDirPin, int newStepPin);
};


// constructor
StepperDriver::StepperDriver() {
  // set the microstep resolution level
  //motorMicrostepLevel = StepperDriverMicrostepLevel::sixteenth;
  setMicrostep(microsteps::sixteenth);
  setMode(modes::range);
  //
  //maxStepsPerFrame = stepTimeMin / ((minimumPulseDelay * 2) / 1000); // (frameTime in millis) / ((minimumPulseDelay * 2)/1000)
  //maxStepsPerFrame = 1;
  //stepsPerFrame = maxStepsPerFrame;
  //stepsThisFrame = 0;

  setNormal(Neuron::normalMode::none);
}


void StepperDriver::workFast() {

  // step timer
  if (stepTimer.interval()) {

    /*
      // reset the step count
      stepsThisFrame = 0;
      }

      if (stepsThisFrame < stepsPerFrame) {
      // can still step this frame
    */
    switch (stepMode) {
      case modes::range:

        // need to step?
        if (stepCurrentPosition != stepTargetPosition) { //  && stepsThisFrame < stepsPerFrame ) {
          // calc diff
          long diff = stepTargetPosition - stepCurrentPosition;
          // set direction
          //digitalWrite(outputDirPin, getSign(diff) == 1 ? HIGH : LOW );
          // step
          stepOnce(Toolkit::getSign(diff));
      //Serial.println(stepCurrentPosition);

        }
        break;
      case modes::rate:

        stepOnce();
        break;
      default:
        break;
    }
  }

}

void StepperDriver::work() {
  // get input
  //setInternalValue(getInput().getValue());
  updateInput();
  // switch on type
  switch (stepMode) {
    case modes::range:
      // calculate target position
      stepTargetPosition = Toolkit::mapf( getValue(), POL_NORMALIZE_MIN, POL_NORMALIZE_MAX, 0, motorStepsPerRotation);
      // kludge, but needed or else it is on slow speed sometimes (why?)
      //stepTimer.setRate(stepTimeMin);
      break;
    case modes::rate:
      // calculate speed

      // steps per frame
      //stepsPerFrame = mapf( getValue(), 0, 1, 1, maxStepsPerFrame );
      //stepTimer.setRate(stepTimeMin);

      // Dont use a local variable here, the compiler doesn't like it
      //float s = Toolkit::mapf( getValue(), POL_NORMALIZE_MIN, POL_NORMALIZE_MAX, stepTimeMax, stepTimeMin); //
      //Serial.println(getValue());
      //Toolkit::printFloat(s,10);
      //Serial.println();

      // frame time
      stepTimer.setRate( Toolkit::mapf( getValue(), POL_NORMALIZE_MIN, POL_NORMALIZE_MAX, stepTimeMax, stepTimeMin) );

      /* This doesn't work yet
        if( getValue() < STEPPER_DRIVER_MAPPING_BREAK ){
        // under the frame rate
        stepTimer.setRate(stepTimeMin);
        stepsPerFrame = mapf( getValue(), 0, STEPPER_DRIVER_MAPPING_BREAK, 1, maxStepsPerFrame );
        }else{
        // within the frame rate
        stepTimer.setRate( mapf( getValue(), STEPPER_DRIVER_MAPPING_BREAK, 1, stepTimeMax, stepTimeMin) );
        stepsPerFrame = maxStepsPerFrame;
        }
      */

      break;
    default: 
      break;
  }
}

// can be: full, half, quarter, eighth, sixteenth
void StepperDriver::setMicrostep(microsteps newStep) {

  // use specific time per mode (I wish this could be math, not a float array)
  switch(newStep){
    case microsteps::full:
      stepTimer.setRate(stepTimes[0]);
      break;
    case microsteps::half:
      stepTimer.setRate(stepTimes[1]);
      break;
    case microsteps::quarter:
      stepTimer.setRate(stepTimes[2]);
      break;
    case microsteps::eighth:
      stepTimer.setRate(stepTimes[3]);
      break;
    case microsteps::sixteenth:
      stepTimer.setRate(stepTimes[4]);
      break;
  }
  
  if (
    newStep == microsteps::full ||
    newStep == microsteps::half ||
    newStep == microsteps::quarter ||
    newStep == microsteps::eighth ||
    newStep == microsteps::sixteenth ) {
    //
    motorMicrostepLevel = newStep;
    //
    motorStepsPerRotation = (int)motorMicrostepLevel * motorPhysicalStepsPerRotation;
  }
}


void StepperDriver::setMode(modes newMode) {
  if (stepMode != newMode) {
    stepMode = newMode;
    stepCurrentPosition = stepTargetPosition;
    //stepsThisFrame = 0;
  }
}


void StepperDriver::stepOnce(int dir) {
  // TODO - check direction for +/-
  // increment step count
  //stepsThisFrame++;
  // change position
  stepCurrentPosition += dir;

  // set direction
  digitalWrite(outputDirPin, dir == 1 ? HIGH : LOW);


  digitalWrite(outputStepPin, HIGH);
  delayMicroseconds(minimumPulseDelay);
  digitalWrite(outputStepPin, LOW);
  //delayMicroseconds(minimumPulseDelay);
}


void StepperDriver::setPin(int newDirPin, int newStepPin) {
  outputDirPin = newDirPin;
  outputStepPin = newStepPin;
  pinMode(outputDirPin, OUTPUT);
  pinMode(outputStepPin, OUTPUT);
}
