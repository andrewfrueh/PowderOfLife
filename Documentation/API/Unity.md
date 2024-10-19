# Unity Library API

LOL... TODO... comment yer code or it can't make an API.
But here is a list of components anyway for reference. 
Better descriptions coming soon.

## Index

- [Drivers](#drivers)
    - [AnimatorDriver](#animatordriver)
    - [AudioDriver](#audiodriver)
    - [BlendshapeDriver](#blendshapedriver)
    - [CameraDriver](#cameradriver)
    - [CanvasDriver](#canvasdriver)
    - [DespawnDriver](#despawndriver)
    - [GameObjectActiveDriver](#gameobjectactivedriver)
    - [GrowthDriver](#growthdriver)
    - [LightDriver](#lightdriver)
    - [MaterialDriver](#materialdriver)
    - [RigidbodyDriver](#rigidbodydriver)
    - [SceneLoadDriver](#sceneloaddriver)
    - [SerialDriver](#serialdriver)
    - [SpawnDriver](#spawndriver)
    - [TextDriver](#textdriver)
    - [TransformDriver](#transformdriver)

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

**Description:** Controls animation parameters in Unity's Animator component, enabling animation blending and manipulation based on input signals.

**Methods:**

* `SetupDriver()` - Initializes the `AnimatorDriver` by retrieving and storing a reference to the Animator component on the target game object.


### AudioDriver

**Description:** The `AudioDriver` manipulates audio properties, such as volume and pitch, of an `AudioSource` component.

**Methods:**

* `SetupDriver()` - Initializes the driver by fetching the `AudioSource` component from the target game object, setting up a timer for delayed triggering.
* `RecordBaselineValues()` - Records the initial values of audio properties before any manipulation. 
* `Do()` - Executes the audio manipulation based on input signal and selected output type, applying pitch shift, volume control, or triggering playback. 

### BlendshapeDriver

**Description:** Controls blendshape weights on a `SkinnedMeshRenderer`, allowing for dynamic morphing and deformation of 3D models based on input signals.

**Methods:**

* `SetupDriver()` - Initializes the driver, fetching the `SkinnedMeshRenderer` component, finding the index of the target blendshape, and recording its initial weight. 
* `Do()` -  Adjusts the blendshape weight according to the input signal, smoothly interpolating between the baseline and target values.


### CameraDriver

**Description:** The `CameraDriver` modifies properties of a `Camera` component, such as background color, field of view, and clipping planes, based on input signals.

**Methods:**

* `Do()` - Modifies camera properties (background color, field of view, or clipping planes) based on input signal and chosen output type. 
* `RecordBaselineValues()` - Records the initial values of the camera's background color, field of view, and clipping planes for use as a reference point for blending. 
* `SetupDriver()` -  Initializes the driver by getting the `Camera` component from the targeted game object.


### CanvasDriver

**Description:** The `CanvasDriver` manipulates properties of UI elements within a Canvas, including scaling and transparency. 

**Methods:**

* `Do()` - Modifies either the alpha value of a `CanvasGroup` or the scale factor of a `CanvasScalar`, based on the input signal and chosen output type. 
* `RecordBaselineValues()` - Records the initial values of either the alpha value of the `CanvasGroup` or the scale factor of the `CanvasScalar`, depending on the output type. 
* `SetupDriver()` - Initializes the driver by fetching either the `CanvasGroup` or `CanvasScaler` component based on the chosen output type. 


### DespawnDriver

**Description:** The `DespawnDriver` destroys game objects when triggered by a specific input threshold, used for object removal or lifecycle management.

**Methods:**

* `Do()` - Checks if the input signal exceeds the trigger threshold and destroys the target game object if the condition is met. 
* `SetupDriver()` - Initializes the driver, ensuring the target game object is set. 

### GameObjectActiveDriver

**Description:** Controls the activation and deactivation of game objects based on input signals, allowing for dynamic object visibility and behavior.

**Methods:**

* `SetupDriver()` - Initializes the driver, primarily setting up the timer that governs the delay between state changes.
* `RecordBaselineValues()` - Records the initial activation state of the target game object. 


### GrowthDriver

**Description:** This driver dynamically changes the size of game objects, potentially creating effects of growth or expansion. 

This driver is mentioned in the source, but no methods are given.


### LightDriver

**Description:** The `LightDriver` controls properties of a `Light` component, like intensity and color, based on input signals, allowing for dynamic lighting effects.

**Methods:**

* `SetupDriver()` - Initializes the driver by obtaining the `Light` component from the target game object.
* `RecordBaselineValues()` - Records the initial intensity and color of the light for later blending with the target values.
* `Do()` -  Adjusts the light's intensity or color or both, based on input signal and selected control options, smoothly interpolating between baseline and target values.


### MaterialDriver

**Description:** The `MaterialDriver` dynamically alters properties of a material attached to a `Renderer` component.

**Methods:**

* `Do()` - Modifies material properties, either changing the color (including alpha), based on input signal and chosen output type. 
* `RecordBaselineValues()` - Records the initial color of the material. 
* `SetupDriver()` - Initializes the driver by fetching the `Renderer` component from the target game object. 

### RigidbodyDriver

**Description:** The `RigidbodyDriver` applies forces and torques or modifies properties of a `Rigidbody` component based on input signals, enabling physics-based movement and interaction.

**Methods:**

* `Do()` - Applies forces, torques, or modifies properties of the `Rigidbody` (mass, drag, angular drag) based on input signal and chosen output type.
* `SetupDriver()` - Initializes the driver, primarily getting the `Rigidbody` component and recording baseline values for mass, drag, and angular drag.


### SceneLoadDriver

**Description:**  The `SceneLoadDriver` triggers the loading of a new scene when the input signal crosses a specified threshold.

**Methods:**

* `Do()` - Checks if the input signal surpasses the trigger threshold and if so, loads the specified scene. 

### SerialDriver

**Description:** The `SerialDriver` sends data over a serial port, allowing communication with external devices or other applications. It requires a `SerialNode` to manage the serial port. 

**Methods:**


### SpawnDriver

**Description:** This driver creates new game objects at runtime, potentially with randomized positions, rotations, and scales, driven by input signals. 

**Methods:**

* `Do()` - Spawns a new instance of a predefined prefab, applying optional random offsets to its position, rotation, and scale. 


### TextDriver

**Description:** The `TextDriver` manipulates the text content of a UI `Text` component.

**Methods:**

* `Do()` - Modifies the text content of a `Text` component. It either appends the input signal to the existing text or replaces the text entirely with the input.
* `RecordBaselineValues()` - Records the initial text content of the `Text` component before any manipulation. 
* `SetupDriver()` - Initializes the driver by obtaining the `Text` component from the target game object.


### TransformDriver

**Description:** The `TransformDriver` manipulates the position, rotation, or scale of a game object's `Transform` component based on input signals.

**Methods:**

* `Do()` - Modifies the position, rotation, or scale of the target `Transform`, based on the input signal, chosen output type, and specified axis. 


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

