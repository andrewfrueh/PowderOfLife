/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Button Sensor
  
  ===========================

  The ButtonSensor class aims to simplify the process of reading input from buttons connected to an Arduino board. It handles the complexities of debouncing and provides a standardized output, making it easy to use button presses as triggers or inputs for other components in the Powder Of Life system.  


  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

#define BUTTONSENSOR_LERP_SPEED 0.4
#define BUTTONSENSOR_LERP_ACCEL 0.4
#define BUTTONSENSOR_DEBOUNCE_DEPTH 3

class ButtonSensor : public Sensor {
  private:
    bool rawInput;
    byte digitalInputPin;
    bool toggleEnabled;
    bool buttonState;
    // work I really need two variables to work this?
    bool upStateBuffer;
    bool downStateBuffer;
    bool shortToGround = true;
    // This stuff is not used... yet
    //bool debounces[BUTTONSENSOR_DEBOUNCE_DEPTH];
    //bool Debounce(bool newState);
  public:
    ButtonSensor();
    //
    void workFast();
    void work();
    void setPin(int newPin, bool newPullup=true);
    void setToggle(bool newToggle);
};


// constructor
ButtonSensor::ButtonSensor() {
  setNormal(normalMode::custom, normalClip::clip, 0, 1); 
  //setPinType(pinType::digital); // TODO
}


void ButtonSensor::workFast() {
  //rawInput = digitalRead(digitalInputPin);
  rawInput = digitalReadMod(digitalInputPin);
  rawInput = shortToGround ? !rawInput : rawInput;
  //rawInput = Debounce(rawInput);
}


void ButtonSensor::work() {
  // rawInput should be 0 or 1 only

  // State change (f the raw state, and button state are different)
  if (buttonState != rawInput) {
    // override the button state with the raw state
    buttonState = shortToGround?rawInput:!rawInput;
    // Toggle?
    if (toggleEnabled) {
      // On down
      if (buttonState) {
        if(getState()){
          setInternalValue(0);
        }else{
          setInternalValue(1);
        }
      }
    } else {
      // button is momentary
      setInternalValue((int)buttonState);
    } 

  } // END state change check

}

/*
// Debounce is not implimented yet... it didn't seem necessary
bool ButtonSensor::Debounce(bool newState){
  byte sum;
  for(byte i=0; i<BUTTONSENSOR_DEBOUNCE_DEPTH; i++){
    sum += debounces[i];
  }
  return sum/BUTTONSENSOR_DEBOUNCE_DEPTH;
}
*/


// For buttons, pullups should be the default because students can work without extra circuitry.
void ButtonSensor::setPin(int newPin, bool newPullup) {
  digitalInputPin = newPin;
  setPinPullup(newPullup);
  setPinInputMode(digitalInputPin);
}

void ButtonSensor::setToggle(bool newToggle) {
  toggleEnabled = newToggle;
}





// =====================================
