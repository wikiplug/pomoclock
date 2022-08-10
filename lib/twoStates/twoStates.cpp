#include "twoStates.h"

twoStates::twoStates(){
}

// ALTERNA ENTRE DOS ESTADOS Y RETORNA EL ESTADO CON LA FUNCIÓN getState().
void twoStates::process(){
    _num++; 
    if(_num > 99){
        _num = 0; 
    }
    _div = _num % 2; 
    if(_div != 0){
        _result = true;
    }
    if(_div == 0){
        _result = false; 
    }
}

int twoStates::getState(){
    process(); 
    return _result; 
}
