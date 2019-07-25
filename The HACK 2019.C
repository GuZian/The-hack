/*

                           本程序仅供  2019 The hack   使用


                       注：Arduino引脚占用:
                       9-chief servo
                       10,11-vice servo



*/

#include <Servo.h>

Servo servo1;  // create servo object to control a servo
Servo servo2;
Servo servo3;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup()
{
  servo1.attach(9);
  servo2.attach(11);
  servo3.attach(10);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  Serial.begin(115200);
}

void loop()
{
  int difA0;
  int difA1;
  int sensorValueA0_1 = analogRead(0);
  int sensorValueA1_1 = analogRead(1);
  delay(100);
  int sensorValueA0_2 = analogRead(0);
  int sensorValueA1_2 = analogRead(1);
  difA0 = abs(sensorValueA0_1 - sensorValueA0_2);
  difA1 = abs(sensorValueA1_1 - sensorValueA1_2);
  Serial.println(difA0);
  Serial.println(difA1);



  int sensorValueA2 = analogRead(2);//steam sensor
  // difA1 = Serial.read();
  bool L1 = false;
  bool L2 = false;
  bool T1 = false;
  bool T2 = false;
  Serial.println(sensorValueA2);


  if (difA0 >= 6) {
    L2 = true;
  }
  if (difA1 >= 6) {
    L1 = true;
  }
  if (sensorValueA2 >= 300) {
    T1 = true;
  }
  if (sensorValueA2 >= 1023) {
    T2 = true;
  }
  cal(L1, L2, T1, T2);
}
void cal(bool L1, bool L2, bool T1, bool T2)
{
  short e = 0;
  if (L2)
  {
    e = 1;

  }
  if (L1 && T2 && T1)
  {
    e = 2;
  }
  else if (L1 && !T1)
  {
    e = 3;
  }
  else if (L1 && T1)
  {
    e = 4;
  }
  else {}
  Serial.print("e=");
  Serial.println(e);
  switch (e) {
    case 1:
      servo1.write(0);
      delay(500);
      servo2.write(0);
      break;
    case 2:
      servo1.write(0);
      delay(500);
      servo2.write(180);
      break;
    case 3:
      servo1.write(180);
      delay(500);
      servo3.write(0);
      break;
    case 4:
      servo1.write(180);
      delay(500);
      servo3.write(180);
      break;
    default:
      break;
  }
  delay(1000);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  if (e > 0)
  {
    delay(2000);
    e = 0;
  }
}
