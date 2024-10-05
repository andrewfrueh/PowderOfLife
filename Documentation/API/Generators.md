## Index
- [Generators](#generators)
    - [BeatGenerator](#beatgenerator)
    - [ContinuousGenerator](#continuousgenerator)
    - [RandomGenerator](#randomgenerator)

## Generators

### BeatGenerator

The `BeatGenerator` class generates a rhythmic pulse, similar to a metronome.

- `void work()` -  Updates the internal value of the beat generator, either using a ramp or by updating the beat state.
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

- `void work()` -  Generates a new random value when the state change timer triggers.
- `float getRandomValue()` -  Returns a random value within the specified range.
- `float randomFloat(float randMin, float randMax)` -  Generates a random float between the specified minimum and maximum values.
- `void setRandomRates(float newUpMin, float newUpMax, float newDownMin, float newDownMax)` -  Sets the minimum and maximum times for both the "up" and "down" states of the random generator.
}