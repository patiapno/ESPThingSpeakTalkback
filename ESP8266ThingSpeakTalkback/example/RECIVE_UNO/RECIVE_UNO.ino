#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <SoftwareSerial.h>

SoftwareSerial serial(0,1); //rx,tx
RTC_DS3231 rtc;
#define pin_1 2    //light
#define pin_2 3   //pump
#define pin_3 4   //air
void setup() {
  Wire.begin();
  rtc.begin();
  Serial.begin(115200);
  serial.begin(115200);
  //Serial.println("Arduino uon control device!!");
  pinMode(pin_1,OUTPUT);
  pinMode(pin_2,OUTPUT);
  pinMode(pin_3,OUTPUT);
  Serial.println("OPEN\n");
  digitalWrite(pin_1,LOW);
  digitalWrite(pin_2,LOW);
  digitalWrite(pin_3,LOW);
  delay(1000);
  Serial.println("CLOSE\n");
  digitalWrite(pin_1,HIGH);
  digitalWrite(pin_2,HIGH);
  digitalWrite(pin_3,HIGH);
  delay(500);
}

void loop() {
  DateTime now=rtc.now();
  float Temp=rtc.getTemperature();
  int Hour=now.hour();
  int Minute=now.minute();
  float Soil=analogRead(A0);
  if(serial.readString())
  {
    if(serial.readString()=="light_hr") //ถามเวลา ว่าเปิด/ปิด ได้หรือยัง
    {
      Serial.print(Hour);
    }
    if(serial.readString()=="light_min") //ถามเวลา ว่าเปิด/ปิด ได้หรือยัง
    {
      Serial.print(Minute);
    }
    if(serial.readString()=="temp")
    {
      Serial.print(Temp);
    }
    if(serial.readString()=="soil")
    {
      Serial.print(Soil);
    }
    if(serial.readString()=="Open_light")
    {
      Serial.print("LIHGT ON");
    }
    if(serial.readString()=="Close_light")
    {
      Serial.print("LIHGT OFF");
    }
    if(serial.readString()=="Open_pump")
    {
      Serial.print("PUMP ON");
    }
    if(serial.readString()=="Close_pump")
    {
      Serial.print("PUMP OFF");
    }
    if(serial.readString()=="Open_air")
    {
      Serial.print("AIR ON");
    }
    if(serial.readString()=="Close_air")
    {
      Serial.print("AIR OFF");
    }
  }
  delay(5*1000);
}
