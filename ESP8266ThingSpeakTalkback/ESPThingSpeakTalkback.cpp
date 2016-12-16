#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ThingSpeak.h"
#include "ESPThingSpeakTalkback.h"
#define host "api.thingspeak.com"
const char* Thing_key;
const char* Thing_read;
const char* Talk_id;
const char* Talk_key;

WiFiClient client;
ESPThingSpeakTalkback::ESPThingSpeakTalkback(const char* thing_key,const char* talk_id,
                       const char* talk_key,const char* thing_read)
{
	Thing_key=thing_key; //write_thingspeak
	Thing_read=thing_read; //read_thingspeak
	Talk_id=talk_id; //id_talkback
	Talk_key=talk_key; //key_talkback
}
void ESPThingSpeakTalkback::begin_nom(const char* ssid,const char* pass)
{
	Serial.print("\n\n Connected.");
	WiFi.begin(ssid,pass);
	while(WiFi.status()!=WL_CONNECTED){
		Serial.print(".");
		delay(500);
	}
	Serial.print("\n\nConnect at: ");
	Serial.println(WiFi.localIP());
}
void ESPThingSpeakTalkback::setAddress(int ip[4],int getway[4],int subnet[4])
{
	int i;
	for(i=0;i<4;i++)
	{
		Ip[i]=ip[i];
		Getway[i]=getway[i];
		Subnet[i]=subnet[i];
	}
}
void ESPThingSpeakTalkback::begin_config(const char* ssid,const char* pass)
{
	Serial.print("\n\n Connected.");
	WiFi.begin(ssid,pass);
	while(WiFi.status()!=WL_CONNECTED){
		Serial.print(".");
		delay(500);
	}
	Serial.print("\n\nConnect at: ");
	IPAddress ip={Ip[0],Ip[1],Ip[2],Ip[3]};
	IPAddress getway={Getway[0],Getway[1],Getway[2],Getway[3]};
	IPAddress subnet={Subnet[0],Subnet[1],Subnet[2],Subnet[3]};
	WiFi.config(ip,getway,subnet);
	Serial.println(WiFi.localIP());
}
void ESPThingSpeakTalkback::thingspeakbegin()
{
	ThingSpeak.begin(client);
}
String ESPThingSpeakTalkback::getCommands2(const char* command_id)
{
	String url = "http://";
	url += host;
	url += "/talkbacks/";
	url += Talk_id;
	url += "/commands/";
	url +=command_id;
	url += "?api_key=";
	url += Talk_key;
	
	http.begin(url);
	int state=http.GET();
	if(state>0)
	{
		if(state==HTTP_CODE_OK)
		{
			Serial.println("State: "+String(state));
			String response=http.getString();
			Serial.println("Response: "+response);
			return response;
		}
	}
	else{
		Serial.println("Error 400 Badrequest");
		return "400";
	}
}
void ESPThingSpeakTalkback::thingspeakwrite(int ch_num,int field,float data)
{
	ThingSpeak.writeField(ch_num,field,data,Thing_key);
}
float ESPThingSpeakTalkback::thingspeakread(int ch_num,int filed)
{
	return ThingSpeak.readFloatField(ch_num,filed);
}
void ESPThingSpeakTalkback::thingspeakwritemultiple(int num_field,float data[8],int ch_num)
{
	int i;
	for(i=1;i<=num_field;i++)
	{
		ThingSpeak.setField(i,data[i-1]);
	}
	ThingSpeak.writeFields(ch_num,Thing_key);
}