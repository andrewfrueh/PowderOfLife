## Index
- [Drivers](#drivers)
    - [AnalogDriver](#analogdriver)
    - [MotorDriver](#motordriver)
    - [MidiDriver](#mididriver)
    - [ServoDriver](#servodriver)
    - [StepperDriver](#stepperdriver)
    - [ToneDriver](#tonedriver)

## Drivers

### AnalogDriver

This class is a basic driver that uses the standard Arduino analog output.

- `void setPin(int newPin)` -  Sets the output pin number and sets the pin mode to output. 

### MotorDriver

This class controls a basic DC motor driver board using two pins for direction and speed.

- `void setPin(int newDirPin, int newSpeedPin)` - Sets the direction pin and speed pin for the motor driver and sets their pin modes to output.
- `void setRange(byte newMin, byte newMax)`- Sets the minimum and maximum values for the motor speed.
- `void setReverse(bool newRev)` - Sets whether to invert the motor direction.
- `void setCenter(float newCenter)` - Sets the center point for the motor's normalization.

### MidiDriver

This class sends MIDI messages over the serial port. 

- `void setBase(float newBase)` - Sets the base note for MIDI note calculations.
- `void playNote(byte note, byte velocity = 100, byte channel = 1, bool playStop = true)` - Plays a MIDI note with the specified note number, velocity, and channel. 
- `void stopNote(byte note, byte channel = 1)` - Stops a MIDI note with the specified note number and channel. 
- `void sendClock()` - Sends a MIDI timing clock message.
- `void allNotesOff()` - Sends an "all notes off" MIDI message.

### ServoDriver

The ServoDriver class controls a basic servo motor with standard Arduino PWM output.

- `void setPin(int newPin)` - Sets the output pin for the servo motor and attaches the servo object to the pin.
- `void setRange(byte newMin, byte newMax)` - Sets the minimum and maximum servo positions in degrees.

### StepperDriver

The StepperDriver class controls a basic stepper motor driver board.

- `void setMicrostep(microsteps newStep)` -  Sets the microstepping level for the stepper motor driver.
- `void setMode(modes newMode)` - Sets the mode of the stepper driver, which can be either `range` (absolute positioning) or `rate` (speed and direction).
- `void stepOnce(int dir = 1)` - Steps the motor once in the specified direction.
- `void setPin(int newDirPin, int newStepPin)` - Sets the direction and step pins for the stepper driver and sets the pin modes to output.

### ToneDriver

This class generates audio tones on a specified pin using either hardware (using the `tone()` function) or software (by toggling the pin at a specific frequency).

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
