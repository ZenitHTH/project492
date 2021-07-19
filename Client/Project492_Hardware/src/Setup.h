#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"

#define tcaAddrStart    0x70
#define tcaAddrEnd      0x73

class Data
{
    public:
        unsigned short *ps_val;
        float *als_val;
        byte rc[];

        void InitData(unsigned short ps[],float als[],byte r[])
        {
            *ps_val=*ps;
            *als_val=*als;
            *rc = *r;
        }

        unsigned short* GetPS()
        {
            return ps_val;
        }

        float* GetAls()
        {
            return als_val;
        } 

        byte* GetRC()
        {
            return rc;
        }
};

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
        TCA9548A(i,tcaAddrStart);
        while (!Serial);
        rc[i] = rpr[i].init();
        Serial.println(rc[i]);
    }
}

Data GetValue(RPR0521RS rpr[],int device_max)
{
    unsigned short ps_val[device_max];
    float als_val[device_max];
    byte rc[device_max];
    for(int i=0;i<device_max;i++) 
    {
        TCA9548A(i,tcaAddrStart);
        rc[i] = rpr[i].get_psalsval(&ps_val[i],&als_val[i]);
    }
    Data data;
    data.InitData(ps_val,als_val,rc);

    return data;
}