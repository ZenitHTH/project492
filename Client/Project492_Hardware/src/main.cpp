#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"
#include "SerialMonitor.h"
#include "SetupV2/Setup.h"
#include "SetupV2/Data.h"
#include "SetupV2/Board.h"



#define DEVICE_COL  4
#define DEVICE_ROW  4 
RPR0521RS rpr0521rs[DEVICE_ROW][DEVICE_COL];
int tcaAddr[] = {0x70,0x71};
//RPR0521RS rpr0521rs[DEVICE_MAX];

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  SetupSensor(rpr0521rs,tcaAddr);
}

void loop()
{
  Board board();
  GetValue(rpr0521rs,tcaAddr,&board());

  board().PrintStatus();
}

 
// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(115200);
//   Wire.begin();
//   SetupSensor(rpr0521rs,DEVICE_MAX);
// }

// void loop() {
//   // put your main code here, to run repeatedly:

//   Data dat = GetValue(rpr0521rs,DEVICE_MAX);
//   PrintSersorStatus(dat.GetPS(),dat.GetAls(),DEVICE_MAX);
//   delay(5000);
// }