#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ThingSpeak.h>
#include <ESPThingSpeakTalkback.h>

#define ssid "AAAAAAAAAA"
#define pass "AAAAAAAAAA"

#define Thing_write "AAAAAAAAAA" //write key
#define Thing_read "AAAAAAAAAA" //read key
int ch_num = 0000000000;

//Talkbacks commands
#define Talk_id "AAAAAAAAAA"
#define Talk_key "AAAAAAAAAA"
#define command_id1 "AAAAAAAAAA"
#define command_id2 "AAAAAAAAAA"

ESPThingSpeakTalkback Thing_talk(Thing_write,Talk_id,Talk_key,Thing_read); //write talkid talkkey read
void setup() {
  Serial.begin(115200);
  Serial.println("\n Welcome to Thingspeak ESP8266");
  Thing_talk.begin_nom(ssid,pass);  //ESP connect to wifi
  Thing_talk.thingspeakbegin();     // Thingspeak work
  delay(500);
}
float data1=0,data2=1,data3=2;
void loop() {
  data1++;
  data2++;
  data3++;
  float GET[3]={data1,data2,data3};
  Serial.println("\n GET commands");
  Serial.println(Thing_talk.getCommands2(command_id1));
  Serial.println(Thing_talk.getCommands2(command_id2));
  Serial.println("===============");
  Serial.println("\nThingspeak write\n");
  Thing_talk.thingspeakwritemultiple(3,GET,ch_num);
  Serial.println("\n READ Thingspeak");
  Serial.println(Thing_talk.thingspeakread(ch_num,1));
  Serial.println(Thing_talk.thingspeakread(ch_num,2));
  Serial.println(Thing_talk.thingspeakread(ch_num,3));
  Serial.println("==================");
  delay(20*1000);
}
