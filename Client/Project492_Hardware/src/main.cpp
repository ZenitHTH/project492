#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"
#include "Setup.h"
#include "Data.h"
#include "Board.h"
#include "Pin.h"
//#include "PinCheck.h"
#include <WiFi.h>
#include <WiFiManager.h> 
#include <PubSubClient.h>
#include <time.h>

#define DEVICE_COL        4
#define DEVICE_ROW        4 
#define mqtt_server       "m24.cloudmqtt.com"
#define mqtt_port         15342
#define mqtt_user         "qyuzvafp"
#define mqtt_pass         "0ynj_3e3rzJ6"
#define topic             "toys/test"         
#define deLay             59999u

WiFiManager wm;
WiFiClient espClient;
PubSubClient client(espClient);
RPR0521RS rpr0521rs[DEVICE_ROW][DEVICE_COL];

bool before[4][4] = {
                      {false,false,false,false},
                      {false,false,false,false},
                      {false,false,false,false},
                      {false,false,false,false}
                    };
pin **p;


void freeBoard(Board);
void WiFi_Setup();
void Reconnect();
//char* f2char(double);
//char* int2char(int);

void setup()
{
  const uint8_t tcaAddr[2] = {0x71,0x70};
  Serial.begin(115200);
  while(!Serial);
  delay(1000);
  Wire.begin();
  //WiFi Setup
  WiFi_Setup();

  //Get the time
  configTime(6*60*60,3600,"0.th.pool.ntp.org");
  p = MatchSensor(tcaAddr,DEVICE_ROW,DEVICE_COL);
  SetupSensor(p,rpr0521rs);
}

void loop()
{
  Board board = GetValue(p,rpr0521rs);;
  board.PrintStatus();
  
  struct tm timeinfo;
  if(!client.connected())
  {
    Reconnect();
  }
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  client.loop();
  

  uint8_t diffrent = 0;
  bool** pinStatus = board.PinDetect();
  for(uint8_t i=0;i<DEVICE_COL;i++)
  {
    for(uint8_t j=0;j<DEVICE_ROW;j++)
    {
      if(pinStatus[i][j] != before[i][j]) 
      {
        diffrent++;
        before[i][j] = pinStatus[i][j];
      }
    }
  }

  for(uint8_t i=0;i<DEVICE_ROW;i++)
  {
    delete[] pinStatus[i];
  }
  delete[] pinStatus;

  char tm_Y[5]; strftime(tm_Y,5,"%Y",&timeinfo);
  char tm_m[3]; strftime(tm_m,3,"%m",&timeinfo);
  char tm_d[3]; strftime(tm_d,3,"%d",&timeinfo);
  //char d[11]; strftime(d,11,"%Y:%m:%d",&timeinfo);
  char t[9]; strftime(t,9,"%H:%M:%S",&timeinfo);
  //char key[9]; strftime(key,9,"%Y%m%d",&timeinfo);
  char msg[40];
  sprintf(msg,"%s:%s:%s,%d,%s,%s%s%s",tm_Y,tm_m,tm_d,diffrent,t,tm_Y,tm_m,tm_d);

  Serial.println(msg);
  client.publish("toys/test",msg,true);
  delay(deLay);
}

void WiFi_Setup()
{
    wm.setTimeout(300);

    if(!wm.autoConnect("AutoConnect_ESP32"))
    {
        Serial.println("Connecting Failed");
        delay(3000);
        ESP.restart();
    }

    client.setServer(mqtt_server,mqtt_port);
    client.subscribe(topic);
}

void Reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// char* f2char(double f)
// {
//   char* value;
//   dtostrf(f,8,4,value);
//   return value;
// }

// char* int2char(int i)
// {
//   char* value;
//   String s = String(i,DEC);
//   s.toCharArray(value,8);
//   return value;
// }
