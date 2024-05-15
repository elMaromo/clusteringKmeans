#include "SKM.h"
int delayTime = 20;
char buffer[40];

bool initialiced = false;
SKM stremKmeans;

void setup()
{
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop()
{
  delay(delayTime);
  
  if (Serial.available() > 0)
  {
    if ( !initialiced )
    {
      readSetUpParameters();
    }
    else
    {
      float coord [10];
      readPointFromSerial(coord);
      int result = stremKmeans.funcionStreamKmeans(coord);
  
      sprintf(buffer, "%i", result );
      Serial.println(buffer);
    }
  }
}


void readPointFromSerial(float (& coord) [10])
{
  for( int i = 0; i < stremKmeans.numDimensions; i++ )
  {
    coord[i] = Serial.parseFloat();
  }
}

void readSetUpParameters()
{
  int numKlusters = Serial.parseInt();
  bool forget = Serial.parseInt();
  float learningR = Serial.parseFloat();
  int numDimensions = Serial.parseInt();

  stremKmeans.setUp( numKlusters, forget, learningR, numDimensions );
  initialiced = true;
}



