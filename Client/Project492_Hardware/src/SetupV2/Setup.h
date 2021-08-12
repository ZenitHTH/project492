#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"
#include "Data.h"
#include "Board.h"

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

template <size_t row,size_t col>
Board GetValue(RPR0521RS rpr[row][col],int *tcaAddr)
{
  unsigned short ps_val[row][col];
  float als_val[row][col];
  byte rc[row][col];
  int addrNum=0;
  int num = 0;
  for(int i=0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
      TCA9548A(num,tcaAddr[addrNum]);
      rc[i][j] = rpr[i][j].get_psalsval(&ps_val[i][j],&als_val[i][j]);
      num++;
    }
    if(num == 8)
    {
      num=0;
      addrNum++;
    }

  }
  
  Data pin[i][j]

  for(int i=0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
      pin[i][j].Insert(ps_val[i][j],als_val[i][j]);
    }
  }

  return Board(pin);

}