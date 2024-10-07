## Index
- [Generators](#generators)
    - [BeatGenerator](#beatgenerator)
    - [ContinuousGenerator](#continuousgenerator)
    - [RandomGenerator](#randomgenerator)

## Generators

### BeatGenerator

The `BeatGenerator` acts as a digital metronome, generating a rhythmic on-off signal that can drive other components in the system. This is useful for applications that require timed events or synchronized behaviors.

#### Key Features and Methods

1. **Tempo Control (`setTempo(float newTempo)`)**:
   - This method allows you to set the desired tempo of the beat in beats per minute (BPM). 
   - The tempo determines how fast the beat cycles between its on and off states.
   - For example, `beat.setTempo(120);` would set the tempo to 120 BPM.

2. **Decay or Duty Cycle Control (`setDecay(float newDecay, decayMode newMode)`)**:
   - The decay parameter controls the ratio of on-time to off-time within each beat cycle.
   - It essentially governs the duty cycle of the square wave representing the beat.
   - The `decayMode` can be set to either `ratio` or `time`, allowing you to specify the decay as either:
      - A proportion of the beat duration (ratio mode, e.g., 0.5 for a 50% duty cycle).
      - A fixed time in seconds (time mode).

3. **Subdivisions (`setSubdivisions(byte newSubDiv)`)**:
   - While not fully implemented in the provided code, the `BeatGenerator` includes provisions for beat subdivisions. 
   - Subdivisions would allow for more complex rhythms by dividing each beat into smaller units.

4. **Ramp Functionality (`setRamp(bool newRamp)`)**:
   - The `BeatGenerator` can produce a simple ramp waveform (triangle wave) instead of a square wave beat.
   - This ramp cycles smoothly between 0.0 and 1.0 and back down, synchronized with the beat tempo. 

#### Output Signal and Usage

The `BeatGenerator` primarily provides its output as a normalized value (0.0 to 1.0) reflecting its current state:

- **Square Wave Mode:** The output is 1.0 during the "on" portion of the beat and 0.0 during the "off" portion. 
- **Ramp Mode:** The output smoothly transitions between 0.0 and 1.0 and back to 0.0, following a triangular pattern.

Other components in the Powder Of Life framework, such as drivers or other nodes, can use this output signal to synchronize their behavior with the beat. For instance, an `AnalogDriver` connected to an LED could be driven by a `BeatGenerator` to create a flashing LED synchronized to a specific rhythm.

---

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

- `float getRandomValue()` -  Returns a random value within the specified range.
- `float randomFloat(float randMin, float randMax)` -  Generates a random float between the specified minimum and maximum values.
- `void setRandomRates(float newUpMin, float newUpMax, float newDownMin, float newDownMax)` -  Sets the minimum and maximum times for both the "up" and "down" states of the random generator.
}