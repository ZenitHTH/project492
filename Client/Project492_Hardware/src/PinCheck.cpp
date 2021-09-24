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
                    // local l; l.i = i; l.j = j;
                    // diff.add(l);
                    Serial.println("Found Difrent");
                    a++;
                }
            }
        }
    }
    
}

char* PinCheck::PublishData(struct tm timeinfo)
{
    //uint8_t size = diff.size();
    //if(size != 0)
    if(a != 0)
    {
        Serial.println("a != 0");
        a = 0;
        if(!getLocalTime(&timeinfo))
        {
            Serial.println("Failed to obtain time");
            return "ERR";
        }
        //char* digit = this->int2char(size);
        char* digit = this->int2char(a);
        char d[10]; strftime(d,10,"%Y:%m:%d",&timeinfo);
        char t[10]; strftime(t,10,"%H:%M:%S",&timeinfo);
        char key[8]; strftime(key,8,"%Y%m%d",&timeinfo);
        char msg[32]; sprintf(msg,"%s/,%s/,%s/,%s",d,digit,t,key);
        return msg;

    }
    else{
        Serial.print("a = 0");
        return "ERR";
    }
}

char* PinCheck::int2char(int i)
{
    char* value;
    String s = String(i,DEC);
    s.toCharArray(value,8);
    return value;
}