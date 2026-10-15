/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Midi Driver
  
  ===========================

  MIDI communication is a serial protocol. This driver sends standard MIDI messages.
  Note: this driver will conflict with the SerialNode and it's control of the serial port.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2026
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

/*
  TODO
    - set up the serial port in the constructor
    - set the rate to the correct rate for MIDI
    - etc....
*/


class MidiDriver : public Driver {
  private:
    float noteBase;
    //int noteOffset;
    //int midiClockModulo = 24;
    //int noteSubdiv = 4;
    //float noteTimerRate = 0.5;
    //Timer noteTimer;
    //Timer clockTimer;
  public:
    MidiDriver();
    void work();
    void wake();
    void setBase(float newBase);
    //void SetOffset(int newOffset);
    //
    void playNote(byte note, byte velocity = 100, byte channel = 1, bool playStop = true);
    void stopNote(byte note, byte channel = 1);
    void sendClock();
    void allNotesOff();
};

MidiDriver::MidiDriver() {
  // TODO - setup serial port
}


void MidiDriver::work() {
  // TODO, nice to have, not need to have... internal timing
  /*
    if (clockTimer.interval() && midiOutput) {
    sendClock();
    }
    if (noteTimer.interval()) {
    playNote();
    }
  */
}

void MidiDriver::wake() {
  /*
    noteTimer.setRate(noteTimerRate / noteSubdiv);
    clockTimer.setRate(noteTimerRate / midiClockModulo);
  */
  setBase(60);
}

void MidiDriver::setBase(float newBase) {
  noteBase = newBase;
}

/*
  void MidiDriver::SetOffset(int newOffset) {

  }
*/

// =================

// 0x7B: All notes off?
// 0x80: Note off (128)
// 0x90: Note on (144)
// 0xA0: Poly pressure (160)
// 0xB0: control change (176)
// 0xE0: pitch bend
// ----
// 0xf1: MIDI Time Code (MTC) Quarter Frame
// 0xF8: timing clock (24 per quarter note)
void MidiDriver::playNote(byte note, byte velocity, byte channel, bool playStop)
{
  //MIDI channels 1-16 are really 0-15
  byte noteOnStatus = (playStop ? 0x90 : 0x80) + (channel - 1);

  //Transmit a Note-On message
  Serial.write(noteOnStatus);
  Serial.write(note);
  Serial.write(velocity);
}

void MidiDriver::stopNote(byte note, byte channel) {
  byte noteOnStatus = 0x80 + (channel - 1);
  //Transmit a Note-Off message
  Serial.write(noteOnStatus);
  Serial.write(note);
  Serial.write(0);

}


void MidiDriver::sendClock() {
  byte clockByte = 0xF8;
  Serial.write(clockByte);
}

// TODO - This shit don't work!
void MidiDriver::allNotesOff() {
  Serial.write(0x7B);
  /*
    // https://forum.arduino.cc/t/midi-reset/169120/8
    Serial.write(0xF0);
    Serial.write(0x7F);
    Serial.write(0x7F); //device id 7F = 127 all channels
    Serial.write(0x02);
    Serial.write(0x7F); // command format 7F = all devices
    Serial.write(0x0A); // action 0x0A= reset
    Serial.write(0xF7);
  */
  // Serial.write(0xFF);

}
