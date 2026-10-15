/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Beat Generator

  ===========================

  The BeatGenerator acts as a digital metronome, generating a rhythmic on-off signal that can drive other components in the system. This is useful for applications that require timed events or synchronized behaviors.


  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

  ==================================================================================================== */


/* TODO
  - add a proterty/method for setting subdivisions
  - Add a method to retrieve the current beat in the subdivision
*/


class BeatGenerator : public Generator {
  private:
    Timer pulse;
    float tempo;
    float decayTime; // the duty-cycle
    float decayRatio; // the duty-cycle
    byte currentDecayMode;
    //bool onDownTrigger;// kludge supreme... needs to be an event!!!
    void updateDecayTime();
    bool useRamp;
    byte beatSubdivisions;
    byte currentBeat;
    bool beatState;
    void updateBeat();
    float getRampRatio();
    bool clickUp;
  public:
    BeatGenerator();
    //
    enum decayMode : byte  { ratio, time };
    //
    void work();
    void setTempo(float newTempo);
    float getTempo();
    void setDecay(float newDecay, decayMode newMode = decayMode::ratio);
    float getDecay();
    void setRamp(bool newRamp);
    void setSubdivisions(byte newSubDiv);
    byte getSubdivisions();
    void clickBeat();
    byte getBeat();
    bool getState();
    float getRatio();
    bool getClick();
};


BeatGenerator::BeatGenerator() {
  //
  setDecay(0.5, decayMode::ratio);
  setTempo(60);
  setSubdivisions(0);
}



void BeatGenerator::work() {

  // To update the pulse
  pulse.interval();

  if (useRamp) {
    setInternalValue(getRampRatio());
  } else {
    updateBeat();
  }


}


void BeatGenerator::setTempo(float newTempo) {
  tempo = newTempo;
  float s = (60 / tempo);
  pulse.setRate( s );
  updateDecayTime();
}



float BeatGenerator::getTempo() {
  return tempo;
}

// Decay is the duty cycle
void BeatGenerator::setDecay(float newDecay, decayMode newMode) {
  if (newMode == decayMode::ratio) {
    decayRatio = newDecay;
    updateDecayTime();
  } else {
    decayTime = newDecay;
  }
  //decay = newDecay;
  currentDecayMode = newMode;
}

float BeatGenerator::getDecay() {
  return decayTime;
}

void BeatGenerator::updateDecayTime() {
  // Decay needs to be adjusted here only if it is "ratio" mode. Else, leave it alone.
  decayTime = (currentDecayMode == decayMode::ratio) ? pulse.getRate() * decayRatio : decayTime;
}

float BeatGenerator::getRampRatio() {
  if (pulse.getRatio() < 0.5) {
    return Toolkit::mapf(pulse.getRatio(), 0.0, 0.5, 0.0, 1.0);
  } else {
    return Toolkit::mapf(pulse.getRatio(), 0.5, 1.0, 1.0, 0.0);
  }
}


void BeatGenerator::setRamp(bool newRamp) {
  useRamp = newRamp;
}


void BeatGenerator::setSubdivisions(byte newSubDiv) {
  beatSubdivisions = newSubDiv;
}

byte BeatGenerator::getSubdivisions() {
  return beatSubdivisions;
}

void BeatGenerator::clickBeat() {
  currentBeat++;
  currentBeat %= beatSubdivisions;
}

byte BeatGenerator::getBeat() {
  // Return +1 so the beat starts on 1 ... as music does
  return currentBeat + 1;
}


void BeatGenerator::updateBeat() {
  if (pulse.getElapsed() < decayTime) {
    if (beatState == false) {
      // Top of the beat
      beatState = true;
      setInternalValue(1.0);
      clickBeat();
      clickUp = true;
      //callback();
    }
  } else {
    if (beatState == true) {
      beatState = false;
      setInternalValue(0.0);
    }
  }
}

bool BeatGenerator::getState() {
  return beatState;
}

float BeatGenerator::getRatio() {
  return Toolkit::mapf(getBeat(), 1, getSubdivisions(), 0, 1);
}

// This is a psudo-event
bool BeatGenerator::getClick() {
  bool c = clickUp;
  clickUp = false;
  return c;
}



// ===== EOF =====
