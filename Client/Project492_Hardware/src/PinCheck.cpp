#include "PinCheck.h"


PinCheck::PinCheck(uint8_t col, uint8_t row)
{
    this->col = col;
    this->row = row;
    before = new bool*[col];
    for(uint8_t i=0;i<col;i++)
    {
        before[i] = new bool[row];
        for(uint8_t j=0;j<row;j++)
        {
            before[i][j] = false;
        }
    }
}



void PinCheck::Insert(Board now)
{
    //Serial.println("PinCheck Insert 0");

    if(CheckDiffrent(now))
    {
        //Serial.println("PinCheck Insert 1");
        this->before=now.PinDetect();
    }

}

//true is different, false is not diffrent
bool PinCheck::CheckDiffrent(Board now)
{
    //Serial.println("PinCheck CheckDiffent 0");
    bool** pinStatus = now.PinDetect();
     //Serial.println("PinCheck CheckDiffent 1");
    for(uint8_t i=0;i<col;i++)
    {
        for(uint8_t j=0;j<row;j++)
        {
            if(before[i][j] != pinStatus[i][j]) a++;
        }
    }
     Serial.println("PinCheck CheckDiffent 2");

    for(uint8_t i=0;i<now.len_x;i++)
    {
        delete[] pinStatus[i];
    }
     //Serial.println("PinCheck CheckDiffent 3");
    delete[] pinStatus;
     //Serial.println("PinCheck CheckDiffent 4");

    if(a>0) return true;
    else if(a==0) return false;

    
}

//must insert char might be work?
char* PinCheck::PublishData(char* d,char* t,char* key)
{
    //uint8_t size = diff.size();
    //if(size != 0)
    Serial.println("PinCheck PublishData 0");
    if(a != 0)
    {
        //Serial.println("PinCheck PublishData 1");
        Serial.println("a != 0");
        a = 0;
        //Serial.println("PinCheck PublishData 2");
        //char* digit = this->int2char(size);
        char* digit = this->int2char(a);
        //Serial.println("PinCheck PublishData 3");
        char msg[32]; sprintf(msg,"%s/,%s/,%s/,%s",d,digit,t,key);
        //Serial.println("PinCheck PublishData 4");
        a=0;
        return msg;

    }
    else{
        //Serial.println("PinCheck PublishData 5");
        Serial.println("a = 0");
        return "ERR";
    }
}

char* PinCheck::int2char(int i)
{
    //Serial.println("PinCheck int2char 0");
    char* value;
    //Serial.println("PinCheck int2char 1");
    String s = String(i,DEC);
    //Serial.println("PinCheck int2char 2");
    s.toCharArray(value,8);
    //Serial.println("PinCheck int2char 3");
    return value;
}