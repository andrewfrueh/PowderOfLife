# POL Arduino API

This is the reference / API for POL in the Arduino environment. See the examples for usage (available once you install the library in your Arduino IDE).

## Overview of the framework in the Arduino environment

Here is an explanation of how the Engine and Neuron base functionality interact in the provided source code, written for new users:

### Engine and Neuron Interaction

*   The Engine class acts as a container and manager for Neuron objects. It is responsible for starting, updating, and coordinating the behavior of all registered Neurons.
*   Neurons are the basic building blocks of the system and represent different components, such as sensors, drivers, and processing nodes.
*   To use the framework, you create instances of specific Neuron subclasses (e.g., AnalogSensor, MotorDriver) and add them to the Engine using the `addNeuron` method.
*   The `start` method of the Engine initializes all registered Neurons by calling their respective `start` methods. This allows each Neuron to perform any necessary setup operations.
*   The Engine's `update` method is called repeatedly in the main program loop. This method iterates through all registered Neurons and calls their `update` methods, which contain the core logic for each component.
*   Neurons can interact with each other by establishing input-output relationships. The `setInput` method of a Neuron is used to connect it to another Neuron, allowing it to receive data from the connected Neuron.
*   The Engine does not directly handle low-level hardware interactions. Instead, specific Neuron subclasses, such as Sensor and Driver, are responsible for interfacing with sensors and actuators.

### Example

The source code provides an example of using the Engine and Neuron classes:

*   In the `setup` function, an instance of `Engine` is created and several Neurons, including `SerialDriver`, `SerialSensor`, and `SerialNode`, are created and added to the Engine.
*   The `loop` function repeatedly calls the Engine's `update` method, which in turn updates all registered Neurons.

## Index
- [Drivers](Drivers.md#drivers)
    - [AnalogDriver](Drivers.md#analogdriver)
    - [MotorDriver](Drivers.md#motordriver)
    - [MidiDriver](Drivers.md#mididriver)
    - [ServoDriver](Drivers.md#servodriver)
    - [StepperDriver](Drivers.md#stepperdriver)
    - [ToneDriver](Drivers.md#tonedriver)
- [Generators](Generators.md#generators)
    - [BeatGenerator](Generators.md#beatgenerator)
    - [ContinuousGenerator](Generators.md#continuousgenerator)
    - [RandomGenerator](Generators.md#randomgenerator)
- [Nodes](Nodes.md#nodes)
    - [CloneNode](Nodes.md#clonenode)
    - [CurveNode](Nodes.md#curvenode)
    - [EncodedMotorNode](Nodes.md#encodedmotornode)
    - [LerpNode](Nodes.md#lerpnode)
    - [MixNode](Nodes.md#mixnode)
    - [SustainNode](Nodes.md#sustainnode)
- [Sensors](Sensors.md#sensors)
    - [AnalogSensor](Sensors.md#analogsensor)
    - [ButtonSensor](Sensors.md#buttonsensor)
    - [EncoderSensor](Sensors.md#encodersensor)
    - [MPUSensor](Sensors.md#mpusensor)
    - [PingSensor](Sensors.md#pingsensor)

