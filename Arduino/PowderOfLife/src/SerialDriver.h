/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Serial Driver
  
  ===========================

  Writes to the serial port. Used to create a channel for connecting to Neurons outside of this Arduino context.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */




class SerialDriver : public Driver {
  private:
    byte channelNumber;
    // reference to the SerialNode that will be used for serial communication
    SerialNode* serialNode;
  public:
    SerialDriver();
    void work();
    void setSerialNode(SerialNode &newNeuron, byte newChannel); // C++ use Neuron by reference
    SerialNode& getSerialNode();
    // void setName(String newName);
};


// constructor
SerialDriver::SerialDriver() {
  setFrameTime(0.03);
  setNormal(normalMode::none);
}


void SerialDriver::work(){
  //updateInput();
  // Only update if different
  if( getInput().getValue() != getValue() ){
    // set my own value
    setInternalValue(getInput().getValue());
    // send my value out via the serial node
    getSerialNode().setPortData(channelNumber, getValue());
  }
  //
}

void SerialDriver::setSerialNode(SerialNode &newNeuron, byte newChannel){
  serialNode = &newNeuron;
  channelNumber = newChannel;
}

SerialNode& SerialDriver::getSerialNode(){
  return *serialNode;
}

// EOF
