#include <Arduino.h>

int a = 0;

void setup()
{
  Serial.begin(9600);
  //pinMode(6,OUTPUT);
}
void loop()
{
  //digitalWrite(6,HIGH);
  delay(1000);
  a = analogRead(A14);
  Serial.println(a);
}
