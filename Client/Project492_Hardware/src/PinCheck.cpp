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

char* PinCheck::PublishData(time_t t)
{
    uint8_t size = diff.size();
    if(size != 0)
    {
        char* digit = this->int2char(size);
        char* y = this->int2char(year(t));
        char* mon;
        if(month(t) < 10) mon = '0'+this->int2char(month(t));
        else mon = this->int2char(month(t));
        char* d;
        if(day(t) < 10) d = '0'+this->int2char(day(t));
        else d = this->int2char(day(t));
        char* h;
        if(hour(t) >= 0 && hour(t) <10) h = '0'+this->int2char(hour(t));
        else h = this->int2char(hour(t));
        char* min;
        if(minute(t) >= 0 && minute(t) < 10) min = '0'+this->int2char(minute(t));
        else min = this->int2char(minute(t));
        char* sec;
        if(second(t) >= 0 && minute(t) < 10) sec = '0'+this->int2char(second(t));
        sec = this->int2char(second(t));

        char msg[40];
        sprintf(msg,"%s%s%s,%s,%s:%s:%s,%s:%s:%s",y,mon,d,digit,h,min,sec,y,mon,d);
        return msg;
    }
    return "ERR";
}

char* PinCheck::int2char(int i)
{
    char* value;
    String s = String(i,DEC);
    s.toCharArray(value,8);
    return value;
}