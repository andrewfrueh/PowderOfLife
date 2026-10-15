/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Serial Sensor
  
  ===========================

  Reads from the serial port. Used to create a channel for connecting to Neurons outside of this Arduino context.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */





/*
  Each driver/sensor pair needs to be on the same channel. The driver is the sender, the sensor is the receiver.
  So, you pick a name, and that becomes the name of that channel.
  It is proper broacasting: multiple senders or recievers on the same channel.
*/

// Note: we use the Node superclass (not the Sensor) because we need to set an inputNeuron
class SerialSensor : public Node {
  private:
    byte channelNumber;
    // reference to the SerialNode that will be used for serial communication
    SerialNode* serialNode;
  protected:
  public:
    SerialSensor();
    //
    void work();
    void setSerialNode(SerialNode &newNeuron, byte newChannel); // C++ use Neuron by reference
    SerialNode& getSerialNode();
};


// constructor
SerialSensor::SerialSensor() {
}


void SerialSensor::work() {
  // get updated value from the serial node
  setInternalValue(getSerialNode().getPortData(channelNumber));
}



void SerialSensor::setSerialNode(SerialNode &newNeuron, byte newChannel){
  serialNode = &newNeuron;
  channelNumber = newChannel;
}

SerialNode& SerialSensor::getSerialNode(){
  return *serialNode;
}


// EOF

