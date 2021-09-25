#include "PinCheck.h"


PinCheck::PinCheck(void)
{
    
}

void PinCheck::ReplaceBoard(Board now)
{
    // Serial.println("PinCheck Replace Board 0");
    // this->before.DeleteData();
    // Serial.println("PinCheck Replace Board 1");
    // this->before.DeleteLen();
    Serial.println("PinCheck Replace Board 0");
    this->before = now;
    Serial.println("PinCheck Replace Board 1");
}

void PinCheck::Insert(Board now)
{
    Serial.println("PinCheck Insert 0");
    if(this->before.len_x == 1 && this->before.len_y == 1)
    {
        Serial.println("PinCheck Insert 1");
        ReplaceBoard(now);
    }
    else 
    {
        Serial.println("PinCheck Insert 2");
        this->CheckDiffrent(now);
        ReplaceBoard(now);

    }

    // if((this->before.len_x == 0 && this->before.len_y == 0) && (this->after.len_x == 0 && this->after.len_y == 0))
    // {
    //     this->before = now;
    // }else 
    // if((this->before.len_x != 0 && this->before.len_y != 0) && (this->after.len_x == 0 && this->after.len_y == 0))
    // {
    //     this->after = now;
    // }
    // else
    // if((this->before.len_x != 0 && this->before.len_y != 0) && (this->after.len_x != 0 && this->after.len_y != 0))
    // {
    //     this->before = this->after;
    //     this->after = now;
    // }
}

void PinCheck::CheckDiffrent(Board now)
{
    //check boardsize
    if( now.len_x == this->before.len_x &&
        now.len_y == this->before.len_y &&
        now.len_x != 0 && now.len_y != 0 &&
        this->before.len_x != 0 && this->before.len_y != 0)
    {
        bool **isPin_after = now.PinDetect();
        bool **isPin_before = this->before.PinDetect();
        for(uint8_t i=0;i<now.len_x;i++)
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

        for(uint8_t i=0;i<before.len_x;i++)
        {
            delete[] isPin_after[i];
            delete[] isPin_before[i];
        }
        delete[] isPin_before;
        delete[] isPin_after;
    }


    
}

//must insert char might be work?
char* PinCheck::PublishData(char* d,char* t,char* key)
{
    //uint8_t size = diff.size();
    //if(size != 0)
    Serial.println("PinCheck PublishData 0");
    if(a != 0)
    {
        Serial.println("PinCheck PublishData 1");
        Serial.println("a != 0");
        a = 0;
        Serial.println("PinCheck PublishData 2");
        //char* digit = this->int2char(size);
        char* digit = this->int2char(a);
        Serial.println("PinCheck PublishData 3");
        char msg[32]; sprintf(msg,"%s/,%s/,%s/,%s",d,digit,t,key);
        Serial.println("PinCheck PublishData 4");
        return msg;

    }
    else{
        Serial.println("PinCheck PublishData 5");
        Serial.print("a = 0");
        return "ERR";
    }
}

char* PinCheck::int2char(int i)
{
    Serial.println("PinCheck int2char 0");
    char* value;
    Serial.println("PinCheck int2char 1");
    String s = String(i,DEC);
    Serial.println("PinCheck int2char 2");
    s.toCharArray(value,8);
    Serial.println("PinCheck int2char 3");
    return value;
}