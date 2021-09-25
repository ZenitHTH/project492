#ifndef PINCHECK_H
#define PINCHECK_H
#include "Board.h"
#include "Data.h"
#include <Arduino.h>
//#include <LinkedList.h>
#include <time.h>
class PinCheck
{
    private :
    Board before;
    // struct local
    // {
    //     uint8_t i;
    //     uint8_t j;
        
    // };
    // LinkedList<local> diff;
    uint8_t a = 0;
    char* int2char(int);
    void ReplaceBoard(Board);
    void CheckDiffrent(Board);

    public :
    PinCheck(void);
    void Insert(Board);
    
    char* PublishData(char*, char*, char*);

};


#endif