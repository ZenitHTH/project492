#include "Data.h"

class Board
{
    private :
        Data **data;

    public:
        int len_x, len_y , tcaaddr;

        Board(int,int,int);

};

Board::Board(int x,int y,int tcaaddr)
{
    this->len_x = x;
    this->len_y = y;
    this->tcaaddr = tcaaddr;

    //SetupSensor
    

}