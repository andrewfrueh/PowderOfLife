/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Serial Node

  ===========================

  Manages the serial connection (the port).
  SerialSensor and SerialDriver use this node for sending / receiving messages.

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */

// Required for string conversion in C
#include <stdlib.h>
#include <stdio.h>

class SerialNode : public Node
{
private:
  bool serialActive = false;
  unsigned int currentSerialRate;
  float incomingData[SERIAL_NODE_CHANNELS];
  String inputBuffer;
  bool messageIsActive = false;
  String currentMessage;
  byte floatDepth;
  void readSerialData();
  void parseMessage(String newMessage);
  int stringToInt(String text);
  float stringToFloat(String text);
  void writeData(byte channelName, float data);

protected:
  // Overidden
  void wake();

public:
  // constructor
  SerialNode();
  // work
  void work();
  // The serial rate options
  enum serialRate : byte
  {
    debug,
    standard,
    midi
  }; // Kludge, re. "standard", I wanted "default" but it's a keyword or something
  void setSerial(serialRate newRate);
  void setSerial(unsigned int newRate);
  // getters / setters for the sensor and driver
  float getPortData(byte channelName);
  void setPortData(byte channelName, float newValue);
  void setDepth(byte newDepth);
};

SerialNode::SerialNode()
{
  setDepth(SERIAL_FLOAT_DECIMALS);
}

void SerialNode::wake()
{
  if (!serialActive)
  {
    // If not defined, then...
    setSerial(serialRate::debug);
  }
}

void SerialNode::work()
{
  // check for incoming serial data
  readSerialData();
}

void SerialNode::setSerial(serialRate newRate)
{
  //
  switch (newRate)
  {
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

void SerialNode::setSerial(unsigned int newRate)
{
  //
  if (serialActive)
  {
    Serial.end();
  }
  //
  currentSerialRate = newRate;
  //
  Serial.begin(currentSerialRate);
  //
  serialActive = true;
}

void SerialNode::readSerialData()
{

  // Returns the number of bytes available to read.
  int lenTemp = Serial.available();

  if (lenTemp > 0)
  {
    char incomingByte;
    for (int i = 0; i < lenTemp; i++)
    {
      // read the incoming byte:
      incomingByte = Serial.read();

      switch (incomingByte)
      {
      case SERIAL_MESSAGE_OPEN: // open tag
        //
        messageIsActive = true;
        inputBuffer = "";
        break;
      case SERIAL_MESSAGE_CLOSE: // close tag
        //
        if (messageIsActive)
        {
          parseMessage(inputBuffer);
          messageIsActive = false;
        }
        break;
      default: // tag contents?
        if (messageIsActive)
        {
          inputBuffer += incomingByte;
        }
      }
    }
  }
}

void SerialNode::parseMessage(String newMessage)
{
  byte dataName;
  float dataValue;
  int splitIndex;

  splitIndex = newMessage.indexOf(SERIAL_PAIR_SPLIT);
  dataName = (byte)stringToInt(newMessage.substring(0, splitIndex)); // from start up to split
  dataValue = stringToFloat(newMessage.substring(splitIndex + 1));   // from after split to the end

  // store the value in the correct channel (using channel number)
  incomingData[dataName] = dataValue;
}

float SerialNode::getPortData(byte channelName)
{
  return incomingData[channelName];
}

void SerialNode::setPortData(byte channelName, float newValue)
{
  writeData(channelName, newValue);
}

void SerialNode::writeData(byte channelName, float data)
{
  Serial.print(SERIAL_MESSAGE_OPEN);
  Serial.print(channelName);
  Serial.print(SERIAL_PAIR_SPLIT);
  Toolkit::printFloat(data, floatDepth);
  Serial.print(SERIAL_MESSAGE_CLOSE);
  if (SERIAL_MESSAGE_LINEBREAK)
  {
    Serial.println();
  }
}

void SerialNode::setDepth(byte newDepth)
{
  floatDepth = newDepth;
}

// ====================================
// convert from String to int, so the incoming message can be used in math
// TODO, move this to the Neuron. Maybe make a float version.
// ====================================
// taken from -- http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1285085509
// probably needs improvement
int SerialNode::stringToInt(String text)
{
  char temp[20];
  text.toCharArray(temp, 19);
  int x = atoi(temp);
  if (x == 0 && text != "0")
  {
    x = -1;
  }
  return x;
}

// by extension from above
float SerialNode::stringToFloat(String text)
{
  char temp[20];
  char *p;
  text.toCharArray(temp, 19);
  // fgets (temp,256,stdin);
  // float x = atof(temp); // text or temp?
  float x = strtod(temp, &p);

  /*
    if (x == 0 && text != "0")
    {
      x = -1;
    }
  */

  return x;
}

// EOF
