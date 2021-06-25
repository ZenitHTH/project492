#include <Arduino.h>

void PrintSersorStatus(unsigned short ps_val[],float als_val[],int device_max)
{
    Serial.println();
    Serial.print("\t");
    for(int i=0;i<device_max;i++)
    {
        Serial.print("[");Serial.print(i);Serial.print("]\t");
    }
    Serial.println();
    Serial.print("Proxy\t");
    for(int i=0;i<device_max;i++)
    {
        
        Serial.print(ps_val[i]);Serial.print('\t');
        
    }
    Serial.println();
    Serial.print("Amb\t");
    for(int i=0;i<device_max;i++)
    {
        Serial.print(als_val[i]);Serial.print('\t');
        
    }
  Serial.println();   
}