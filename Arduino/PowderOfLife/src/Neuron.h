/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Neuron

  ===========================

  The Neuron class is a first-level super-class from which all second-level super-classes are derived.
  The Neuron class is not meant to be instantiated directly. 

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2026
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

  ==================================================================================================== */


/*
  TODO
  - review getPortData / setPortData
    - why are they here and not in the SerialNode?
 */

class Neuron {

  private:
    // ===================
    // Internal State
    float value; // Stores the processed output value of the Neuron.
    bool enabled = true; //  Flag indicating whether the Neuron is currently active and processing data.
    bool state; // Represents the binary state of the Neuron (e.g., on/off, true/false).
    byte stateChange; //  Indicates the type of state change: 0 is null, 1 is down, 2 is up.
    Timer frameTimer; // Manages the timing of the Neuron's update cycle.

    //byte currentCurveType;
    //float currentCurveExponent; // bring this back

    // ===================
    // Normalization
    float normalRangeMin; //  The minimum value of the normalization range.
    float normalRangeMax; //  The maximum value of the normalization range.
    byte normalizationMode; //  The selected normalization mode (see normalMode).
    byte normalizationClip; //  The chosen clipping method for handling values outside the normalization range (see normalClip).
    bool normalAbsolute; // Flag indicating whether normalization should use absolute values.

  protected:
    // ===================
    // Virtual methods 
    //    Subclasses override these methods to define their specific behavior and logic.
    virtual void setInput(); 
    virtual Neuron& getInput(); 
    virtual bool hasInput();
    //
    virtual Neuron& getSerialNode();
    // ===================
    virtual void wake();
    virtual void workFast();
    virtual void work();
    // ===================
    void setInternalValue(float newValue);

  public:
    // Constructor
    Neuron();
    // ===================
    // Core functionality
    void start(); // Initializes the Neuron. Typically called by Engine.
    void update(); // Updates the Neuron's state and processing. Typically called by Engine.
    void setEnabled(bool newEnabled); // Enables or disables the Neuron.
    bool getEnabled(); // Returns `true` if the Neuron is enabled, `false` otherwise.
    void setFrameTime(float newTime); // Sets the desired frame time (update rate) for the Neuron.
    float getFrameTime(); // Returns the current frame time of the Neuron.
    float getFrameDelta(); // Returns the time elapsed since the last frame.
    // ===================
    // Internal value
    //void setValue(float newValue);
    float getValue(); //  Returns the processed and normalized output value of the Neuron.
    bool getState(); //  Returns the current binary state of the Neuron (e.g., true/false, on/off).
    // ===================
    // These are pseudo-events, but they are easy to use. keep them even if you get actual events working
    bool getDown(); // on down, true only once
    bool getUp(); // on up, true only once

    // ===================
    // Enum lists for options
    enum normalMode : byte { none, custom }; // type of normalization to apply to the input
    enum normalClip : byte { clip, overflow, invert }; // to clip or not to clip the output,

    // ===================
    // Normalization
    void setNormal(
      normalMode newScale = normalMode::none,
      normalClip newClip = normalClip::overflow,
      float p1 = 0.0,
      float p2 = 0.0,
      bool newAbs = false
    );
    void setNormalClip(normalClip newClip = normalClip::clip);
    void setNormalRange(float newMin, float newMax);
    void setNormalMin(float newMin);
    void setNormalMax(float newMax);
    float getNormalMin(); // Returns the minimum value of the normalization range.
    float getNormalMax(); // Returns the maximum value of the normalization range.
    normalMode getNormalMode(); // Returns the current normalization mode.
    normalClip getNormalClip(); // Returns the current clipping method.

    // ===================
    // Curvinator
    //void setCurve(Curvinator::mode newCurve, float newExponent = 2 ); //currentCurveType

    // ===================
    // Serial Communication (why is this in here?)
    float getPortData(byte channelName); // Reads data from the specified channel from the SerialNode.
    void setPortData(byte channelName, float newValue); // Writes data to the specified channel on the SerialNode.
};

// Constructor
Neuron::Neuron() {
  setFrameTime(NEURON_FRAME_TIME); //  Sets the initial frame time to the default value
  setNormal(normalMode::none);
}

// ==================================================================
// Core functionality

// To be called by the main program
void Neuron::start() {
  // Calls startup on instance
  wake();
}

void Neuron::update() {
  // The main loop
  if ( enabled ) {
    // workFast is outside the frame timer
    workFast();
    // Render a frame?
    if (frameTimer.interval()) {
      // work() is inside the frame timer
      work();
    }
  } else {
    // Neuron is disabled
  }
}


// ============================================
// These virtual methods are to be overridden by subclasses

// Intended for initialization tasks specific to subclasses
void Neuron::wake() {
}

// Designed for high-frequency or time-critical operations
void Neuron::workFast() {
}

// Contains the core processing logic for the Neuron
void Neuron::work() {
}

// Kludge, needed for the SerialNode trio
// These methods handle data associated with specific channels on a SerialNode. 
float Neuron::getPortData(byte channelName) {
}
void Neuron::setPortData(byte channelName, float newValue) {
}

// Input neuron methods
void Neuron::setInput() {
}
Neuron& Neuron::getInput() {
}
bool Neuron::hasInput() {
}
Neuron& Neuron::getSerialNode() {
}

/*
  // one day...
  // To be overridden
  void Neuron::onDown() {
  }

  // To be overridden
  void Neuron::onUp() {
  }
*/

void Neuron::setEnabled(bool newEnabled) {
  enabled = newEnabled;
}

bool Neuron::getEnabled() {
  return enabled;
}


void Neuron::setFrameTime(float newTime) {
  frameTimer.setRate(newTime);
}

// Arduino can't work the float math for micros
float Neuron::getFrameTime() {
  return frameTimer.getRate();
}

float Neuron::getFrameDelta() {
  return frameTimer.getDelta();
}






// ==================================================================
// Value


void Neuron::setInternalValue(float newValue) {

  //if (valueIsValid) {
  // Scale: none, automatic, custom
  switch (normalizationMode) { // for C++ use case: static_cast<normalMode>(normalizationMode)

    case normalMode::custom:

      newValue = Toolkit::mapf(newValue, normalRangeMin, normalRangeMax, POL_NORMALIZE_MIN, POL_NORMALIZE_MAX);

      // Clip: clip, overflow
      switch (normalizationClip) {
        case normalClip::clip:
        case normalClip::invert:
          // clip output
          newValue = Toolkit::constrainf(newValue, POL_NORMALIZE_MIN, POL_NORMALIZE_MAX);
          // Invert (only okay if output is clipped since it uses 1-x)
          newValue = (normalizationClip == normalClip::invert) ? (1.0 - newValue) : newValue;
          break;
        case normalClip::overflow:
        default:
          break;
      }

    // no break;
    case normalMode::none:
    // no break;
    default:
      break;
  }


  // Absotule must be done at the end so it can handle negative mapping
  newValue = normalAbsolute ? abs(newValue) : newValue;

  // Handle curving (currentCurveType)
  //newValue = Curvinator::curve(newValue, currentCurveExponent, currentCurveType);

  // Finally (drumroll), set the internal value
  value = newValue;



  // Set the state
  bool newState = value > 0.5 ? true : false;
  if (newState != state) {
    state = newState;
    //stateChange = (state == false) ? 1 : 2;
    stateChange = state + 1;
  }

  //}// valid / invalid wrapper

  //}// Value has changed wrapper

}


float Neuron::getValue() {

  return value;

}




bool Neuron::getState() {
  return state;
}

bool Neuron::getDown() {
  if (stateChange == 2) {
    stateChange = 0;
    return true;
  } else {
    return false;
  }
}

bool Neuron::getUp() {
  if (stateChange == 1) {
    stateChange = 0;
    return true;
  } else {
    return false;
  }
}


// ==================================================================
// Normalize
// ---
// Mode: none, custom
// Clip: clip, overflow, invert
// The four parameters change depending on the mode
//	- automatic: p1 is decay, p2 is band
//	- custom: p1/p2 are min/max for range


//void Neuron::setNormal(normalMode newScale=normalMode::automatic, normalClip newClip=normalClip::overflow, float p1=0.0, float p2=0.0, bool newAbs=false, bool newInv=false) {
void Neuron::setNormal(
  normalMode newScale,
  normalClip newClip,
  float p1,
  float p2,
  // float p3,
  // float p4,
  bool newAbs
) {
  // Set the basic things
  normalizationMode = newScale;
  normalizationClip = newClip;
  normalAbsolute = newAbs;

  // How tu use p1&p2?
  switch (newScale) {
    case normalMode::custom:
      setNormalRange(p1, p2);
      break;
    case normalMode::none:
    default:
      break;
  }
}






void Neuron::setNormalRange(float newMin, float newMax) {
  setNormalMin(newMin);
  setNormalMax(newMax);
}

void Neuron::setNormalMin(float newMin) {
  normalRangeMin = newMin;
}

void Neuron::setNormalMax(float newMax) {
  normalRangeMax = newMax;
}


float Neuron::getNormalMin() {
  return normalRangeMin;
}


float Neuron::getNormalMax() {
  return normalRangeMax;
}

void Neuron::setNormalClip(normalClip newClip) {
  normalizationClip = newClip;
}

Neuron::normalMode Neuron::getNormalMode() {
  return (Neuron::normalMode)normalizationMode;
}
Neuron::normalClip Neuron::getNormalClip() {
  return (Neuron::normalClip)normalizationClip;
}


// ==================================================================
// Curvinator

//void Neuron::setCurve(Curvinator::mode newCurve, float newExponent = 2 ){
//  currentCurveType = newCurve;
//  currentCurveExponent = newExponent;
//}

// ==================================================================



// EOF
