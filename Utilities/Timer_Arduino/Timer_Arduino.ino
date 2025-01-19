
#include "Timer.h"

Timer seconds;
Timer outOfPhase;

char ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);

  // Each of these is the same
  seconds.setRate(1.0);
  //seconds.setRateMillis(1000);
  //seconds.setRateMicros(1000000);

  outOfPhase.setRate(1.0);
  

}

void loop() {
  
  if (seconds.interval()) {
    Serial.print(seconds.getCycles());
    Serial.print(" : ");
    Serial.print(seconds.getCycles()%2?"HIGH":"LOW");
    Serial.println();
    digitalWrite(ledPin,seconds.getCycles()%2?HIGH:LOW);
  }
  
}
