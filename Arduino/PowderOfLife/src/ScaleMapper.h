/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  Scale Mapper

  ===========================

	This Scale Mapper quantizes an input to a spcified scale. You can put it into various
	modes, set the start and end points, and the mapper will automatically return the correct
	frequency (with rollover for octaves).

	See below for full list of resources.

  Note: This class is HUGE for Arduino due to the large arrays. It can use 300 bytes of memory!
    But, you only incur this if you call map() (or any method that accesses the arrays).
    And, it is a static class so you only pay for it once.

  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2026
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

  ==================================================================================================== */



#define CHROMATIC_LENGTH 12
#define NUMBER_OF_SCALES 23

class ScaleMapper {

  private:
    ScaleMapper();
    // Static properties need to be defined just like methods to be able to be accessed within static methods (rewrite this)
    static float BaseScale_JustTuning[CHROMATIC_LENGTH];
    static float BaseScale_EqualTuning[CHROMATIC_LENGTH];
    static byte ScaleMappings[NUMBER_OF_SCALES][CHROMATIC_LENGTH];

    //static int GetNotePositionInScale(int i, byte scale);
    static float GetTunedRatio(byte note, byte tuning);
    const static int numberOfScales = NUMBER_OF_SCALES;
    static int rolloverCalculation(int input, int rollover);
    static int octaveCalculation(int input, int rollover);

  public:


    // TODO, static types should be here... but I get an "undefined reference" error
    // Why work they not work? Enums and methods work fine as static... but not these variables

    // Enums -- order of optins must match the scale / chord charts

    enum scales : byte {
      // 3 tone: Triad chords
      majorTriad, minorTriad, augmentedTriad, diminishedTriad,
      // 4 tone: Seventh chords
      majorSeventh, minorSeventh, dominantSeventh, augmentedSeventh, diminishedSeventh,
      // 5 tone: Pentatonics
      pentatonicMajor, pentatonicMinor, 
      // 6 tone
      blues, wholeTone, 
      // 7 tone: Diatonic modes
      ionian, dorian, phrygian, lydian, mixolydian, aeolian, locrian,
      // 8 tone
      octatonic, 
      // 12 tone
      circleOfFifths, chromatic
    };

    // meta-scale... dark to light (Berklee style)
    // Sevenths: augmented(4), major(1), dominant(3), minor(2), diminished(5)
    // Diatonic: lydian(4), ionian(1), mixolydian(5), dorian(2), phrygian(3), aeolian(6), locrian(7)

    enum tunings : byte { just, equal };
    enum mappings : byte { pitch, position };


    static int getNumberOfScales();
    static byte getScaleLength(scales scale); // make byte
    static float map(float input, float base = 0, float modulate = 0, int transpose = 0, byte scale = scales::ionian, byte mapping = mappings::position, byte tuning = tunings::equal);


};

ScaleMapper::ScaleMapper() {
}

int ScaleMapper::getNumberOfScales() {
  return numberOfScales;
}

// Tunings
// ... work we need these? can you just use math for equal tuning?
float ScaleMapper::BaseScale_JustTuning[CHROMATIC_LENGTH] = { 1.0f, 1.0417f, 1.1250f, 1.2000f, 1.2500f, 1.3333f, 1.4063f, 1.5000f, 1.6000f, 1.6667f, 1.8000f, 1.8750f };
float ScaleMapper::BaseScale_EqualTuning[CHROMATIC_LENGTH] = { 1.0f, 1.05946f, 1.12246f, 1.18921f, 1.25992f, 1.33483f, 1.41421f, 1.49831f, 1.58740f, 1.68179f, 1.78180f, 1.88775f };

// Scale and chord mappings
byte ScaleMapper::ScaleMappings[NUMBER_OF_SCALES][CHROMATIC_LENGTH] = {
  // 3 tone: Triad chords
  { 1, 5, 8 }, // major triad
  { 1, 4, 8 }, // minor triad
  { 1, 5, 9 }, // augmented triad
  { 1, 4, 7 }, // diminished triad
  // 4 tone: Seventh chords
  { 1, 5, 8, 12 }, // major seventh
  { 1, 4, 8, 11 }, // minor seventh
  { 1, 5, 8, 11 }, // dominant seventh
  { 1, 5, 9, 11 }, // augmented seventh
  { 1, 4, 7, 10 }, // diminished seventh
  // 5 tone: Pentatonics
  { 1, 3, 5, 8, 10 }, // major pentatonic
  { 1, 3, 4, 8, 9 }, // minor pentatonic
  // 6 tone
  { 1, 4, 6, 7, 8, 11 }, // blues
  { 1, 3, 5, 7, 9, 11 }, // whole tone
  // 7 tone: Diatonic modes (W = whole-step, H = half-step)
  { 1, 3, 5, 6, 8, 10, 12 }, // Ionian (I), WWHWWW
  { 1, 3, 4, 6, 8, 10, 11 }, // Dorian (II), WHWWWH
  { 1, 2, 4, 6, 8, 9, 11 }, // Phrygian (III), HWWWHW
  { 1, 3, 5, 7, 8, 10, 12 }, // Lydian (IV), WWWHWW
  { 1, 3, 5, 6, 8, 10, 11 }, // Mixolydian (V), WWHWWH
  { 1, 3, 4, 6, 8, 9, 11 }, // Aeolian (VI), WHWWHW
  { 1, 2, 4, 6, 7, 9, 11 }, // Locrian (VII), HWWHWW
  // 8 tone
  { 1, 2, 4, 5, 7, 8, 10, 11 }, // octatonic
  // 12 tone
  { 1, 8, 3, 10, 5, 12, 7, 2, 9, 4, 11, 6 }, // circle of fifths
  { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 } // chromatic
};




// Simple wrapper for getting the length
byte ScaleMapper::getScaleLength(scales scale) {
  // int length;
  for (byte i = 0; i < CHROMATIC_LENGTH + 1; i++) {
    if (i == CHROMATIC_LENGTH) { // protects from illegal array reference (there is no level 12!)
      return i;
    } else if (ScaleMappings[scale][i] == 0) {
      return i;
    }
  }
}




float ScaleMapper::GetTunedRatio(byte note, byte tuning) {
  // Grab the frequency from the scale array.
  // Use -1 here because the scale list is done in musical notation, with 1 being the first element in the array
  float f;
  // Switch on the tuning type for which array to reference
  switch (tuning) {
    case tunings::just:
      f = BaseScale_JustTuning[note];
      break;
    case tunings::equal:
      f = BaseScale_EqualTuning[note];
      //f = ScaleMappings[4][0];
      break;
  }
  // BaseScale_EqualTuning[ScaleMappings[(byte)s][i] - 1]
  return f;
}



int ScaleMapper::octaveCalculation(int input, int rollover) {
  return floor((float)input / rollover);
}

int ScaleMapper::rolloverCalculation(int input, int rollover) {
  // Modulo over the scale length
  input = input % rollover;
  // Deal with negative input (like doing 1-x)
  input = input < 0 ? rollover + input : input;
  return input;
}

float ScaleMapper::map(float input, float base, float modulate, int transpose, byte scale, byte mapping, byte tuning) {

  //
  //int position;
  int degree; // index in current scale
  int modulatedDegree;
  int note; // chromatic note
  int octave;
  float output;
  byte scaleLength = getScaleLength((ScaleMapper::scales)scale); // CHROMATIC_LENGTH


  // Degree calculation
  // ---

  // map the input against the selected scale to get the scale degree
  degree = (int)Toolkit::mapf(input, (float)0, (float)1, (float)0, (float)scaleLength);
  modulatedDegree = (int)Toolkit::mapf(modulate, (float)0, (float)1, (float)0, (float)scaleLength);


  octave = octaveCalculation(degree, scaleLength);
  degree = rolloverCalculation(degree, scaleLength);
  
//  Serial.print(degree);
//  Serial.print(",");
  
  // calculate the offset (chomatic steps) before combining with degree
  int modulatedDiff = (ScaleMappings[scale][0] - 1) - (ScaleMappings[scale][rolloverCalculation(modulatedDegree, scaleLength)] - 1);

  // modulatedDegree now represents the modulated scale degree
  modulatedDegree = rolloverCalculation(degree + modulatedDegree, scaleLength);


//  Serial.print(modulate);
//  Serial.print(":");


  // Note calculation
  // ---

  //int modulatedNote = ScaleMappings[scale][modulate] - 1;
  // Use the degree to get the correct chromatic note. Note is -1 'cause scales are 1 based
  note =  ScaleMappings[scale][degree] - 1;

  // modulated note
  int modulatedNote = ScaleMappings[scale][modulatedDegree] - 1;

//  Serial.print(note);
//  Serial.print(",");
//  Serial.print(modulatedNote);
//  Serial.print(",");
//  Serial.print(modulatedDiff);



  // Now, we reapply the modulation offset
  octave += octaveCalculation(modulatedNote, CHROMATIC_LENGTH);
  note = rolloverCalculation(modulatedNote + modulatedDiff, CHROMATIC_LENGTH);

  // Add transpose to note value
  note += transpose; 
  
//    Serial.print("=");
//  Serial.print(note);





  // Mapping calculation
  // ---

  switch (mapping) {
    case mappings::position:

      // start with the base
      output = base;

      // Add the note offset
      output += note;

      // Add the octave offset
      output += (octave * CHROMATIC_LENGTH);

      break;
    case mappings::pitch:

      // start with the base
      output = base;

      // Multiply by the note offset
      output *= GetTunedRatio(note, tuning);

      // Multiply by the octave offset
      output *= pow(2, octave);

      break;
    default:
      break;
  }

//    Serial.print("/");
//  Serial.print(output);
//  Serial.println();

  // Finally, return the output
  return output;
}




/*
  =====================================================================
  Lists and charts

  =================
  Chromatic scale numbers on C
  01	C
  02	C#/Db
  03	D
  04	D#/Eb
  05	E
  06	F
  07	F#/Gb
  08	G
  09	G#/Ab
  10	A
  11	A#/Bb
  12	B

  ==================================================================
  Intervals and frequencies:
  ---------------------
  interval		Fraction		Just Scale		Equal Temperament
  Unison			1/1				1.0000			1.0000
  Minor Second	25/24			1.0417 			1.05946
  Major Second 	9/8				1.1250 			1.12246
  Minor Third 	6/5				1.2000 			1.18921
  Major Third 	5/4				1.2500 			1.25992
  Fourth			4/3				1.3333 			1.33483
  Dim. Fifth 		45/32			1.4063 			1.41421
  Fifth 			3/2				1.5000 			1.49831
  Minor Sixth 	8/5				1.6000 			1.58740
  Major Sixth 	5/3				1.6667 			1.68179
  Minor Seventh 	9/5				1.8000 			1.78180
  Major Seventh 	15/8			1.8750 			1.88775
  Octave 			2/1				2.0000 			2.0000
  ==================================================================
*/
