/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Node

  ===========================

  The Node class is a second-level super-class for all Node sub-classes (e.g. MixNode).
  The Node class is not meant to be instantiated directly. 

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

  ==================================================================================================== */



class Node : public Neuron {
  protected:
    // ===================
    // reference to the input neuron
    Neuron* inputNeuron[NODE_INPUT_NEURON_COUNT];
    // ===================
  public:
    Node();
    // ===================
    // Input neuron
    void setInput(Neuron &newNeuron, byte index = 0); // C++ use Neuron by reference
    Neuron& getInput(byte index = 0); // C++ use Neuron by reference
    bool hasInput(byte index = 0);
    void updateInput();
    void setValue(float newValue);

};

// Constructor
Node::Node() {
}



// ==================================================================
// Input neuron


// C++ use Neuron by reference
void Node::setInput(Neuron &newNeuron, byte index) {
  inputNeuron[index] = &newNeuron;
}

// C++ use Neuron by reference
Neuron& Node::getInput(byte index) {
  return *inputNeuron[index];
}

bool Node::hasInput(byte index) {
  return (inputNeuron[index] != NULL) ? true : false;
}

void Node::updateInput(){
  if (hasInput()) {
    // Grab the value from the input
    setValue(getInput().getValue());
  }
}

void Node::setValue(float newValue) {
  setInternalValue(newValue);
}


// EOF
