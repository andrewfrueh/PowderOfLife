/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Sustain Node
  
  ===========================

  TODO
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */




class SustainNode : public Node {
  private:
    // If threshold is defined, sustain is binary. If threshold is not defined, sustain is analog.
    float threshold;
    Timer sustainTimer;
  protected:
    float frameTime = 0.001;
  public:
    SustainNode();
    // enum options
    //enum mode : byte {  };
    //
    void work();
    void setTime(float newTime);
    void setLevel(float newLevel);
};


// constructor
SustainNode::SustainNode() {
  setTime(1.0);
  setLevel(0.0);
}

void SustainNode::setTime(float newTime) {
  sustainTimer.setRate(newTime);
}

// What the hell is the point of this method?
// SAME as SetValue()
void SustainNode::setLevel(float newLevel) {
  threshold = newLevel;
}


void SustainNode::work() {

  float input = getInput().getValue();

  // This is kind of a kludge. The threshold controls the "mode"
  if (threshold == 0.0) {
    // If threshold is zero, sustain is analog
    // If input is greater than internal, update
    if (getInput().getValue() > getValue()) {
      setInternalValue( getInput().getValue() );
      sustainTimer.reset();
    }
  } else {
    // If threshold is non-zero, sustain is digital
    if ((getInput().getValue() > threshold)) {
      setInternalValue( 1 );
      sustainTimer.reset();
    }
  }



  // Reset the internal value to zero?
  if ( sustainTimer.timeout()) {
    setInternalValue( 0 );
  } else {
    // do nothing
  }

}

// =====================
