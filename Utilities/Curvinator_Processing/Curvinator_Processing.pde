/* ====================================================================================================

  Powder Of Life
  Curvinator Sandbox
  
  ===========================
  
  A sandbox for testing and building Curvinator in Java.
  Processing was chosen as an environment because it's good at drawing.
  
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */


// ================================================================
// Settings for the test curve

// Curve type. Can be: none, in, out, inOut, outIn, bell, skew, bathtub
CurvinatorTypes curveTypeToDraw = CurvinatorTypes.inOut;

// The center of the curve (i.e. x offset). Between 0-1, default is 0.5.
float curveCenterpoint = 0.5;

// The exponent of the curve. 1 is linear.
float curveExponent = 3;

// ================================================================
// Other settings, enter at your own risk (¬‿¬)

int canvasSize = 1000;

int marginSize = int(canvasSize * 0.2);

int graphSize = int(canvasSize - (marginSize*2));

float dotRadius = graphSize/100;

int[] dotPos = {0, 0};
int[] lastPos = {0, 0};

boolean go;

float stepCounter;

float stepSize = 0.01;

float stepMax = 1.0;

int imagePixelCount;


float strokeWeightGuide = 5;
float strokeWeightCurve = 20;
float strokeWeightLevel = canvasSize*stepSize;

void setup() {
  size(1000, 1000);
  //size(819, 1024);
  stroke(0);
  fill(0);

  // noLoop() causes draw() only to run once
  noLoop();
  //
}

// This draw only runs once
void draw() {
  
  SimpleGraph(CurvinatorTypes.inOut, curveExponent);

}

// ==========================================================

void SimpleGraph(CurvinatorTypes curveType, float expo) {

  stepCounter = 0.0;
  dotPos[0] = 0;
  dotPos[1] = 0;
  lastPos[0] = 0;
  lastPos[1] = 0;
  imagePixelCount = 0;
  go = true;

  // clear the canvas
  clear();
  background(255);

  // >> red center-line >>
  stroke(255, 0, 0);
  strokeWeight(strokeWeightGuide);

  line(
    marginSize, 
    int(marginSize+(graphSize)), 
    int(marginSize+graphSize), 
    int(marginSize)
    );
  // << end red center-line


  stroke(0, 0, 0);

  strokeWeight(strokeWeightCurve);
  //strokeJoin(ROUND);
  noFill();

  beginShape();

  while (go==true) {

    go = stepCounter < stepMax ? true : false;

    // this if(go) keeps the action within the bounds of the counter
    if (go==true) {

      float a = Curvinator.Curve(stepCounter, expo, curveType, false, false, curveCenterpoint);
      //float a = Curvinator.Curve(stepCounter, expo, curveType);

      DrawCurve(a);
    }

    stepCounter += stepSize;
  }
  
  endShape();
}

// ==========================================================


public void DrawCurve(float y) {
  // validate input
  y = Float.isNaN(y) ? 0 : y;
  // Set the pos... kind of kludgy, but then so is Processing (slam!)
  dotPos[0] = int(marginSize) + int(map(stepCounter, 0, 1, 0, graphSize));
  dotPos[1] = int(marginSize+(graphSize)) - int(map(y, 0, 1, 0, graphSize));

  vertex(dotPos[0], dotPos[1]);
}


// EOF
