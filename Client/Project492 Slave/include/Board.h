#ifndef BOARD_H
#define BOARD_H
#include <Arduino.h>
#include "Data.h"

class Board
{
    private :
        Data** data;
        bool HaveData();

    public:
        uint8_t len_x, len_y ;

        Board(Data **,uint8_t,uint8_t);
        Board(void);
        Board operator=(const Board&);
        void PrintStatus();
        bool** PinDetect();
        void ReplaceData(Data **);
        void DeleteData();
        void DeleteLen();

};


#endif