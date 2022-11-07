#ifndef incLib_h
#define incLib_h

#include "Arduino.h"
#include "button.h"

class incLib 
{
    private:
        int _k;
        int _varInc; 
        int _lcdClear; 
        byte _buzzerPin; 
        void process(); 
    public:
        incLib(byte buzzerPin);
        void incThisVar(int varInc); 
        int varValue();
        int lcdValue(); 
}; 

#endif