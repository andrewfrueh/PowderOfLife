/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Lerped Beat
  
  ===========================

  This sketch demonstrates both the Beat Generator and the Lerp Node. 
  This is also technically a two-neuron network.

  There is no circuit for this sketch. Simply observe the output in the serial monitor / plotter.

  The Beat Generator is used to create the alternating digital signal. 
  The Lerp Node takes this digital signal and smooths it out with a lerp.
 
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an instance of Beat Generator
BeatGenerator beat;

// Create an instance of Lerp Node
LerpNode lerp;

// Create an instance of Timer for debugging
Timer debugTimer;


void setup() {

  // Give the debug timer a slow frame rate
  debugTimer.setRate(0.1);

  // Register the beat with the engine
  engine.addNeuron(beat);
  // ...
  beat.setTempo(30);

  // Register the lerp with the engine
  engine.addNeuron(lerp);
  // Connect the beat to the lerp
  lerp.setInput(beat);
  // ...
  lerp.setLerp(2,2);

}


void loop() {

  // Update the engine
  engine.update();
  
  // The debugging timer slows down the debug messages so they don't interfere.
  // Everything below is not required, but is simply there to help us see what's going on.
  // Open the Serial Monitor or Serial Plotter to see the debug output
  if (debugTimer.interval()) {    
    Serial.print(beat.getValue());
    Serial.print(",");
    Serial.print(lerp.getValue());
    Serial.println();
  }

}

// ===== END =====
