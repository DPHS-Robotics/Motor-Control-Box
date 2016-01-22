#include <Servo.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
int percentL, percentR;
int potL, potR;
String rightOut, leftOut;
Servo Right;
Servo Left;

// LCD stuff
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
  
  Left.attach(10);
  Right.attach(11);
  lcd.begin(20,4);

  // Switch on the LCD backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.on();
  lcd.setCursor(0, 0);
  lcd.print("Left:  ");
  lcd.setCursor(0, 1);
  lcd.print("Right: ");
}

void loop() {
  potL = analogRead(A0);
  potR = analogRead(A1);
  percentL = map(potL, 1023, 0, 50, 140);
  percentR = map(potR, 1023, 0, 50, 140);
  rightOut = "";
  leftOut = "";
  if (percentL <= 88)
  {
    leftOut += (map(percentL, 88, 50, 0, 100));
    leftOut += ("%rev  ");
  }
  else if (percentL >= 100)
  {
    leftOut += (map(percentL, 100, 140, 0, 100));
    leftOut += ("%fwd  ");
  }
  else
  {
    leftOut += ("neutral");
  }
  if (percentR <= 88)
  {
    rightOut += (map(percentR, 88, 50, 0, 100));
    rightOut += ("%rev  ");
  }
  else if (percentR >= 100)
  {
    rightOut += (map(percentR, 100, 140, 0, 100));
    rightOut += ("%fwd  ");
  }
  else
  {
    rightOut += ("neutral");
  }
  lcd.setCursor(7, 0);
  lcd.print(leftOut);
  lcd.setCursor(7, 1);
  lcd.print(rightOut);
  Left.write(percentL);
  Right.write(percentR);
}
