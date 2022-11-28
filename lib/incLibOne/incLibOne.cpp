#include "incLibOne.h"

button button_1IncLibOne(25, 150); 
button button_2IncLibOne(26, 150); 

//SE LE ASIGNA AL CONSTRUCTOR EL PIN DEL BUZZER
incLibOne::incLibOne(byte buzzerPin){
    _buzzerPin = buzzerPin; 
    pinMode(_buzzerPin, OUTPUT); 
}

void incLibOne::incThisVar(int varInc, int max){
    _varInc = varInc;
    _max = max; 
}

void incLibOne::process(){ 
    //LEE EL ESTADO DEL PULSADOR Y EN BASE A ESO INCREMENTA/DECREMENTA LA VARIABLE
    if(button_1IncLibOne.getState()){
        _varInc++;
        tone(_buzzerPin, 1000, 100);
    }
    if(button_2IncLibOne.getState()){
        _varInc--; 
        tone(_buzzerPin, 1000, 100);
    }
    // SI LA VARIABLE SUPERA CIERTO VALOR VUELVE A 0
    if(_varInc < 0){
        _lcdClear = true; 
        _varInc = 0;
    }
    if(_varInc > _max){
        _lcdClear = true; 
        _varInc = _max;
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
