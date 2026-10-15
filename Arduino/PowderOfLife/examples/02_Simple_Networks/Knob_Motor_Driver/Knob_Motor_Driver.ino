/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Knob Motor Driver
  
  ===========================

  This is a simple two-neuron network to control a DC motor with an analog knob (potentiometer).
 
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an instance of Analog Sensor
AnalogSensor sensor;

// Create an instance of Stepper Driver
MotorDriver driver;

SerialNode serial;

Timer debug;

void setup() {

  // If we don't use POL's SerialNode, we need to setup serial manually
  Serial.begin(9600);
  debug.setRate(0.1);

  // Register the sensor with the engine
  engine.addNeuron(sensor);
  // Set the pin
  sensor.setPin(0);
  //
  // sensor.setNormalClip(Neuron::normalClip::overflow);
  // sensor.setNormalRange(512, 1023);
  sensor.setNormal(Neuron::normalMode::custom, Neuron::normalClip::overflow, 512, 1023, false);

  // Register the node with the engine.
  engine.addNeuron(driver);
  // Link the driver to the sensor
  driver.setInput(sensor);
  // Set the output pins for the driver (dir, speed)
  driver.setPin(4,5);

}

void loop() {
  // Update the engine
  engine.update();

  // Debugging
  if(debug.interval()){
    Serial.print(sensor.getValue());
    Serial.println();
  }
  
}

// === END ===
