#ifndef DATA_H
#define DATA_H
#include <Arduino.h>

class Data
{
    private:
        unsigned short ps_val;
        float als_val;
        byte rc;

    public:

        unsigned short GetPS();
        float GetAls();
        byte GetRC();
        void Insert(unsigned short,float,byte);
        bool HaveItData();
        

};


#endif