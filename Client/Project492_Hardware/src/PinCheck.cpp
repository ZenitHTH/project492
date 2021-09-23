#include "PinCheck.h"


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
