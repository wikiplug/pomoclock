#include "incLibOne.h"

button button_1IncLibOne(13, 150); 
button button_2IncLibOne(14, 150); 

incLibOne::incLibOne(){
}

void incLibOne::incThisVar(int varInc){
    _varInc = varInc;
}

void incLibOne::process(){ 
    static int _n = _varInc; 
    //LEE EL ESTADO DEL PULSADOR Y EN BASE A ESO INCREMENTA/DECREMENTA LA VARIABLE
    if(button_1IncLibOne.getState()){
        _n++;
    }
    if(button_2IncLibOne.getState()){
        _n--; 
    }
    // SI LA VARIABLE SUPERA CIERTO VALOR VUELVE A 0
    if(_n > 999 || _n < 0){
        _lcdClear = HIGH; 
        _n = 0;
    }
    // CUANDO CAMBIA DE CENTENAS A DECENAS, DECENAS A UNIDADES, ETC. LCD.CLEAR = HIGH
    else if((_n == 9 && _k == 10)|| (_n == 99 && _k == 100) || (_n == 999 && _k == 1000)){
        _lcdClear = HIGH; 
    }
    else{
        _lcdClear = LOW; 
    }
    _k = _n;  
    _result = _n; 
}

int incLibOne::varValue(){
    process();
    return _result; //retorna el valor de la variable
}

int incLibOne::lcdValue(){
    process(); 
    return _lcdClear; //retorna el valor de la variable
}
