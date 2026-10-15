/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Encoder Sensor
  ===========================

  This script is for testing an encoder as input.

  Most encoders have four wires: -/+ voltage (Gnd/Vcc), and A/B phase.
  The A/B phase are connected to the pins named in setPin().
  setPin() has three parameters: setPin(A-phase, B-phase, use-pullups)
  Encoders that have a self-powered board often don't need pullups.
  Encoders that don't have a self-powered board, or mechanical encoders, will likely need pullups.
  
  Open the serial monitor to see the output of your encoder.

  For deeper understanding, use two buttons connected to the pins in place of an encoder. 
  You will have to press them in the correct pattern to make the encoder count up or down.
 
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */


#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an instance of Analog Sensor
EncoderSensor sensor;

// Create an instance of Timer for debugging
Timer debugTimer;

// Each encoder has a specific number of steps per rotation
//  80 for cheap non-powered ones, 96 for POL original "100mm" size
int encoderStepsPerRotation = 80;

// ==========

void setup() {

  // Give the debug timer a slow frame rate
  debugTimer.setRate(0.1);

  // Register the sensor with the engine.
  engine.addNeuron(sensor);
  // Set the input pins for the sensor (A-phase, B-phase, use-pullups)
  sensor.setPin(2, 3, false);
  // If you want to reverse the direction, just use setReverse()
  sensor.setReverse(true);
  
  // Each encoder has a specific number of steps per rotation.
  // To determine how many steps your encoder has, use the following below...

  // Start with normalization set to "none". This will allow us to see the raw output of the sensor in the debug output.
  sensor.setNormal(Neuron::normalMode::none);

  // Next, set encoderStepsPerRotation above, and then use this line instead of the one above and one rotation should equal one unit. 
  //sensor.setNormal(Neuron::normalMode::custom, Neuron::normalClip::overflow, 0, encoderStepsPerRotation);

  // You can also switch between two modes: range (default) and rate
  //  range: count steps linearly (distance); rate: count rate of steps over time (speed)
  // sensor.setMode(EncoderSensor::modes::rate);

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

// END
