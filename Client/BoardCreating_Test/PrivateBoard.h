#include "Board.h"

bool Board::isInBoard(int x,int y)
{
    if(this->len_x <= x || this->len_y <= y) return false;
    else return true;
}