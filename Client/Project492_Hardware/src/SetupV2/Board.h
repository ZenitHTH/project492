#ifndef BOARD_H
#define BOARD_H

#include "Data.h"

class Board
{
    private :
        Data** data;

    public:
        int len_x, len_y ;

        Board(Data **,int,int);
        void Insert(Data **,int,int);
        Board operator=(const Board&);
        void PrintStatus();

};

Board::Board(Data **data,int row,int col)
{
    this->len_x = row;
    this->len_y = col;
    this->data = data;
}

void Board::Insert(Data **data,int row,int col)
{
    this->len_x = row;
    this->len_y = col;
    this->data = data;
}

Board Board::operator=(const Board& b)
{
    this->data = b.data;
    this->len_x = b.len_x;
    this->len_y = b.len_y;

    return *this;
}

void Board::PrintStatus()
{
    Serial.println();
    for(int i=0;i<len_x;i++)
    {
        for(int j=0;j<len_y;j++)
        {
            Serial.print("[");Serial.print(data[i][j].GetAls());Serial.print("] ");
            Serial.print("[");Serial.print(data[i][j].GetPS());Serial.print("]\t");
        }
        Serial.println();
    }
}

#endif