/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Encoder Driving Stepper
  
  ===========================

  This is a simple two-neuron network to control a stepper motor with an encoder knob.
 
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an instance of Analog Sensor
EncoderSensor sensor;

// Create an instance of Stepper Driver
StepperDriver driver;

void setup() {

  // Register the sensor with the engine
  engine.addNeuron(sensor);
  // Set the pins: trigger, echo
  sensor.setPin(2, 3);
  // Using reverse makes the knob positive in the clockwise direction which is more standard / intuitive
  sensor.setReverse(true);
  // Use "slide" normalization for a more robust interface
  sensor.setNormal(Neuron::normalMode::slide, Neuron::normalClip::clip, encoderStepsPerRotation);

  // Register the node with the engine.
  engine.addNeuron(driver);
  // Link the sensor to the lerp node
  driver.setInput(sensor);
  // Set the output pins for the driver (step, dir)
  sensor.setPin(4, 5);

}

void loop() {
  // Update the engine
  engine.update();
}

// ===== END =====
