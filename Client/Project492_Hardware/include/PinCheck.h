#ifndef PINCHECK_H
#define PINCHECK_H
#include "Board.h"
#include "Data.h"
#include <Arduino.h>
#include <LinkedList.h>
#include <TimeLib.h>

class PinCheck
{
    private :
    Board before;
    Board after;
    struct local
    {
        uint8_t i;
        uint8_t j;
        
    };
    LinkedList<local> diff;
    char* int2char(int);

    public :
    PinCheck(void);
    void Insert(Board);
    void CheckDiffrent();
    char* PublishData(time_t t);

};


#endif