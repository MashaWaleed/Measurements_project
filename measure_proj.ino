#include <Servo.h>

#define LDR1 A5
#define LDR2 A4
#define ir 8
bool objectDetected = false;
int Spoint = 90;
int servoAngle = 90;
int servoTarget = 90;

Servo servo1;
Servo servo2;

void solar_tracker();
void auto_door();

void setup() {
  pinMode(ir, INPUT);
  servo1.attach(3);
  servo2.attach(9);
  servo1.write(servoAngle);
  servo2.write(servoAngle);
  delay(1000);
  Serial.begin(9600);
}

void loop() 
{
  solar_tracker();
  auto_door();
}




void solar_tracker(){
  int ldr1 = analogRead(LDR1);
  int ldr2 = analogRead(LDR2);
  
//  Serial.println(ldr1);
//  Serial.println(ldr2);
//  Serial.println("\n");
//  delay(100);


  if ((ldr2 > ldr1) && (ldr2 - ldr1 >= 20)){
    Spoint++;
  }
  else if ((ldr1 > ldr2) && (ldr1 - ldr2 >= 80)){
    Spoint--;
  }
  
  servo1.write(Spoint);
  delay(10);
}





void auto_door(){
  int irValue = digitalRead(ir);
  
  if (irValue == LOW && !objectDetected) {
    objectDetected = true;
    servoTarget = 180;
  }
  
  if (servoAngle != servoTarget) {
    if (servoAngle < servoTarget) {
      servoAngle++;
    }
    else {
      servoAngle--;
    }
    servo2.write(servoAngle);
    delay(10);
  }
  
  else if (servoAngle == servoTarget && objectDetected) {
    delay(1000);
    servoTarget = 90;
    objectDetected = false;
  }
}
