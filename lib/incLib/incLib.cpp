#include "incLib.h"

button button_1IncLib(13, 150); 
button button_2IncLib(14, 150); 

incLib::incLib(){
}

void incLib::incThisVar(int varInc){
    _varInc = varInc;
}

void incLib::process(){ 
    static int _n = _varInc; 
    //LEE EL ESTADO DEL PULSADOR Y EN BASE A ESO INCREMENTA/DECREMENTA LA VARIABLE
    if(button_1IncLib.getState()){
        _n = _n + 5;
    }
    if(button_2IncLib.getState()){
        _n = _n - 5; 
    }
    // SI LA VARIABLE SUPERA CIERTO VALOR VUELVE A 0
    if(_n > 9999 || _n < 0){
        _lcdClear = HIGH; 
        _n = 0;
    }
    // CUANDO CAMBIA DE CENTENAS A DECENAS, DECENAS A UNIDADES, ETC. LCD.CLEAR = HIGH
    else if((_n == 5 && _k == 10)|| (_n == 95 && _k == 100) || (_n == 995 && _k == 1000)){
        _lcdClear = HIGH; 
    }
    else{
        _lcdClear = LOW; 
    }
    _k = _n;  
    _result = _n; 
}

int incLib::varValue(){
    process();
    return _result; //retorna el valor de la variable
}

int incLib::lcdValue(){
    process(); 
    return _lcdClear; //retorna el valor de la variable
}
