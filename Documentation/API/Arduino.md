# Arduino Library API

Here is an API for all components in the Arduino library, grouped by types:

## Index

- [Drivers](#drivers)
    - [AnalogDriver](#analogdriver)
    - [MotorDriver](#motordriver)
    - [MidiDriver](#mididriver)
    - [ServoDriver](#servodriver)
    - [StepperDriver](#stepperdriver)
    - [SerialDriver](#serialdriver)
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
    - [SerialNode](#serialnode)
    - [SustainNode](#sustainnode)

- [Sensors](#sensors)
    - [AnalogSensor](#analogsensor)
    - [ButtonSensor](#buttonsensor)
    - [EncoderSensor](#encodersensor)
    - [MPUSensor](#mpusensor)
    - [PingSensor](#pingsensor)
    - [SerialSensor](#serialsensor)

- [Utilities](#utilities)
    - [Curvinator](#curvinator)
    - [Mixer](#mixer)
    - [RailcarLerp](#railcarlerp)
    - [ScaleMapper](#scalemapper)
    - [Timer](#timer)
    - [Toolkit](#toolkit)

## Drivers

### AnalogDriver

The AnalogDriver controls components that respond to analog signals using Pulse Width Modulation (PWM). For example, you can use an AnalogDriver to control the brightness of an LED. You can use the `setPin()` method to assign a pin for output. Be aware that only certain pins on Arduino boards support PWM.

*   `setPin(int newPin)` - Assigns the output pin the AnalogDriver will control. 

### MotorDriver

The MotorDriver controls a basic DC motor driver board using two pins: one for digital direction and one for PWM speed. 

*  `setPin(int newDirPin, int newSpeedPin)` - Assigns the direction and speed pins.
*  `setRange(byte newMin, byte newMax)` - Sets the minimum and maximum output range.
*  `setReverse(bool newRev)` - Inverts the direction of the motor.
*  `setCenter(float newCenter)` - Sets the center offset point.

### MidiDriver

The MidiDriver sends standard MIDI messages over serial communication. Using the MidiDriver requires setting the serial baud rate to the MIDI standard of 31250. You will not be able to use the SerialNode while using MidiDriver, as they both use the serial port.

*  `setBase(float newBase)` - Sets the base note.
*  `allNotesOff()` - Turns off all notes.

### ServoDriver

The ServoDriver controls a basic servo motor using the standard Arduino Servo library.

*  `setPin(int newPin)` - Assigns the output pin.
*  `setRange(byte newMin, byte newMax)` - Sets the minimum and maximum output range for the servo.

### StepperDriver

The StepperDriver controls a basic stepper motor driver board using two pins: one for direction, and the other for step.

*   `setPin(int newDirPin, int newStepPin)` - Assigns the direction and step pins for output.

#### StepperDriver Modes

The StepperDriver has two modes: `range` and `rate`. In `range` mode, the driver sets the position of the motor. In `rate` mode, the driver sets the speed of the motor.

#### StepperDriver Microsteps

The StepperDriver supports different microstep levels: `full`, `half`, `quarter`, `eighth`, and `sixteenth`. You can use microstepping to achieve smoother motor movement.


### SerialDriver

The SerialDriver writes to the serial port. You can use it to send data to other devices or software.  To use the SerialDriver, you must link it to a SerialNode. 

* `setSerialNode(SerialNode &newNeuron, byte newChannel)` - Assigns the serial node that the SerialDriver will use, and the channel number.
* `getSerialNode()` - Returns the assigned SerialNode.

### ToneDriver

The ToneDriver generates an audio square wave. You can use it to control a speaker or buzzer.

*  `setPin(int newPin)` - Assigns the output pin for the audio output.
*  `setFrequency(float newFrequency)` - Sets the frequency of the tone in Hertz.
*  `stopAllTones()` - Stops all tones on the assigned pin.
*  `octaves(byte newOctaves)` - Sets the octave multiplier. 


#### Powder Of Life Drivers and the Engine

All drivers, just like all sensors, must be registered with the Arduino Engine to be updated.. The Engine class in Powder of Life handles registration and updating of all components.


## Generators

### BeatGenerator

The BeatGenerator acts as a digital metronome, generating a rhythmic on-off signal that can drive other components in the system. You can use it for applications that require timed events or synchronized behaviors. 

* `setRate(float newRate)` - Sets the rate of the beat in seconds.
* `setClickLength(float newLength)` - Sets the length of the click in seconds.
* `click()` - Returns true during the click.

### ContinuousGenerator 

The ContinuousGenerator is a neuron with a fixed state. It has no internal functionality and its value is always 1.

### RandomGenerator

The RandomGenerator generates random values within a defined range. You can configure separate ranges for values going up and down. This allows for asymmetric random behavior.  For example, you can make a value increase quickly but decrease slowly.

*   `setRandomRates(float newUpMin, float newUpMax, float newDownMin = -1, float newDownMax = -1)` - Sets the minimum and maximum random rates for up and down values. If `newDownMin` and `newDownMax` are not specified, they default to the values for `newUpMin` and `newUpMax`. 

#### Powder Of Life Generators and the Engine

All generators, just like all sensors and drivers, must be registered with the Arduino Engine to be updated. You can add generators to the engine using the  `addNeuron()` method.  The Engine class in Powder of Life handles registration and updating of all components. 


## Nodes

### CloneNode

The CloneNode replicates the input value from another neuron as its output. This allows the output of one neuron to be directed to multiple destinations within the network. 

*   `work()` - Updates the node, copying the value from the input neuron to its internal value.
*   `setValue(float newValue)` - Sets the internal value.

### CurveNode

The CurveNode applies mathematical curves to signal values, enabling you to alter the response characteristics of other nodes in the network.

*   `work()` -  Updates the node, applying a curve to the input value using the Curvinator class.
*   `setCurve(Curvinator::mode newCurve, float newExponent = 2 )` - Sets the type of curve and exponent.

### EncodedMotorNode

The EncodedMotorNode combines multiple neurons into a cluster for controlling an encoded motor. It includes an EncoderSensor, two ButtonSensors for endstops, a MotorDriver, and a LerpNode. You can configure the node for different motor behaviors depending on the endstop configuration. 

*   `work()` - Updates the node based on its current encoding mode.
*   `workFast()` - Updates the sensors within the node.
*   `wake()` - Runs once when the node is initialized. 
*   `setPin(int mdPin1, int mdPin2, int mePin)` - Assigns pins for the MotorDriver and EncoderSensor (for analog encoding).
*   `setPin(int mdPin1, int mdPin2, int mePin1, int mePin2, int esPin1 = -1, int esPin2 = -1, bool mePullup = true, bool esPullup = true)` -  Assigns pins for the MotorDriver, EncoderSensor (for digital encoding), and ButtonSensors (for endstops). If no endstop pins are provided, they default to -1, disabling the endstops.
*   `setSteps(int newSteps)` - Sets the total steps for the encoder. Only works in specific endstop modes.
*   `getSteps()` - Returns the total steps for the encoder.
*   `setLerp(float newSpeed, float newAcceleration)` - Sets the speed and acceleration for the internal LerpNode. 
*   `setBehavior(behaviorMode newBehavior)` - Defines the motor behavior. 
*   `getBehavior()` - Returns the current motor behavior.
*   `getEndstopState(bool index)` - Returns the state of the specified endstop button.
*   `setEndstopMode(endstopMode newMode)` - Defines the endstop configuration.
*   `getEndstopMode()` - Returns the current endstop configuration.
*   `setEncodingMode(encodingMode newMode)` -  Sets the encoding mode to either `analog` or `digital`.
*   `getEncodingMode()` - Returns the current encoding mode.
*   `setMotorStartSpeed(float newSpeed)` - Sets the startup speed of the motor.
*   `setAnalogWindow(int rangeMin, int rangeMax)` - Defines the input range for the analog encoder.

#### EncodedMotorNode Behaviors

The EncodedMotorNode uses the following behavior modes to determine the motor's response to the endstops:

*   `undefined` - This is the default behavior and has no specific functionality.
*   `endstopA` - The motor will stop when it reaches endstop A.
*   `endstopB` - The motor will stop when it reaches endstop B.
*   `standard` - The motor will stop when it reaches either endstop.

#### EncodedMotorNode Endstop Modes

The EncodedMotorNode supports three endstop modes, defining which endstops to use:

*   `none` - No endstops are used.
*   `one` - Only endstop A is used.
*   `both` - Both endstops A and B are used.

### LerpNode

The LerpNode smooths out the signal between two neurons. You can use it to address issues related to noisy or jerky behavior.  The LerpNode acts as a wrapper for the RailcarLerp class, which provides smooth interpolation with acceleration. 

*   `work()` -  Updates the node, using the RailcarLerp class to smooth the input value.
*   `wake()` -  Runs once when the node is initialized. 
*   `setLerp(float newSpeed, float newAcceleration)` - Sets the speed and acceleration for the internal RailcarLerp.

### MixNode

The MixNode combines the signals from two neurons to create a mixed output.  You can use it to blend, modify, or apply logic operations to signals. 

*   `work()` - Updates the node, blending the values from the two input neurons using the Mixer class.
*   `setMode(Mixer::mode newMode)` - Sets the blending mode using the  `Mixer::mode` enum.

### SerialNode

The SerialNode manages the serial connection, acting as a conduit for communication with external devices or software.

*   `wake()` - Runs once when the node is initialized, starting the serial connection. 
*   `workFast()` - Reads and parses incoming serial data.
*   `setSerial(serialRate newRate)` - Sets the serial baud rate using the `serialRate` enum.
*   `setSerial(unsigned int newRate)` - Sets the serial baud rate using an integer value.
*   `getPortData(byte channelName)` - Reads data from the specified channel.
*   `setPortData(byte channelName, float newValue)` - Writes data to the specified channel.
*   `setDepth(byte newDepth)` - Sets the number of decimal places for float values in serial messages. 

### SustainNode

The SustainNode extends the duration of an input signal. It can either hold a high signal indefinitely or smooth out a fluctuating signal.

*   `work()` - Updates the node based on its current mode.
*   `hold()` - Holds the current value.
*   `setThreshold(float newThreshold)` - Sets the threshold for binary sustain mode. If no threshold is defined, the sustain node operates in analog mode.

#### SustainNode Modes

The SustainNode has two operating modes:

*   **Binary Sustain:** The node outputs 1 if the input is above the threshold and 0 if it's below. It will hold the output value at 1 even if the input drops below the threshold until it receives a specific signal to release the hold.
*   **Analog Sustain:** The node smooths out the input signal, preventing rapid fluctuations.  It creates a gradual decline in the output when the input decreases, rather than a sharp drop.

These are the nodes in the Powder Of Life Arduino library based on the provided source code. Note that the source code does not include descriptions for every method, so some of the descriptions in this API are based on the context and usage of the methods in the code. 

## Sensors

### AnalogSensor 

The AnalogSensor class reads the standard Arduino analog input. Normalization is set by default to the 10-bit depth of the standard Arduino board (0-1023).

*   `setPin(int newPin)` - Assigns an analog pin to the sensor for reading input.
*   `setCenter(int newCenter)` - Sets the center point for normalization using an integer value.
*   `setCenter(float newCenter)` - Sets the center point for normalization using a float value (0.0-1.0).

### ButtonSensor

The ButtonSensor class simplifies reading input from buttons connected to an Arduino board. It handles debouncing and provides a standardized output.

* `setPin(int newPin, bool newPullup = true)` - Sets the input pin for the sensor. You can also define whether to use the internal pullup resistor.
* `setToggle(bool newToggle)` - Configures the button to behave like a toggle.

### EncoderSensor

The EncoderSensor reads a quadrature encoder, using quadrature encoding to determine direction of travel and displacement. The default for "pullup" on the pins is true, assuming a non-powered board.

* `setPin(int newPin1, int newPin2, bool newPullup = true)` - Sets the input pins for the encoder.
* `setMode(modes newMode)` - Sets the mode to either `range` or `rate`.
* `setReverse(bool newState)` - Reverses the direction of the encoder.
* `setSteps(int newSteps)` - Sets the total number of steps in the encoder's range. This only works with certain endstop modes.
* `getSteps()` - Returns the total number of steps in the encoder's range.
* `getCurrentStep()` - Returns the current step count.
* `setRate(float newRate=0.2)` -  Adjusts the rate used to determine change by the encoder (rate in seconds).

#### EncoderSensor Normalization

The steps per revolution of an encoder can vary. The example code for the EncoderSensor shows how to determine how many steps your encoder has. This value can then be used to normalize the sensor.

#### EncoderSensor and EncodedMotorNode

The EncoderSensor can be used as part of the EncodedMotorNode. The EncodedMotorNode is a complex node that combines multiple neurons into a neural cluster. It is used to control an encoded motor. The EncodedMotorNode can be used to control a motor with endstops. The EncodedMotorNode can operate in different behaviors depending on the endstop configuration.

### MPUSensor

The MPUSensor is designed to interface with MPU-6050 chips. Most MPU breakout boards provide SDA/SCL pins, enabling communication via the I2C interface.

* `setMode(modes newMode)` - Sets the mode to either `accelerometer`, `gyroscope`, or `temperature`.
* `setAxis(axes newAxis)` -  Sets the axis to either `x`, `y`, `z` or `all`.

### PingSensor

The PingSensor interfaces with standard ultrasonic distance sensors (also known as "ping" sensors). These sensors work by emitting ultrasonic pulses and measuring the time it takes for the echo to return.

* `setPin(int newTriggerPin, int newEchoPin)` - Sets the trigger and echo pins for the sensor.
* `setMax(int newMax)` - Sets the maximum distance the sensor will measure.

### SerialSensor

The SerialSensor reads data from the serial port. This sensor requires a SerialNode to manage the serial connection. Each driver/sensor pair needs to be on the same channel.

* `setSerialNode(SerialNode &newNeuron, byte newChannel)` - Links the SerialSensor to a SerialNode and sets the channel number.
* `getSerialNode()` - Returns a reference to the linked SerialNode object.

#### Serial Communication

Powder Of Life supports inter-environment networks. The SerialNode manages the serial connection. SerialDriver and SerialSensor can use the SerialNode to send and receive data. The serial node is shared by all serial drivers and sensors.


## Utilities

### Curvinator

The Curvinator class provides easing functions for creating smooth transitions and animations. You can use the `curve()` method to apply various easing curves to input values. The class is designed to be static, so you can call its functions directly without creating an instance.

*   `curve(mode curveType, float input, float expo = 2)` - Applies the specified curve to the input value.
*   `linear(float input)` - Applies a linear curve to the input, returning the input value unchanged. 
*   `sin(float input, bool easeIn = true, bool easeOut = true)` - Applies a sine curve to the input.
*   `quad(float input, bool easeIn = true, bool easeOut = true)` - Applies a quadratic curve to the input.
*   `cubic(float input, bool easeIn = true, bool easeOut = true)` - Applies a cubic curve to the input.
*   `quart(float input, bool easeIn = true, bool easeOut = true)` - Applies a quartic curve to the input.
*   `quint(float input, bool easeIn = true, bool easeOut = true)` - Applies a quintic curve to the input.
*   `expo(float input, float expo, bool easeIn = true, bool easeOut = true)` - Applies an exponential curve to the input.
*   `circ(float input, bool easeIn = true, bool easeOut = true)` - Applies a circular curve to the input.

The Curvinator class also includes an enum for the different curve modes:

*   `none` - No easing applied.
*   `linear` - Linear easing. 
*   `sin` - Sine easing.
*   `quad` - Quadratic easing.
*   `cubic` - Cubic easing.
*   `quart` - Quartic easing.
*   `quint` - Quintic easing.
*   `expo` - Exponential easing. 
*   `circ` - Circular easing.

### Mixer

The Mixer class enables mixing and blending of two input values using various modes. Like the Curvinator, it is a static class, allowing you to call its functions directly.

*   `Mix(float a, float b, mode mixMode)` - Blends the two inputs (`a` and `b`) based on the specified mode.

The Mixer class includes an extensive list of modes:

*   **Mathematical Operations:**
    *   `add`
    *   `subtract`
    *   `multiply`
    *   `divide`
    *   `average`
    *   `modulo`
    *   `power`

*   **Blending Modes:**
    *   `screen`
    *   `overlay`
    *   `difference`
    *   `min`
    *   `max`
    *   `less`
    *   `greater`

*   **Logic Gates:**
    *   `AND`
    *   `OR`
    *   `NAND`
    *   `NOR`
    *   `XOR`
    *   `XNOR`

### RailcarLerp

The RailcarLerp class provides smooth interpolation of values with acceleration and deceleration. You can use it to create natural-feeling movements or transitions.

*   `update(float timeDelta)` - Updates the internal state of the lerp based on the time elapsed.
*   `setSpeed(float newSpeed)` - Sets the speed of the lerp.
*   `setAcceleration(float newAcceleration)` - Sets the acceleration of the lerp.
*   `setTarget(float newTarget)` - Sets the target value to lerp towards.
*   `getValue()` - Returns the current lerped value.

### ScaleMapper

The ScaleMapper class quantizes input values to musical scales and chords. This utility is helpful for creating musical applications with Arduino. 

*   `map(float input, scales scale, tunings tuning, float modulate = 0, int octave = 0)` - Maps the input value to a note on the specified scale and tuning, with optional modulation and octave settings.

**ScaleMapper Scales**

The ScaleMapper includes a comprehensive list of scales represented by the `scales` enum. Here are a few examples:

*   `major` 
*   `minor` 
*   `pentatonicMajor` 
*   `pentatonicMinor` 
*   `blues` 

**ScaleMapper Tunings**

You can choose between two tuning systems using the `tunings` enum:

*   `just` - Just intonation.
*   `equal` - Equal temperament.

**Additional ScaleMapper Methods and Properties** 

*   `getBaseScaleLength(tunings tuning)` - Returns the length of the base chromatic scale for the selected tuning system.
*   `getNumberOfScales()` - Returns the total number of scales defined in the `ScaleMappings` array.
*   `getScaleLength(scales scale)` -  Returns the number of notes in the specified scale.

**Note:** The ScaleMapper is a large class and can consume significant memory on an Arduino board. If you are working with limited memory, consider optimizing your code to only use the ScaleMapper when necessary.

### Timer

The Timer class helps you create and manage simple timers in your Arduino sketches.

*   `setRate(float newRate)` - Sets the interval for the timer in seconds.
*   `setRateMillis(unsigned long newRate)` - Sets the interval for the timer in milliseconds. 
*   `setRateMicros(unsigned long newRate)` - Sets the interval for the timer in microseconds.
*   `getRate()` - Returns the timer interval.
*   `interval()` - Returns true if the specified interval has elapsed.
*   `timeout()` - Returns true if the timer has exceeded the set duration. 
*   `start()` - Starts the timer.
*   `stop()` - Stops the timer.
*   `restart()` - Restarts the timer.
*   `setDuration(float newDuration)` - Sets the duration of the timer.
*   `getDuration()` - Returns the timer's duration.

### Toolkit

The Toolkit class offers a collection of utility functions for common tasks, including mathematical operations, data conversion, and debugging. Like the other utility classes, it's designed to be static.

*   `mapi(int x, int in_min, int in_max, int out_min, int out_max)` - Maps an integer value from one range to another.
*   `mapf(float x, float in_min, float in_max, float out_min, float out_max)` - Maps a float value from one range to another.
*   `constraini(int amt, int low, int high)` - Constrains an integer value within a specified range.
*   `constrainf(float amt, float low, float high)` -  Constrains a float value within a specified range.
*   `getSign( float input )` - Returns the sign of the input: 1 for positive, -1 for negative, 0 for zero. 
*   `printFloat(double number, uint8_t digits=8)` - Prints a formatted float value to the serial port, handling negative numbers and rounding.



This API focuses specifically on the Arduino utilities. For information about the other classes in the Powder Of Life framework (Sensors, Drivers, Generators, Nodes) please refer to the previous responses in our conversation history.  
