#ifndef twoStates_h
#define twoStates_h

#include "Arduino.h"
class twoStates{
    private:
        int _num; 
        int _div; 
        int _result; 
    public: 
        twoStates();
        void process(); 
        int getState();
};

#endif