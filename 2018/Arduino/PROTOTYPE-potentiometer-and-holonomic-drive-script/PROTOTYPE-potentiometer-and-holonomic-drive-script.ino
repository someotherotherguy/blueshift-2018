/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo frontLeft;  // create servo object to control a servo
Servo frontRight;
Servo backLeft;
Servo backRight;
Servo center; //6
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  frontLeft.attach(8);  // attaches the servo on pin 6 to the servo object
  frontRight.attach(12);
  backLeft.attach(10);
  backRight.attach(4);
  center.attach(6);
  frontLeft.writeMicroseconds(1500);
  frontLeft.writeMicroseconds(1500);
  frontLeft.writeMicroseconds(1500);
  frontLeft.writeMicroseconds(1500);
  frontLeft.writeMicroseconds(1500);
  delay(7000);
  Serial.begin(9600);
  Serial.println("begin");
}

void loop() {
  delay(5);
  int pos = analogRead(A0);
  

  float x = joystickCorrection(A0);
  float y = joystickCorrection(A3); //these first two are the joystick's x and y (centered at ~512, corrected to be within -90 and 90)
  float r = 0;//joystickCorrection(A4);
  float z = joystickCorrection(A5);

  float flDeg = constrain( x + y + r + 90, 0.0, 180.0);//microseconds contsrain: constrain( x + y + r + 400.0, 1100.0, 1900.0);
  float frDeg = constrain( x - y + r + 90, 0.0, 180.0);
  float blDeg = constrain(-x + y + r + 90, 0.0, 180.0);
  float brDeg = constrain(-x - y + r + 90, 0.0, 180.0);//adds/subtracts x y and z, then centers at 90 degrees

  int fl = degToMicro(flDeg);
  int fr = degToMicro(frDeg);
  int bl = degToMicro(blDeg);
  int br = degToMicro(brDeg);

  Serial.println(x);
  Serial.println(y);
  Serial.println(fr);
//  Serial.println(bl);
//  Serial.println(br);

  frontLeft.writeMicroseconds(fl);
  frontRight.write(fr);
  backLeft.write(bl);
  backRight.write(br);
  center.write(constrain(degToMicro(z), 1100, 1900));
  
  //the magic f = y + x + r stuff hereish
  
}

float joystickCorrection(int pin) {
  float joystickValue = analogRead(pin)/1023.0*180.0-90; //returns between -90 and 90, so that way middle position is zero (no motion)
  //float joystickValue = analogRead(pin)/1023.0*800.0+1100.0;
  if (joystickValue > -10 && joystickValue < 10) {
    return 0.0;
  } else {
    if (joystickValue > 0) {
      return joystickValue*1.111 - 10;
    } else {
      return joystickValue*1.111 + 10;
    }
  }
}

int degToMicro(float deg) {
  int micro = (int) ((deg / 180) * 800 + 1100);
  return micro;
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
