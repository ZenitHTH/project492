#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h> 
#include <PubSubClient.h>
#include <time.h>
#include "PinCheck.h"

#define mqtt_server       "m24.cloudmqtt.com"
#define mqtt_port         15342
#define mqtt_user         "qyuzvafp"
#define mqtt_pass         "0ynj_3e3rzJ6"
#define topic             "toys/test"

WiFiManager wm;
WiFiClient espClient;
PubSubClient client(espClient);
PinCheck pincheck;

void WiFi_Setup();
void Reconnect();

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  while(!Serial);
  delay(1000);
  Wire.begin();
  //WiFi Setup
  WiFi_Setup();

  //Get the time
  configTime(7*60*60,3600,"pool.ntp.org");
}

void loop() {
  // put your main code here, to run repeatedly:
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