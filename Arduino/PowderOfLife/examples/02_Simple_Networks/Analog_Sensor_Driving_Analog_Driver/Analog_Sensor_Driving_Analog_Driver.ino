/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Analog Sensor driving Analog Driver
  
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

// Create an Analog Driver
AnalogDriver driver;

// Create an instance of Timer for debugging
Timer debugTimer;

void setup() {

  // Give the debug timer a slow frame rate
  debugTimer.setRate(0.1);

  // Register the sensor with the engine.
  engine.addNeuron(sensor);
  // Set the pin, AnalogSensor uses analog pins
  sensor.setPin(0);
  // To invert the output of the sensor...
  sensor.setNormal(Neuron::normalMode::custom, Neuron:normalClip::invert, 0, 1023 );

  // Register the driver with the engine.
  engine.addNeuron(driver);
  // Set the pin, AnalogDriver uses PWM pins
  driver.setPin(3);
  // Link the sensor node
  driver.setInput(sensor);

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
