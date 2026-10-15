/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Analog Driver

  ===========================

  The AnalogDriver class in the Powder Of Life Arduino library is a type of Driver that simplifies controlling external components that respond to analog signals, such as LEDs, using Pulse Width Modulation (PWM). 

  Use setPin() to assign the output pin that tha AnalogDriver will control. Be aware that only certain pins offer PWM on most Arduino boards (typically 3, 5, 6, 9, 10, and 11).

  The output bit-depth is dependent on the board and is generally 8-bit (0-255).

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

  ==================================================================================================== */


class AnalogDriver : public Driver {
  private:
    int outputPin;
  protected:
    void wake();
  public:
    AnalogDriver();
    void work();
    void setPin(int newPin);
    //void setInternalValue(float newValue);
};


// constructor
AnalogDriver::AnalogDriver() {
  // Normalization is set to "custom" by default, allowing you to define the input range.
  //setNormal(normalMode::custom);
  // The output is clipped to the defined range to prevent overflow.
  setNormalClip(normalClip::clip);
}

void AnalogDriver::wake() {
  // The 'wake' function is currently unused but can be overridden for custom initialization.
}


void AnalogDriver::work() {
  // Read the input value from the connected neuron.
  updateInput();
  // Map the input value (0.0-1.0) to the output range (ANALOG_OUTPUT_MIN - ANALOG_OUTPUT_MAX).
  float output = Toolkit::mapf( getValue(), 0, 1, ANALOG_OUTPUT_MIN, ANALOG_OUTPUT_MAX);
  // Constrain the output to prevent exceeding the bit-depth of the analog output.
  output = Toolkit::constrainf(output, ANALOG_OUTPUT_MIN, ANALOG_OUTPUT_MAX );
  // Send the calculated value to the specified output pin. 
  analogWrite( outputPin, output );
}

void AnalogDriver::setPin(int newPin) {
  // Store the pin number for use in the 'work' function.
  outputPin = newPin;
  // Set the specified pin as an OUTPUT.
  pinMode(outputPin, OUTPUT);
}


// EOF
