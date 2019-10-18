#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define TRIG_PIN 8
#define ECHO_PIN 7
#define TIME_OUT 5000
 
float GetDistance()
{
  long duration, distanceCm;
   
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH, TIME_OUT);
 
  // convert to distance
  distanceCm = duration / 29.1 / 2;
  
  return distanceCm;
}
 
void setup() {  
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lcd.init();       //Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình
  lcd.backlight();
}
 
void loop() {
  lcd.clear();
  long distance = GetDistance();
  lcd.setCursor(0,0);
  lcd.print("Distance to obs:");
  if (distance <= 0)
  {
    Serial.println("Echo time out !!");
    lcd.setCursor(0,1);
    lcd.print("Echo time out !!");
  }
  else
  {   
    Serial.print("Distance to obstacle (cm): ");
    Serial.println(distance);
    lcd.setCursor(0,1);
    lcd.print(distance);
  }
  delay(1000);
}
