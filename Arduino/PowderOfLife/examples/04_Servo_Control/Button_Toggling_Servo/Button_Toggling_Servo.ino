/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Button Toggling Servo
  
  ===========================

  This is a simple two-neuron network to control a servo motor with a toggle button.
  This example would be a good foundation for building an open/close mechanism operated by a single button.

  Note that even though this sketch uses the Servo library, we can still interact with it in a hybrid way. 
  We let POL handle the behavior of the data, and then simply hand that value to the servo in the loop().

  Dependency: This example uses the standard Arduino Servo library. Please install it first.

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

// Create an Encoder Sensor
ButtonSensor button;

// Create a Lerp Node
LerpNode lerp;

// Create a Servo object (note: this is not a POL object)
Servo servo;

// ==========

void setup() {


  // Register the sensor with the engine
  engine.addNeuron(button);
  // Set the pin that the button is attached to
  button.setPin(2);
  // Make the button a toggle
  button.setToggle(true);
  // For a button, you probably want to use "pullup" on the input, unless you are providing the resistor
  button.setPinPullup(true);

  // Register the lerp with the engine
  engine.addNeuron(lerp);
  // Set the speed of the lerp
  lerp.setLerp(1,1);
  // Connect the sensor to the lerp
  lerp.setInput(button);

  // Set the pin on the servo object
  servo.attach(3);

}

void loop() {
  
  // Update the engine
  engine.update();

  // Manually update the servo object
  servo.write(lerp.getValue()*180);

}

// EOF
