/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Mixer
  
  ===========================

  The Mixer class allows mixing / blending of two inputs.
  This can be used in a wide variety of situations, but is also the main utility of the MixNode.
  
  The modes:
    add
    subtract
    multiply
    divide
    screen
    overlay
    difference
    min
    max
    less
    greater
    modulo
    power
    average
    [logic gate types]
    AND
    OR
    NAND
    NOR
    XOR
    XNOR
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */




class Mixer {

  private:
    Mixer();
  public:
    enum mode : byte { add, subtract, multiply, divide, screen, overlay, difference, min, max, less, greater, modulo, power, average, AND, OR, NAND, NOR, XOR, XNOR };
    static float Mix(float a, float b, mode newMode);
};

// Constructor
Mixer::Mixer() {
}

float Mixer::Mix(float a, float b, Mixer::mode newMode) {
  float c;
  switch (newMode) {
    case mode::add:
      c = a + b;
      break;
    case mode::subtract:
      c = a - b;
      break;
    case mode::multiply:
      c = a * b;
      break;
    case mode::divide:
      c = b != 0 ? (a / b) : 1;
      break;
    case mode::screen:
      c = 1 - ((1 - a) * (1 - b));
      break;
    case mode::overlay:
      c = b < 0.5 ? 2 * a * b : (1 - (2 * (1 - a) * (1 - b)));
      break;
    case mode::difference:
      c = abs(a - b);
      break;
    case mode::min:
      c = a < b ? a : b;
      break;
    case mode::max:
      c = a > b ? a : b;
      break;
    case mode::less:
      c = a < b ? 1 : 0;
      break;
    case mode::greater:
      c = a > b ? 1 : 0;
      break;
    case mode::modulo:
      c = fmod(a,b); //a % b; // fmod is float-modulo and part of C++
      break;
    case mode::power:
      c = pow(a, b);
      break;
    case mode::average:
      c = (a + b) / 2;
      break;
    case mode::AND:
      c = (bool(a) && bool(b)) ? 1 : 0;
      break;
    case mode::OR:
      c = (bool(a) || bool(b)) ? 1 : 0;
      break;
    case mode::NAND:
      c = !(bool(a) && bool(b)) ? 1 : 0;
      break;
    case mode::NOR:
      c = !(bool(a) || bool(b)) ? 1 : 0;
      break;
    case mode::XOR: // OR & NAND
      c = (bool(a) || bool(b)) && !(bool(a) && bool(b)) ? 1 : 0;
      break;
    case mode::XNOR: // NOR | AND
      c = !(bool(a) || bool(b)) || (bool(a) && bool(b)) ? 1 : 0;
      break;
    default:
      c = 0;
      break;
  }
  //
  return c;
}
