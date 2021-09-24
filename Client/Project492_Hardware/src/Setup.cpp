#include "Setup.h"


void TCA9548A(uint8_t bus,uint8_t address)
{
  if (bus > 7) return;
  Wire.beginTransmission(address);
  Wire.write(1<<bus);
  Wire.endTransmission();
}

void TCA9548A_end(uint8_t address)
{
  Wire.beginTransmission(address);
  Wire.write(0);
  Wire.endTransmission();
}


pin** MatchSensor(const uint8_t (*tcaAddr),uint8_t row,uint8_t col)
{
  pin **p;
  p = new pin*[row];
  //uint8_t posLed[4][4] = 
  // {
  //   {0,1,2,3},
  //   {7,6,5,4},
  //   {8,9,10,11},
  //   {15,14,13,12}
  // };
  uint8_t posSensor[4][4][2] =
  { //{position,address}
    {{0,0},{7,0},{0,1},{7,1}},
    {{1,0},{6,0},{1,1},{6,1}},
    {{2,0},{5,0},{2,1},{5,1}},
    {{3,0},{4,0},{3,1},{4,1}}
  };

  for(int i=0;i<row;i++)
  {
    p[i] = new pin[col];
    for(int j=0;j<col;j++)
    {
      p[i][j].num = posSensor[i][j][0];
      p[i][j].tcaAddr = tcaAddr[posSensor[i][j][1]];
      p[i][j].sen.i = (uint8_t)i;
      p[i][j].sen.j = (uint8_t)j;
      //p[i][j].posLed = posLed[i][j];

      //num++;
    }
    // if(num == 7)
    // {
    //   num = 0;
    //   addrNum++;
    // }
  }
  return p;
}


