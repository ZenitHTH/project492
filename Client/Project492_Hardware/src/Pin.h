#ifndef PIN_H
#define PIN_H

#include "RPR-0521RS.h"

struct pin
{
    RPR0521RS rpr;
    int tcaAddr;
    int num;
};

#endif