# POL Arduino API

## Index
- [Sensors](#sensors)
    - [AnalogSensor](#analogsensor)
- [Drivers](#drivers)
- [Nodes](#nodes)
- [Generators](#generators)


========================================================================
Created using Notebook LM. Fed it the Arduino library (converted to ".txt" with Python)

## Drivers

### AnalogDriver
This class controls an analog output pin (PWM).

#### `void work() `
Maps the input value to the analog output range, constrains it to avoid overflow, and then writes the value to the output pin.

#### `void setPin(int newPin) `
Sets the analog output pin and configures it as an output.

### MotorDriver
This class controls a DC motor connected to a motor driver board.

#### `void work() `
Updates the input value, determines the direction based on the input value and reverse setting, maps the absolute input value to the output speed range, constrains the speed, and then writes the direction and speed to the corresponding output pins.

#### `void setPin(int newDirPin, int newSpeedPin) `
Sets the direction and speed pins for the motor driver and configures them as outputs.

#### `void setRange(byte newMin, byte newMax) `
Sets the minimum and maximum values for the motor speed output range.

#### `void setReverse(bool newRev) `
Sets whether the motor direction should be reversed.

#### `void setCenter(float newCenter) `
Sets the center point of the input range for controlling the motor.

### MidiDriver
This class sends MIDI messages over the serial port. 

#### `void work() `
This method currently does nothing.

#### `void wake() `
Sets the base note to 60.

#### `void setBase(float newBase) `
Sets the base MIDI note.

#### `void playNote(byte note, byte velocity = 100, byte channel = 1, bool playStop = true) `
Sends a MIDI note on/off message.

#### `void stopNote(byte note, byte channel = 1) `
Sends a MIDI note off message.

#### `void sendClock() `
Sends a MIDI clock message.

#### `void allNotesOff() `
Sends a MIDI all notes off message.

### ServoDriver
 This class controls a servo motor.

#### `void work() `
Sets the internal value to the input value, maps the input value to the servo's output range, constrains the position, and then writes the position to the servo.

#### `void setPin(int newPin) `
Sets the output pin for the servo and attaches the servo object to the pin.

#### `void setRange(byte newMin, byte newMax) `
Sets the minimum and maximum values for the servo's output range.

### StepperDriver
This class controls a stepper motor connected to a stepper motor driver board.

#### `void workFast() `
Checks if it's time to step the motor and, if so, steps the motor based on the selected mode.

#### `void work() `
Updates the input value and then, based on the selected mode, calculates either the target position or the motor speed.

#### `void setMicrostep(microsteps newStep) `
Sets the microstepping resolution for the stepper motor.

#### `void setMode(modes newMode) `
Sets the mode of the stepper motor driver.

#### `void stepOnce(int dir = 1) `
Increments the current step count, sets the direction pin based on the input direction, sets the step pin high, delays for a minimum pulse duration, sets the step pin low, and then delays again for a minimum pulse duration.

#### `void setPin(int newDirPin, int newStepPin) `
Sets the direction and step pins for the stepper motor driver and configures them as outputs.

### ToneDriver
This class controls the frequency of a tone output.

#### `void workFast() `
If the tone mode is set to hardware, toggles the output state of the tone pin at a specific interval determined by the `waveFormTimer`.

#### `void work() `
Updates the input value, maps the input value to the desired frequency range based on the selected scale and mapping, and then either starts or stops the tone depending on the `toneActive` flag.

#### `void setPin(int newPin) `
Sets the output pin for the tone and configures it as an output.

#### `void softToneOn(float newTone) `
Calculates the timer interval for the desired tone frequency and starts the hardware tone generation.

#### `void softToneOff() `
Stops the hardware tone generation.

#### `void setTonic(float newTonic) `
Sets the base frequency for the tone generator.

#### `void setScale(byte newScale) `
Sets the musical scale used for mapping input values to frequencies.

#### `void setMode(byte newMode) `
Sets the mode of the tone driver to either hardware or software.

#### `modes getMode() `
Returns the current mode of the tone driver.

#### `float getTone() `
Returns the current tone frequency.

#### `float getRate() `
Returns the rate of the `waveFormTimer`.

#### `void start() `
Activates the tone output.

#### `void stop() `
Deactivates the tone output.

#### `void stopAllTones() `
Stops both the hardware and software tone generation.

#### `void octaves(byte newOctaves) `
Sets the octave multiplier for the tone generator.

## Generators

### BeatGenerator 
This class generates a rhythmic beat signal with a specified tempo and decay.

#### `void work() `
Updates the internal value based on the selected output mode. If the `useRamp` flag is true, the output will be a ramp wave. If the `useRamp` flag is false, the output will be a beat with a specified decay.

#### `void setTempo(float newTempo) `
Sets the tempo (in beats per minute) and updates the decay time if necessary.

#### `float getTempo() `
Returns the current tempo in beats per minute.

#### `void setDecay(float newDecay, decayMode newMode = decayMode::ratio) `
Sets the decay of the beat signal. If the decay mode is set to `ratio` the decay will be a ratio of the beat duration. If the decay mode is set to `time`, the decay will be a fixed duration in seconds.

#### `float getDecay() `
Returns the decay time in seconds.

#### `void updateDecayTime() `
Updates the decay time based on the selected decay mode.

#### `float getRampRatio() `
Returns a value between 0.0 and 1.0 representing the current position within the ramp cycle.

#### `void setRamp(bool newRamp) `
Sets whether to use a ramp wave instead of a beat signal.

#### `void setSubdivisions(byte newSubDiv) `
Sets the number of subdivisions within each beat.

#### `byte getSubdivisions() `
Returns the number of subdivisions within each beat.

#### `void clickBeat() `
Increments the internal beat counter.

#### `byte getBeat() `
Returns the current beat number within the bar (starting from 1).

#### `void updateBeat() `
Updates the internal value of the node based on the beat state and decay time.

#### `bool getState() `
Returns the current state of the beat (true = on, false = off).

#### `float getRatio() `
Returns the ratio of the current beat to the total number of subdivisions.

#### `bool getClick() `
Returns `true` if it is the start of a new beat.

### ContinuousGenerator 
This class generates a continuous signal (always on).

#### `ContinuousGenerator() `
Constructor for the `ContinuousGenerator` class. Does nothing.

### RandomGenerator 
This class generates random values with a specified rate of change.

#### `void work() `
Generates a new random value and sets the internal value based on the state of the `stateChangeTimer`.

#### `float getRandomValue() `
Returns a random floating-point value between the configured minimum and maximum values.

#### `float randomFloat(float randMin, float randMax) `
Generates a random float value between `randMin` and `randMax`.

#### `void setRandomRates(float newUpMin, float newUpMax = -1, float newDownMin = -1, float newDownMax = -1) `
Sets the minimum and maximum duration (in seconds) for both the up and down states of the random generator. 

## Sensors

### AnalogSensor
This class reads data from the analog input pin.

#### `void workFast() `
Reads the raw analog input from the specified pin and stores it in the `rawInput` variable.

#### `void work() `
Sets the `internalValue` of the sensor to the value read from the analog input pin.

#### `void setPin(int newPin) `
Sets the analog input pin.

#### `void setCenter(int newCenter) `
Sets a center point for the sensor's input range by casting the input to an integer.

#### `void setCenter(float newCenter) `
Sets the center point for the sensor's input range.

### ButtonSensor
This class reads the state of a button.

#### `void workFast() `
Reads the button state from the specified pin and stores it in the `rawInput` variable.

#### `void work() `
If the button state has changed, the `internalValue` of the sensor is updated.

#### `void setPin(int newPin, bool newPullup=true) `
Configures a digital input pin for reading a button's state.

#### `void setToggle(bool newToggle) `
Sets whether the button should act as a momentary switch or a toggle.

### EncoderSensor
 This class uses quadrature encoding to track the rotation of an encoder.

#### `void workFast() `
Reads the states of the encoder pins, converts them into a quadrature state, and then processes the state.

#### `void work() `
Based on the selected encoder mode, it updates the sensor's `internalValue` to reflect either the current encoder position or the rate of change in position.

#### `void setPin(int newPin1, int newPin2, bool newPullup = true) `
Sets the Arduino pins for the two signal pins on the encoder.

#### `void setMode(modes newMode) `
Sets the operational mode of the encoder sensor, defining how it interprets the encoder's signals.

#### `void setReverse(bool newState) `
Sets whether the direction of the encoder should be reversed.

#### `void setSteps(int newSteps) `
Configures the number of steps the encoder takes to complete one full revolution.

#### `int getSteps() `
Returns the number of steps per revolution.

#### `long getCurrentStep() `
Returns the current encoder step count.

#### `void setRate(float newRate) `
Sets the rate at which the encoder sensor's output is updated.

### MPUSensor
 This class uses I2C communication to read data from an MPU-6050 accelerometer/gyroscope sensor. 

#### `void wake() `
Initializes the Wire library, starts communication with the MPU-6050, and then sends a command to wake up the sensor.

#### `void workFast() `
Placeholder method, does nothing.

#### `void work() `
Reads the raw accelerometer, temperature, and gyroscope data from the MPU-6050 and stores it in the array `mpuData`.

#### `void setMode(modes newMode) `
Sets the mode for the sensor to accelerometer, gyroscope, or temperature.

#### `void setAxis(axes newAxis) `
Sets the axis to x, y, z, or all.

### PingSensor
This class uses a sensor that determines distance by measuring the time it takes for an ultrasonic pulse to reflect off a surface and return to the sensor. 

#### `void wake() `
Placeholder method, does nothing.

#### `void work() `
Initiates a distance measurement by the sensor.

#### `void workFast() `
Checks for the sensor's response to the distance measurement request.

#### `void setPin(int newTriggerPin, int newEchoPin) `
Sets the Arduino pins for the trigger and echo pins of the distance sensor.

#### `void sendPing() `
Sends a trigger pulse to the sensor, initiating a distance measurement.

#### `void checkEcho() `
Listens for the echo from the sensor to determine the distance to an object.

#### `void setMax(int newMax) `
Sets the maximum distance that the sensor can measure.

## Nodes

### CloneNode
This class clones the input from one neuron to another.

#### `void work() `
Updates the input value and invalid state from the connected input neuron.

#### `void setValue(float newValue) `
Sets the internal value of the node.

### CurveNode
This class applies a curve to the input from one neuron and outputs the result.

#### `void work() `
Applies a curve to the input value based on the currently set curve type and exponent.

#### `void setCurve(Curvinator::mode newCurve, float newExponent = 2 ) `
Sets the curve function to be applied to the input.

### LerpNode
This class smoothly interpolates between values over time.

#### `void work() `
If there is an input neuron connected, updates the target of the internal `lerp` object with the input value. It then updates the `lerp` object and sets the internal value of the node to the current lerped value.

#### `void wake() `
Placeholder method, does nothing.

#### `void setLerp(float newSpeed, float newAcceleration) `
Sets the speed and acceleration for the internal `lerp` object.

### EncodedMotorNode
This class controls a motor with an encoder using either analog or digital input.

#### `void work() `
Calls either `workProcessAnalog` or `workProcessDigital` to process the motor's movement depending on the current encoding mode.

#### `void workFast() `
Updates the values of the analog and digital encoders, as well as the state of the two buttons.

#### `void wake() `
Placeholder method, does nothing.

#### `void setPin(int mdPin1, int mdPin2, int mePin) `
Sets the pin numbers for the motor driver and analog encoder.

#### `void setPin(int mdPin1, int mdPin2, int mePin1, int mePin2, int esPin1 = -1, int esPin2 = -1, bool mePullup = true, bool esPullup = true) `
Sets the pin numbers for the motor driver, digital encoder, and two optional endstop buttons.

#### `void setSteps(int newSteps) `
Sets the number of steps the motor takes to make one revolution.

#### `int getSteps() `
Returns the number of steps the motor takes to make one revolution.

#### `void setLerp(float newSpeed, float newAcceleration) `
Sets the speed and acceleration for the `lerp` object.

#### `void setBehavior(behaviorMode newBehavior) `
Sets the current behavior of the motor.

#### `byte getBehavior() `
Returns the current behavior mode.

#### `bool getEndstopState(bool index) `
Returns the state of either endstop A or endstop B.

#### `void setEndstopMin() `
Sets the minimum value of the digital encoder.

#### `void setEndstopMax() `
Sets the maximum value of the digital encoder.

#### `void setEndstopMode(endstopMode newMode) `
Sets the mode for the endstops.

#### `byte getEndstopMode() `
Returns the current endstop mode.

#### `void setEncodingMode(encodingMode newMode) `
Sets the encoding mode for the motor.

#### `byte getEncodingMode() `
Returns the current encoding mode.

#### `void setMotorStartSpeed(float newSpeed) `
Sets the motor startup speed.

#### `void setAnalogWindow(int rangeMin, int rangeMax) `
Sets the analog input range for the analog encoder.

### MixNode
This class mixes the signals from two neurons.

#### `void work() `
Sets the internal value by mixing the values of the two input neurons, using the mixing mode set with `setMode()`.

#### `void setMode(Mixer::mode newMode) `
Sets the mixing mode.

### SustainNode
This class sustains the input signal for a set amount of time.

#### `void work() `
Sustains the input signal based on the configured threshold and timer.

#### `void setTime(float newTime) `
Sets the duration of the sustain.

#### `void setLevel(float newLevel) `
Sets the threshold for the sustain. When the input falls below this threshold, the sustain is released.

## Others

### Curvinator (Utility Class)

The `Curvinator` class is a static class that provides various curve functions for manipulating signals. It's not meant to be instantiated, but rather used as a collection of utility functions.

#### `float curve(float x, float e, mode newMode, boolean invX=false, boolean invY=false, float c=0.5)`

This function applies a curve to the input value `x`, based on the exponent `e`, curve `newMode`, and optional parameters for inverting the X or Y axes (`invX`, `invY`) and adjusting the curve center (`c`). 

####  Curve Modes (`Curvinator::mode`)

The following curve modes are available:

- `none`: Applies no curve (linear).
- `in`: Applies an "ease-in" curve using a variable exponent.
- `out`: Applies an "ease-out" curve using a variable exponent.
- `inOut`: Applies an "ease-in-out" curve using a variable exponent and center point.
- `outIn`: Applies an "ease-out-in" curve using a variable exponent and center point.
- `bell`: Applies a bell-shaped curve using a variable exponent.
- `skew`: Applies a skewed curve using a variable exponent.
- `bathtub`: Applies a "bathtub" curve using a variable exponent.

#### Example Usage

```cpp
// Apply an "ease-in-out" curve with an exponent of 2.5 and a center point of 0.6:
float curvedValue = Curvinator::curve(inputValue, 2.5, Curvinator::mode::inOut, false, false, 0.6);
```

### Mixer (Utility Class)

The `Mixer` class, similar to `Curvinator`, is a static class that provides various mixing modes for blending two input signals. 

####  `float Mix(float a, float b, mode newMode)`

This static function mixes two input values (`a` and `b`) based on the selected mixing `newMode`.

#### Mixing Modes (`Mixer::mode`)

The following mixing modes are available:

- Mathematical operations: `add`, `subtract`, `multiply`, `divide`, `modulo`, `power`, `average`.
- Comparison-based: `min`, `max`, `less`, `greater`.
- Boolean logic: `AND`, `OR`, `NAND`, `NOR`, `XOR`, `XNOR`.

#### Example Usage:

```cpp
// Mix two signals using multiplication:
float mixedValue = Mixer::Mix(signalA, signalB, Mixer::mode::multiply);
```

### Toolkit (Utility Class)

The `Toolkit` class is another static class containing various utility functions.

####  `int mapi( int x, int in_min, int in_max, int out_min, int out_max )`

This function maps an integer input value (`x`) from one range (`in_min`, `in_max`) to another (`out_min`, `out_max`).

#### `float mapf( float x, float in_min, float in_max, float out_min, float out_max )`

This function maps a floating-point input value (`x`) from one range (`in_min`, `in_max`) to another (`out_min`, `out_max`).

### Timer

The `Timer` class allows the creation of timers for triggering events in the code.

#### Key Functionality

- **Setting the Rate:** You can configure the timer's rate using `setRate()`, `setRateMillis()`, or `setRateMicros()` depending on your desired time unit (milliseconds or microseconds). 
- **Checking for Intervals:** Use `interval()` to check for repeating intervals and `timeout()` for one-time events.
- **Resetting the Timer:** The `reset()` function resets the timer.

#### Example Usage

```cpp
Timer myTimer;

void setup() {
  // Set the timer for a 500ms interval
  myTimer.setRateMillis(500); 
}

void loop() {
  // Check if the timer interval has elapsed
  if (myTimer.interval()) {
    // Execute code every 500ms
  }
}
```

### RailcarLerp

The `RailcarLerp` class provides smooth interpolation between values using a "railcar" metaphor, likely involving acceleration and deceleration for more natural movement.

#### Key Functionality:

- **Setting the Target:** Use `setTarget()` to set the desired end value for interpolation.
- **Updating the Interpolation:**  Call `update()` to advance the interpolation based on the elapsed time (`deltaTime`).
- **Getting the Current Value:** Access the current interpolated value using `getValue()`.

#### Example Usage

```cpp
RailcarLerp myLerp;

void setup() {
  // ...
}

void loop() {
  // Update the lerp target based on some condition
  if (someCondition) {
    myLerp.setTarget(newValue); 
  }

  // Update the interpolation (assuming 'deltaTime' holds the elapsed time)
  myLerp.update(deltaTime); 

  // Use the lerped value
  float currentValue = myLerp.getValue(); 
}
```

### ScaleMapper (Utility Class)

The `ScaleMapper` class quantizes an input value to a specified musical scale, useful for musical applications.

#### Key Functionality

- **Mapping to Scales:** The `map()` function takes an input value and maps it to a specific note within a chosen scale.
- **Scale and Tuning Options:** It supports a variety of scales (e.g., major, minor, pentatonic, chromatic) through the `scales` enum and tuning systems (e.g., just, equal) via the `tunings` enum.

#### Example Usage:

```cpp
// Map an input value to the C Major scale:
float mappedFrequency = ScaleMapper::map(inputValue, /* base frequency */ 440.0, /* modulate */ 0, /* transpose */ 0, ScaleMapper::scales::majorTriad, ScaleMapper::mappings::pitch, ScaleMapper::tunings::equal);
```
