/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Driver
  
  ===========================

  The Driver class is a second-level super-class for all Driver sub-classes (e.g AnalogDriver).
  The Driver class is not meant to be instantiated directly. 

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */



class Driver : public Neuron{
  protected:
    Neuron* inputNeuron; // A pointer to the Neuron that provides input to this Driver
  public:
    Driver(); // Constructor for the Driver class
    // ===================
    // Input neuron
    void setInput(Neuron &newNeuron); // Takes a reference to the input Neuron as an argument
    Neuron& getInput(); // Returns a reference to the connected input Neuron
    bool hasInput(); // Checks if the Driver has a connected input Neuron
    void updateInput(); // Fetches the value from the connected input Neuron
    void setValue(float newValue); // Sets the Driver's internal value directly.
};

// Constructor
Driver::Driver(){
}

// Assigns the address of the input Neuron to the inputNeuron pointer
//    Note: C++ uses Neuron by reference
void Driver::setInput(Neuron &newNeuron) {
  inputNeuron = &newNeuron;
}

// Returns a reference to the connected input Neuron (pointer)
Neuron& Driver::getInput() {
  return *inputNeuron;
}

// Checks if the inputNeuron pointer is not NULL
bool Driver::hasInput() {
  return (inputNeuron != NULL) ? true : false;
}

// If the Driver has a connected input Neuron:
// - Fetches the value from the input Neuron using getInput().getValue()
// - Sets the Driver's own internal value using setValue()
void Driver::updateInput(){
  if (hasInput()) {
    // Grab the value from the input
    setValue(getInput().getValue());
  }
}

// Sets the Driver's internal value 
void Driver::setValue(float newValue) {
  setInternalValue(newValue);
}


// EOF
