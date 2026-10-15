/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Encoder Sensor
  
  ===========================

  A specific kind of digital input sensor (perhaps it could extend that type?).
  Typically used with a twin infrared reflectance sensor and a binary encoder pattern (strip or wheel).
    Note, this could also be any digital input (i.e. a switch) that moves across a regular pattern.
  Uses simple quadrature encoding to determine direction of travel and displacement.

  * Note: The default for "pullup" on the pins is true (assuming a non-powered board). 
    Be sure to check whether you need pullups or not.

  Steps per revolution:
   - 80 for the cheap ones, wired directly
   - 96(?) for the laser-cut ones I have
   - For the one's I purchased, multiply by ?TODO?
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */





class EncoderSensor : public Sensor {
private:
  // Input pins for the encoder
  int digitalInputPin1;
  int digitalInputPin2;
  // Current state of each input pin
  bool inputState1;
  bool inputState2;
   // Current and previous quadrature states
  int currentQuadratureState;
  int lastQuadratureState;
  // Current step count (total displacement)
  long currentStepCount;
  // Variables for tracking rate of change (steps per time unit)
  //  Note: this could be implemented at the Neuron level (value change)
  long lastStepCount;
  Timer rateOfChangeTimer;
  // Total number of steps per output unit (e.g., steps per revolution)
  int totalStepRange;
  // Current operating mode (range or rate)
  byte encoderMode;
  // Flag to reverse the direction of the encoder
  bool reverseDirection = false;
  // Determine the quadrature state based on input pin states
  char CheckPattern(bool x, bool y);
  // Update the step count based on the quadrature state transitions
  void QuadratureToStep();
protected:
  void wake();
  void work();
  void workFast();
  //float frameTime = 0.001;
public:
  EncoderSensor();
  //
  // Operating modes: 
  // - range: track total displacement (step count)
  // - rate: track rate of change (steps per time unit) [5]
  enum modes : byte { range,
                      rate };
  // Quadrature states: a, b, c, d (representing different combinations of input pin states)
  enum quadratureStates : byte { a,
                                 b,
                                 c,
                                 d };
  // Quadrature patterns for each state (used for determining the current state)
  bool quadraturePatterns[4][2] = {
    { 0, 0 },
    { 1, 0 },
    { 1, 1 },
    { 0, 1 },
  };
  
  void setPin(int newPin1, int newPin2, bool newPullup = true); // Set the input pins and pullup configuration
  void setMode(byte newMode); // Set the operating mode (range or rate)
  void setReverse(bool newState); // Reverse the direction of the encoder
  void setSteps(int newSteps); // Set the number of steps per output unit
  int getSteps(); // Get the number of steps per output unit 
  long getCurrentStep(); // Get the current step count
  void setRate(float newRate); // Set the rate of change timer (for rate mode)
};


// constructor
EncoderSensor::EncoderSensor() {
  // Set the default mode
  // setMode(modes::range);
  setMode(ENCODERSENSOR_DEFAULT_MODE);
  // Set the default rate of change 
  setRate(ENCODERSENSOR_RATEOFCHANGE);
  // Set default normalization
  setNormal(Neuron::normalMode::custom, Neuron::normalClip::overflow, 0, ENCODERSENSOR_STEPS_PER_REVOLUTION);
}

void EncoderSensor::wake() {
}


void EncoderSensor::workFast() {

  // Read the digital inputs
  inputState1 = digitalReadMod(digitalInputPin1);
  inputState2 = digitalReadMod(digitalInputPin2);

  // Convert the current input state to a quatrature state
  QuadratureToStep();

  switch (encoderMode) {
    case modes::range:
      // "range" mode
      break;
    case modes::rate:
      // "rate" mode
      break;
    default:
      break;
  }
}


void EncoderSensor::work() {
  //Serial.println(inputState1);

  // Switch on the mode
  switch (encoderMode) {
    case modes::range:
      // "range" mode
      //Serial.println(currentStepCount);
      setInternalValue(currentStepCount);
      break;
    case modes::rate:
      // "rate" mode
      // TODO

      if (rateOfChangeTimer.interval()) {
        setInternalValue(currentStepCount - lastStepCount);
        lastStepCount = currentStepCount;
      }

      //currentStepCount = 0;
      break;
    default:
      break;
  }
}

void EncoderSensor::QuadratureToStep() {

  // check the pattern to figure out what state we are in
  currentQuadratureState = CheckPattern(inputState1, inputState2);

  // Use the state to decide where we are in the pattern
  if (currentQuadratureState == -1) {
    // ERROR, pattern was not matched! work nothing.
  } else if (lastQuadratureState != currentQuadratureState) {
    // Check last state against current state to determine movement. (wish it were a switch statement)

    if (currentQuadratureState == 0 && lastQuadratureState == 3) {
      // roll over, going up
      currentStepCount += reverseDirection ? -1 : 1;
    } else if (currentQuadratureState == 3 && lastQuadratureState == 0) {
      // roll over, going down
      currentStepCount -= reverseDirection ? -1 : 1;
    } else {
      // default is to check that we have only moved 1 (+/-)
      int d = (currentQuadratureState - lastQuadratureState);
      currentStepCount += abs(d) == 1 ? (reverseDirection ? -d : d) : 0;  // if distance is only 1 then use it, else use 0
    }

    // finally, update the prevoius state
    lastQuadratureState = currentQuadratureState;
  }
}

char EncoderSensor::CheckPattern(bool x, bool y) {

  for (int i = 0; i < 4; i++) {
    if (x == quadraturePatterns[i][0] && y == quadraturePatterns[i][1]) {
      return i;
    }
  }

  // This means there was no pattern matched. This should not happen. Check for this.
  return -1;
}


// For encoders pullups should be true becuase all professional encoders are four wire. But be sure to explain this in all examples.
void EncoderSensor::setPin(int newPin1, int newPin2, bool newPullup) {
  digitalInputPin1 = newPin1;
  digitalInputPin2 = newPin2;

  // Only set pinMode if pin type is ditital
  setPinPullup(newPullup);
  setPinInputMode(digitalInputPin1);
  setPinInputMode(digitalInputPin2);
}

void EncoderSensor::setMode(byte newMode) {
  encoderMode = newMode;
}

void EncoderSensor::setReverse(bool newState) {
  reverseDirection = newState;
}


// don't override normalization
void EncoderSensor::setSteps(int newSteps) {
  totalStepRange = newSteps;
  setNormal(getNormalMode(), getNormalClip(), totalStepRange);
}

int EncoderSensor::getSteps() {
  return totalStepRange;
}

long EncoderSensor::getCurrentStep() {
  return currentStepCount;
}

void EncoderSensor::setRate(float newRate=0.2) {
  rateOfChangeTimer.setRate(newRate);
}



// end
