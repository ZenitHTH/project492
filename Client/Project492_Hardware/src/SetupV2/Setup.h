#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"

#define TCA_ADDR_0  0x70
#define TCA_ADDR_1  0x71

void TCA9548A(uint8_t bus,int address)
{
  Wire.beginTransmission(address);
  Wire.write(1<<bus);
  Wire.endTransmission();
}

template <size_t row,size_t col>
void SetupSensor(RPR0521RS (&rpr)[row][col],int (*tcaAddr))
{
    byte rc[row][col];
    int addrNum=0;
    int num = 0;
    for(int i=0;i<row;i++)
    {
      for(int j=0;j<rol;j++)
      {
        TCA9548A(num,tcaAddr[addrNum]);
        while (!Serial);
        rc[i][j] = rpr[i][j].init();
        Serial.println(rc[i][j]);
        num++;

      }
      if(num == 8)
      {
        num = 0;
        addrNum++;
      }
    }
}