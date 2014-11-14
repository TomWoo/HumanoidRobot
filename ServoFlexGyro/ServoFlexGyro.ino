// 2 elbow flex sensors, 3 dof for 2 shoulder gyros, 2 dof for neck gyro, 2 locomotion

#include <Servo.h>

// APinOutput
const int kAPin0 = 1; // set first pin: A0??
const int kNumFingers = 5;
int baudRate = 9600;

// Servos
const int kServoPin0 = 7;
Servo servos[kNumFingers];

// right hand calibration
int lower[kNumFingers];
int upper[kNumFingers];

// right wrist calibration using photoresistor
int CWThreshold_right, CCWThreshold_right;/////////////////////////////////////////////////////////

void setup() {
  for (int i=0; i<kNumFingers; i++) {
    servos[i].attach(kServoPin0+i);
  }
  
  Serial.begin(baudRate);
  // Check whether Processing GUI is running
  establishContact();
}

void loop() {
  int APinVals[kNumFingers];
  
  for(int i=0; i<kNumFingers; i++) {
    APinVals[i] = analogRead(kAPin0+i);
  }

  for(int i=0; i<kNumFingers; i++) {
    int val = constrain(map(APinVals[i], lower[0], upper[0], 0, 180), 0, 180);
    servos[i].write(val);
  }

  if (Serial.available()>0) {
    int in = Serial.read();
    if (in==1) { // give pin values to GUI
      for (int i=0; i<kNumFingers; i++) {
        Serial.print(APinVals[i]);
        Serial.print(' ');
      }
      Serial.println();
    }
    if (in==3) { // ask for calibration thresholds
      for (int i=0; i<kNumFingers; i++) {
        lower[i] = APinVals[i];
        Serial.print(lower[i]);
        Serial.print(' ');
      }
      Serial.println();
    }
    if (in==4) {
      for (int i=0; i<kNumFingers; i++) {
        upper[i] = APinVals[i];
        Serial.print(upper[i]);
        Serial.print(' ');
      }
      Serial.println();
    }
  }
  
  delay(10);
}

void establishContact() {
  while (Serial.available()<=0) {
    Serial.println(0);
    delay(100);
  }
}

