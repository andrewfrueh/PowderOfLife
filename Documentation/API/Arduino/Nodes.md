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

The `CloneNode` class simply copies the value of its input neuron to its own internal value.

- `void setValue(float newValue)` - Sets the internal value to the provided value.

### CurveNode

The `CurveNode` class applies a mathematical curve to the input value, allowing for non-linear transformations of the signal.

- `void setCurve(Curvinator::mode newCurve, float newExponent = 2 )`- Sets the curve type and exponent for the node.

### EncodedMotorNode

The `EncodedMotorNode` class is a more complex node that combines multiple neurons to control a motor with an encoder.

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

- `void setLerp(float newSpeed, float newAcceleration)` -  Sets the speed and acceleration of the internal lerp object.

### MixNode

The `MixNode` class combines the values of two input neurons using a chosen mixing mode.

- `void setMode(Mixer::mode newMode)` - Sets the mixing mode for the node, determining how the two input values are combined.

### SustainNode
The `SustainNode` class holds its output value at the last input value that exceeded a specified threshold or, if no threshold is set, it will hold the highest received input.

- `void setTime(float newTime)` -  Sets the duration of the sustain timer.
- `void setLevel(float newLevel)` -  Sets the threshold level for the sustain node. If the threshold is zero, the sustain node will hold the highest input value. If the threshold is non-zero, the sustain node will act as a gate.
