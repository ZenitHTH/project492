#include "Board.h"


Board::Board(Data **data,uint8_t row,uint8_t col)
{
    this->len_x = row;
    this->len_y = col;
    this->data = data;
}

Board::Board()
{
    this->len_x = 1;
    this->len_y = 1;
    Data** dat = new Data*[0];
    dat[0] = new Data[0];
    dat[0][0].Insert(1,-1.0f,1);
}

Board Board::operator=(const Board& b)
{
    this->data = b.data;
    this->len_x = b.len_x;
    this->len_y = b.len_y;

    return *this;
}

//if all data have it => return true
//if someone in data has not data => return false
bool Board::HaveData()
{

    for(uint8_t i=0;i< this->len_x;i++)
    {
        for(uint8_t j=0;j<this->len_y;j++)
        {
            if(this->data[i][j].HaveItData() == false) return false;
        }
    }

    return true;
}

// true is havepin , false is have not pin
bool** Board::PinDetect()
{
    bool** pinStatus;
    pinStatus = new bool* [this->len_x];
    if(this->HaveData())
    {
        for(uint8_t i=0;i<this->len_x;i++)
        {
            pinStatus[i] = new bool [this->len_y];
            for(uint8_t j=0;j<this->len_y;j++)
            {
                if(data[i][j].GetAls() < 10.00) pinStatus[i][j] = true;
                else pinStatus[i][j] = false;
            }
        }
    }

    return pinStatus;
}

void Board::PrintStatus()
{
    Serial.println();
    for(uint8_t i=0;i<len_x;i++)
    {
        for(uint8_t j=0;j<len_y;j++)
        {
            Serial.print("["+String(data[i][j].GetAls(),2)+"]");
            Serial.print("["+String(data[i][j].GetPS(),DEC)+"]\t");
        }
        Serial.println();
    }
}

void Board::ReplaceData(Data** dat)
{
    Serial.println("Board Replace Data 0");
    //this->DeleteData();
    //Serial.println("Board Replace Data 1");
    this->data = dat;
    Serial.println("Board Replace Data 2");

}

void Board::DeleteData()
{
    Serial.println("Board Delete Data 0");
    for(uint8_t i=0;i<this->len_x;i++)
    {
        //delete[] this->data[i];
        free((void*)this->data[i]);
    }
    Serial.println("Board Delete Data 1");
    //delete[] this->data;
    free(this->data);
    Serial.println("Board Delete Data 2");
    this->data = NULL;
    Serial.println("Board Delete Data 3");   
}

void Board::DeleteLen()
{
    this->len_x = 0;
    this->len_y = 0;
}

