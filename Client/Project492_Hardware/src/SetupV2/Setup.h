#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"
#include "Data.h"
#include "Board.h"
#include "Pin.h"
#define DEVICE_COL  4
#define DEVICE_ROW  4 

void TCA9548A(uint8_t bus,int address)
{
  Wire.beginTransmission(address);
  Wire.write(1<<bus);
  Wire.endTransmission();
}

template <size_t row,size_t col>
pin** MatchSensor(RPR0521RS (&rpr)[row][col],const int (*tcaAddr))
{
  pin **p;
  p = new pin*[row];
  int num = 0;
  int addrNum = 0;

  for(int i=0;i<row;i++)
  {
    p[i] = new pin[col];
    for(int j=0;j<col;j++)
    {
      p[i][j].num = num;
      p[i][j].tcaAddr = addrNum;
      p[i][j].rpr = rpr[i][j];

      num++;
    }
    if(num == 8)
    {
      num = 0;
      addrNum++;
    }
  }
  return p;
}

void SetupSensor(pin **p,int row,int col)
{
    byte rc[row][col];

    for(int i=0;i<row;i++)
    {
      for(int j=0;j<col;j++)
      {
        pin _p = p[i][j];
        TCA9548A(_p.num,_p.tcaAddr);
        while (!Serial);
        rc[i][j] = _p.rpr.init();
        Serial.println(rc[i][j]);
        
      }
    }

}


Board GetValue(pin **p,int row,int col)
{
  unsigned short ps_val[row][col];
  float als_val[row][col];
  byte rc[row][col];
  for(int i=0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
      pin _p = p[i][j];
      TCA9548A(_p.num,_p.tcaAddr);
      rc[i][j] = _p.rpr.get_psalsval(&ps_val[i][j],&als_val[i][j]);
    }
  }
  
  Data **dat = new Data*[row];

  for(int i=0;i<row;i++)
  {
    dat[i] = new Data[col];
    for(int j=0;j<col;j++)
    {
      dat[i][j].Insert(ps_val[i][j],als_val[i][j],rc[i][j]);
    }
  }

  return Board(dat,row,col);
}

#endif