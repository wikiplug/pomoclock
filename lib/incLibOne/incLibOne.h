#ifndef incLibOne_h
#define incLibOne_h

#include "Arduino.h"
#include "button.h"

class incLibOne 
{
    private:
        int _k;
        int _varInc; 
        int _lcdClear; 
        byte _buzzerPin; 
        void process(); 
    public:
        incLibOne(byte buzzerPin);
        void incThisVar(int varInc); 
        int varValue();
        int lcdValue(); 
}; 

#endif