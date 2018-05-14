// Include the required Wire library for I2C
#include <Servo.h>

#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 10);

Servo frontLeft;  // create servo object to control a servo
Servo frontRight;
Servo backLeft;
Servo backRight;

int fl = 1500;// 1500
int fr = 1500;
int bl = 1500;
int br = 1500;

int LED = 13;

void setup() {
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  //Wire.begin(9); 
  // Attach a function to trigger when something is received.
  //Wire.onReceive(receiveEvent);

  frontLeft.attach(8);  // attaches the servo on pin 6 to the servo object
//  frontRight.attach(7);
//  backLeft.attach(13);
//  backRight.attach(5);


  frontLeft.writeMicroseconds(1500);  // attaches the servo on pin 6 to the servo object
  frontRight.writeMicroseconds(1500);
  backLeft.writeMicroseconds(1500);
  backRight.writeMicroseconds(1500);

  
  //delay(7000);
  
  mySerial.begin(4800);
  
  Serial.begin(9600);
  Serial.println("cheese moose");
}
//void receiveEvent(int bytes) {
//  int index = 0;
//  int thrust[8];
//  while (mySerial.available()) {
//    thrust[index*2] = mySerial.read();
//    thrust[index*2+1] = mySerial.read();
//    index ++;
//  }

//  fl = intJoin(thrust[0], thrust[1]);// = thrust[0] + thrust[1];
//  fr = intJoin(thrust[2], thrust[3]);
//  bl = intJoin(thrust[4], thrust[5]);
//  br = intJoin(thrust[6], thrust[7]);

  // read one character from the I2C
//  Serial.println(degToMicro(fl));
//  Serial.println(bytes);
//  Serial.println("printed");
//}
void loop() {
  //delay(10);
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
  int index = 0; 
  int thrust[8];
  if (mySerial.available()==8) {
    while (mySerial.available()>0) {
      thrust[index] = mySerial.read();
      index ++;
    }
    fl = degToMicro(intJoin(thrust[0], thrust[1]));// = thrust[0] + thrust[1];
    fr = intJoin(thrust[2], thrust[3]);
    bl = intJoin(thrust[4], thrust[5]);
    br = intJoin(thrust[6], thrust[7]);
    Serial.println("received");
    Serial.println(mySerial.available()); 
  }

  
  
  Serial.println("thrust 0");
  Serial.println(thrust[0]);
  Serial.println(thrust[1]);
  Serial.println(thrust[2]);
  Serial.println(thrust[3]);
  Serial.println(thrust[4]);
  Serial.println(thrust[5]);
  Serial.println(thrust[6]);
  Serial.println(thrust[7]);
  Serial.println(fl);
  
  if (fl < 1900 && fl > 1100) {
    frontLeft.writeMicroseconds(fl);
  } else {
    frontLeft.writeMicroseconds(1500);
    Serial.println("fail");
//    mySerial.end();
//    mySerial.begin(4800);
  }
//  frontRight.write(fr);
//  backLeft.write(bl);
//  backRight.write(br);  
  Serial.println(fl);
}

int intJoin(int intPart, int decimalPart) {
  float flIntPart = (float) intPart;
  float flDecPart = (float) decimalPart;
  return (int) flIntPart + (flDecPart/100);
}

int degToMicro(float deg) {
  int micro = (int) ((deg / 180) * 800 + 1100);
  return micro;
}

