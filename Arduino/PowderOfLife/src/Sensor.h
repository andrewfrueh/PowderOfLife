/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Sensor

  ===========================

  The Sensor class is a second-level super-class for all Sensor sub-classes (e.g. AnalogSensor).
  The Sensor class is not meant to be instantiated directly. 

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

  ==================================================================================================== */


// TODO
// - add control for digital / analog input pin
// - add setValue() wrapper for setInternalValue() like the Driver class


class Sensor : public Neuron {
  private:
    bool valueIsValid = true; // Flag to indicate if the sensor reading is considered valid.
    byte currentInvalidMode; // Stores the currently selected mode for handling invalid sensor readings.
    byte currentPinType; // Stores the type of pin the sensor is connected to (digital or analog).
    bool currentPinPullup; // Flag to indicate if the internal pull-up resistor should be enabled for the sensor pin.
  protected:
  public:
    Sensor();
    //
    enum invalidMode : byte { hold, min, mid, max }; // Modes for handling invalid readings
    enum pinType : byte { digital, analog }; // Which type of pin is connected
    //
    //void setValueIsValid(bool newValid);
    //bool getValueIsValid();
    byte getInvalid(); // Returns the selected mode for handling invalid sensor readings.
    void setInvalid(byte newInvalid); // Sets the mode for handling invalid sensor readings.
    float getInvalidValue(); // Returns the value to use when the sensor reading is invalid.
    void setPinType(pinType newType); // Sets the type of pin the sensor is connected to.
    byte getPinType(); // Returns the type of pin the sensor is connected to (digital or analog).
    void setPinPullup(bool newType); // Enables or disables the internal pull-up resistor for the sensor pin.
    bool getPinPullup(); // Returns whether the internal pull-up resistor is enabled
    void setPinInputMode(int pin); // Configures the input mode (INPUT or INPUT_PULLUP) for the specified pin based on the currentPinType.

    // this is the new stuff... we go dancing in
    bool digitalReadMod(int pin); // A modified version of digitalRead() that can read from both digital and analog pins.
};

// Constructor
Sensor::Sensor() {
  setInvalid(invalidMode::hold);
  //setPinType(pinType::digital);
}


/*
  void Sensor::setValueIsValid(bool newValid) {
  valueIsValid = newValid;
  }
  bool Sensor::getValueIsValid() {
  return valueIsValid;
  }
*/


void Sensor::setInvalid(byte newInvalid) {
  currentInvalidMode = newInvalid;
}

byte Sensor::getInvalid() {
  return currentInvalidMode;
}


float Sensor::getInvalidValue() {
  switch (getInvalid()) {
    case invalidMode::hold:
      // use value... it should not have changed due to invalid
      return getValue();
      break;
    case invalidMode::min:
      // use normal min
      return POL_NORMALIZE_MIN; // getNormalMin();
      break;
    case invalidMode::mid:
      // use normal mid
      return POL_NORMALIZE_MIN + ((POL_NORMALIZE_MAX - POL_NORMALIZE_MIN) / 2); // getNormalMid();
      break;
    case invalidMode::max:
      // use normal max
      return POL_NORMALIZE_MAX; // getNormalMax();
      break;
  }
}


void Sensor::setPinType(pinType newType) {
  currentPinType = newType;
}

byte Sensor::getPinType() {
  return currentPinType;
}

void Sensor::setPinPullup(bool newPullup) {
  currentPinPullup = newPullup;
}

bool Sensor::getPinPullup() {
  return currentPinPullup;
}

// Configures the input mode for the pin.
void Sensor::setPinInputMode(int pin) {
  switch (currentPinType) {
    case digital:
      pinMode(pin, getPinPullup() ? INPUT_PULLUP : INPUT);
      break;
    case analog:
      // do nothing
      break;
  }

}

// Really just a wrapper that acts like digitalRead() but can route to either analog or digital
bool Sensor::digitalReadMod(int pin) {
  switch (currentPinType) {
    case digital:
      return digitalRead(pin);
      break;
    case analog:
      return analogRead(pin) < ((ANALOG_INPUT_MAX - ANALOG_INPUT_MIN) / 2) ? false : true;
      break;
  }
}










// EOF
