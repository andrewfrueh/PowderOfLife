/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Mix Node Logic Gates
  
  ===========================

  It is possible to use the mix node as a logic gate.
  The Mixer has the six main logic gate types built in: AND, OR, NAND, NOR, XOR, XNOR
  A good basic demo of logic types can be made with two buttons and an LED (or other output).

  Also note, that the two basic gates (AND / OR) can easily be made with the more traditional modes.
  An AND gate can be made when inputs are multiplied. An OR gate can be made when inputs are added.
  The inversions of these can be achieved by using "invert" type clipping in normalization.
  
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */


#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create two Button Sensors as our logic input
ButtonSensor input_A;
ButtonSensor input_B;

// Create a Mix Node to act as the logic gate
MixNode logicGate;

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
  input_A.setPin(2);
  engine.addNeuron(input_B);
  input_B.setPin(3);

  // Setup the logic gate
  engine.addNeuron(logicGate);
  // Connect the inputs to the logic gate
  logicGate.setInput(input_A, 0);
  logicGate.setInput(input_B, 1);

  // -----------------

  // We can change the type of logic gate via the mixer mode -- possible options are:
  //  AND, OR, NAND, NOR, XOR, XNOR
  logicGate.setMode(Mixer::modes::AND);

  // -----------------

  // Setup the output
  engine.addNeuron(output);
  // ...
  output.setPin(5);
  // Connect the inputs to the logic gate
  output.setInput(logicGate);

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
      Serial.print(logicGate.getValue());
      Serial.println();
  }
  
}

// ===== END =====
