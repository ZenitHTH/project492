#ifndef PINCHECK_H
#define PINCHECK_H
#include "Board.h"
#include "Data.h"
#include <Arduino.h>

class PinCheck
{
    private :
    Board before;
    Board after;

    public :
    PinCheck(void);
    void Insert(Board);
    
};


#endif