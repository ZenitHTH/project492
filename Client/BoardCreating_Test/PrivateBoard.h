#include "Board.h"

bool Board::isInBoard(int x,int y)
{
    if(this->len_x <= x || this->len_y <= y) return false;
    else return true;
}

bool Board::isBoardEqual(const Board& b)
{
    if(this->len_x != b.len_x || this->len_y != b.len_y) return false;
    else return true;
}