/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Ping Sensor
  
  ===========================

  Designed to interface with standard ultrasonic distance sensors (AKA "ping" sensors). 
  These sensors emit ultrasonic pulses and measure the time it takes for the echo to return.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */



// *#*#*#*#*#*#
// TODO!
//  - Decide what the value should be depending on validity (defalut, or stay the same?)
//    see recordDistance()
//    - modes: hold, low, mid, high
//  - Explain the weird behavoir of the distance sensor in the header (need to check validity)


class PingSensor : public Sensor {
  private:
    byte triggerPin;
    byte echoPin;
    //
    unsigned long pingTime = 0;
    unsigned long echoTime = 0;
    int maxEchoDistance;
    //
    int distance = -1;
    //
    bool pulseIsActive = false;
    bool echoIsActive = false;
    //
    unsigned long microsecondsToInches(unsigned long microseconds);
    unsigned long microsecondsToCentimeters(unsigned long microseconds);
    void recordDistance();
  protected:
  public:
    PingSensor();
    // Overidden
    void wake();
    void work();
    void workFast();
    void setPin(int newTriggerPin, int newEchoPin);
    //
    void sendPing();
    void checkEcho();
    void setMax(int newMax);
};

PingSensor::PingSensor() {
  // setNormal(Neuron::normalMode::automatic, Neuron::normalClip::clip, 1, 2, 10);
  setNormal(Neuron::normalMode::custom, Neuron::normalClip::clip, 0, 200);
  setFrameTime(0.2);
  setMax(600);
}

void PingSensor::wake() {
}

void PingSensor::workFast() {
  checkEcho();
}

void PingSensor::work() {
  sendPing();
}

void PingSensor::setPin(int newTriggerPin, int newEchoPin) {
  triggerPin = newTriggerPin;
  echoPin = newEchoPin;
  pinMode(triggerPin, OUTPUT); // digital
  pinMode(echoPin, INPUT); // analog
}

/*
  void PingSensor::setPin(int newPin1, int newPin2, bool newPullup=false) {
  triggerPin = newPin1;
  echoPin = newPin2;
  pinMode(triggerPin, newPullup?INPUT_PULLUP:INPUT);
  pinMode(echoPin, newPullup?INPUT_PULLUP:INPUT);
  }

*/

// ===========
void PingSensor::sendPing() {
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  //
  pingTime = micros();
  echoTime = 0;
  pulseIsActive = true;
  echoIsActive = false;

}


void PingSensor::checkEcho() {
  if ( pulseIsActive == true ) {
    if ( digitalRead(echoPin) == HIGH && echoIsActive == false) {
      echoIsActive = true;
      echoTime = micros();
    } else if (digitalRead(echoPin) == LOW && echoIsActive == true) {
      echoIsActive = false;
      echoTime = micros() - echoTime;
      pulseIsActive = false;
      //
      recordDistance();
    }
  }
}


void PingSensor::recordDistance() {
  distance = microsecondsToCentimeters(echoTime);
  if (distance < maxEchoDistance) {
    // value is valid
    //setValueIsValid(true);
    // use the value
    setInternalValue(distance);
  } else {
    // value is not valid
    //setValueIsValid(false);
    // use the value, BUT it will be overwritten due to "invalid"
    setInternalValue(getInvalidValue());
  }
}

void PingSensor::setMax(int newMax) {
  maxEchoDistance = newMax;
}




/*
  if (valueIsValid) {
    return value;
  } else {
    // Value is NOT valid... decide what to do
    switch (getInvalid()) {
      case invalidMode::hold:
        // use value... it should not have changed due to invalid
        return value;
        break;
      case invalidMode::min:
        // use normal min
        return POL_NORMALIZE_MIN; // getNormalMin();
        break;
      case invalidMode::mid:
        // use normal mid
        return POL_NORMALIZE_MIN + ((POL_NORMALIZE_MAX - POL_NORMALIZE_MIN) / 2); // getNormalMid();
        break;
      case invalidMode::max:
        // use normal max
        return POL_NORMALIZE_MAX; // getNormalMax();
        break;
    }
  }

*/


// From the Arduino internal example for "ping"

unsigned long PingSensor::microsecondsToInches(unsigned long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

unsigned long PingSensor::microsecondsToCentimeters(unsigned long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
