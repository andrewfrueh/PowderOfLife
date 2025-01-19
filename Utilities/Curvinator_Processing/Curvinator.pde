/* ====================================================================================================

  Powder Of Life
  Processing Environment
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

enum CurvinatorTypes { 
  none, in, out, inOut, outIn, bell, skew, bathtub
}

public static class Curvinator {

  // This duplicate function can be removed in languages that support default properties
  public static float Curve(float x, float e, CurvinatorTypes type ) {
    return Curve( x, e, type, false, false, 0.5 );
  }


  // I like this this, but Java sucks!!! No default values on parameters!!! WTF
  // Wrapper method
  // x is input, type is type, a is optional variable
  public static float Curve(float x, float e, CurvinatorTypes type, boolean invX, boolean invY, float c ) {
    //
    x = invX ? 1-x : x;
    //
    switch(type) {
    case none:
      // do nothing
      break;
    case in:
      x = In(x, e);
      break;
    case out:
      x = Out(x, e);
      break;
    case inOut:
      x = curveInOut(x, e, c);
      break;
    case outIn:
      x = curveOutIn(x, e, c);
      break;
    case bell:
      x = Bell(x, e);
      break;
    case skew:
      x = Skew(x, e);
      break;
    case bathtub:
      x = Bathtub(x, e);
      break;
    default:
      //return x;
      break;
    }

    // y axis inversion
    x = invY ? 1-x : x;

    return x;
  }


  // ========================================================
  // My own Variable Exponent easing. It takes the place of Quad, Cubic, Quint, etc. 

  public static float In(float x, float e) {
    return pow(x, e);
  }
  public static float Out(float x, float e) {
    return 1-pow(abs(x-1), e); // pow doesn't like negative numbers, hence 1-pow()
  }

  // ========================================
  // These compound curves are built piecewise from In and Out above.
  //   x : input, e : exponent, c : center
  public static float curveOutIn(float x, float e, float c){ // Be sure to add the default property: c = 0.5
    return x<c ? 
      Out(x/c, e)*c: 
      (In((x-c)/(1-c), e)*(1-c))+c;
  }
  public static float curveInOut(float x, float e, float c){ // Be sure to add the default property: c = 0.5
    return x<c ? 
      In(x*(1/c), e)/(1/c): 
      (Out((x-c)/(1-c), e)*(1-c))+c;
  }
  
  

  // ===========================================
  // Bell Vari is as good as Expo Vari above

  public static float Bell(float x, float e) {
    return (pow(sin(x*PI), e)/2) * 2;
  }

  public static float Skew(float x, float e) {
    return ( pow(x, e) - pow(x, e*2) ) * 4;
  }

  public static float Bathtub(float x, float e) {
    return pow( (abs(x - 0.5) * 2), e );
  }
  
  // ==========================================
  // Conversion

  public static CurvinatorTypes StringToType(String typeString) {

    CurvinatorTypes returnType;

    if (typeString == "none") {
      returnType = CurvinatorTypes.none;
    } else if (typeString == "in") {
      returnType = CurvinatorTypes.in;
    } else if (typeString == "out") {
      returnType = CurvinatorTypes.out;
    } else if (typeString == "inOut") {
      returnType = CurvinatorTypes.inOut;
    } else if (typeString == "outIn") {
      returnType = CurvinatorTypes.outIn;
    } else if (typeString == "bell") {
      returnType = CurvinatorTypes.bell;
    } else if (typeString == "skew") {
      returnType = CurvinatorTypes.skew;
    } else if (typeString == "bathtub") {
      returnType = CurvinatorTypes.bathtub;
    } else {
      returnType = CurvinatorTypes.none;
    }

    return returnType;
  }
  // ==========================================
};
