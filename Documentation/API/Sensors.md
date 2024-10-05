## Index
- [Sensors](#sensors)
    - [AnalogSensor](#analogsensor)
    - [ButtonSensor](#buttonsensor)
    - [EncoderSensor](#encodersensor)
    - [MPUSensor](#mpusensor)
    - [PingSensor](#pingsensor)

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