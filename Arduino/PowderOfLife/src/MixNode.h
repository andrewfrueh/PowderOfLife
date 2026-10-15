/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Mix Node
  
  ===========================

  The MixNode is a wrapper for the Mixer class. 
  Use it in your network to blend the signals of two neurons to create a mixed output.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2026
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */



class MixNode : public Node {
  private:
    //Neuron* inputNeuronB; // second input neuron
    byte mixMode;
  protected:
    float frameTime = 0.001;
  public:
    MixNode();
    //
    void work();
    void setMode(Mixer::mode newMode);
};


// constructor
MixNode::MixNode() {
  //
  setNormal(Neuron::normalMode::none);
  //
  setMode(Mixer::mode::average);
}

void MixNode::work() {
  // Need to fix input to handle multiple refs. first
  setInternalValue( Mixer::Mix( getInput(0).getValue(), getInput(1).getValue(), static_cast<Mixer::mode>(mixMode) ) );
}



void MixNode::setMode(Mixer::mode newMode) {
  mixMode = newMode;
}

//
