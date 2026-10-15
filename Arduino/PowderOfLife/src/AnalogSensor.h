/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Analog Sensor

  ===========================

  This is a basic sensor that simply gives you the standard Arduino analog input. Normalization is set by default to the 10-bit depth of the standard Arduino board (0-1023).

  Use setPin() to set the analog pin it will read from. Be aware that only certain pins offer analog input. These are labeled as A# (e.g. A0 through A5).

  Use setCenter() to define a custom center point for the input range.

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2026
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

  ==================================================================================================== */


// TODO 
// - add curvination





class AnalogSensor : public Sensor {
  private:
    float rawInput; // Stores the raw input value read from the analog pin (0-1023). 
    int analogInputPin; // Stores the analog pin number assigned to the sensor.
  protected:
    // These methods can be overridden from the Sensor class
    void wake();
    void workFast();
  public:
    AnalogSensor();
    //
    void work();
    void setPin(int newPin);
    void setCenter(int newCenter);
    void setCenter(float newCenter);
    // void setCurve(Curvinator::mode newMode, float newExpo);
};

//

// Constructor
AnalogSensor::AnalogSensor() {
  // Initialize the center point to 0. This also sets normalization.
  setCenter(0);
  // Define the pin type as 'analog'.
  setPinType(Sensor::pinType::analog);
  // setCurve(Curvinator::mode::none, 1.0);
}

void AnalogSensor::wake() {
  // Currently unused but can be overridden for custom initialization during the engine's 'wake' phase.
}

void AnalogSensor::workFast() {
  // Read the raw value from the assigned analog pin
  rawInput = analogRead(analogInputPin);
}


void AnalogSensor::work() {
  // Set the sensor's internal value
  setInternalValue(rawInput);
}

// Assign an analog pin to the sensor for reading input.
void AnalogSensor::setPin(int newPin) {
  // Store the pin number.
  analogInputPin = newPin;
  // Configure the pin for input.
  setPinInputMode(analogInputPin);
}

  // Set the center point for normalization using an integer value.
void AnalogSensor::setCenter(int newCenter) {
  // Configure normalization to use the defined center point, using absolute values for symmetrical output.
  setNormal(normalMode::custom, normalClip::clip, newCenter, 1023, true); 
}


  // Set the center point for normalization using a float value (0.0-1.0).
void AnalogSensor::setCenter(float newCenter) {
  // Set the center point for normalization using a float value, cast to int.
  setCenter((int)(newCenter * 1023)); 
}


// void AnalogSensor::setCurve(Curvinator::mode newMode, float newExpo){
//   curveType = newMode;
//   curveExpo = newExpo;
// }


