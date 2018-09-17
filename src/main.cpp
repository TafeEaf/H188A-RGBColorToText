#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

int redVal,greenVal,blueVal ;
String checkColour (int redValue , int greenValue , int blueValue);
void mapColourVals( int redCol, int greenCol , int blueCol);

void setup() {
  redVal = 0;
  greenVal = 0;
  blueVal = 0;
  Serial.begin(115200);
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
}


void loop() {
  uint16_t clear, red, green, blue;
  Serial.println("Reading a new color..");

  tcs.setInterrupt(false);      // turn on LED
  delay(60);  // takes 50ms to read
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED

  Serial.println("Row reading:");
  Serial.print("Clear: \t"); Serial.print(clear);
  Serial.print("\tRed: \t"); Serial.print(red);
  Serial.print("\tGreen: \t"); Serial.print(green);
  Serial.print("\tBblue: \t"); Serial.print(blue);

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;

  Serial.println("Value in hexadecimal:");
  Serial.print("Red:");
  Serial.println((int)r, HEX);
  Serial.print("Green: ");
  Serial.println((int)g, HEX);
  Serial.print("Blue: ");
  Serial.println((int)b, HEX);
  Serial.println();

  Serial.println("Value in integer from 0 to 255:");
  Serial.print("Red:");
  Serial.println((int)r);
  Serial.print("Green: ");
  Serial.println((int)g);
  Serial.print("Blue: ");
  Serial.println((int)b);
  Serial.println();

  mapColourVals( (int)r, (int)g, (int)b);
  String colourName = checkColour (redVal, greenVal , blueVal);

  Serial.println("Value in integer from 0 to 5:");
  Serial.print("Red: ");
  Serial.println(redVal);
  Serial.print("Green: ");
  Serial.println(greenVal);
  Serial.print("Blue: ");
  Serial.println(blueVal);
  Serial.println();

  Serial.print("Color readed: ");
  Serial.println(colourName);
  Serial.println();

  delay(2000);  // takes 50ms to read
}

/*
Re-maps a number from one range to another. That is, a value of fromLow would get mapped to toLow, a value of fromHigh to toHigh, values in-between to values in-between, etc.

Syntax
  map(value, fromLow, fromHigh, toLow, toHigh)

Parameters
  value: the number to map

  fromLow: the lower bound of the value’s current range

  fromHigh: the upper bound of the value’s current range

  toLow: the lower bound of the value’s target range

  toHigh: the upper bound of the value’s target range

Returns
  The mapped value.

*/
void mapColourVals( int redCol, int greenCol , int blueCol){
  redVal = map(redCol , 0 , 255 , 0 , 5);
  greenVal = map(greenCol , 0 , 255 , 0 , 5);
  blueVal = map(blueCol , 0 , 255 , 0 , 5);
}

String checkColour (int redValue , int greenValue , int blueValue) {
  switch (redValue) {
    case 5:                 // redValue  5
    case 4:                 // redValue  4
      switch (blueValue) {
        case 5:                 // redValue  4  blueValue  5
        case 4:                 // redValue  4  blueValue  4
          switch (greenValue) {
            case 5:                 // redValue  4  blueValue  4  greenValue  5
            case 4:                 // redValue  4  blueValue  4  greenValue  4
              return "white";
              break;
            case 3:                 // redValue  4  blueValue  4  greenValue  3
            case 2:                 // redValue  4  blueValue  4  greenValue  2
              return "Fuschia Pink";
              break;
            case 1:                 // redValue  4  blueValue  4  greenValue  1
            case 0:                 // redValue  4  blueValue  4  greenValue  0
              return "Magenta";
              break;
          }
          break;
        case 3:                 // redValue  4  blueValue  3
        case 2:                 // redValue  4  blueValue  2
          switch (greenValue) {
            case 5:                 // redValue  4  blueValue  2  greenValue  5
            case 4:                 // redValue  4  blueValue  2  greenValue  4
              return "Yellow Haze";
              break;
            case 3:                 // redValue  4  blueValue  2  greenValue  3
            case 2:                 // redValue  4  blueValue  2  greenValue  2
              return "Salmon";
              break;
            case 1:                 // redValue  4  blueValue  2  greenValue  1
            case 0:                 // redValue  4  blueValue  2  greenValue  0
              return "Deep Pink";
              break;
          }
          break;
        case 1:                 // redValue  4  blueValue  1
        case 0:                 // redValue  4  blueValue  0
          switch (greenValue) {
            case 5:                 // redValue  4  blueValue  0  greenValue  5
            case 4:                 // redValue  4  blueValue  0  greenValue  4
            return "Yellow";
              break;
            case 3:                 // redValue  4  blueValue  0  greenValue  3
            case 2:                 // redValue  4  blueValue  0  greenValue  2
              return "Dark Orange";
              break;
            case 1:                 // redValue  4  blueValue  0  greenValue  1
            case 0:                 // redValue  4  blueValue  0  greenValue  0
              return "Red";
              break;
          }//green
          break;
      }//blue
      break;
    case 3:                 // redValue  3
    case 2:                 // redValue  2
      switch (blueValue) {
        case 5:                 // redValue  2  blueValue  5
        case 4:                 // redValue  2  blueValue  4
          switch (greenValue) {
            case 5:                 // redValue  2  blueValue  4  greenValue  5
            case 4:                 // redValue  2  blueValue  4  greenValue  4
              return "Electric Blue";
              break;
            case 3:                 // redValue  2  blueValue  4  greenValue  3
            case 2:                 // redValue  2  blueValue  4  greenValue  2
              return "Light Slate Blue";
              break;
            case 1:                 // redValue  2  blueValue  4  greenValue  1
            case 0:                 // redValue  2  blueValue  4  greenValue  0
              return "Indigo";
              break;
          }
          break;
        case 3:                 // redValue  2  blueValue  3
        case 2:                 // redValue  2  blueValue  2
          switch (greenValue) {
            case 5:                 // redValue  2  blueValue  2  greenValue  5
            case 4:                 // redValue  2  blueValue  2  greenValue  4
              return "Light Green";
              break;
            case 3:                 // redValue  2  blueValue  2  greenValue  3
            case 2:                 // redValue  2  blueValue  2  greenValue  2
              return "Grey";
              break;
            case 1:                 // redValue  2  blueValue  2  greenValue  1
            case 0:                 // redValue  2  blueValue  2  greenValue  0
              return "Purple";
              break;
          }
          break;
        case 1:                 // redValue  2  blueValue  1
        case 0:                 // redValue  2  blueValue  0
          switch (greenValue) {
            case 5:                 // redValue  2  blueValue  0  greenValue  5
            case 4:                 // redValue  2  blueValue  0  greenValue  4
              return "Charteuse";
              break;
            case 3:                 // redValue  2  blueValue  0  greenValue  3
            case 2:                 // redValue  2  blueValue  0  greenValue  2
              return "Olive";
              break;
            case 1:                 // redValue  2  blueValue  0  greenValue  1
            case 0:                 // redValue  2  blueValue  0  greenValue  0
              return "Maroon";
              break;
          }//green
          break;
      }//blue
      break;
    case 1:                 // redValue  1
    case 0:                 // redValue  0
      switch (blueValue) {
        case 5:                 // redValue  0  blueValue  5
        case 4:                 // redValue  0  blueValue  4
          switch (greenValue) {
            case 5:                 // redValue  0  blueValue  4  greenValue  5
            case 4:                 // redValue  0  blueValue  4  greenValue  4
              return "Cyan";
              break;
            case 3:                 // redValue  0  blueValue  4  greenValue  3
            case 2:                 // redValue  0  blueValue  4  greenValue  2
              return "Azure";
              break;
            case 1:                 // redValue  0  blueValue  4  greenValue  1
            case 0:                 // redValue  0  blueValue  4  greenValue  0
              return "Blue";
              break;
          }
          break;
        case 3:                 // redValue  0  blueValue  3
        case 2:                 // redValue  0  blueValue  2
          switch (greenValue) {
            case 5:                 // redValue  0  blueValue  2  greenValue  5
            case 4:                 // redValue  0  blueValue  2  greenValue  4
              return "Spring Green";
              break;
            case 3:                 // redValue  0  blueValue  2  greenValue  3
            case 2:                 // redValue  0  blueValue  2  greenValue  2
              return "Teal";
              break;
            case 1:                 // redValue  0  blueValue  2  greenValue  1
            case 0:                 // redValue  0  blueValue  2  greenValue  0
              return "Navy";
              break;
          }
          break;
        case 1:                 // redValue  0  blueValue  1
        case 0:                 // redValue  0  blueValue  0
          switch (greenValue) {
            case 5:                 // redValue  0  blueValue  0  greenValue  5
            case 4:                 // redValue  0  blueValue  0  greenValue  4
              return "Green";
              break;
            case 3:                 // redValue  0  blueValue  0  greenValue  3
            case 2:                 // redValue  0  blueValue  0  greenValue  2
              return "Office Green";
              break;
            case 1:                 // redValue  0  blueValue  0  greenValue  1
            case 0:                 // redValue  0  blueValue  0  greenValue  0
              return "Black";
              break;
          }//green
          break;
      }//blue
      break;
  }//red
return "No color detected";
}//close function
