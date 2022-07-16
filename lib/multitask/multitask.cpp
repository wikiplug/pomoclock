#include <Arduino.h>
#include "multitask.h"

multitask::multitask(long time){
    _time = time; 
}

void multitask::countTime(){
    _TA = millis();
    if((_TA - _TP) >= _time){
        _timeState = true;
        _TP = millis();
    }
    else{
        _timeState = false; 
    }
}

int multitask::getState(){
    countTime(); 
    return _timeState; 
}
