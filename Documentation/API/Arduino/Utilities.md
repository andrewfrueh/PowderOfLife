## Index
- [Utilities](#utilities)
    - [Curvinator](#curvinator)
    - [Mixer](#mixer)
    - [RailcarLerp](#railcarlerp)
    - [ScaleMapper](#scalemapper)
    - [Timer](#timer)
    - [Toolkit](#toolkit)

## Utilities
### Curvinator
The `Curvinator` class provides various mathematical curves for easing and shaping values.  It is intended to be used statically, meaning you do not create an instance of the class to use it.  Instead, you call its methods directly using the class name, like this: `Curvinator::curve()`.

- `enum mode : byte` -  Defines the available curve types: `none`, `in`, `out`, `inOut`, `outIn`, `bell`, `skew`, and `bathtub`.
- `static float curve(float x, float e, mode newMode, boolean invX=false, boolean invY=false, float c=0.5)` - Applies the selected curve to the input value (`x`) using the provided exponent (`e`) and optional parameters for center point (`c`) and axis inversions (`invX`, `invY`).
- `static float curveIn(float x, float e)` - Applies an "in" curve (ease-in) to the input value (`x`) using the provided exponent (`e`).  The curve starts slowly and accelerates towards the end.
- `static float curveOut(float x, float e)` - Applies an "out" curve (ease-out) to the input value (`x`) using the provided exponent (`e`).  The curve starts quickly and decelerates towards the end.
- `static float curveInOut(float x, float e, float c)`-  Applies an "in-out" curve (ease-in-out) to the input value (`x`) using the provided exponent (`e`) and center point (`c`).  The curve starts slowly, accelerates towards the middle, and then decelerates towards the end.
- `static float curveOutIn(float x, float e, float c)`-  Applies an "out-in" curve (ease-out-in) to the input value (`x`) using the provided exponent (`e`) and center point (`c`).  The curve starts quickly, decelerates towards the middle, and then accelerates towards the end.
- `static float curveBell(float x, float e)` - Applies a bell-shaped curve to the input value (`x`) using the provided exponent (`e`). The curve peaks in the middle and gradually slopes down on both sides.
- `static float curveSkew(float x, float e)` - Applies a skewed curve to the input value (`x`) using the provided exponent (`e`). The curve is asymmetrical, with a steeper slope on one side.
- `static float curveBathtub(float x, float e)` - Applies a bathtub-shaped curve to the input value (`x`) using the provided exponent (`e`).  The curve starts high, dips down in the middle, and then rises again towards the end.

### Mixer
The `Mixer` class is used to blend or combine two input values in various ways. It is also intended to be used statically.

- `enum mode : byte` - Defines the available mixing modes: `add`, `subtract`, `multiply`, `divide`, `screen`, `overlay`, `difference`, `min`, `max`, `less`, `greater`, `modulo`, `power`, `average`, `AND`, `OR`, `NAND`, `NOR`, `XOR`, and `XNOR`.
- `static float Mix(float a, float b, mode newMode)`-  Combines the two input values (`a` and `b`) using the specified mixing mode and returns the result.

### RailcarLerp
The `RailcarLerp` class simulates simple physics to create smooth movement and transitions between values. It can be used to implement smooth movement for animations, motor control, and other applications that require gradual changes over time.

- `void update(float deltaTime)`- Updates the object's position based on its target, velocity, acceleration, and the elapsed time (`deltaTime`) since the last update.
- `void setTarget(float newTarget)` - Sets the desired target value that the object should move towards.
- `float acceleration` - Controls how quickly the object accelerates towards its target.
- `float velocity`- Represents the object's current speed and direction.
- `float position` - Represents the object's current position.
- `float target` -  The desired target value that the object should move towards.
- `float difference` -  The difference between the current position and the target.
- `float maxSpeed` - Limits the object's maximum speed.
- `float defaultAcceleration` - The default acceleration value used by the object.

### ScaleMapper
The `ScaleMapper` class maps an input value to a specific musical scale and tuning, providing functionality for quantizing values to musical notes and generating melodic sequences.

- `enum scales : byte`- Defines a wide range of musical scales and chords, including major and minor triads, seventh chords, pentatonic scales, diatonic modes, octatonic scale, circle of fifths, and chromatic scale.
- `enum tunings : byte` - Defines the available tuning systems: just and equal temperament.  Just tuning uses mathematically pure intervals, while equal temperament divides the octave into 12 equal semitones.
- `enum mappings : byte` - Determines how the input value is mapped to the scale: `pitch` (outputs the frequency of the note) or `position` (outputs the position of the note within the scale).
- `static int getNumberOfScales()` - Returns the total number of scales available.
- `static byte getScaleLength(scales scale)` -  Returns the number of notes in the specified scale.
- `static float map(float input, float base = 0, float modulate = 0, int transpose = 0, byte scale = scales::ionian, byte mapping = mappings::position, byte tuning = tunings::equal)`- This is the core method of the class.  It takes the input value and maps it to a specific note within the selected scale, considering the base frequency, modulation, transposition, mapping type, and tuning.

### Timer
The `Timer` class creates and manages timers for various timing and scheduling tasks.

- `enum units : byte` - Specifies the time units used by the timer: `millisecond` or `microsecond`.
- `void setRate(float newRate)` - Sets the duration of the timer in the specified time units.
- `void setRateMillis(unsigned long newRate)` - Sets the duration of the timer in milliseconds.
- `void setRateMicros(unsigned long newRate)` - Sets the duration of the timer in microseconds.
- `float getRate()` - Returns the timer's duration in the specified time units.
- `unsigned long getCycles()`- Returns the number of times the timer has been triggered since it was created.
- `unsigned long getRemaining()` -  Returns the remaining time in the current timer cycle (in specified time units).
- `float getElapsed()` -  Returns the elapsed time since the timer's last reset.
- `float getRatio()` -  Returns a value between 0.0 and 1.0 representing the timer's progress through its current cycle.  A value of 0.0 indicates the beginning of the cycle, while 1.0 indicates the end.
- `boolean interval()` -  Use this for repeating events.  Returns `true` once per timer cycle when the timer's duration has elapsed.  Then, it automatically resets to `false` and starts a new cycle.
- `boolean timeout()` -  Use this for single-run events.  Returns `true` once when the timer's duration has elapsed. It continues to return `true` until manually reset.
- `void reset()` -  Resets the timer, restarting the current cycle and setting the elapsed time to zero.  It does not reset the cycle count.
- `boolean checkTime()` -  Returns `true` if the specified time has passed, otherwise returns `false`.
- `float getDelta()` - Returns the time difference in seconds between the current frame and the last frame.

### Toolkit
The `Toolkit` class offers a collection of helpful utility functions that can be used throughout the Powder Of Life library. It is designed to be used statically.

- `static int mapi( int x, int in_min, int in_max, int out_min, int out_max )`- Maps an integer value (`x`) from one range (`in_min`-`in_max`) to another (`out_min`-`out_max`), similar to the Arduino `map()` function.
- `static float mapf( float x, float in_min, float in_max, float out_min, float out_max )` - Maps a floating-point value (`x`) from one range to another.
- `static float absf( float x )` - Returns the absolute value of a floating-point number (`x`).
- `static float constrainf(float x, float min, float max)`- Constrains a floating-point value (`x`) to stay within the specified range (`min`-`max`).
- `static int constraini(int x, int min, int max)` - Constrains an integer value (`x`) to stay within the specified range (`min`-`max`).
- `static int getSign( float input )` -  Returns the sign of a floating-point number (`input`) as either 1 (positive), -1 (negative), or 0 (zero).
- `static void printFloat(double number, uint8_t digits)` -  Prints a floating-point number (`number`) to the serial port with a specified number of decimal places (`digits`).
