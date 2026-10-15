/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Analog Sensor
  
  ===========================

  This script is for testing any of the numerous analog sensors (knob, light, etc.) as input.

  Commonly this would be a resistive input such as a light sensor or potentiometer knob.
  Often a voltage divider is needed to balance the resitive input, such as with a light sensor.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an Analog Sensor
AnalogSensor sensor;

// Create an instance of Timer for debugging
Timer debugTimer;

void setup() {

  // If we don't have a SerialNode, we need to start the serial port
  Serial.begin(9600);

  // Give the debug timer a slow frame rate
  debugTimer.setRate(0.1);

  // Register the sensor with the engine.
  engine.addNeuron(sensor);
  // Set the pin, AnalogSensor uses analog pins
  sensor.setPin(0);

}

void loop() {
  
  // Update the engine
  engine.update();

  // The debugging timer slows down the debug messages so they don't interfere.
  // Everything below is not required, but is simply there to help us see what's going on.
  // Open the Serial Monitor or Serial Plotter to see the debug output
  if (debugTimer.interval()) {
    // Use the Toolkit's printFloat to get more decimals
    Toolkit::printFloat(sensor.getValue(),4);
    Serial.println();    
  }
  
}

// ===== END =====
