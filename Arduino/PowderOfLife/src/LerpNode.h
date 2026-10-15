/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Lerp Node

  ===========================

  The LerpNode is a wrapper for the RailcarLerp class.
  Put it inline in your network to smooth out a signal between two nodes.
  Useful for a range of issues related to noisy / jerky behavior (such as controlling servos).

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

  ==================================================================================================== */



class LerpNode : public Node {
  private:
    //
  public:
    // Constructor
    LerpNode();
    // Lerp
    RailcarLerp lerp;
    //
    void work();
    void wake();
    void setLerp(float newSpeed, float newAcceleration);
};

LerpNode::LerpNode() {

  setNormal(normalMode::none);
  lerp.setSpeed(1.0);
  lerp.setAcceleration(0.1);
}

void LerpNode::wake() {
}


void LerpNode::work() {
  //Serial.println(getFrameDelta());
  if (hasInput()) {
    lerp.setTarget(getInput().getValue());
  }
  lerp.update(getFrameDelta());
  setInternalValue(lerp.getValue());
}

void LerpNode::setLerp(float newSpeed, float newAcceleration) {
  lerp.setSpeed(newSpeed);
  lerp.setAcceleration(newAcceleration);
}


// EOF
