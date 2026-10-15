/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  MPU Sensor
  
  ===========================

  This component assumes an MPU 6050 mounted on a breakout board that provides SDA/SCL pins.
  This component uses the I2C ("two-wire") interface via Arduino analog pins 4/5.
  The SDA pin is connected to Arduino analog input 4.
  The SCL pin is connected to Arduino analog input 5.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an instance of Ping Sensor
MPUSensor sensor;

// Create an instance of Timer for debugging
Timer debugTimer;

void setup() {

  // Give the debug timer a slow frame rate
  debugTimer.setRate(0.1);

  // Register the sensor with the engine.
  engine.addNeuron(sensor);
  sensor.setMode(MPUSensor::modes::gyroscope);
  sensor.setAxis(MPUSensor::axes::x);

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
