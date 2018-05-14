// Include the required Wire library for I2C
#include <Servo.h>

#include <Wire.h>

Servo frontLeft;  // create servo object to control a servo
Servo frontRight;
Servo backLeft;
Servo backRight;

float fl = 90.0;// 1500
float fr = 90.0;
float bl = 90.0;
float br = 90.0;

int LED = 13;

void setup() {
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);

  frontLeft.attach(11);  // attaches the servo on pin 6 to the servo object
//  frontRight.attach(7);
//  backLeft.attach(13);
//  backRight.attach(5);

  frontLeft.writeMicroseconds(1500);  // attaches the servo on pin 6 to the servo object
  frontRight.writeMicroseconds(1500);
  backLeft.writeMicroseconds(1500);
  backRight.writeMicroseconds(1500);
  
  delay(7000);
  
  Serial.begin(9600);
  Serial.println("cheese moose");
}
void receiveEvent(int bytes) {
  int index = 0;
  int thrust[8];
  while (Wire.available()) {
    thrust[index*2] = Wire.read();
    thrust[index*2+1] = Wire.read();
    index ++;
  }

  fl = intJoin(thrust[0], thrust[1]);// = thrust[0] + thrust[1];
  fr = intJoin(thrust[2], thrust[3]);
  bl = intJoin(thrust[4], thrust[5]);
  br = intJoin(thrust[6], thrust[7]);

  // read one character from the I2C
  Serial.println(degToMicro(fl));
//  Serial.println(bytes);
//  Serial.println("printed");
}
void loop() {
  delay(2);
//  //If value received is 0 blink LED for 200 ms
//  if (fl == 0) {
//    digitalWrite(LED, HIGH);
//    delay(200);
//    digitalWrite(LED, LOW);
//    delay(200);
//  }
//  //If value received is 3 blink LED for 400 ms
//  if (fl == 3) {
//    digitalWrite(LED, HIGH);
//    delay(400);
//    digitalWrite(LED, LOW);
//    delay(400);
//  }

  frontLeft.writeMicroseconds(degToMicro(fl));
//  frontRight.write(fr);
//  backLeft.write(bl);
//  backRight.write(br);  
}

float intJoin(int intPart, int decimalPart) {
  float flIntPart = (float) intPart;
  float flDecPart = (float) decimalPart;
  return flIntPart + (flDecPart/100);
}

int degToMicro(float deg) {
  int micro = (int) ((deg / 180) * 800 + 1100);
  return micro;
}

