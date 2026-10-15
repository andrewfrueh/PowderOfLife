

/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Curve Node

  ===========================

  The CurveNode provides a way to apply mathematical curves to signal values. It acts as a non-linear signal processor, enabling you to alter the response characteristics of sensors, generators, or other nodes in a network.

  CurveNode is essentially a wrapper for the Curvinator class that does the actual calculation for the curve. See the Curvinator class for more info.

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2026
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

  ==================================================================================================== */


class CurveNode : public Node {
  private:
    byte currentCurveType;
    float currentCurveExponent;
  public:
    CurveNode();
    void work();
    void setCurve(Curvinator::mode newCurve, float newExponent = 2 ); //currentCurveType
};

CurveNode::CurveNode() {
  setNormal(normalMode::custom, normalClip::clip, 0, 1);
}

void CurveNode::work() {
  if (hasInput()) {
    // Simply transfer value like the clone node, but apply Curvinator
    setInternalValue(Curvinator::curve(getInput().getValue(), currentCurveExponent, static_cast<Curvinator::mode>(currentCurveType)));
  }
}

void CurveNode::setCurve(Curvinator::mode newCurve, float newExponent ) {
  currentCurveType = newCurve;
  currentCurveExponent = newExponent;
}


// EOF
