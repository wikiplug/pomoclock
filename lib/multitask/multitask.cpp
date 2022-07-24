#include <Arduino.h>
#include "multitask.h"

/* CREAMOS EL OBJETO */
multitask::multitask(){
}
/* INICIALIZAMOS EL OBJETO USANDO AL TIEMPO */ 
void multitask::init(long time){
    _time = time; 
}

/*  LA FUNCIÓN PONE EN TRUE O FALSE A LA VARIABLE TIME STATE DEPENDIENDO 
    DE SI EL TIEMPO TRANSCURRIDO ES EL MISMO AL TIEMPO SETEADO COMO DELAY   */
void multitask::countTime(){
    if((millis() - _TP) >= _time){
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
