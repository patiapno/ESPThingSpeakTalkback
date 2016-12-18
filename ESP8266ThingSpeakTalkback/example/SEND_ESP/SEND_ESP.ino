#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ThingSpeak.h>
#include <ESPThingSpeakTalkback.h>
#include <SoftwareSerial.h>
SoftwareSerial serial(D5,D6); //rx,tx

#define ssid "TP-LINK_D3B838"
#define pass "034996393"

#define Thing_write "0UTN3TESA594F39V"
#define Thing_read "A76OA5F3KEPHQV4S"
int ch_num=203958;
#define Talk_id "12266"
#define Talk_key "FD108CTVY6DF8XQU"

#define LIGHT_OPEN "3476690"
#define LIGHT_OFF "3476691"
#define PUMP_ON "3504217"
#define PUMP_OFF "3504218"
#define AIR_ON "3504219"
#define AIR_OFF "3504220"
ESPThingSpeakTalkback Talking(Thing_write,Talk_id,Talk_key,Thing_read);
void setup() {
  Serial.begin(115200);
  serial.begin(115200);
  Serial.println("\nWelcome to ESP8266");
  Talking.begin_nom(ssid,pass);
  Talking.thingspeakbegin();
}

void loop() {
  String light_hr="";   //รับค่าจาก Arduino uno
  String light_min="";
  String pump="";
  String air="";
  while(light_hr=="")
  {
    Serial.println("GET HR");
    serial.print("light_hr");
    light_hr=serial.readString();
    Serial.println(light_hr);
    delay(500);
  }
  while(light_min=="")
  {
    Serial.println("GET MIN");
    serial.print("light_min");
    light_min=serial.readString();
    Serial.println(light_min);
    delay(500);
  }
  while(pump=="")
  {
    Serial.println("GET SOIL");
    serial.print("soil");
    pump=serial.readString();
    Serial.println(pump);
    delay(500);
  }
  while(air=="")
  {
    Serial.println("GET TEMP");
    serial.print("temp");
    air=serial.readString();
    Serial.println(air);
    delay(500);
  }
  Serial.println("==GET==");
  Serial.println(light_hr);
  Serial.println(light_min);
  Serial.println(pump);
  Serial.println(air);
  Serial.println("=======\n");
  int Hr=Convert_toInt(light_hr);
  int Min=Convert_toInt(light_min);
  float Pump=Convert_toFloat(pump);
  float Air=Convert_toFloat(air);
  float keep_data[2]= {Pump,Air};
  Serial.println("===Write mutipule data===");
  Talking.thingspeakwritemultiple(2,keep_data,ch_num);
  Serial.println("=========================\n\n");
  String rest1="";  //รับการตอบสนองจาก Arduino uno
  String rest2="";
  String rest3="";
  while(rest1=="")
  {
    Serial.println("GET rest1\n");
    if(Hr>=15||Hr<8) //off
    {
      if(Min>=10)
      {
        String send_data=Talking.getCommands2(LIGHT_OFF);
        serial.print(send_data);
        rest1=serial.readString();
      }
    }
    else if(Hr>=8) //open
    {
      if(Min>=10)
      {
        String send_data=Talking.getCommands2(LIGHT_OPEN);
        serial.print(send_data);
        rest1=serial.readString();
      }
    }
    Serial.println(rest1);
    delay(500);
  }
  while(rest2=="")
  {
    Serial.println("GET rest2\n");
    if(Pump>=800)
    {
        String send_data=Talking.getCommands2(PUMP_ON);
        serial.print(send_data);
        rest2=serial.readString();
    }
    else if(Pump<=250)
    {
        String send_data=Talking.getCommands2(PUMP_OFF);
        serial.print(send_data);
        rest2=serial.readString();
    }
    Serial.println(rest2);
    delay(500);
  }
  while(rest3=="")
  {
    Serial.println("GET rest3\n");
    if(Air>=30)
    {
        String send_data=Talking.getCommands2(AIR_ON);
        serial.print(send_data);
        //Serial.println(sern_data);
        rest3=serial.readString();
    }
    else if(Air<=26)
    {
        String send_data=Talking.getCommands2(AIR_OFF);
        serial.print(send_data);
        //Serial.println(sern_data);
        rest3=serial.readString();
    }
    Serial.println(rest3);
    delay(500);
  }
  Serial.println("====REST======");
  Serial.println(rest1);
  Serial.println(rest2);
  Serial.println(rest3);
  Serial.println("==============\n\n");
  delay(20*1000);
}

float Convert_toFloat(String data) //แปลงค่า String ไปเป็นเลขทศนิยม
{
  return data.toFloat();
}
int Convert_toInt(String data)
{
  return data.toInt();
}

