#ifndef twoStates_h
#define twoStates_h

#include "Arduino.h"
class twoStates{
    private:
        int _div; 
        int _result; 
    public: 
        int _num;
        twoStates();
        void process(); 
        int getState();
};

#endif