/* ====================================================================================================

  Powder Of Life
  Arduino Examples
  ---
  Serial Echo
  ===========================

  TODO

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */


#include <PowderOfLife.h>

// Create an instance of Engine
Engine engine;

// The serial node is shared by all serial drivers and sensors
SerialNode serialManager;

// The SerialSensor reads data in via the SerialNode
SerialSensor serialIn_A;
// The SerialDriver sends data out via the SerialNode
SerialDriver serialOut_A;
// Since the serial port is shared, we need to declare a channel number
byte serialChannel_A;

// ==========

void setup() {

  // The SerialNode manages the serial connection (the port)
  engine.addNeuron(serialManager);

  // The SerialSensor pulls data from the SerialNode
  engine.addNeuron(serialIn_A);
  // It needs to be linked to the SerialNode and declare a channel number
  serialIn_A.setSerialNode(serialManager, serialChannel_A);

  // The SerialDriver uses the SerialSensor as input, then echoes it back out using the SerialNode
  engine.addNeuron(serialOut_A);
  // It needs to be linked to the SerialNode and declare a channel number
  serialOut_A.setSerialNode(serialManager, serialChannel_A);
  // Set the sensor as the input for this driver so we can echo
  serialOut_A.setInput(serialIn_A);

}

void loop() {
  
  // Update the engine
  engine.update();

}

// END
