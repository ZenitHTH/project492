#include "Board.h"
using namespace std;

int main()
{
    // 0 is nothing ,1 is red ,2 is green ,3 is yellow
//    Board tnew_board(5,5);  
//    Board told_Board(5,5);
    Board corrboard(5,5); // correctingAnswer

    int b[5][5] =
    {
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1}
    };

    corrboard.InsertAll(b);
    corrboard.PrintBoard();
    corrboard.Insert(2,1,3);
    corrboard.PrintBoard();
    corrboard.Insert(2,5,3);
    corrboard.PrintBoard();

    return 0;
}