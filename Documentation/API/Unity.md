# Unity Library API

LOL... TODO... comment yer code or it can't make an API.
But here is a list of components anyway for reference. 
Better descriptions coming soon.

## Index

- [Drivers](#drivers)
    - [Animator Driver](#animatordriver)
    - [Audio Driver](#audiodriver)
    - [Blendshape Driver](#blendshapedriver)
    - [Camera Driver](#cameradriver)
    - [Canvas Driver](#canvasdriver)
    - [Despawn Driver](#despawndriver)
    - [Game Object Active Driver](#gameobjectactivedriver)
    - [Growth Driver](#growthdriver)
    - [Light Driver](#lightdriver)
    - [Material Driver](#materialdriver)
    - [Rigidbody Driver](#rigidbodydriver)
    - [Scene Load Driver](#sceneloaddriver)
    - [Serial Driver](#serialdriver)
    - [Spawn Driver](#spawndriver)
    - [Text Driver](#textdriver)
    - [Transform Driver](#transformdriver)

- [Generators](#generators)
    -   [Beat Generator](#beatgenerator)
    -   [Continuous Generator](#continuousgenerator)
    -   [Random Generator](#randomgenerator)

- [Nodes](#nodes)
    - [CloneNode](#clonenode)
    - [CurveNode](#curvenode)
    - [EncodedMotorNode](#encodedmotornode)
    - [LerpNode](#lerpnode)
    - [MixNode](#mixnode)
    - [SerialNode](#serialnode)
    - [SustainNode](#sustainnode)

- [Sensors](#sensors)
    - [Audio Sensor](#audiosensor)
    - [Button Sensor](#buttonsensor)
    - [Collision Sensor](#collisionsensor)
    - [Microphone Sensor](#microphonesensor)
    - [Rigidbody Sensor](#rigidbodysensor)
    - [Screen Sensor](#screensensor)
    - [Serial Sensor](#serialsensor)
    - [Transform Sensor](#transformsensor)


## Drivers

### AnimatorDriver

**Description:** Controls parameters of an Animator component.

*   SetupDriver()
*   RecordBaselineValues()
*   Do()

### AudioDriver

**Description:** Controls an audio source component.

*   SetupDriver() - sets the audio source to drive and initializes a timer.
*   RecordBaselineValues()
*   Do() - plays the audio source when triggered and blends the baseline pitch and volume with the input signal.

### BlendshapeDriver

**Description:** Controls a blendshape on a skinned mesh renderer.

*   SetupDriver() - Gets the skinned mesh renderer and blendshape index.
*   RecordBaselineValues() - Records the blendshape's initial weight.
*   Do() - Sets the blendshape weight by blending the baseline value with the input signal.

### CameraDriver

**Description:** Controls properties of a camera.

*   Do() - modifies camera properties like background color, field of view, and clipping planes, based on the input signal and selected output type.
*   RecordBaselineValues() - Records the initial values of the camera's properties.
*   SetupDriver() - Gets the camera component from the target object.

### CanvasDriver

**Description:** Controls properties of a canvas group, such as its alpha or scale factor.

*   Do() - Modifies the canvas group's alpha or scale factor by blending baseline values with the input signal.
*   RecordBaselineValues() - Records the initial alpha and scale factor of the canvas group.
*   SetupDriver() - Gets the canvas group component from the target object.

### DespawnDriver

**Description:** Destroys the game object when triggered.

*   Do() - Checks if the input signal exceeds the trigger threshold and destroys the game object.
*   SetupDriver()

### GameObjectActiveDriver

**Description:** Activates or deactivates the game object based on the input signal.

*   SetupDriver() - Initializes the state change timer.
*   RecordBaselineValues()

### GrowthDriver

**Description:** This driver is not functional yet.

*   Do()
*   SetupDriver() - Logs an error message.
*   RecordBaselineValues()

### LightDriver

**Description:** Controls properties of a light component, like intensity and color.

*   SetupDriver() - Gets the light component.
*   RecordBaselineValues() - Records the initial intensity and color of the light.
*   Do() - sets the light color by lerping between the baseline and target colors based on the input signal. If the driver is configured to drive intensity, it sets the intensity by blending the baseline intensity with the input signal using the selected output blending mode.

### MaterialDriver

**Description:** Controls properties of a material.

*   Do() - Changes the material color or alpha based on input signal and output type selection.
*   RecordBaselineValues() - Records the material's initial color.
*   SetupDriver() - Gets the Renderer component from the target object.

### RigidbodyDriver

**Description:** Applies forces and torque to a Rigidbody component.

*   Do() - Applies forces or modifies Rigidbody properties like mass, drag, and angular drag based on the input signal and selected output type.
*   SetupDriver() - Gets the Rigidbody component.
*   RecordBaselineValues() - Records initial values for mass, drag, and angular drag of the Rigidbody.

### SceneLoadDriver

**Description:** Loads a new scene when the input signal exceeds a threshold.

*   Do() - checks if the input signal is above the trigger threshold. If it is, it gets the current scene, logs the scene name, and loads the new scene using SceneManager.LoadScene.
*   SetupDriver() 

### SerialDriver

**Description:** Sends data to a device over a serial port. This requires a SerialNode to manage the port.

*   SetupDriver() - sets the frame rate to 0.03f.

### SpawnDriver

**Description:** Spawns a new game object with the SpawnDriverChild component.

*   Do() - checks if spawn on trigger is true, and if so, it checks if the input signal is above the trigger threshold. If both conditions are met, it spawns the new game object using Instantiate.

### TextDriver

**Description:** Controls the text content of a Text component.

*   Do() - Updates the text content by either appending the input signal to the baseline text or replacing the text with the input signal.
*   RecordBaselineValues() - Stores the initial text content.
*   SetupDriver() - Gets the Text component.

### TransformDriver

**Description:** Modifies the position, rotation, or scale of a Transform.

*   Do() - Changes the Transform's position, rotation, or scale based on the input signal, selected output type, and specified output axis.
*   RecordBaselineValues() - Records initial values for position, rotation, and scale of the Transform.
*   SetupDriver() - Gets the Transform component. 


## Generators

### BeatGenerator

(description goes here)

*   SetTimers()

### ContinuousGenerator

(description goes here)

*   SetupGenerator()
*   Do()
*   RecordBaselineValues()

### RandomGenerator

(description goes here)

*   SetupTimers()

**Analysis of Sources:** The source code reveals the names of the Generator classes and their associated methods, but it does not provide explicit descriptions of their functionality.  

## Nodes

### CloneNode

**Description:** The `CloneNode` replicates the input value from another neuron as its output, allowing a signal to be directed to multiple destinations within the network.

**Methods:**

* `work()` - Replicates the input value.
* `setValue(float newValue)` - Sets the internal value of the CloneNode.

### CurveNode

**Description:** The `CurveNode` applies mathematical curves to signal values, acting as a non-linear signal processor to alter the response characteristics of other nodes. It uses the `Curvinator` class for curve calculations.

**Methods:**

* `work()` - Applies the specified curve to the input value.
* `setCurve(Curvinator::mode newCurve, float newExponent = 2)` -  Sets the type of curve and exponent to use.

### EncodedMotorNode

**Description:** A complex node that combines multiple neurons to create a neural cluster for controlling an encoded motor. It utilizes `EncoderSensor`, `ButtonSensor`, and `MotorDriver`.

**Methods:**

* `work()` - Updates the node's state and processing based on the chosen encoding mode (analog or digital).
* `workFast()` -  Updates the connected sensors (`encoderAnalog`, `encoderDigital`, `buttonA`, `buttonB`).
* `wake()` - Initializes the node.
* `setPin(int mdPin1, int mdPin2, int mePin)` -  Sets the pins for the motor driver and motor encoder for analog mode.
* `setPin(int mdPin1, int mdPin2, int mePin1, int mePin2, int esPin1 = -1, int esPin2 = -1, bool mePullup = true, bool esPullup = true)` - Sets the pins for the motor driver, motor encoder, and optional endstops for digital mode.
* `setSteps(int newSteps)` - Sets the number of steps for the motor in digital mode, works only with one or no endstop.
* `getSteps()` - Returns the number of steps set for the motor.
* `setLerp(float newSpeed, float newAcceleration)` - Sets the speed and acceleration of the internal `LerpNode`.
* `setBehavior(behaviorMode newBehavior)` - Sets the motor's behavior mode (undefined, endstopA, endstopB, standard).
* `getBehavior()` - Returns the current behavior mode of the motor.
* `getEndstopState(bool index)` - Returns the state of the specified endstop (0 or 1).
* `getEncodingMode()` -  Returns the current encoding mode (analog or digital).
* `setEncodingMode(encodingMode newMode)` -  Sets the encoding mode (analog or digital).
* `setMotorStartSpeed(float newSpeed)` - Sets the motor's startup speed.
* `setAnalogWindow(int rangeMin, int rangeMax)` - Sets the analog input window for the encoder in analog mode.

### LerpNode

**Description:** A wrapper for the `RailcarLerp` class, the `LerpNode` smooths out signals between two nodes, reducing noise or jerky behavior.

**Methods:**

* `work()` - Updates the lerp based on the input value and sets the internal value to the lerped value.
* `wake()` - Initializes the node.
* `setLerp(float newSpeed, float newAcceleration)` -  Sets the speed and acceleration of the lerp.

### MixNode

**Description:** A wrapper for the `Mixer` class, the `MixNode` blends the signals of two neurons based on a chosen blending mode to produce a mixed output.

**Methods:**

* `work()` - Blends the input values using the specified mixing mode and sets the internal value to the result.
* `setMode(Mixer::mode newMode)` - Sets the mixing mode to use for blending the input signals.

### SerialNode

**Description:** The `SerialNode` manages serial communication, opening and managing the serial port for use by `SerialSensor` and `SerialDriver` for sending and receiving messages.

**Methods:**

* `work()` - Checks and processes incoming serial data.
* `wake()` - Initializes the node and sets the serial rate if not already defined.
* `setSerial(serialRate newRate)` - Sets the serial rate using the predefined options (debug, standard, midi).
* `setSerial(unsigned int newRate)` - Sets the serial rate using a custom baud rate.
* `getPortData(byte channelName)` - Retrieves data from the specified channel.
* `setPortData(byte channelName, float newValue)` - Sends data to the specified channel.
* `setDepth(byte newDepth)` - Sets the decimal precision for float values in serial communication.


### SustainNode

**Description:** The `SustainNode` maintains a signal at a certain level for a specified duration, useful for holding a state or extending the duration of an event.

**Methods:**

* `work()` - Updates the node's state, handling the sustain behavior based on input and threshold settings.
* `setThreshold(float newThreshold)` - Sets the threshold value that triggers the sustain.
* `setDuration(float newDuration)` - Sets the duration for the sustain.
* `setHoldHigh(bool newHold)` - Sets whether the sustain should hold the signal high or low.


## Sensors

### AudioSensor

**Description:** Reads from an Audio Source component. Uses spectral analyser to create an array of amplitudes.

*   SetupSensor() - Sets the output resolution and gets the audio source.
*   Do() - Gets the spectrum data and sets the output data.
*   RecordBaselineValues()

### ButtonSensor

**Description:** Reads from a canvas button component.

*   SetupSensor() - Gets the button component and sets up the sustain timer.
*   Do() - If the button is active, the sustain timer is reset. If the sustain timer times out, the output data is set to 0.
*   RecordBaselineValues()
*   OnClick() - This method is called when the button is clicked. It sets the button to active and resets the sustain timer.

### CollisionSensor

**Description:** Detects collisions with other game objects.

*   SetupSensor() - Sets the output resolution and checks if collision validation is needed.
*   Do() -  Checks for collisions and sets the output data based on the collision point.
*   RecordBaselineValues()
*   OnCollisionEnter() - Called when a collision occurs.
*   OnCollisionStay() - Called every frame while a collision persists. 
*   OnCollisionExit() - Called when a collision ends.
*   resetOutputData() - Resets the output data to 0.

### MicrophoneSensor

**Description:** This sensor is currently non-functional, but it is designed to read audio data from a microphone.

*   SetupSensor() - Logs a warning that the sensor is not functional.
*   Do() 
*   RecordBaselineValues()

### RigidbodySensor

**Description:** Reads data from a Rigidbody component, such as velocity and angular velocity.

*   SetupSensor() - Gets the rigidbody component and sets the output resolution.
*   Do() -  Sets the output data based on the selected input type, such as velocity or angular velocity.
*   RecordBaselineValues()

### ScreenSensor

**Description:** This sensor does not have any explicitly stated functionality in the sources, but based on the comments, it may be used to pin other objects to the edges of the screen.

*   SetupSensor()
*   Do()
*   RecordBaselineValues()

### SerialSensor

**Description:** Reads data from a device over a serial port. This requires a SerialNode to manage the port.

*   work() - Gets the updated value from the serial node.
*   setSerialNode(SerialNode&amp; newNeuron, byte newChannel) - Sets the serial node and channel number.
*   getSerialNode() - Returns the serial node.

### TransformSensor

**Description:** Reads data from a Transform component, such as position, rotation, and scale.

*   SetupSensor() - Sets the output resolution and gets the transform.
*   Do() -  Sets the output data based on the selected input type (position, rotation, or scale).
*   RecordBaselineValues() - Records the baseline values for the transform.

