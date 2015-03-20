#include <Servo.h>

Servo myServo;
int pin = A0;

void setup(){
  Serial.begin(9600);
  pinMode(pin,INPUT);
  myServo.attach(13);
}
void loop(){
  int flex = analogRead(pin);//with 10k resistor, 480-680(bent)
  myServo.write(180*(flex-480)/(680-480));
  delay(100);
}

