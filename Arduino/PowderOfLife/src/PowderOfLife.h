/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Config script
  
  ===========================

  This script is the main file that has global level elements and loads other scripts.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

// Create the unique identifier for this library
//  (in your code, you can check for this to know if POL is installed)
#ifndef PowderOfLife_h
  #define PowderOfLife_h
#endif

// Global Constants
// 10-bit input
#define ANALOG_INPUT_MIN 0
#define ANALOG_INPUT_MAX 1023
// 8-bit output
#define ANALOG_OUTPUT_MIN 0
#define ANALOG_OUTPUT_MAX 255
// 1-bit input
#define DIGITAL_INPUT_MIN 0
#define DIGITAL_INPUT_MAX 1
// POL normalize range
#define POL_NORMALIZE_MIN 0.0
#define POL_NORMALIZE_MAX 1.0
// Arduino's analog pins start at...
#define ANALOG_PIN_NUMBER_OFFSET 14

// Serial
#define SERIAL_BAUD_RATE_DEBUG 9600 // This is the Arduino IDE default state
#define SERIAL_BAUD_RATE_MIDI 31250 // This is defined by the MIDI standard
#define SERIAL_BAUD_RATE_DEFAULT 19200 // This is still not resolved, IDK what is a good high-speed rate that works on most boards

// Parsing symbols
#define SERIAL_MESSAGE_OPEN '<'
#define SERIAL_MESSAGE_CLOSE '>'
#define SERIAL_MESSAGE_LINEBREAK false
#define SERIAL_PAIR_SPLIT ':'
#define SERIAL_VALUE_SPLIT '|'
#define SERIAL_FLOAT_DECIMALS 4

// Neuron defaults
#define NEURON_FRAME_TIME 0.02
#define NEURON_NORMAL_DECAY 0.1
#define NEURON_NORMAL_BAND 0.1
#define NEURON_NORMAL_FRAME_SKIP 20

// POL engine (this clas)
#define POL_ENGINE_NUM_OF_NEURONS 20

// Node
#define NODE_INPUT_NEURON_COUNT 2

// SerialNode
#define SERIAL_NODE_CHANNELS 2

// EncoderSensor
#define ENCODERSENSOR_DEFAULT_MODE 0 // need to use a number here because the modes are defined in the class
#define ENCODERSENSOR_RATEOFCHANGE 0.2
#define ENCODERSENSOR_STEPS_PER_REVOLUTION 80


// Includes

// Utilities
#include "Arduino.h"
#include "Toolkit.h"
#include "Timer.h"
#include "Curvinator.h"
#include "RailcarLerp.h"
#include "ScaleMapper.h"
#include "Mixer.h"


// Base types
#include "Neuron.h"
#include "Engine.h"
#include "Sensor.h"
#include "Driver.h"
#include "Node.h"
#include "Generator.h"

// Sensors
#include "AnalogSensor.h"
//#include "DigitalInputSensor.h"
//#include "AccelerometerSensor.h"
//#include "AudioSensor.h"
#include "ButtonSensor.h"
#include "PingSensor.h"
#include "MPUSensor.h"
#include "EncoderSensor.h"

// Drivers
#include "AnalogDriver.h"
#include "MotorDriver.h"
#include "MidiDriver.h"
// #include "ServoDriver.h" // Requires the Servo library. Not implemented due to how the Arduino IDE handles dependencies (it sucks)
#include "StepperDriver.h"
#include "ToneDriver.h"


// Generators
#include "RandomGenerator.h"
#include "ContinuousGenerator.h"
#include "BeatGenerator.h"

// Nodes
#include "LerpNode.h"
#include "EncodedMotorNode.h"
#include "MixNode.h"
#include "SustainNode.h"
#include "CloneNode.h"
#include "CurveNode.h"

//
#include "SerialNode.h"
#include "SerialDriver.h"
#include "SerialSensor.h"

// EOF
