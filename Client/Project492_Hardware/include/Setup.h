#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"
#include "Data.h"
#include "Board.h"
#include "Pin.h"

void TCA9548A(uint8_t,uint8_t);
void TCA9548A_end(uint8_t);

pin** MatchSensor(const uint8_t *,uint8_t,uint8_t);
template <size_t row,size_t col>
void SetupSensor(pin **p,RPR0521RS (&rpr)[row][col])
{
    byte rc[row][col];
    pin lastpin;
    pin _p;
    for(int i=0;i<row;i++)
    {
      for(int j=0;j<col;j++)
      {
        if(_p.tcaAddr != 0) lastpin = _p;
        _p = p[i][j];
        // check if address's lastpin and address's thispin is unmatch -> end tranmission lastpin's address before use newpin's address
        if(lastpin.tcaAddr != _p.tcaAddr && lastpin.tcaAddr != 0) TCA9548A_end(lastpin.tcaAddr);
        TCA9548A(_p.num,_p.tcaAddr);
        while (!Serial);
        rc[i][j] = rpr[_p.sen.i][_p.sen.j].init();
        Serial.println(rc[i][j]);
        delay(10);
      }
    }
}

template <size_t row,size_t col>
Board GetValue(pin **p,RPR0521RS (&rpr)[row][col])
{
  unsigned short ps_val[row][col];
  float als_val[row][col];
  byte rc[row][col];
  pin _p, lastpin;
  for(int i=0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
      if(_p.tcaAddr != 0) lastpin = _p;
      _p = p[i][j];
      if(lastpin.tcaAddr != _p.tcaAddr && lastpin.tcaAddr != 0) TCA9548A_end(lastpin.tcaAddr);
      TCA9548A(_p.num,_p.tcaAddr);
      unsigned short _ps;
      float _als;
      rc[i][j] = rpr[_p.sen.i][_p.sen.j].get_psalsval(&_ps,&_als);
      ps_val[i][j] = _ps;
      als_val[i][j] = _als;
      delay(10);
      //Serial.println("["+String(i,DEC)+","+String(j,DEC)+"]"+" :"+String(_als,2)+"\t"+String(ps_val[i][j],DEC));
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