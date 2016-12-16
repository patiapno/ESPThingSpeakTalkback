#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ThingSpeak.h"
#include <ESPThingSpeakTalkback.h>

#define ssid "XXXXXXXXXXXX"
#define pass "YYYYYYYYYYYY"

#define Thing_key "QQQQQQQQQQQQQQQQQ"
#define Thing_read "XXXXXXXXXXXXXXXX"
int ch_num = 11111;
#define Talk_id "KKKKKKKK"
#define Talk_key "WWWWWWWWWWW"
#define command_id "000000000"
ESPThingSpeakTalkback Thing_talk(Thing_key,Talk_id,Talk_key,Thing_read);
void setup() {
  Serial.begin(115200);
  Serial.println("\nWorking connected");
  Thing_talk.begin_nom(ssid,pass);
  Thing_talk.thingspeakbegin();
  delay(500);
}

void loop() {
  Serial.println(Thing_talk.getCommands2(command_id));
  /*Thing_talk.thingspeakwrite(ch_num,1,12.36);
  Thing_talk.thingspeakwrite(ch_num,2,17.36);*/
  float data[2]={17.6,13.5};
  Thing_talk.thingspeakwritemultiple(2,data,ch_num);
  Serial.println();
  Serial.println("THING READ");
  Serial.println(Thing_talk.thingspeakread(ch_num,1));
  Serial.println("==========");
  delay(20*1000);
}
