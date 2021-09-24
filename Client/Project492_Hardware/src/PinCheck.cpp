#include "PinCheck.h"
#include <Arduino.h>


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

void PinCheck::CheckDiffrent()
{
    //check boardsize
    if(this->after.len_x == this->before.len_x && this->after.len_y == this->before.len_y)
    {
        bool **isPin_after = this->after.PinDetect();
        bool **isPin_before = this->before.PinDetect();
        for(uint8_t i=0;i<this->after.len_x;i++)
        {
            for(uint8_t j=0;j<this->before.len_y;j++)
            {
                
                if(isPin_after[i][j] == false && isPin_before[i][j] == true)
                {
                    local l; l.i = i; l.j = j;
                    diff.add(l);
                }
            }
        }
    }
    
}
