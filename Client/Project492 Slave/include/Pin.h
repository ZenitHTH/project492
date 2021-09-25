#ifndef PIN_H
#define PIN_H
#include <Arduino.h>

struct pin
{
    struct sensor
    {
        uint8_t i;
        uint8_t j;
    };
    sensor sen;
    uint8_t tcaAddr;
    uint8_t num;
    uint8_t posLed;
};



#endif