/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Timer
  
  ===========================

	This Timer class allows you to create simple timers.
	A common implementation is to us an if() to check interval(). This conditional construction allows
	you to create parallel threads -- also called protothreads, coroutines, or concurrency. This
	allows you to lower load on the CPU by spreading out tasks at a lower clock rate.
	Additionally, you can use getRatio() to achieve a simple linear lerp.

	To update the timer, you must call one of the following: interval() or timeout()
	interval() is for a repeating item. It calls reset().
	timeout() is for one-time events. It does not call reset().

	Public methods:
		interval() -- Use for repeating events. Returns false until triggered, then returns true only once, then auto-resets to false when read.
		timeout() -- Use for single-run (terminal) events. Returns false until triggered, then returns true until reset.
		reset() -- Resets the timer to zero. Cycle count is maintained.
		setRate() -- Use any unit system to set the duration of the timer. Returns nothing.
		getRate() -- Returns the current rate of the timer.
		getCycles() -- Returns how many cycles have passed since the timer was started.
		getElapsed() -- Returns (UNIT) passed since timer started (or last reset)
		getRemaining() -- Returns (UNIT) until the timer will trigger
		getRatio() -- Returns float 0-1 representing how long until the next trigger time
		getDelta() -- Returns float representing how many seconds have passed since last frame (the actual frame rate)

  Notes on efficiency:
  - int (and unsigned int 0 to 65,535) are 2 bytes (16 bits)
  - long (and unsigned long 0 to 4,294,967,295) are 4 bytes (32 bits)
  - float is 4 bytes (32 bits) and not precise

  Notes on time units:
  - all times are handles internally with unsigned long (4,294,967,295)
  - that max (rate cannot be greater than this) translates to:
    - millis: 50 days
    - micros: 72 minutes
    
  Notes on constraints:
  - The "last" must be the same size or larger than the "counter"
  - The "interval" must be the same size or smaller than "counter"
  - We can only hold one old "last" value while the "counter" rolls over (overflow)
    - ... and that old "last" value will be used to calculate the new rolled-over "last"
  - It would be possible to construct a system that handles more complex overflow problems (... for another time)
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */




#define TIMER_SECOND_TO_MILLIS 1000
#define TIMER_MINUTE_TO_MILLIS 60000
#define TIMER_HOUR_TO_MILLIS 3600000
#define TIMER_DAY_TO_MILLIS 86400000
#define TIMER_SECONDS_TO_MICROS 1000000
#define TIMER_OVERFLOW_SIZE 4294967295
// unsigned long: 0 to 4294967295

// You must include the Arduino class.
#include "Arduino.h"


class Timer {
  private:
    //
    unsigned long lastTime; 
    unsigned long rate; // the rate, can be millis or micros depending on unit
    unsigned int cycles;
    unsigned long deltaTime; 
    unsigned long calculateTimeDifference();
    // unsigned long phase; // cost = 8 bytes
    byte unit;
  public:
    Timer();
    // enum
    enum units : byte { millisecond, microsecond };
    void setRate(float newRate);
    void setRateMillis(unsigned long newRate);
    void setRateMicros(unsigned long newRate);
    float getRate(); // Kludge, this possibly returns false values
    unsigned long getCycles();
    unsigned long getRemaining();
    float getElapsed();
    float getRatio();
    boolean interval();
    boolean timeout();
    void reset();
    boolean checkTime();
    String zeros(int num);
    float getDelta();
    void setUnit(units newUnit);
    Timer::units getUnit();
    unsigned long getUnitMultiplier();
    unsigned long getTime();
};


// Constructor
Timer::Timer() {
  setUnit(units::millisecond);
  lastTime = getTime();
  setRate(1.0f);
}

// TODO, add unit
void Timer::setRate(float newRate) {
  rate = newRate * getUnitMultiplier();
}

void Timer::setRateMillis(unsigned long newRate) {
  // set the unit
  setUnit(units::millisecond);
  rate = newRate;
}

void Timer::setRateMicros(unsigned long newRate) {
  // set the unit
  setUnit(units::microsecond);
  rate = newRate;
}

// TODO, add unit
float Timer::getRate() {
  return (float)rate/(float)getUnitMultiplier();
}


unsigned long Timer::getCycles() {
  return cycles;
}

// TODO, add unit
float Timer::getElapsed() {
  return (float)calculateTimeDifference() / (float)getUnitMultiplier();
}

// TODO, add unit
unsigned long Timer::getRemaining() {
  return rate - calculateTimeDifference();
}


// Returns ratio, between 0-1.
float Timer::getRatio() {
  return (float)calculateTimeDifference() / (float)rate;
}


boolean Timer::interval() {
  if ( checkTime() ) {
    reset();
    return true;
  }
  else {
    return false;
  }
}

boolean Timer::timeout() {
  if ( checkTime() ) {
    // no reset for timeout
    return true;
  }
  else {
    return false;
  }
}

// TODO, add unit
void Timer::reset() {
  // calculate the delta
  deltaTime = calculateTimeDifference();
  // record last time
  lastTime = getTime();
  // increment the cycle
  cycles += 1;
}

// TODO, add unit
// TODO, add overflow
// This method is essentially the update for the Timer
boolean Timer::checkTime() {
  //
  if ( calculateTimeDifference() >= rate ) {
    return true;
  } else {
    return false;
  }
}

// TODO, add unit
// TODO, add overflow fix here
unsigned long Timer::calculateTimeDifference() {
  //return (getTime() - lastTime); // was just this
  if (getTime() < lastTime) {
    // overflow state, use the max to calculate the offset from zero
    return (getTime() + (TIMER_OVERFLOW_SIZE - lastTime) + 1);
  } else {
    // default state, simple difference will do
    return (getTime() - lastTime);
  }
}


// Delta is the actual time the last frame took, in seconds
float Timer::getDelta() {
  return (float)deltaTime / (float)getUnitMultiplier();
}

void Timer::setUnit(units newUnit) {
  unit = newUnit;
}

Timer::units Timer::getUnit() {
  return unit;
}

unsigned long Timer::getUnitMultiplier() {
  return unit == units::millisecond ? TIMER_SECOND_TO_MILLIS : TIMER_SECONDS_TO_MICROS;
}

unsigned long Timer::getTime(){
  return unit == units::millisecond ? millis() : micros();
}


// =====================================

// Utility function to add leading zeros
String Timer::zeros(int num) {
  String output = "";
  if (num < 10) {
    output += "0";
  }
  output += num;
  return output;
}
