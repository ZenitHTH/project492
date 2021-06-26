#include "Board.h"


Board::Board(int x,int y)
{
    board = new int*[x];
    for(int i=0;i<x;i++)
    {
        board[i] = new int[y];
    }
    this->len_x=x;
    this->len_y=y;
}


void Board::Insert(int x,int y,int pin)
{
    if(isInBoard(x,y))
    {
        this->board[x][y] = pin;
        cout<< "(x,y) : " << "(" << x << ","<< y << ") = " << this->board[x][y] << endl;
    }
    else 
        cout << "This pin is out of board." << endl;
    
}

void Board::PrintBoard()
{
    for(int i=0;i<this->len_x;i++)
    {
        for(int j=0;j<this->len_y;j++)
        {
            cout<<"["<<this->board[i][j]<<"]";
            if(j < this->len_y-1) cout << "\t"; 
        }
        cout<<endl;
    }
    cout<<endl;
}

Board Board::operator=(const Board& b)
{

    Board theboard(this->len_x,this->len_y);
    theboard.board = b.board;


    return theboard;
}