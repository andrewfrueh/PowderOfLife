/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  IR Sensor Driving Servo
  
  ===========================

  This is a simple five-neuron network create a reactive robot that will try to hold a fixed distance.

  It uses an IR Sensor and Servo Driver for input and output.

  Note that there are three additional neurons between the sensor and driver:
    a clone for applying "custom" type normalization to help invert and re-frame the sensor's output
    a clone for applying "steering" type normalization to help create a center-point
    a lerp for smoothing out the system and behavior
 
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

// Include the PowderOfLife library
#include <PowderOfLife.h>

// Include the Servo library
#include <Servo.h>

// Create an Engine
Engine engine;

// Create an Analog Sensor
AnalogSensor sensor;

// Create a Lerp Node
LerpNode lerp;

// Create a Servo object (note: this is not a POL object)
Servo servo;

void setup() {

  // Register the sensor with the engine.
  engine.addNeuron(sensor);
  // Set the input pin for the sensor -- analog pin
  sensor.setPin(0);

  // Register the node with the engine.
  engine.addNeuron(lerp);
  // Link the sensor to the lerp node
  lerp.setInput(sensor);
  // Set the speed for the lerp
  lerp.setLerp(4.0, 4.0);

  // Set the pin on the servo object
  servo.attach(3);

}

void loop() {

  // Update the engine
  engine.update();

  // Manually update the servo object
  servo.write(lerp.getValue()*180);

}

// ===== END =====
