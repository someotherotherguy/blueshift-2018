/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Wire.h>

// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

float x = 0.0;
float y = 0.0;
float r = 0.0;
float z = 0.0;

float fl = 90.0;// = 1500
float fr = 90.0;
float bl = 90.0;
float br = 90.0;

bool rotate = true;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  //pinMode(4, INPUT);
}

void loop() {
  delay(200);
  //int pos = analogRead(A0);
//  rotate = digitalRead(4);
//  Serial.println(rotate);

  x = joystickCorrection(A2);
  y = joystickCorrection(A1); //these first two are the joystick's x and y (centered at ~512, corrected to be within -90 and 90)
  
//  if (rotate) {
//    r = joystickCorrection(A0);
//    z = 0;
//  } else {
//    r = 0;
//    z = joystickCorrection(A0);
//  }
  r = 0;//joystickCorrection(A0);
  z = joystickCorrection(A0);

  fl = constrain( x + y + r + 90, 0.0, 180.0);//microseconds contsrain: constrain( x + y + r + 400.0, 1100.0, 1900.0);
  fr = constrain( x - y + r + 90, 0.0, 180.0);
  bl = constrain(-x + y + r + 90, 0.0, 180.0);
  br = constrain(-x - y + r + 90, 0.0, 180.0);//adds/subtracts x y and z, then centers at 90 degrees

  float thrust[4];

  thrust[0] = fl;
  thrust[1] = fr;
  thrust[2] = bl;
  thrust[3] = br;

  Serial.println("begin");
  Serial.println(x);
  Serial.println(y);
  Serial.println(fr);
  Serial.println(bl);
//  Serial.println(br);

  byte data[8];

  for (int i = 0; i < 4; i++) {
    data[i*2] = truncate(thrust[i]);// = (int) (thrust[i] / 100);
    data[i*2+1] = (int) ((thrust[i] - (float)data[i]) * 100);//(int) (thrust[i]-data[i*2];
  }

  //the number splitting function will need to be rewritten to split into 1000s and 10s

  Wire.beginTransmission(9);
  Wire.write(data, 8);
  Wire.endTransmission();

  
  //the magic f = y + x + r stuff hereish
  
}

float joystickCorrection(int pin) {
  float joystickValue = analogRead(pin)/1023.0*180.0-90; //returns between -90 and 90, so that way middle position is zero (no motion)
  if (joystickValue > -10 && joystickValue < 10) {
    return 0.0;
  } else {
    if (joystickValue > 0) {
      return joystickValue - 10;
    } else {
      return joystickValue + 10;
    }
  }
}

float joystickCorrectionMicro(int pin) { //should we (very likely) switch to servo.writeMicroseconds
  float joystickValue = analogRead(pin)/1023.0*800.0+1100.0; //returns between 1100 and 1900
  if (joystickValue > 1475 && joystickValue < 1525) {
    return 1500.0;
  } else {
    if (joystickValue > 1500) {
      return joystickValue - 25;
    } else {
      return joystickValue + 25;
    }
  }
}

int truncate(float value) {
  int thingy = (int) value;
  return thingy;
}

