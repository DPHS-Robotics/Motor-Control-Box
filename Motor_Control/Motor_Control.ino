#include <Servo.h>;
int percentL, percentR;
int potL, potR;

Servo Right;
Servo Left;
  
void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  Right.attach(11);
  Left.attach(10);
  Serial.begin(9600);
}

void loop() {
  potL = analogRead(A0);
  potR = analogRead(A1);
  percentL = map(potL, 1023, 0, 50, 140);
  percentR = map(potR, 1023, 0, 50, 140); 
  Serial.print("Left: ");
  if (percentL <= 88)
  {
    Serial.print(map(percentL, 88, 50, 0, 100));
    Serial.print("%rev");
  }
  else if (percentL >= 100)
  {
    Serial.print(map(percentL, 100, 140, 0, 100));
    Serial.print("%fwd");
  }
  else
  {
    Serial.print("neutral");
  }
  Serial.print("  -  Right: ");
  if (percentR <= 88)
  {
    Serial.print(map(percentR, 88, 50, 0, 100));
    Serial.print("%rev");
  }
  else if (percentR >= 100)
  {
    Serial.print(map(percentR, 100, 140, 0, 100));
    Serial.print("%fwd");
  }
  else
  {
    Serial.print("neutral");
  }
  Serial.print("\n");
  Left.write(percentL);
  Right.write(percentR);
}
