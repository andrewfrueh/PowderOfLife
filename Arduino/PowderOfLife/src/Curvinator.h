/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Curvinator
  
  ===========================

  The Curvinator is designed as a static class, meaning you don't create instances of it. Instead, you directly call its functions, which are essentially mathematical formulas representing different types of easing curves.

  Use the curve() method for high-level access and control over all properties. Useful for cases where you want to change the type of curve dynamically.
    curve(
          float x: input value
          float e: exponent of the curve 
          mode newMode: type of curve (can be: none, in, out, inOut, outIn, bell, skew, bathtub)
          boolean invX: if true, invert along the x axis
          boolean invY: if true, invert along the y axis
          float c: center point (0.5 is default)
          )

  Use the individual curve methods as needed (e.g. curveIn(), curveOut(), etc.).
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */






class Curvinator {
private:
  Curvinator();
public:
  enum mode : byte { none,
                     in,
                     out,
                     inOut,
                     outIn,
                     bell,
                     skew,
                     bathtub };  // These conflict with the method names! Why?
  // curve() could have 3 forms
  // static float curve(float x, float e, mode newMode);
  // static float curve(float x, float e, mode newMode, float c);
  // static float curve(float x, float e, mode newMode, boolean invX, boolean invY, float c);
  static float curve(float x, float e, mode newMode, boolean invX=false, boolean invY=false, float c=0.5);
  //
  static float curveIn(float x, float e);
  static float curveOut(float x, float e);
  static float curveOutIn(float x, float e, float c);
  static float curveInOut(float x, float e, float c);
  static float curveBell(float x, float e);
  static float curveSkew(float x, float e);
  static float curveBathtub(float x, float e);
  // Conversion
  //static types stringToType(String typeString);
};

// Constructor
Curvinator::Curvinator() {
}


// Wrapper method
// x is input, e is exponent, type is type

// float Curvinator::curve(float x, float e, mode newMode) {
//   curve( x, e, newMode, 0.5 );
// }

// float Curvinator::curve(float x, float e, mode newMode, float c) {
//   curve( x, e, newMode, false, false, c );
// }

// float Curvinator::curve(float x, float e, mode newMode, boolean invX, boolean invY, float c) {
float Curvinator::curve(float x, float e, mode newMode, boolean invX, boolean invY, float c) {

  // x axis inversion
  x = invX ? 1 - x : x;

  // switch on type (routing)
  switch (newMode) {
    case mode::none:
      // work nothing
      break;
    case mode::in:
      x = curveIn(x, e);
      break;
    case mode::out:
      x = curveOut(x, e);
      break;
    case mode::inOut:
      x = curveInOut(x, e, c);
      break;
    case mode::outIn:
      x = curveOutIn(x, e, c);
      break;
    case mode::bell:
      x = curveBell(x, e);
      break;
    case mode::skew:
      x = curveSkew(x, e);
      break;
    case mode::bathtub:
      x = curveBathtub(x, e);
      break;
    default:
      // work nothing
      break;
  }

  // y axis inversion
  x = invY ? 1 - x : x;

  return x;
}


// ========================================================
// My own Variable Exponent easing. It takes the place of Quad, Cubic, Quint, etc.

float Curvinator::curveIn(float x, float e) {
  return pow(x, e);
}
float Curvinator::curveOut(float x, float e) {
  return 1 - pow(abs(x - 1), e);  // pow doesn't like negative numbers, hence 1-pow()
}

// ========================================
// These compound curves are built piecewise from In and Out above.
//   x : input, e : exponent, c : center
float Curvinator::curveOutIn(float x, float e, float c) {  // Be sure to add the default property: c = 0.5
  return x < c ? curveOut(x / c, e) * c : (curveIn((x - c) / (1 - c), e) * (1 - c)) + c;
}
float Curvinator::curveInOut(float x, float e, float c) {  // Be sure to add the default property: c = 0.5
  return x < c ? curveIn(x * (1 / c), e) / (1 / c) : (curveOut((x - c) / (1 - c), e) * (1 - c)) + c;
}


// ===========================================
// bell Vari is as good as Expo Vari above

float Curvinator::curveBell(float x, float e) {
  return (pow(sin(x * PI), e) / 2) * 2;
}

float Curvinator::curveSkew(float x, float e) {
  return (pow(x, e) - pow(x, e * 2)) * 4;
}

float Curvinator::curveBathtub(float x, float e) {
  return pow((abs(x - 0.5) * 2), e);
}

// ==========================================
// Conversion

/*
Curvinator::types Curvinator::stringToType(String typeString){

  curvinatorTypes returnType;

  if (typeString == "none") {
    returnType = curvinatorTypes::none;
  }else if (typeString == "in") {
    returnType = curvinatorTypes::in;
  }else if (typeString == "out") {
    returnType = curvinatorTypes::out;
  }else if (typeString == "inOut") {
    returnType = curvinatorTypes::inOut;
  }else if (typeString == "outIn") {
    returnType = curvinatorTypes::outIn;
  }else if (typeString == "bell") {
    returnType = curvinatorTypes::bell;
  }else if (typeString == "skew") {
    returnType = curvinatorTypes::skew;
  }else if (typeString == "bathtub") {
    returnType = curvinatorTypes::bathtub;
  }else{
    returnType = curvinatorTypes::none;
  }

  return returnType;
  
}
*/
