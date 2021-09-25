#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"
#include "Setup.h"
#include "Data.h"
#include "Board.h"
#include "Pin.h"
#include "PinCheck.h"
#include <WiFi.h>
#include <WiFiManager.h> 
#include <PubSubClient.h>
#include <time.h>

#define DEVICE_COL  4
#define DEVICE_ROW  4 
#define mqtt_server       "m24.cloudmqtt.com"
#define mqtt_port         15342
#define mqtt_user         "qyuzvafp"
#define mqtt_pass         "0ynj_3e3rzJ6"
#define topic             "toys/test"

WiFiManager wm;
WiFiClient espClient;
PubSubClient client(espClient);
RPR0521RS rpr0521rs[DEVICE_ROW][DEVICE_COL];
PinCheck pincheck;


const uint8_t tcaAddr[2] = {0x71,0x70};
pin **p;


void freeBoard(Board);
void WiFi_Setup();
void Reconnect();
//char* f2char(double);
//char* int2char(int);

void setup()
{
  Serial.begin(115200);
  while(!Serial);
  delay(1000);
  Wire.begin();
  //WiFi Setup
  WiFi_Setup();

  //Get the time
  configTime(7*60*60,3600,"pool.ntp.org");
  p = MatchSensor(tcaAddr,DEVICE_ROW,DEVICE_COL);
  SetupSensor(p,rpr0521rs);
}

//buffer overflow
void loop()
{
  Serial.println("Main 0");
  Board board;
  char* msg;
  struct tm timeinfo;
  Serial.println("Main 01");
  if(!client.connected())
  {
    Reconnect();
  }
  Serial.println("Main 1");
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println("Main 2");
  client.loop();
  Serial.println("Main 3");

  board = GetValue(p,rpr0521rs);
  Serial.println("Main 4");
  board.PrintStatus();
  Serial.println("Main 5");
  pincheck.Insert(board);
  //Serial.println("Main 1");
  //freeBoard(board);
  //Serial.println("Main 2");

  char d[10]; strftime(d,10,"%Y:%m:%d",&timeinfo);
  char t[10]; strftime(t,10,"%H:%M:%S",&timeinfo);
  char key[8]; strftime(key,8,"%Y%m%d",&timeinfo);
  Serial.println("Main 6");
  msg = pincheck.PublishData(d,t,key);
  Serial.println("Main 7");
  Serial.print(msg);
  if(msg != "ERR") client.publish("toys/test",msg,true);
  Serial.println("Main 8");
  delay(10000);
}

void freeBoard(Board b)
{
  b.DeleteData();
  b.DeleteLen();
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