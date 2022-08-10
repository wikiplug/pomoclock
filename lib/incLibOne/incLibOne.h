#ifndef incLibOne_h
#define incLibOne_h

#include "Arduino.h"
#include "button.h"

class incLibOne 
{
    private:
        int _k;
        int _varInc; 
        int _result; 
        int _lcdClear; 
        void process(); 
    public:
        incLibOne();
        void incThisVar(int varInc); 
        int varValue();
        int lcdValue(); 
}; 

#endif