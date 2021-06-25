#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"
#include "SerialMonitor.h"
#include "Setup.h"

#define DEVICE_MAX 6
RPR0521RS rpr0521rs[DEVICE_MAX];

 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  SetupSensor(rpr0521rs,DEVICE_MAX);
}

void loop() {
  // put your main code here, to run repeatedly:

  Data dat = GetValue(rpr0521rs,DEVICE_MAX);
  PrintSersorStatus(dat.GetPS(),dat.GetAls(),DEVICE_MAX);
  delay(5000);
}