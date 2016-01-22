#include <Servo.h>;
int percentL, percentR;
int potL, potR;

Servo Right;
Servo Left;

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

  
void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  Right.attach(11);
  Left.attach(10);
  Serial.begin(9600);

  lcd.begin (20,4);

// Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.on();
  lcd.setCursor(0, 0);
  lcd.print("Left: ");
  lcd.setCursor(0, 1);
  lcd.print("Right: ");
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
