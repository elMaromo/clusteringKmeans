
int delayTime = 20;
char buffer[40];

void setup() 
{
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop()
{
  delay(delayTime);
  
  // reply only when you receive data:
  if (Serial.available() > 0) 
  {
    float coord [3];
    readPointFromSerial(coord);

    // say what you got:
    sprintf(buffer, "1: %f 2: %f 3: %f", coord[0], coord[1], coord[2]);
    Serial.println(buffer);
  }
}


void readPointFromSerial(float (& coord) [3])
{
  coord[0] = Serial.parseFloat();
  coord[1] = Serial.parseFloat();
  coord[2] = Serial.parseFloat();
}