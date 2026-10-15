/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  LED Candle
  
  ===========================

  This simple little test will make an LED flicker like a candle light. 
  This is also technically a two-neuron network.

  Your led has two wires. One is connected to ground, the other is conncted to a resistor (typically 330 Ohm @ 5v)
    that is then connected to the digital output (pin 3 in this example).
  The resistor is there to keep the voltage (therefore current) low enough not to burn out the LED.

  The Random Generator is used to create the candle flicker -- it has four inputs: up-min, up-max, down-min, down-max.
  The "up" time means the LED is lit, and "down" time means the LED is not lit.
  "min" and "max" are the ranges for how long, randomly, each "up" and "down" will take place.
  
  A PWM enabled pin (like pin 3) will give you a better candle, but you can see the randomization on a digital pin as well (like pin 2). 
    
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// Create an instance of Random Generator for our candle flicker effect
RandomGenerator generator;

// Create an instance of Analog Driver to control the LED brightness
AnalogDriver led;


void setup() {

  engine.addNeuron(generator);
  // Since we want our candle lit all the time, we only use the first two "up" values
  generator.setRandomRates(0.1,0.01,0.0,0.0);

  // Register the led with the engine.
  engine.addNeuron(led);
  // Use a PWM enabled pin for best effect. Or use pin 13 for simple testing like the infamous Blink sketch.
  led.setPin(3);
  // Connect the random generator to the led.
  led.setInput(generator);

}


void loop() {

  // Update the engine
  engine.update();

}

// ===== END =====
