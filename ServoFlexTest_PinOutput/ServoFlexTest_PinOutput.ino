// 2 elbow flex sensors, 3 dof for 2 shoulder gyros, 2 dof for neck gyro, 2 locomotion

#include <Servo.h>

// APinOutput
const int kAPin0 = 1; // set first pin: A0??
const int kNumFingers = 5;
//int APins[kNumFingers]; // pins: A0-A5
//int APinVals[kNumFingers]; // pin values
int baudRate = 9600;

// Servos
//Servo servo1; //thumb
//Servo servo2; //index
//Servo servo3; //middle
//Servo servo4; //ring
//Servo servo5; //pinky
const int kServoPin0 = 7;
//const int kNumFingers = 5;
Servo servos[kNumFingers];

// Calibration
//const int kNumFingers = 6;
int lower[kNumFingers];
int upper[kNumFingers];

void setup() {
  for (int i=0; i<kNumFingers; i++) {
//    pinMode(kAPin0+i, INPUT);
//    pinMode(kServoPin0+i, OUTPUT);
    servos[i].attach(kServoPin0+i);
  }
  
  Serial.begin(baudRate);
  // Check whether Processing GUI is running
  establishContact();
  
//  servo1.attach(7); 
//  servo2.attach(8);
//  servo3.attach(9);
//  servo4.attach(10);
//  servo5.attach(11);
//  for(int i=0; i<kNumFingers; i++) {
//    servos[i].attach(kServoPin0+i);
//  }
}

void loop() {
//   int val1 = analogRead(1);
//   int val2 = analogRead(2);
//   int val3 = analogRead(3);
//   int val4 = analogRead(4);
//   int val5 = analogRead(5);
// 
//   Serial.print(val1);
//   Serial.print(',');
//   Serial.print(val2);
//   Serial.print(',');
//   Serial.print(val3);
//   Serial.print(',');
//   Serial.print(val4);
//   Serial.print(',');
//   Serial.print(val5);
//   Serial.println(' ');
  
  int APinVals[kNumFingers];
  
  for(int i=0; i<kNumFingers; i++) {
    APinVals[i] = analogRead(kAPin0+i);
//    Serial.print(APinVals[i]);
//    Serial.print(' ');
  }
//  Serial.println();
 
// val1 = constrain(map(val1, lower[0], upper[0], 0, 180), 0, 180);
// val2 = constrain(map(val2, lower[1], upper[1], 0, 180), 0, 180);
// val3 = constrain(map(val3, lower[2], upper[2], 0, 180), 0, 180);
// val4 = constrain(map(val4, lower[3], upper[3], 0, 180), 0, 180);
// val5 = constrain(map(val5, lower[4], upper[4], 0, 180), 1, 179);
 
// servo1.write(val1);
// servo2.write(val2);
// servo3.write(val3);
// servo4.write(val4);
// servo5.write(val5);

  for(int i=0; i<kNumFingers; i++) {
    int val = constrain(map(APinVals[i], lower[0], upper[0], 0, 180), 0, 180);
    servos[i].write(val);
  }

  if (Serial.available()>0) {
    int in = Serial.read();
    if (in==1) { // give pin values to GUI
      for (int i=0; i<kNumFingers; i++) {
        //Serial.println(digitalRead(APins[i]));
        Serial.print(APinVals[i]);
        Serial.print(' ');
      }
//      Serial.println(APinVals[kNumFingers-1]);
      Serial.println();
    }
    if (in==3) { // ask for calibration thresholds
      for (int i=0; i<kNumFingers; i++) {
        lower[i] = APinVals[i];
        Serial.print(lower[i]);
        Serial.print(' ');
      }
//      Serial.println(lower[kNumFingers-1]);
      Serial.println();
    }
    if (in==4) {
      for (int i=0; i<kNumFingers; i++) {
        upper[i] = APinVals[i];
        Serial.print(upper[i]);
        Serial.print(' ');
      }
//      Serial.println(upper[kNumFingers-1]);
      Serial.println();
    }
  }
  
//  for (int i=0; i<kNumFingers-1; i++) {
//    Serial.print(lower[i]);
//    Serial.print(',');
//  }
//  Serial.println(lower[kNumFingers-1]);
//  
//  for (int i=0; i<kNumFingers-1; i++) {
//    Serial.print(upper[i]);
//    Serial.print(',');
//  }
//  Serial.println(upper[kNumFingers-1]);
  
//  pinMode(13, OUTPUT);
//  digitalWrite(13, lower[0]);
  
  delay(10);
}

void establishContact() {
  while (Serial.available()<=0) {
    Serial.println(0);
    delay(100);
  }
}

