## Index
- [Nodes](#nodes)
    - [CloneNode](#clonenode)
    - [CurveNode](#curvenode)
    - [EncodedMotorNode](#encodedmotornode)
    - [LerpNode](#lerpnode)
    - [MixNode](#mixnode)
    - [SustainNode](#sustainnode)

## Nodes

### CloneNode

The primary function of the `CloneNode` is to receive an input value from another neuron in the network and replicate that value as its output. This cloning process, while simple in concept, is essential for several reasons:

* **Signal Splitting and Distribution:** The `CloneNode` allows for the output of one neuron to be directed to multiple destinations within the network. This is crucial for scenarios where the same signal needs to influence different processing paths or control multiple outputs simultaneously. 

* **Normalization and Modification:** Although the `CloneNode` itself doesn't directly modify the input value, its position within the signal flow allows for applying normalization or other transformations to the cloned signal before passing it on to subsequent neurons. This is evident in the use of `CloneNode` instances for inversion and steering in the "IR\_Sensor\_Driving\_Servo.txt" example. The code snippet below demonstrates how a `CloneNode` named `invert` is used to invert the output of an `AnalogSensor` before feeding it into another `CloneNode` responsible for steering behavior.

---

- `void setValue(float newValue)` - Sets the internal value to the provided value.

### CurveNode

The `CurveNode` class applies a mathematical curve to the input value, allowing for non-linear transformations of the signal.

- `void setCurve(Curvinator::mode newCurve, float newExponent = 2 )`- Sets the curve type and exponent for the node.

### EncodedMotorNode

The `EncodedMotorNode` class is a more complex node that combines multiple neurons to control a motor with an encoder.

Has it's own internal neurons: [AnalogSensor](Sensors.md#analogsensor), [EncoderSensor](Sensors.md#encodersensor), [MotorDriver](Drivers.md#motordriver), [LerpNode](Nodes.md#lerpnode),  [ButtonSensor](Sensors.md#buttonsensor)

- `enum endstopMode : byte { none, one, both }` - The possible modes for endstop behavior.
- `enum encodingMode : byte { analog, digital }` - The possible modes for the encoder.
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

Uses the [RailcarLerp](Utilities.md#railcarlerp) utility class.

- `void setLerp(float newSpeed, float newAcceleration)` -  Sets the speed and acceleration of the internal lerp object.

### MixNode
The `MixNode` class combines the values of two input neurons using a chosen mixing mode.

Uses the [Mixer](Utilities.md#mixer) utility class.

- `void setMode(Mixer::mode newMode)` - Sets the mixing mode for the node, determining how the two input values are combined.

### SustainNode
The `SustainNode` class holds its output value at the last input value that exceeded a specified threshold or, if no threshold is set, it will hold the highest received input.

- `void setTime(float newTime)` -  Sets the duration of the sustain timer.
- `void setLevel(float newLevel)` -  Sets the threshold level for the sustain node. If the threshold is zero, the sustain node will hold the highest input value. If the threshold is non-zero, the sustain node will act as a gate.
