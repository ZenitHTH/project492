#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"
#include "Setup.h"
#include "Data.h"
#include "Board.h"
#include "Pin.h"


#define DEVICE_COL  4
#define DEVICE_ROW  4 
RPR0521RS rpr0521rs[DEVICE_ROW][DEVICE_COL];
uint8_t slaveAddress = 0x53;
const uint8_t tcaAddr[2] = {0x71,0x70};
pin **p;

void requestEvent();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
  Wire.begin(slaveAddress);
  p = MatchSensor(tcaAddr,DEVICE_ROW,DEVICE_COL);
  SetupSensor(p,rpr0521rs);
  Wire.onRequest(requestEvent);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void requestEvent()
{
  Board board = GetValue(p,rpr0521rs);
  bool** pinDetect = board.PinDetect();
  char p[16];
  uint8_t k=0;
  for(uint8_t i=0;i<board.len_x;i++)
  {
    for(uint8_t j=0;j<board.len_y;j++)
    {
      if(pinDetect[i][j] == 1)
      {
        p[k] = '1';
        k++;
      }else{
        p[k] = '0';
        k++;
      }

    }
  }
  Wire.write(p);
}