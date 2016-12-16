#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ThingSpeak.h"

class ESPThingSpeakTalkback
{
	public:
		ESPThingSpeakTalkback(const char* thing_key,const char* talk_id,
		const char* talk_key,const char* thing_read);
		
		void begin_nom(const char* ssid,const char* pass); //connected normal
		void begin_config(const char* ssid,const char* pass); //config ip address
		void setAddress(int ip[4],int getway[4],int subnet[4]);
		String getCommands2(const char* command_id);
		void thingspeakbegin();
		void thingspeakwrite(int ch_num,int field,float data);
		void thingspeakwritemultiple(int num_field,float data[8],int ch_num);
		float thingspeakread(int ch_num,int field);		
   public: HTTPClient http;
   public:
   	int Ip[4]={0,0,0,0};
   	int Getway[4]={0,0,0,0};
   	int Subnet[4]={0,0,0,0};
};