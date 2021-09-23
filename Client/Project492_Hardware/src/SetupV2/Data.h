#ifndef DATA_H
#define DATA_H

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

bool Data::HaveItData()
{
    if(rc == 0 && (ps_val > 0 || als_val > 0)) return true;
    else return false;
}

void Data::Insert(unsigned short ps_val,float als_val,byte rc)
{
    this->ps_val = ps_val;
    this->als_val = als_val;
    this->rc = rc;
}

#endif