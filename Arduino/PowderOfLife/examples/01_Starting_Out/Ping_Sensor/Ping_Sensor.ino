/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Ping Sensor
  
  ===========================

  This script is for testing a "ping" sensor (the standard, cheap ultrasonic distance sensor) as input.

  The original Ping sensor from Parallax had three wires (using one pin for both trigger and echo). 
  The more standard kind that ships in most kits has four wires (one pin for trigger, another for echo).
  The PingSensor currently only supports the four-wire version, so you must declare two pins in setPin().
  The other two pins are -/+ voltage (Gnd and 5v). 
  
  Open the serial monitor to see the debug output.
 
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an instance of Ping Sensor
PingSensor sensor;

// Create an instance of Timer for debugging
Timer debugTimer;

void setup() {

  // Give the debug timer a slow frame rate
  debugTimer.setRate(0.1);

  // Register the sensor with the engine.
  engine.addNeuron(sensor);
  // Set the pins: trigger, echo.
  sensor.setPin(2, 3);

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
