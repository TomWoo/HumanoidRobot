#include <Servo.h>

Servo servo1; //thumb
Servo servo2; //index
Servo servo3; //middle
Servo servo4; //ring
Servo servo5; //pinky 

void setup() {
  Serial.begin(9600);
  
  servo1.attach(7); 
  servo2.attach(8);
  servo3.attach(9);
  servo4.attach(10);
  servo5.attach(11);
  
  int val1 = 0;
  int val2 = 0;
  int val3 = 0;
  int val4 = 0;
  int val5 = 0;
}


void loop() {
 int val1 = analogRead(1);
 int val2 = analogRead(2);
 int val3 = analogRead(3);
 int val4 = analogRead(4);
 int val5 = analogRead(5);
 
// val1 = map(val1, 30, 70, 0, 180);
// val2 = map(val2, 30, 70, 0, 180);
// val3 = map(val3, 30, 70, 0, 180);
// val4 = map(val4, 30, 70, 0, 180);
 val5 = map(val5, 950, 1000, 0, 180);
// 
// servo1.write(val1);
// servo2.write(val2);
// servo3.write(val3);
// servo4.write(val4);
 servo5.write(val5);
 
// Serial.print(val1);
// Serial.print(',');
// Serial.print(val2);
// Serial.print(',');
// Serial.print(val3);
// Serial.print(',');
// Serial.print(val4);
// Serial.print(',');
 Serial.print(val5);
 Serial.println();
 
 delay(100);
}

