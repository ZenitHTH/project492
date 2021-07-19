#include <Arduino.h>

class Data
{
    private:
        unsigned short ps_val;
        float als_val;
        byte rc;

    public:

        Data(unsigned short,float,byte);
        unsigned short GetPS();
        float GetAls();
        byte GetRC();

};

Data::Data(unsigned short ps_val,float als_val,byte rc)
{
    this->ps_val = ps_val;
    this->als_val = als_val;
    this->rc = rc;
}

unsigned short Data::GetPS()
{
    return this->ps_val;
}

float Data::GetAls()
{
    return this->als_val;
}

byte Data::GetRC()
{
    return this->rc;
}

