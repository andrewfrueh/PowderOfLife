/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Tone Driver
  
  ===========================

  TODO
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */



// TODO
// - check the freq timer in workFast()

#define TONE_DRIVER_DEFAULT_FREQUENCY 0.002273f

class ToneDriver : public Driver {
  private:
    int outputPin; // digital
    bool outputState;
    //unsigned long toneTimerRate;
    float currentTone;
    float lastTone;
    Timer waveFormTimer;
    //int minFrequency = 110;
    //int maxFrequency = 880;
    int baseFrequency = 440;
    byte scale = ScaleMapper::scales::pentatonicMajor;
    byte mapping = ScaleMapper::mappings::pitch;
    byte octaveMultiplier = 1;
    bool toneActive = true;
    byte mode;
    bool doHardwareTone;
    float softToneTuning = 1.01676; // 1.016 is flat, 1.017 is sharp, 1.01676?
    //
  protected:
    //
  public:
    ToneDriver();
    //
    enum modes : byte { hardware, software };
    void work();
    void workFast();
    void setPin(int newPin);
    void softToneOn(float newTone);
    void softToneOff();
    void setTonic(float newTonic);
    void setScale(byte newScale);
    void setMode(byte newMode);
    modes getMode();
    float getTone();
    float getRate();
    void start();
    void stop();
    void stopAllTones();
    void octaves(byte newOctaves);
};


// constructor
ToneDriver::ToneDriver() {
}

void ToneDriver::workFast() {
  // If we work the ditital waveform manually (NOT using the built in tone())

  if (waveFormTimer.interval() && doHardwareTone) {
    outputState = !outputState;
    digitalWrite(outputPin, outputState);
  }

}

void ToneDriver::work() {

  updateInput();

  //float v = getInput().getValue();

  // use ScaleMapper
  currentTone = ScaleMapper::map( getValue() * octaveMultiplier, baseFrequency * (mode == ToneDriver::modes::hardware ? 1.0f : softToneTuning), 0, scale, mapping );

  if (toneActive) {
    if (mode == ToneDriver::modes::hardware) {
      tone(outputPin, currentTone);
    } else {
      softToneOn(currentTone);
    }
  } else {
    if (mode == ToneDriver::modes::hardware) {
      noTone(outputPin);
    } else {
      softToneOff();
    }
  }


}


void ToneDriver::setPin(int newPin) {
  outputPin = newPin;
  pinMode(outputPin, OUTPUT); // digital
}

void ToneDriver::softToneOn(float newTone) {
  currentTone = newTone;
  // 1/x, but use (1/2)/x so you get a proper square wave frequency with 1 sec = 1,000,000 micros, hence 500000
  unsigned long t = ( (500000) / (currentTone) ); 
  //waveFormTimer.setRate(t);
  waveFormTimer.setRateMicros(t);
  doHardwareTone = true;
}

void ToneDriver::softToneOff() {
  doHardwareTone = false;
}


void ToneDriver::setTonic(float newTonic) {
  baseFrequency = newTonic;
}

void ToneDriver::setScale(byte newScale = ScaleMapper::scales::pentatonicMajor) {
  scale = newScale;
}

void ToneDriver::setMode(byte newMode) {
  mode = newMode;
}

// AI refactor notes... the chatbot recommended that I do casting here in the method. In previous sessions, it had me change the type above (from enum to byte)
// When I asked it about it today, it said that I should retain my enum typing since it represents the interface better. But then we have to do the casting here.
// Kludge... this is not consistent across the code base. At some point, I'll need to standardize this.
ToneDriver::modes ToneDriver::getMode(){
  return static_cast<ToneDriver::modes>(mode);
  //return mode; 
}

float ToneDriver::getTone() {
  return currentTone;
}
float ToneDriver::getRate() {
  return waveFormTimer.getRate();
}

void ToneDriver::start() {
  toneActive = true;
}
void ToneDriver::stop() {
  toneActive = false;
}

void ToneDriver::stopAllTones(){
  toneActive = false;
  noTone(outputPin);
  softToneOff();
}

void ToneDriver::octaves(byte newOctaves) {
  octaveMultiplier = newOctaves;
}
