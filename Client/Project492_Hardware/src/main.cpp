#include <Arduino.h>
#include <Wire.h>
#include <FastLED.h>
#include "RPR-0521RS.h"
#include "SetupV2/Setup.h"
#include "SetupV2/Data.h"
#include "SetupV2/Board.h"
#include "Pin.h"


#define DEVICE_COL  4
#define DEVICE_ROW  4 
#define NUM_LEDS    16
#define LED_PIN     2

CRGB leds[NUM_LEDS];
pin **p;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  RPR0521RS rpr0521rs[DEVICE_ROW][DEVICE_COL];
  const uint8_t tcaAddr[] = {0x70,0x71};

  FastLED.addLeds<WS2812B,LED_PIN,GRB>(leds,NUM_LEDS);
  FastLED.setBrightness(50);
  p = MatchSensor(rpr0521rs,tcaAddr);
  SetupSensor(p,DEVICE_ROW,DEVICE_COL);
}

void loop()
{
  Board board = GetValue(p,DEVICE_ROW,DEVICE_COL);

  board.PrintStatus();
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