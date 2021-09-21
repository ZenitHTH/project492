#ifndef PUBLISH_H
#define PUBLISH_H

#include <WiFi.h>
#include <WiFiManager.h> 
#include <PubSubClient.h>
#include "Typeof.h"

#define mqtt_server       "m24.cloudmqtt.com"
#define mqtt_port         15342
#define mqtt_user         "qyuzvafp"
#define mqtt_pass         "0ynj_3e3rzJ6"
#define topic             "toys/test"

WiFiManager wm;
WiFiClient espClient;
PubSubClient client(espClient);

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

char* f2char(float f)
{
  char val[8];
  dtostrf(f,4,4,val);
  return val;
}

template <typename T>
char* digit2char(T digit)
{
  char val[8];
  if(isDigit(digit))
  {
    if(typeof(digit) == "int")
    {
      String s = String(digit,DEC);
      s.toCharArray(val,8);
      return val;
    }
    else if(typeof(digit) == "float")
    {
      dtostrf(digit,8,4,val);
      return val;
    }
    
  }
  else{
    return "ERR";
  }
}

#endif

/*

  void loop()
  {
    if(!client.connected())
    {
      reconnect();
    }

    client.loop();
    client.publish(topic,"Im ESP32",true);
    delay(3000);
  }


*/