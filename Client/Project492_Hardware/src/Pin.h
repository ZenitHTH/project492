#ifndef PIN_H
#define PIN_H

#include "RPR-0521RS.h"

struct pin
{
    RPR0521RS rpr;
    uint8_t tcaAddr;
    uint8_t num;
    uint8_t posLed;
};

#endif