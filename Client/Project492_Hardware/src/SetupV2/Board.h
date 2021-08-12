#include "Data.h"

class Board
{
    private :
        Data **data;

    public:
        int len_x, len_y ;

        template<size_t row,size_t col>
        Board(Data [row][col]);

};

template<size_t row,size_t col>
Board::Board(Data data[row][col])
{
    this->len_x = row;
    this->len_y = col;
    this->data = data;
    

}