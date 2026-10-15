/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Clone Node
  
  ===========================

  The primary function of the `CloneNode` is to receive an input value from another neuron in the network and replicate that value as its output. The `CloneNode` allows for the output of one neuron to be directed to multiple destinations within the network. This is crucial for scenarios where the same signal needs to influence different processing paths or control multiple outputs simultaneously. 
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */


class CloneNode : public Node {
  private:
  public:
    CloneNode();
    void work();
    void setValue(float newValue);
};

CloneNode::CloneNode(){
  setNormal(normalMode::none);
}

void CloneNode::work() {

  updateInput();
    
  // simply clone the input
  //setInternalValue(getInput().getValue());
  // also transfer invalid?
  //setInvalid(getInput().getInvalid());
}

void CloneNode::setValue(float newValue) {
  setInternalValue(newValue);
}


// EOF
