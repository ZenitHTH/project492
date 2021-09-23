#ifndef PUBLISH_H
#define PUBLISH_H

#include <WiFi.h>
#include <WiFiManager.h> 
#include <PubSubClient.h>


void WiFi_Setup();
void Reconnect();
char* f2char(float);
template <typename T>
char* digit2char(T);

#endif