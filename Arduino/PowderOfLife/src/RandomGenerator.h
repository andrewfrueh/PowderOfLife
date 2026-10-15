/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Random Generator
  
  ===========================

  TODO
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */




#define RANDOM_FLOAT_PRECISION 1000
#define RANDOMGENERATOR_DEFAULT_DOWN_VALUE 0.0
#define RANDOMGENERATOR_DEFAULT_UP_VALUE 1.0

#define RANDOMGENERATOR_DEFAULT_MIN 0.0
#define RANDOMGENERATOR_DEFAULT_MAX 1.0

class RandomGenerator : public Generator {
  private:
    Timer stateChangeTimer;
    float randomUpTimeMin = 0;
    float randomUpTimeMax = 1;
    float randomDownTimeMin = 0;
    float randomDownTimeMax = 0;
    bool randomState = false;
  public:
    RandomGenerator();
    void work();
    float getRandomValue();
    float randomFloat(float randMin, float randMax);
    void setRandomRates(float newUpMin, float newUpMax, float newDownMin, float newDownMax);
};


RandomGenerator::RandomGenerator() {
  //
  stateChangeTimer.setRate(randomDownTimeMin);
  stateChangeTimer.reset();
}


void RandomGenerator::work() {
  //
  if (stateChangeTimer.interval()) {
    //
    if (randomState) { // Going up
      // Set the value
      setInternalValue(getRandomValue());
      // Set the timer rate
      stateChangeTimer.setRate(randomFloat(randomUpTimeMin, randomUpTimeMax));
      // switch states
      //randomState = false;
    } else { // Going down
      // Get a random value
      float r = randomFloat(randomDownTimeMin, randomDownTimeMax);
      // check for zero, don't bother to set value if time is zero else we get a pop down
      if (r != 0) {
        setInternalValue(RANDOMGENERATOR_DEFAULT_DOWN_VALUE);
      }
      // Set the timer rate
      stateChangeTimer.setRate(r);
    }
    // switch states
    randomState = !randomState;
  }
}



float RandomGenerator::getRandomValue() {
  return randomFloat(RANDOMGENERATOR_DEFAULT_MIN, RANDOMGENERATOR_DEFAULT_MAX);
}



float RandomGenerator::randomFloat(float randMin, float randMax) {
  //
  return Toolkit::mapf(float(random(0, RANDOM_FLOAT_PRECISION)), 0, float(RANDOM_FLOAT_PRECISION), randMin, randMax);
}

void RandomGenerator::setRandomRates(float newUpMin, float newUpMax = -1, float newDownMin = -1, float newDownMax = -1) {
  randomUpTimeMin = newUpMin;
  randomUpTimeMax = newUpMax == -1 ? newUpMin : newUpMax;
  randomDownTimeMin = newDownMin == -1 ? newUpMin : newDownMin;
  randomDownTimeMax = newDownMax == -1 ? newUpMax : newDownMax;
}


// EOF
