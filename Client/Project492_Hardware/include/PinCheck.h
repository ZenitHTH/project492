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
    //Board before;
    bool** before;
    uint8_t col,row;
    // struct local
    // {
    //     uint8_t i;
    //     uint8_t j;
        
    // };
    // LinkedList<local> diff;
    uint8_t a = 0;
    char* int2char(int);
    bool CheckDiffrent(Board);

    public :
    PinCheck(uint8_t,uint8_t);
    void Insert(Board);
    
    char* PublishData(char*, char*, char*);

};


#endif