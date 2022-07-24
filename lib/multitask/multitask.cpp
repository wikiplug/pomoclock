#include <Arduino.h>
#include "multitask.h"

/*  LA FUNCIÓN OBTIENE COMO ARGUMENTO AL TIEMPO QUE QUEREMOS DE DELAY   */
multitask::multitask(long time){
    _time = time; 
}

/*  LA FUNCIÓN PONE EN TRUE O FALSE A LA VARIABLE TIME STATE DEPENDIENDO 
    DE SI EL TIEMPO TRANSCURRIDO ES EL MISMO AL TIEMPO SETEADO COMO DELAY   */
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

/*  LA FUNCIÓN OBTIENE EL ESTADO DE TIME STATE Y DEVUELVE UN VALOR EN BASE AL ESTADO OBTENIDO   */
int multitask::delay(){
    countTime(); 
    return _timeState; 
}
