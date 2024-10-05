# POL Arduino API

## Index
- [Sensors](#sensors)
    - [AnalogSensor](#analogsensor)
- [Drivers](#drivers)
- [Nodes](#nodes)
- [Generators](#generators)


========================================================================

Created all content below using Notebook LM. Fed it the Arduino library (converted to ".txt" with Python)


## Index
- [Drivers](Drivers.md#drivers))
    - [AnalogDriver](#analogdriver)
    - [MotorDriver](#motordriver)
    - [MidiDriver](#mididriver)
    - [ServoDriver](#servodriver)
    - [StepperDriver](#stepperdriver)
    - [ToneDriver](#tonedriver)
- [Generators](#generators)
    - [BeatGenerator](#beatgenerator)
    - [ContinuousGenerator](#continuousgenerator)
    - [RandomGenerator](#randomgenerator)
- [Nodes](#nodes)
    - [CloneNode](#clonenode)
    - [CurveNode](#curvenode)
    - [EncodedMotorNode](#encodedmotornode)
    - [LerpNode](#lerpnode)
    - [MixNode](#mixnode)
    - [SustainNode](#sustainnode)
- [Sensors](#sensors)
    - [AnalogSensor](#analogsensor)
    - [ButtonSensor](#buttonsensor)
    - [EncoderSensor](#encodersensor)
    - [MPUSensor](#mpusensor)
    - [PingSensor](#pingsensor)

## Drivers

### AnalogDriver

This class is a basic driver that uses the standard Arduino analog output.

- `void wake()` - Does nothing.
- `void work()` - Updates the input, maps the input value to the output range, constrains the output to avoid overflow, and writes the output value to the output pin.
- `void setPin(int newPin)` -  Sets the output pin number and sets the pin mode to output. 

### MotorDriver

This class controls a basic DC motor driver board using two pins for direction and speed.

- `void work()` - Updates the input value, determines the direction based on the sign of the value, maps the absolute value of the input to the output range, constrains the speed to avoid overflow, and writes the direction and speed to the corresponding output pins.
- `void setPin(int newDirPin, int newSpeedPin)` - Sets the direction pin and speed pin for the motor driver and sets their pin modes to output.
- `void setRange(byte newMin, byte newMax)`- Sets the minimum and maximum values for the motor speed.
- `void setReverse(bool newRev)` - Sets whether to invert the motor direction.
- `void setCenter(float newCenter)` - Sets the center point for the motor's normalization.

### MidiDriver

This class sends MIDI messages over the serial port. 

- `void work()` - Currently does nothing.
- `void wake()` - Sets the base note to 60.
- `void setBase(float newBase)` - Sets the base note for MIDI note calculations.
- `void playNote(byte note, byte velocity = 100, byte channel = 1, bool playStop = true)` - Plays a MIDI note with the specified note number, velocity, and channel. 
- `void stopNote(byte note, byte channel = 1)` - Stops a MIDI note with the specified note number and channel. 
- `void sendClock()` - Sends a MIDI timing clock message.
- `void allNotesOff()` - Sends an "all notes off" MIDI message.

### ServoDriver

The ServoDriver class controls a basic servo motor with standard Arduino PWM output.

- `void work()` - Sets the internal value to the input value, maps the input value to the output range, constrains the position to the servo's limits, and writes the position to the servo.
- `void setPin(int newPin)` - Sets the output pin for the servo motor and attaches the servo object to the pin.
- `void setRange(byte newMin, byte newMax)` - Sets the minimum and maximum servo positions in degrees.

### StepperDriver

The StepperDriver class controls a basic stepper motor driver board.

- `void work()` - Gets the input value and updates the target position based on the selected mode. If in `range` mode, it calculates the target position based on the input value and steps the motor towards that position. If in `rate` mode, it steps the motor once per frame.
- `void workFast()` -  Steps the motor towards the target position if in range mode.
- `void setMicrostep(microsteps newStep)` -  Sets the microstepping level for the stepper motor driver.
- `void setMode(modes newMode)` - Sets the mode of the stepper driver, which can be either `range` (absolute positioning) or `rate` (speed and direction).
- `void stepOnce(int dir = 1)` - Steps the motor once in the specified direction.
- `void setPin(int newDirPin, int newStepPin)` - Sets the direction and step pins for the stepper driver and sets the pin modes to output.

### ToneDriver

This class generates audio tones on a specified pin using either hardware (using the `tone()` function) or software (by toggling the pin at a specific frequency).

- `void work()` - Updates the internal value based on the input, scales the input to the desired frequency range, maps the frequency to the correct note in the selected scale, and sets the tone frequency. 
- `void workFast()` - If in software mode, toggles the output pin to generate the tone.
- `void setPin(int newPin)` - Sets the output pin for the tone driver.
- `void softToneOn(float newTone)` - Enables the software tone generation with the specified frequency.
- `void softToneOff()` - Disables the software tone generation.
- `void setTonic(float newTonic)` - Sets the base frequency for the tone generator.
- `void setScale(byte newScale = ScaleMapper::scales::pentatonicMajor)` -  Sets the musical scale used for mapping input values to frequencies.
- `void setMode(byte newMode)` - Sets the tone generation mode, either hardware or software.
- `modes getMode()` - Returns the current tone generation mode.
- `float getTone()` - Returns the current tone frequency.
- `float getRate()` - Returns the rate of the waveform timer, which determines the tone frequency in software mode.
- `void start()` - Enables tone generation.
- `void stop()` - Disables tone generation.
- `void stopAllTones()` - Stops both the hardware and software tone generation.
- `void octaves(byte newOctaves)` -  Sets the octave multiplier for the generated tone.

=======================================================


## Generators

### BeatGenerator

The `BeatGenerator` class generates a rhythmic pulse, similar to a metronome.

- `void work()` -  Updates the internal value of the beat generator, either using a ramp or by updating the beat state.
- `void setTempo(float newTempo)` -  Sets the tempo in beats per minute.
- `float getTempo()` - Returns the current tempo in beats per minute.
- `void setDecay(float newDecay, decayMode newMode = decayMode::ratio)` - Sets the decay time of the beat, either as a ratio of the beat duration or as a fixed time in seconds.
- `float getDecay()` -  Returns the current decay time.
- `void setRamp(bool newRamp)` -  Enables or disables the ramp mode.
- `void setSubdivisions(byte newSubDiv)` -  Sets the number of subdivisions per beat.
- `byte getSubdivisions()` -  Returns the number of subdivisions per beat.
- `void clickBeat()` -  Manually triggers a beat click.
- `byte getBeat()` -  Returns the current beat in the cycle, starting from 1.
- `bool getState()` - Returns the current state of the beat (on or off).
- `float getRatio()` - Returns a value between 0 and 1 representing the position within the current beat subdivision.
- `bool getClick()` -  Acts as a pseudo-event, returning true once when a new beat subdivision starts.

### ContinuousGenerator

This class is not well-defined in the provided sources.

- `ContinuousGenerator()` - Constructor for the ContinuousGenerator class.

### RandomGenerator

The `RandomGenerator` class generates random values within a specified range.

- `void work()` -  Generates a new random value when the state change timer triggers.
- `float getRandomValue()` -  Returns a random value within the specified range.
- `float randomFloat(float randMin, float randMax)` -  Generates a random float between the specified minimum and maximum values.
- `void setRandomRates(float newUpMin, float newUpMax, float newDownMin, float newDownMax)` -  Sets the minimum and maximum times for both the "up" and "down" states of the random generator.
}

=======================================================


## Nodes
### CloneNode

The `CloneNode` class simply copies the value of its input neuron to its own internal value.

- `void work()`- Updates the input value and sets the internal value to the input value. 
- `void setValue(float newValue)` - Sets the internal value to the provided value.

### CurveNode

The `CurveNode` class applies a mathematical curve to the input value, allowing for non-linear transformations of the signal.

- `void work()` - If there is an input, it calculates the curved value using the current curve type and exponent and sets the internal value to the curved result. Otherwise, it does nothing.
- `void setCurve(Curvinator::mode newCurve, float newExponent = 2 )`- Sets the curve type and exponent for the node.

### EncodedMotorNode

The `EncodedMotorNode` class is a more complex node that combines multiple neurons to control a motor with an encoder.

- `void work()`- Calls a more specific work function based on the current encoding mode (analog or digital). 
- `void workFast()` -  Updates the values of the encoder sensors and button sensors.
- `void wake()` - Does nothing.
- `void setPin(int mdPin1, int mdPin2, int mePin)` -  Sets the pins for a motor driver and a single-pin analog encoder. This method is used for analog encoding mode.
- `void setPin(int mdPin1, int mdPin2, int mePin1, int mePin2, int esPin1 = -1, int esPin2 = -1, bool mePullup = true, bool esPullup = true)` - Sets the pins for a motor driver, a two-pin digital encoder, and two optional endstop buttons. This method is used for digital encoding mode.
- `void setSteps(int newSteps)` - Sets the number of steps for the motor encoder and updates the normalization of the digital encoder sensor.
- `int getSteps()` - Returns the number of steps for the motor encoder.
- `void setLerp(float newSpeed, float newAcceleration)`- Sets the speed and acceleration for the internal lerp node.
- `void setEndstopMin()` - Sets the minimum value of the digital encoder's normalization based on the current encoder step count.
- `void setEndstopMax()` - Sets the maximum value of the digital encoder's normalization based on the current encoder step count and updates the `motorEncoderSteps` variable.
- `byte getBehavior()` - Returns the current behavior mode of the motor.
- `void setEndstopMode(endstopMode newMode)` - Sets the endstop mode, which determines how the motor handles endstops.
- `byte getEndstopMode()` -  Returns the current endstop mode.
- `void setEncodingMode(encodingMode newMode)`- Sets the encoding mode, which determines whether the motor is controlled using analog or digital input.
- `byte getEncodingMode()` -  Returns the current encoding mode.
- `void setMotorStartSpeed(float newSpeed)` - Sets the speed of the motor used when homing to endstops.
- `void setAnalogWindow(int rangeMin, int rangeMax)` -  Sets the normalization range for the analog encoder sensor.

### LerpNode
The `LerpNode` class smoothly interpolates between its current value and a target value provided by its input. 

- `void work()`- Updates the internal lerp object with the input value and the frame delta time, and sets the node's internal value to the lerped value.
- `void wake()` - Does nothing.
- `void setLerp(float newSpeed, float newAcceleration)` -  Sets the speed and acceleration of the internal lerp object.

### MixNode

The `MixNode` class combines the values of two input neurons using a chosen mixing mode.

- `void work()` - Calculates the mixed value of its two inputs using the current mixing mode and sets its internal value to the result.
- `void setMode(Mixer::mode newMode)` - Sets the mixing mode for the node, determining how the two input values are combined.

### SustainNode
The `SustainNode` class holds its output value at the last input value that exceeded a specified threshold or, if no threshold is set, it will hold the highest received input.

- `void work()` -  If the threshold is zero, it updates the internal value and resets the sustain timer if the input value is greater than the current value. If the threshold is non-zero, it updates the internal value and resets the sustain timer if the input value is greater than the threshold. Otherwise, it checks if the sustain timer has timed out and if so, sets the internal value to zero.
- `void setTime(float newTime)` -  Sets the duration of the sustain timer.
- `void setLevel(float newLevel)` -  Sets the threshold level for the sustain node. If the threshold is zero, the sustain node will hold the highest input value. If the threshold is non-zero, the sustain node will act as a gate.

=======================================================

## Sensors

### AnalogSensor

This class reads data from an analog input pin.

- `void work()` - Sets the internal value to the raw input value.
- `void setPin(int newPin)` - Sets the pin number for the analog input and sets the pin mode to input.
- `void setCenter(int newCenter)` - Sets the center point for the sensor's normalization.
- `void setCenter(float newCenter)` - Sets the center point for the sensor's normalization.

### ButtonSensor

The ButtonSensor class reads data from a button connected to a digital input pin.

- `void workFast()` -  Reads the raw input from the digital input pin.
- `void work()` - Updates the internal value based on the button state and whether toggle mode is enabled.
- `void setPin(int newPin, bool newPullup=true)` - Sets the pin number for the button and whether to enable the internal pull-up resistor.
- `void setToggle(bool newToggle)` - Enables or disables toggle mode for the button.

### EncoderSensor

This class reads data from a quadrature encoder, which can determine direction and displacement.

- `void workFast()` - Reads the digital inputs, converts the current input state to a quadrature state, and processes the steps based on the selected mode.
- `void work()` - Sets the internal value to either the current step count (in `range` mode) or the rate of change of the step count (in `rate` mode).
- `char CheckPattern(bool x, bool y)` - Checks the current state of the two encoder pins against the four possible quadrature states and returns the corresponding state index.
- `void QuadratureToStep()` - Converts the quadrature encoder state to step count, taking into account the direction of rotation.
- `void setPin(int newPin1, int newPin2, bool newPullup = true)` - Sets the pin numbers for the two encoder inputs and enables or disables the internal pull-up resistors.
- `void setMode(modes newMode)` - Sets the encoder mode, which can be either `range` (absolute position) or `rate` (speed and direction).
- `void setReverse(bool newState)` - Reverses the direction of the encoder.
- `void setSteps(int newSteps)` - Sets the number of steps per revolution for the encoder.
- `int getSteps()` - Returns the number of steps per revolution.
- `long getCurrentStep()` - Returns the current step count of the encoder.
- `void setRate(float newRate)` - Sets the rate at which the rate of change is calculated (only applicable in `rate` mode).

### MPUSensor

The MPUSensor class reads data from an MPU-6050 accelerometer and gyroscope sensor.

- `void wake()` - Initializes the Wire library and configures the MPU-6050 sensor.
- `void workFast()` - Placeholder method, does nothing.
- `void work()` - Reads the accelerometer, gyroscope, and temperature data from the MPU-6050 sensor and updates the internal value based on the selected mode and axis.
- `void setMode(modes newMode)` - Sets the sensor mode to either accelerometer, gyroscope, or temperature.
- `void setAxis(axes newAxis)` - Sets the sensor axis to x, y, z, or all.

### PingSensor

This class reads data from a ping sensor, which measures distances.

- `void wake()` - Placeholder method, does nothing.
- `void workFast()` - Checks for an echo from the sensor.
- `void work()` - Sends a ping.
- `void setPin(int newTriggerPin, int newEchoPin)` - Sets the trigger and echo pins for the ping sensor.
- `void sendPing()` - Triggers the ping sensor to send out a sonic pulse.
- `void checkEcho()` - Checks if the sensor has received an echo, and if so, calculates the distance based on the time elapsed.
- `void setMax(int newMax)` - Sets the maximum distance that the sensor can measure.

