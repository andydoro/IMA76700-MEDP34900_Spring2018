//////////////////////////////////////////////////////////////////
//©2018 Andy Doro
//based on code from bildr
//Released under the MIT License – Please reuse change and share
//Simple code for the ADXL335, prints calculated orientation via serial
//////////////////////////////////////////////////////////////////

//Analog read pins
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;

//LED pins
const int rPin = 3;
const int gPin = 5;
const int bPin = 6;

//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minVal = 265;
int maxVal = 402;

//to hold the calculated values
double x;
double y;
double z;

void setup() {

  // set LED pins to output
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  // LED startup sequence
  // common anode RGB LED so bring LOW to light up
  digitalWrite(rPin, HIGH);
  digitalWrite(gPin, HIGH);
  digitalWrite(bPin, HIGH);

  delay(500);

  // write red
  digitalWrite(rPin, LOW);
  delay(500);
  digitalWrite(rPin, HIGH);
  // write green
  digitalWrite(gPin, LOW);
  delay(500);
  digitalWrite(gPin, HIGH);
  //write blue
  digitalWrite(bPin, LOW);
  delay(500);
  digitalWrite(bPin, HIGH);

  Serial.begin(9600);
}

void loop() {

  //read the analog values from the accelerometer
  int xRead = analogRead(xPin);
  delay(1); // apparently a short delay lets the ADC settle, provides better readings
  int yRead = analogRead(yPin);
  delay(1);
  int zRead = analogRead(zPin);
  delay(1);

  //convert read values to degrees -90 to 90 – Needed for atan2
  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);

  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -π to π (radians)
  //We are then converting the radians to degrees
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  //convert for analogWrite LEDs
  int rLed = map(xRead, minVal, maxVal, 0, 255);
  int gLed = map(yRead, minVal, maxVal, 0, 255);
  int bLed = map(zRead, minVal, maxVal, 0, 255);

  //constrain
  rLed = constrain(rLed, 0, 255);
  gLed = constrain(gLed, 0, 255);
  bLed = constrain(bLed, 0, 255);

  //  invert
  rLed = 255 - rLed;
  gLed = 255 - gLed;
  bLed = 255 - bLed;

  // write to RGB LED
  analogWrite(rPin, rLed);
  analogWrite(gPin, gLed);
  analogWrite(bPin, bLed);

  // Output raw values
  Serial.print("raw x: ");
  Serial.print(xRead);
  Serial.print(" | raw y: ");
  Serial.print(yRead);
  Serial.print(" | raw z: ");
  Serial.print(zRead);

  Serial.print(" || ");

  // Output the calculations
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" | y: ");
  Serial.print(y);
  Serial.print(" | z: ");
  Serial.println(z);

  delay(50);//just here to slow down the serial output – Easier to read
}
