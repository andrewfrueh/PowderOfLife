/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Encoder Sensor With Serial Output
  ===========================

  TODO

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */


#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an instance of Analog Sensor
EncoderSensor sensor;
// Each encoder has a specific number of steps per rotation
int encoderStepsPerRotation = 96;

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
  // Set the input pins for the sensor (A-phase, B-phase, use-pullups)
  sensor.setPin(2, 3, false);
  // If you want to reverse the direction, just use setReverse()
  sensor.setReverse(true);
  // Set encoderStepsPerRotation above, and one rotation should equal one unit. 
  sensor.setNormal(Neuron::normalMode::custom, Neuron::normalClip::overflow, 0, encoderStepsPerRotation);
  // You can adjust the rate used to determine change by the encoder (rate in seconds)
  sensor.setRate(0.3);
  // Set the mode: "rate" or "range"
  sensor.setMode(EncoderSensor::modes::rate);

  // Register the serial manager with the engine.
  engine.addNeuron(serialManager);

  // Register the serial output with the engine.
  engine.addNeuron(serialOutput);
  // It needs to be linked to the serial manager
  serialOutput.setSerialNode(serialManager, serialOutputChannel);
  // Set the sensor as the input for this driver
  serialOutput.setInput(sensor);

}

void loop() {
  
  // Update the engine
  engine.update();

}

// END
