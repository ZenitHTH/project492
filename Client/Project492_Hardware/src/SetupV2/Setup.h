#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"

void TCA9548A(uint8_t bus,int address)
{
  Wire.beginTransmission(address);
  Wire.write(1<<bus);
  Wire.endTransmission();
}

void SetupSensor(RPR0521RS rpr[],int device_max)
{
    byte rc[device_max];
    for(int i=0;i<device_max;i++)
    {
        TCA9548A(i,0x70);
        while (!Serial);
        rc[i] = rpr[i].init();
        Serial.println(rc[i]);
    }
}