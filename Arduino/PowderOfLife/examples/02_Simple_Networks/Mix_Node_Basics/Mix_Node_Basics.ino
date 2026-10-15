/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Mix Node Basics
  
  ===========================

  The Mix Node can support a wide range of behavior. 
  Take time to become familiar with the modes and you will be rewarded.
  These modes are common in many graphics / design applications.

  The Mix Node takes two inputs and outputs the blend between the two based on its current mode.
  This is the list of all available modes:
    add, subtract, multiply, divide, screen, overlay, difference, min, max, less, greater, modulo, power, average, AND, OR, NAND, NOR, XOR, XNOR
  The last six modes (all CAPS) are for binary logic and should be used accordingly.
  
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */


#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create two Button Sensors as our logic input
AnalogSensor input_A;
AnalogSensor input_B;

// Create a Mix Node to act as the logic gate
MixNode mixer;

// Create an Analog Driver to have an LED (or whatever) for output
AnalogDriver output;

// Create an instance of Timer for debugging
Timer debugTimer;

// ==========

void setup() {

  // Give the debug timer a slow frame rate
  debugTimer.setRate(0.1);

  // Setup the two inputs
  engine.addNeuron(input_A);
  input_A.setPin(0);
  engine.addNeuron(input_B);
  input_B.setPin(1);

  // Setup the mixer
  engine.addNeuron(mixer);
  // Connect the inputs to the mixer
  mixer.setInput(input_A, 0);
  mixer.setInput(input_B, 1);
  // We can change the type of blending via the mixer mode -- possible options are:
  //  add, subtract, multiply, divide, screen, overlay, difference, min, max, less, greater, modulo, power, average, AND, OR, NAND, NOR, XOR, XNOR
  mixer.setMode(Mixer::mode::average);

  // -----------------

  // Setup the output
  engine.addNeuron(output);
  // ...
  output.setPin(5);
  // Connect the inputs to the logic gate
  output.setInput(mixer);

}

void loop() {
  
  // Update the engine
  engine.update();

  // The debugging timer slows down the debug messages so they don't interfere.
  // Everything below is not required, but is simply there to help us see what's going on.
  // Open the Serial Monitor or Serial Plotter to see the debug output
  if (debugTimer.interval()) {
      Serial.print(input_A.getValue());
      Serial.print(":");
      Serial.print(input_B.getValue());
      Serial.print("=>");
      Serial.print(mixer.getValue());
      Serial.println();
  }
  
}

// ===== END =====
