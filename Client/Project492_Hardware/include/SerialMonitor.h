#ifndef SERIALMOINTOR_H
#define SERIALMOINTOR_H

#include <Arduino.h>

void PrintSersorStatus(unsigned short ps_val[],float als_val[],uint8_t device_max)
{
    Serial.println();
    Serial.print("\t");
    for(uint8_t i=0;i<device_max;i++)
    {
        Serial.print("[");Serial.print(i);Serial.print("]\t");
    }
    Serial.println();
    Serial.print("Proxy\t");
    for(uint8_t i=0;i<device_max;i++)
    {
        
        Serial.print(ps_val[i]);Serial.print('\t');
        
    }
    Serial.println();
    Serial.print("Amb\t");
    for(uint8_t i=0;i<device_max;i++)
    {
        Serial.print(als_val[i]);Serial.print('\t');
        
    }
  Serial.println();   
}

#endif