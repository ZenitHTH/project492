#include <Arduino.h>
#include "Board.h"


Board::Board(Data **data,int row,int col)
{
    this->len_x = row;
    this->len_y = col;
    this->data = data;
}

Board::Board()
{
    this->len_x = 0;
    this->len_y = 0;
    
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

    for(int i=0;i< this->len_x;i++)
    {
        for(int j=0;j<this->len_y;j++)
        {
            if(this->data[i][j].HaveItData() == false) return false;
        }
    }

    return true;
}

// true is havepin , false is have not pin
bool** Board::PinDetect()
{
    bool **pinStatus;
    pinStatus = new bool* [len_x];
    if(this->HaveData())
    {
        for(int i=0;i<this->len_x;i++)
        {
            pinStatus[i] = new bool [len_y];
            for(int j=0;j<this->len_y;j++)
            {
                if(data[i][j].GetAls() < 10.00) pinStatus[i][j] = 1;
                else pinStatus = 0;
            }
        }
    }

    return pinStatus;
}

void Board::PrintStatus()
{
    Serial.println();
    for(int i=0;i<len_x;i++)
    {
        for(int j=0;j<len_y;j++)
        {
            Serial.print("["+String(data[i][j].GetAls(),2)+"]");
            Serial.print("["+String(data[i][j].GetPS(),DEC)+"]\t");
        }
        Serial.println();
    }
}