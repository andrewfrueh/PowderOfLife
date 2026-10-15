/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Encoded Motor Node

  ===========================

  This is a complex node that combines multiple neurons into a neural cluster that makes up an encoded motor.

  It uses:
      EncoderSensor
      ButtonSensor
      ButtonSensor
      MotorDriver

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

  ==================================================================================================== */



/*
  TODO:
  x add analog input control
  - write wrapper method for "buttonA.getState()" that knows which endstop to return
    - connected to property of endstop polarity, used to switch
    - endstop polarity is set during wake (has implications for the next item)
  - add option for enstops at startup (regardless of setting for running operation) -- allows for "both" without startup (need to define steps)
*/


// Encoders
// high res 100pr:400,  600pr:2400

// Motors
// smaller one 60rpm = 4700, 300rpm = 980, 600 = 490?
// bigger one 1:36 = 1600, 1:72 = 3200?


/*
  #define ENCODEDMOTORNODE_WAKEUP_MOTORSPEED 0.75 // multiplied by the default speed below
  #define ENCODEDMOTORNODE_NORMAL_MOTORSPEED 0.5
  #define ENCODEDMOTORNODE_LOW_VALUE_GATE 0.02 // weird kludge, but good, BUT no, use below
  #define ENCODEDMOTORNODE_MIN_VALUE 0.3
  #define ENCODEDMOTORNODE_POSITION_EASING EasyEaseEasingTypes::out
  #define ENCODEDMOTORNODE_ENDSTOP_COLLISIONS 10
  #define ENCODEDMOTORNODE_ENDSTOP_COLLISION_TIMEOUT 0.2
*/


class EncodedMotorNode : public Node {  // should be Node but it's not updating, so I'm using Sensor for now
private:
  //
  int motorEncoderPin1;
  int motorEncoderPin2;
  int motorDriverPin1;
  int motorDriverPin2;
  int endstopPin1;
  int endstopPin2;
  float motorSpeed;
  float motorStartupSpeed;

  // Digital encoding
  int motorEncoderSteps;
  byte currentBehavior;
  enum behaviorMode : byte { undefined,
                             endstopA,
                             endstopB,
                             standard };
  void setBehavior(behaviorMode newBehavior);
  bool endstopsReversed;
  bool getEndstopState(bool index);  // index is which endstop, 0 or 1

  void workProcessDigital();
  void workProcessAnalog();

  void workProcessMotorTracking();

protected:

public:
  EncodedMotorNode();
  //
  void work();
  void workFast();
  void wake();
  void setPin(int mdPin1, int mdPin2, int mePin);  // motor-driver x2, motor-encoder
  void setPin(int mdPin1, int mdPin2, int mePin1, int mePin2, int esPin1 = -1, int esPin2 = -1, bool mePullup = true, bool esPullup = true);
  void setSteps(int newSteps);  // setSteps only works in "one" or "none" endstopMode, in "both" is it set internally
  int getSteps();
  void setLerp(float newSpeed, float newAcceleration);
  //
  void setEndstopMin();
  void setEndstopMax();
  byte getBehavior();
  //
  enum endstopMode : byte { none,
                            one,
                            both };
  endstopMode currentEndstopMode;
  void setEndstopMode(endstopMode newMode);
  byte getEndstopMode();
  //
  // Analog encoding
  //    currentEncodingMode:ananlog,digital
  enum encodingMode : byte { analog,
                             digital };
  encodingMode currentEncodingMode;
  void setEncodingMode(encodingMode newMode);
  byte getEncodingMode();
  //
  void setMotorStartSpeed(float newSpeed);  //motorStartupSpeed
  //
  void setAnalogWindow(int rangeMin, int rangeMax);

  // Kludge... kind of... two input nodes (analog/digital), but only one can be used so the other is wasted memory
  AnalogSensor encoderAnalog;    // analog input node
  EncoderSensor encoderDigital;  // digital input node
  // Motor
  MotorDriver motor;
  // Lerp
  LerpNode lerp;
  // Buttons if there are endstops
  ButtonSensor buttonA;
  ButtonSensor buttonB;
};

EncodedMotorNode::EncodedMotorNode() {
  // Set the default mode, encodingMode:analog,digital
  setEncodingMode(encodingMode::analog);
  setLerp(1.0, 3.0);

  // These are for "analog" mode
  setAnalogWindow(0,1023);

  // These are for "digital" mode
  setSteps(2000);
  setBehavior(behaviorMode::undefined);
  // default is no endstops
  setEndstopMode(endstopMode::none);
  setMotorStartSpeed(0.5);
}

void EncodedMotorNode::wake() {
}

void EncodedMotorNode::workFast() {
  encoderAnalog.update();
  encoderDigital.update();
  buttonA.update();
  buttonB.update();
}

void EncodedMotorNode::work() {

  switch (currentEncodingMode) {
    case encodingMode::analog:
      workProcessAnalog();
      break;
    case encodingMode::digital:
      workProcessDigital();
      break;
    default:
      break;
  }
}


void EncodedMotorNode::workProcessAnalog() {
  workProcessMotorTracking();
}

void EncodedMotorNode::workProcessDigital() {
  // set endstopsReversed on wake
  switch (currentBehavior) {  // undefined, endstopA, endstopB, standard
    case behaviorMode::undefined:
      // starting up

      // Set motor speed
      motor.setValue(0);

      switch (currentEndstopMode) {
        case endstopMode::both:
        case endstopMode::one:
          // Go next mode
          setBehavior(behaviorMode::endstopA);
          break;
        case endstopMode::none:
          // Go to end
          setBehavior(behaviorMode::standard);
          break;
      }
      break;
    case behaviorMode::endstopA:
      // The first endstop encoutered

      if (
        buttonA.getState() == true && buttonB.getState() == true) {
        // This is bad. Both endstops are triggered. Do nothing?
        break;
      }

      // The assumption is that A is the first endstop. If we hit B first, then set endstopsReversed to true.
      if (buttonA.getState() == true) {
        endstopsReversed = false;
      } else if (buttonB.getState() == true) {
        endstopsReversed = true;
      }

      // Check the A endstop
      if (getEndstopState(0) == true) {

        switch (currentEndstopMode) {
          case endstopMode::both:
            setEndstopMin();
            // go next mode
            setBehavior(behaviorMode::endstopB);
            break;
          case endstopMode::one:
            setEndstopMin();
            encoderDigital.setNormalMax(encoderDigital.getNormalMin() + motorEncoderSteps);
            // Go to end
            setBehavior(behaviorMode::standard);
            break;
        }

      } else {
        // Set motor speed to reverse to first endstop
        motor.setValue(-motorStartupSpeed);
      }

      break;
    case behaviorMode::endstopB:
      // second endstop

      // Check for buttonB
      if (getEndstopState(1) == true) {
        setEndstopMax();
        // Record the number of steps found between endstops
        setSteps(encoderDigital.getNormalMax() - encoderDigital.getNormalMin());
        // go next mode
        setBehavior(behaviorMode::standard);
      } else {
        // Set motor speed to forward to second endstop
        motor.setValue(motorStartupSpeed);
      }

      break;
    case behaviorMode::standard:
      // Running in normal operation

      // Check for buttonA
      if (getEndstopState(0) == true) {
        switch (currentEndstopMode) {
          case endstopMode::one:
          case endstopMode::both:
            // Reset the min
            setEndstopMin();
            // Set the max to min + range
            encoderDigital.setNormalMax(encoderDigital.getNormalMin() + motorEncoderSteps);
            break;
        }
      }  // end buttonA

      // Check for buttonB
      if (getEndstopState(1) == true && currentEndstopMode == endstopMode::both) {
        // Reset the max
        setEndstopMax();
        // Set the min to max - range
        encoderDigital.setNormalMin(encoderDigital.getNormalMax() - motorEncoderSteps);
      }  // end buttonB

      workProcessMotorTracking();

      // // Get the input
      // if (hasInput()) {
      //   lerp.lerp.setTarget(getInput().getValue());
      // }
      // // Set the lerp
      // lerp.lerp.setValue(encoderDigital.getValue());
      // // Set the motor using the lerp
      // motor.setValue(lerp.lerp.getVelocity());

      break;
    default:
      break;
  }
}

#define MOTOR_EXPO 3
#define MOTOR_OFFSET 0.1
#define MOTOR_ENCODER_CURVE_EXPO 1.5f
#define MOTOR_ENCODER_CURVE_CENTER 0.8f

void EncodedMotorNode::workProcessMotorTracking() {
  // Get the input
  if (hasInput()) {
    lerp.lerp.setTarget(getInput().getValue());
  }
  // Set the lerp, and curve the input
  // lerp.lerp.setValue(currentEncodingMode == encodingMode::analog ? encoderAnalog.getValue() : encoderDigital.getValue());

  // lerp.lerp.setValue(currentEncodingMode == encodingMode::analog ? (Curvinator::curve(encoderAnalog.getValue(), MOTOR_ENCODER_CURVE_EXPO, Curvinator::mode::outIn, false, false, MOTOR_ENCODER_CURVE_CENTER)) : encoderDigital.getValue());
  lerp.lerp.setValue(currentEncodingMode == encodingMode::analog ? encoderAnalog.getValue() : encoderDigital.getValue());
  lerp.update();

  // Set the motor using the lerp

  // constrain so you don't crash Curvinator
  motorSpeed = Toolkit::constrainf(lerp.lerp.getVelocity(), -1, 1);
  // Curve abs value of input, again, not to crach urvinator
  motorSpeed = Curvinator::curve(Toolkit::absf(motorSpeed), MOTOR_EXPO, Curvinator::mode::inOut, false, false, MOTOR_OFFSET);
  // re-apply the sign
  motorSpeed *= Toolkit::getSign(lerp.lerp.getVelocity());
  // set the speed
  motor.setValue(motorSpeed);

  // motor.setValue(lerp.lerp.getVelocity());
  // Update()
  motor.update();
}

void EncodedMotorNode::setPin(int mdPin1, int mdPin2, int mePin) {
  motorDriverPin1 = mdPin1;
  motorDriverPin2 = mdPin2;
  motor.setPin(motorDriverPin1, motorDriverPin2);
  encoderAnalog.setPin(mePin);
}

// motor driver, motor enconder, endstops
void EncodedMotorNode::setPin(int mdPin1, int mdPin2, int mePin1, int mePin2, int esPin1, int esPin2, bool mePullup, bool esPullup) {
  // values
  motorDriverPin1 = mdPin1;
  motorDriverPin2 = mdPin2;
  motorEncoderPin1 = mePin1;
  motorEncoderPin2 = mePin2;
  endstopPin1 = esPin1;
  endstopPin2 = esPin2;
  // pullups
  encoderDigital.setPinPullup(mePullup);
  buttonA.setPinPullup(esPullup);
  buttonB.setPinPullup(esPullup);
  // pins
  encoderDigital.setPin(motorEncoderPin1, motorEncoderPin2);
  motor.setPin(motorDriverPin1, motorDriverPin2);
  if (endstopPin1 != -1) {
    buttonA.setPin(endstopPin1);
  }
  if (endstopPin2 != -1) {
    buttonB.setPin(endstopPin2);
  }
}

void EncodedMotorNode::setSteps(int newSteps) {
  motorEncoderSteps = newSteps;
  //
  encoderDigital.setNormal(Neuron::normalMode::custom, Neuron::normalClip::clip, 0, motorEncoderSteps);  // This IS "slide"... doing it here
}

int EncodedMotorNode::getSteps() {
  return motorEncoderSteps;
}

void EncodedMotorNode::setLerp(float newSpeed, float newAcceleration) {
  lerp.setLerp(newSpeed, newAcceleration);
}

//

void EncodedMotorNode::setBehavior(behaviorMode newBehavior) {
  currentBehavior = newBehavior;
}

byte EncodedMotorNode::getBehavior() {
  return currentBehavior;
}

bool EncodedMotorNode::getEndstopState(bool index) {
  switch (index) {
    case 0:
      return endstopsReversed ? buttonB.getState() : buttonA.getState();
      break;
    case 1:
      return endstopsReversed ? buttonA.getState() : buttonB.getState();
      break;
  }
}


void EncodedMotorNode::setEndstopMin() {
  encoderDigital.setNormalMin(encoderDigital.getCurrentStep());
}

void EncodedMotorNode::setEndstopMax() {
  encoderDigital.setNormalMax(encoderDigital.getCurrentStep());
}

void EncodedMotorNode::setEndstopMode(endstopMode newMode) {
  currentEndstopMode = newMode;
}

byte EncodedMotorNode::getEndstopMode() {
  return currentEndstopMode;
}


void EncodedMotorNode::setEncodingMode(encodingMode newMode) {
  currentEncodingMode = newMode;
}

byte EncodedMotorNode::getEncodingMode() {
  return currentEncodingMode;
}


void EncodedMotorNode::setMotorStartSpeed(float newSpeed) {
  motorStartupSpeed = newSpeed;
}

void EncodedMotorNode::setAnalogWindow(int rangeMin, int rangeMax) {
  encoderAnalog.setNormal(Neuron::normalMode::custom, Neuron::normalClip::clip, rangeMin, rangeMax);
}


// EOF
