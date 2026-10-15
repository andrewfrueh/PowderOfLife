/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Analog Sensor Multiple Inputs Lerped with Serial Output
  ===========================

  This example builds on the Analog Sensor Lerped with Serial Output example, and provides two inputs.

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */


#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an Analog Sensor
AnalogSensor sensor_1;
AnalogSensor sensor_2;
// Create a Lerp Node
LerpNode lerp_1;
LerpNode lerp_2;

// The serial node is shared by all serial drivers and sensors
SerialNode serialManager;
//
SerialDriver serialOutput_1;
SerialDriver serialOutput_2;
// declare a channel number
byte serialOutputChannel_1 = 0;
byte serialOutputChannel_2 = 1;

// ==========

void setup() {


  // Register the sensors with the engine.
  engine.addNeuron(sensor_1);
  engine.addNeuron(sensor_2);
  // Set the pins, AnalogSensor uses analog pins
  sensor_1.setPin(0);
  sensor_2.setPin(1);

  // Register the lerps with the engine
  engine.addNeuron(lerp_1);
  engine.addNeuron(lerp_2);
  // Connect the sensors to the lerp node
  lerp_1.setInput(sensor_1);
  lerp_2.setInput(sensor_2);
  // Set the lerp speed and acceleration
  lerp_1.setLerp(2, 0.0001);
  lerp_2.setLerp(2, 0.0001);
  // Disable normalization for 0-1023 output
  lerp_1.setNormal(Neuron::normalMode::none);
  lerp_2.setNormal(Neuron::normalMode::none);

  // Register the serial manager with the engine.
  engine.addNeuron(serialManager);

  // Register the serial output with the engine.
  engine.addNeuron(serialOutput_1);
  engine.addNeuron(serialOutput_2);
  // It needs to be linked to the serial manager
  serialOutput_1.setSerialNode(serialManager, serialOutputChannel_1);
  serialOutput_2.setSerialNode(serialManager, serialOutputChannel_2);
  // Set the lerp as the input for this driver
  serialOutput_1.setInput(sensor_1);
  serialOutput_2.setInput(sensor_2);

}

void loop() {
  
  // Update the engine
  engine.update();

}

// END
