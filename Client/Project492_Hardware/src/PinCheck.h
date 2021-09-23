#ifndef PINCHECK_H
#define PINCHECK_H
#include "SetupV2/Board.h"
#include "SetupV2/Data.h"

class PinCheck
{
    private :
    Board before;
    Board after;

    public :
    PinCheck(void);
    void Insert(Board);
    
};

PinCheck::PinCheck(void)
{
    
}

void PinCheck::Insert(Board now)
{
    if((this->before.len_x == 0 && this->before.len_y == 0) && (this->after.len_x == 0 && this->after.len_y == 0))
    {
        this->before = now;
    }else 
    if((this->before.len_x != 0 && this->before.len_y != 0) && (this->after.len_x == 0 && this->after.len_y == 0))
    {
        this->after = now;
    }
    else
    if((this->before.len_x != 0 && this->before.len_y != 0) && (this->after.len_x != 0 && this->after.len_y != 0))
    {
        this->before = this->after;
        this->after = now;
    }
}


#endif