#include "incLibOne.h"

button button_1IncLibOne(14, 150); 
button button_2IncLibOne(27, 150); 

incLibOne::incLibOne(){
}

void incLibOne::incThisVar(int varInc){
    _varInc = varInc;
}

void incLibOne::process(){ 
    //LEE EL ESTADO DEL PULSADOR Y EN BASE A ESO INCREMENTA/DECREMENTA LA VARIABLE
    if(button_1IncLibOne.getState()){
        _varInc++;
    }
    if(button_2IncLibOne.getState()){
        _varInc--; 
    }
    // SI LA VARIABLE SUPERA CIERTO VALOR VUELVE A 0
    if(_varInc < 0){
        _lcdClear = true; 
        _varInc = 0;
    }
    if(_varInc > 99){
        _lcdClear = true; 
        _varInc = 99;
    }
    // CUANDO CAMBIA DE CENTENAS A DECENAS, DECENAS A UNIDADES, ETC. LCD.CLEAR = HIGH
    else if((_varInc == 9 && _k == 10)|| (_varInc == 99 && _k == 100)){
        _lcdClear = true; 
    }
    else{
        _lcdClear = false; 
    }
    _k = _varInc;   
}

int incLibOne::varValue(){
    process();
    return _varInc; //retorna el valor de la variable
}

int incLibOne::lcdValue(){
    process(); 
    return _lcdClear; //retorna el valor de la variable
}
