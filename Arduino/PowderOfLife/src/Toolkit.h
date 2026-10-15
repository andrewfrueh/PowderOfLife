/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Toolkit
  
  ===========================

  This class is meant to be used as a static (not instanciated). Provides various utility functions.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */




/*
  To use as a static, the context is like this...
  Toolkit::mapi()

  This could just be part of Neuron right? Same with the Unity version!
    Consider moving it
*/


class Toolkit {
  private:
    Toolkit();
  public:
    // NEW
    //static int map( int x, int in_min, int in_max, int out_min, int out_max );
    //static float map( float x, float in_min, float in_max, float out_min, float out_max );
    // OLD
    static int mapi( int x, int in_min, int in_max, int out_min, int out_max );
    static float mapf( float x, float in_min, float in_max, float out_min, float out_max );
    static float absf( float x );
    static float constrainf(float x, float min, float max);
    static int constraini(int x, int min, int max);
    static int getSign( float input );
    static void printFloat(double number, uint8_t digits);
};

// private contstructor as we don't instantiate
Toolkit::Toolkit() {
}


int Toolkit::mapi( int x, int in_min, int in_max, int out_min, int out_max ) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float Toolkit::mapf( float x, float in_min, float in_max, float out_min, float out_max ) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


/*
int Toolkit::map( int x, int in_min, int in_max, int out_min, int out_max ) {
  mapi( x, in_min, in_max, out_min, out_max);
}

float Toolkit::map( float x, float in_min, float in_max, float out_min, float out_max ) {
  mapf( x, in_min, in_max, out_min, out_max);
}

*/

float Toolkit::absf( float x ) {
  if (x == 0) {
    return 0;
  } else if (x < 0) {
    return x * -1;
  } else {
    return x;
  }
}


float Toolkit::constrainf(float x, float min, float max) {
  return (x > min) ? ((x < max) ? x : max) : min;
}

int Toolkit::constraini(int x, int min, int max) {
  return (x > min) ? ((x < max) ? x : max) : min;
}

int Toolkit::getSign( float input ) {
  if ( input < 0 ) return -1;
  if ( input > 0 ) return 1;
  return 0;
}

// got this from: https://forum.arduino.cc/index.php?topic=42733.0
// Note this comment: "the code for "%f" formatting was not supported by the AVR library"
void Toolkit::printFloat(double number, uint8_t digits=8)
{
  // Handle negative numbers
  if (number < 0.0)
  {
    Serial.print('-');
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i = 0; i < digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    Serial.print(".");

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint;
  }
}
