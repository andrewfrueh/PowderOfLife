/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Analog Sensor Lerped with Serial Output
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

// The serial node is shared by all serial drivers and sensors
SerialNode serialManager;
//
SerialDriver serialOutput;
// declare a channel number
byte serialOutputChannel = 0;

// ==========

void setup() {


  // Register the sensor with the engine.
  engine.addNeuron(sensor);
  // Set the pin, AnalogSensor uses analog pins
  sensor.setPin(0);

  // Register the lerp with the engine
  engine.addNeuron(lerp);
  // Connect the sensor to the lerp node
  lerp.setInput(sensor);
  // Set the lerp speed and acceleration
  lerp.setLerp(2, 0.0001);
  // Disable normalization for 0-1023 output
  lerp.setNormal(Neuron::normalMode::none);

  // Register the serial manager with the engine.
  engine.addNeuron(serialManager);

  // Register the serial output with the engine.
  engine.addNeuron(serialOutput);
  // It needs to be linked to the serial manager
  serialOutput.setSerialNode(serialManager, serialOutputChannel);
  // Set the lerp as the input for this driver
  serialOutput.setInput(sensor);

}

void loop() {
  
  // Update the engine
  engine.update();

}

// END
