/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Railcar Lerp
  
  ===========================

  RailcarLerp will provide smooth output with changing input. It is essentially
  a very simple physics-engine. It uses a current position affected by velocity
  and acceleration to provide a smooth output, with inertial damping.
  You have control over three values:
    acceleration: is the default that will be used for speeding up, and slowing
      down when there is sufficient difference to work so
    speed: the fastest (greatest) rate of change allowed
    target: what the output seeks to achieve

  Here are the maths for calculating acceleration (a), and breaking distance (b)
    a = (v^2) / (2d+v) [where 2d+v!=0, and v!=0]
    b = ((v/a)-1) * (v/2) [where a!=0]

  Currently, I'm using this crappy math for applying velocity to position (not correct, but a good approximation)
    p = 2vt
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */



// Includes
#include "Arduino.h"

// Class wrapper
class RailcarLerp {
  private:
    float acceleration;
    float velocity;
    float position;
    float target;
    float difference;
    float maxSpeed;
    float defaultAcceleration;
  public:
    // constructor
    RailcarLerp();
    //
    void update(float deltaTime);
    void setTarget(float newTarget);
    float getTarget();
    void setSpeed(float newSpeed);
    void setAcceleration(float newAcceleration);
    float getSpeed();
    float getAcceleration();
    void setVelocity(float newVelocity);
    float getVelocity();
    float getValue();
    void setValue(float newPosition);
    int getSign(float input);
};

// Constructor
RailcarLerp::RailcarLerp() {
  acceleration = 0;
  velocity = 0;
  position = 0;
  target = 0;
  difference = 0;
  // Default setup
  setSpeed(1);
  setAcceleration(1);
}

// process one frame
void RailcarLerp::update(float deltaTime = 1) {

  // Calculate the difference between current position and target
  difference = target - position;



/*
  // If we are close to target, zero out
  if (
    difference == 0 ||
    abs(difference) < (defaultAcceleration * deltaTime) ||
    abs(difference) < abs(velocity)*deltaTime) {
    // zero everything out
    velocity = 0;
    acceleration = 0;
    position = target;
    return;
  }
*/
/*
  // If we are close to target, zero out
  if (
    abs(difference) < (defaultAcceleration * deltaTime) ||
    abs(difference) < abs(velocity)*deltaTime) {
    // zero everything out
    difference = 0;
    //velocity = 0;
    acceleration = 0;
    position = target;
  }
*/

  // Otherwise, calculate the lerping
  if ( (difference < 0) == (velocity < 0) ) { // check if the signs are different ( (x<0) == (y<0) )
    // Signs are the same. We're headed the correct direction

    // Calculate some local variables for the logic gate below
    float s = abs(velocity);
    float d = abs(difference);
      d = Curvinator::curve(d, 2, Curvinator::mode::inOut);
    float b = pow(s, 2) / (defaultAcceleration * 2); // b is the breaking distance


    // breaking distance?
    if ( d < b ) {
      // Calculate the needed breaking acceleration, acceleration needs to be opposite sign of velocity
      float breakAcceleration = pow(s, 2) / ((2 * d) + s); // always positive, [where 2d+v!=0, and v!=0]
      // Set the acceleration
      acceleration = max( defaultAcceleration, breakAcceleration ) * (getSign(velocity) * -1);
    } else {
      // Not time to break. Keep accelerating.
      // use default acceleration with same sign as difference (in this case, same as velocity)
      acceleration = getSign(difference) * defaultAcceleration;
    }
    

  } else {
    // Signs are different. We're headed the opposite direction
    // Use default acceleration with same sign as difference (in this case, opposite of velocity)
    acceleration = getSign(difference) * defaultAcceleration;
  }

  // use delta to adjust acceleration
  velocity += acceleration * deltaTime;

  // Gate (constrain) the speed to within the maximum
  velocity = Toolkit::constrainf( velocity, -maxSpeed, maxSpeed );

  // use delta to adjust position
  position = position + (velocity * deltaTime) + ( (acceleration * pow(deltaTime, 2)) / 2 );

}

void RailcarLerp::setTarget(float newTarget) {
  target = newTarget;
}

float RailcarLerp::getTarget() {
  return target;
}


void RailcarLerp::setSpeed(float newSpeed) {
  maxSpeed = newSpeed;
}

void RailcarLerp::setAcceleration(float newAcceleration){
  defaultAcceleration = newAcceleration;
}

float RailcarLerp::getSpeed() {
  return maxSpeed;
}

float RailcarLerp::getAcceleration() {
  return acceleration;
}

float RailcarLerp::getVelocity(){
  return velocity;
}

void RailcarLerp::setVelocity(float newVelocity){
  velocity = newVelocity;
}

float RailcarLerp::getValue() {
  return position;
}

void RailcarLerp::setValue(float newPosition) {
  position = newPosition;
}

int RailcarLerp::getSign( float input ) {
  if ( input < 0 ) return -1;
  if ( input > 0 ) return 1;
  return 0;
}
