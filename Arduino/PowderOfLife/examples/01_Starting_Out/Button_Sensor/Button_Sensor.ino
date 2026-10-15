/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Button Sensor
  
  ===========================

  This script is for testing a button (switch) as input.

  Your button has two wires. One is connected to ground, the other is connected to the pin named in setPin(). 
  This assumes no extra circuitry. If you have a circuit with pullup resistors, be sure to set pullup to false in setPin().
  
  Open the serial monitor to see the debug output.
 
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */


#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an instance of Button Sensor
ButtonSensor sensor;

// Create an instance of Timer for debugging
Timer debugTimer;

// ==========

void setup() {

  // Give the debug timer a slow frame rate
  debugTimer.setRate(0.1);
  // Since we aren't using a SerialNode, to do debugging, you also need to fire up the built-in Serial
  Serial.begin(9600);

  // Register the sensor with the engine.
  engine.addNeuron(sensor);
  // Set the input pin for the sensor
  sensor.setPin(2);
  // You can make the button behave like a toggle
  //sensor.setToggle(true);

}

void loop() {
  
  // Update the engine
  engine.update();

  // The debugging timer slows down the debug messages so they don't interfere.
  // Everything below is not required, but is simply there to help us see what's going on.
  // Open the Serial Monitor or Serial Plotter to see the debug output
  if (debugTimer.interval()) {
    
    // This line only shows you when the button is pressed.
    if(sensor.getDown()){
      Serial.println("DOWN");
    }
    
    // This line only shows you when the button is released.
    if(sensor.getUp()){
      Serial.println("UP");
    }
    
    // This line shows you a stream of the button's state. Uncomment to see it.
    //Serial.println(sensor.getValue());

  }
  
}

// ===== END =====
