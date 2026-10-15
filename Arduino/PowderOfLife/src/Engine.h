/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Engine
  
  ===========================

  The Engine is necessary in the Arduino environment as there is no system-level event-manager. It registers and initializes neurons and manages the main update loop so that all neurons are updated. Any neuron that is not registered with the Engine will need to be updated manually.

  One Engine should be instantiated per script.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2026
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */


/*
  TODO
    x add a "ground input" or "disable input" feature
      - will short to ground using the following in setup:
        pinMode(A1, OUTPUT);
        digitalWrite(A1, LOW);
    
    - automate the above groud disable feature so it's done on startup
      - and then each neuron that needs an analog input will get it when they register with the engine

*/


class Engine {
private:
  //
  Neuron *inputNeurons[POL_ENGINE_NUM_OF_NEURONS];
  //
  byte nextNewNeuron = 0;
  bool engineActive = false;
  // unsigned int currentSerialRate;
  // bool serialActive = false;
public:
  // constructor
  Engine();
  //
  void start();
  void update();
  /*
  The serial rate options
  enum serialRate : byte { debug,
                           standard,
                           midi };  // Kludge, I wanted "default" but it's a keyword or something
  */
  // stolen from the old Neuron class (hence "input neuron")
  void setNeuron(Neuron &newNeuron, int index);
  void addNeuron(Neuron &newNeuron);
  Neuron &getNeuron(int index);
  bool hasNeuron(int index);
  byte countNeurons();
  // void setSerial(serialRate newRate);
  // void setSerial(unsigned int newRate);
  void groundAnalogInput(int newPin);
};

// constructor
Engine::Engine() {
  // Note: cannot start the serial in constructor, see start()
}



void Engine::start() {

/*   Serial was not setup, so do it
  if (!serialActive) {
    // If not defined, the
    setSerial(serialRate::debug);
  }
 */
  for (byte i = 0; i < countNeurons(); i++) {
    // update the current component
    inputNeurons[i]->start();
  }
  //
  engineActive = true;
}


void Engine::update() {

  // Engine was not started, so do it
  if (!engineActive) {
    start();
  }
  // Here we will update all registered components
  for (byte i = 0; i < countNeurons(); i++) {
    // update the current component
    inputNeurons[i]->update();
  }
}
// You can also work this...
//Neuron n;
//n = *inputNeurons[i];
//n.update();



void Engine::setNeuron(Neuron &newNeuron, int index = 0) {
  //
  inputNeurons[index] = &newNeuron;
}

void Engine::addNeuron(Neuron &newNeuron) {
  // check to see if the "last neuron" is null, else increment the index
  //byte index = (inputNeurons[nextNewNeuron] ==  NULL) ? nextNewNeuron : nextNewNeuron + 1;
  if (&newNeuron != NULL) {
    inputNeurons[nextNewNeuron] = &newNeuron;
    nextNewNeuron++;
  }
}

Neuron &Engine::getNeuron(int index = 0) {
  return *inputNeurons[index];
}

bool Engine::hasNeuron(int index = 0) {

  if (inputNeurons[index] == NULL) {
    return false;
  } else {
    return true;
  }
}

byte Engine::countNeurons() {
  return nextNewNeuron;
}

/*
void Engine::setSerial(serialRate newRate) {
  //
  switch (newRate) {
    case serialRate::debug:
      currentSerialRate = SERIAL_BAUD_RATE_DEBUG;
      break;
    case serialRate::standard:
      currentSerialRate = SERIAL_BAUD_RATE_DEFAULT;
      break;
    case serialRate::midi:
      currentSerialRate = SERIAL_BAUD_RATE_MIDI;
      break;
  }
  //
  setSerial(currentSerialRate);

}

void Engine::setSerial(unsigned int newRate) {
  //
  Serial.end();
  //
  currentSerialRate = newRate;
  //
  Serial.begin(currentSerialRate);
  //
  serialActive = true;
}

*/

void Engine::groundAnalogInput(int newPin) {
  pinMode(newPin + ANALOG_PIN_NUMBER_OFFSET, OUTPUT);
  digitalWrite(newPin + ANALOG_PIN_NUMBER_OFFSET, LOW);
}


// EOF
