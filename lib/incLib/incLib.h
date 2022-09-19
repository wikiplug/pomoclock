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
        void process(); 
    public:
        incLib();
        void incThisVar(int varInc); 
        int varValue();
        int lcdValue(); 
}; 

#endif