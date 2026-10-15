/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Analog Sensor Lerped
  
  ===========================

  TODO
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an Analog Sensor
AnalogSensor sensor;
// Create a Lerp Node
LerpNode lerp;

// Create an instance of Timer for debugging
Timer debugTimer;

void setup() {

  Serial.begin(9600);

  // Give the debug timer a slow frame rate
  debugTimer.setRate(0.1);

  // Register the sensor with the engine.
  engine.addNeuron(sensor);
  // Set the pin, AnalogSensor uses analog pins
  sensor.setPin(0);
  // Disable normalization for 0-1023 output
  sensor.setNormal(Neuron::normalMode::none);

  // Register the lerp with the engine
  engine.addNeuron(lerp);
  // Connect the sensor to the lerp node
  lerp.setInput(sensor);
  // Set the lerp speed and acceleration
  lerp.setLerp(2, 0.0001);
  // Disable normalization for 0-1023 output
  lerp.setNormal(Neuron::normalMode::none);


}

void loop() {
  
  // Update the engine
  engine.update();

  // The debugging timer slows down the debug messages so they don't interfere.
  // Everything below is not required, but is simply there to help us see what's going on.
  // Open the Serial Monitor or Serial Plotter to see the debug output
  if (debugTimer.interval()) {
    Serial.print(sensor.getValue());
    Serial.println();    
  }
  
}

// ===== END =====
