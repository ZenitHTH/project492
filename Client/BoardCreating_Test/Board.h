#include <iostream>

using namespace std;

class Board
{
    private:
        int** board;
        
        
        bool isInBoard(int,int);
        bool isBoardEqual(const Board&);

    
    public:
        int len_x,len_y;

        Board(int,int);
        void Insert(int,int,int);
        void PrintBoard();
        Board operator=(const Board&);

        template <size_t rows,size_t cols>
        void InsertAll(int (&arr2d)[rows][cols])
        {
            for(int i=0;i<this->len_x;i++)
            {
                for(int j=0;j<this->len_y;j++)
                {
                    this->board[i][j] = arr2d[i][j];
                }
            }
        }
      
};  



