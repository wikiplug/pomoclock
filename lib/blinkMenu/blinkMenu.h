#ifndef blinkMenu_h
#define blinkMenu_h
#include <Arduino.h>
#include "multitask.h"

class blinkMenu
{
    private:
        char _firstWord[30]; 
        char _secondWord[30];  
        char _word[30]; 
        int _time;   
        byte _inc; 
        byte _div; 
        multitask multitaskBlinkMenu; 
    public:
        blinkMenu();
        void alternate(char firstWord[30], char secondWord[30], int time);
        void updateState(); 
        char* getWord(); 
        
}; 

#endif 