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
        int len_x, len_y ;

        Board(Data **,int,int);
        Board(void);
        Board operator=(const Board&);
        void PrintStatus();
        bool** PinDetect();

};


#endif