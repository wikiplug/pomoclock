#ifndef multitask_h
#define multitask_h
#include <Arduino.h> 

class multitask{
    private:
        long _time; 
        int _timeState;
        long _TA; 
        long _TP; 

    public: 
        multitask(long time);
        void countTime(); 
        int getState(); 
}; 

#endif