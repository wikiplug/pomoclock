#include "incLib.h"

button button_1IncLib(25, 150); 
button button_2IncLib(26, 150); 

incLib::incLib(byte buzzerPin){
    _buzzerPin = buzzerPin; 
    pinMode(_buzzerPin, OUTPUT);
}

void incLib::incThisVar(int varInc){
    _varInc = varInc;
}

void incLib::process(){ 
    //LEE EL ESTADO DEL PULSADOR Y EN BASE A ESO INCREMENTA/DECREMENTA LA VARIABLE
    if(button_1IncLib.getState()){
        tone(_buzzerPin, 1000, 100);
        _varInc  = _varInc + 5;
    }
    if(button_2IncLib.getState()){
        tone(_buzzerPin, 1000, 100);
        _varInc  = _varInc - 5; 
    }
    // SI LA VARIABLE SUPERA CIERTO VALOR VUELVE A 0
    if(_varInc < 0){
        _lcdClear = true; 
        _varInc = 0;
    }
    if(_varInc > 255){
        _lcdClear = true; 
        _varInc = 255; 
    }
    // CUANDO CAMBIA DE CENTENAS A DECENAS, DECENAS A UNIDADES, ETC. LCD.CLEAR = HIGH
    else if((_varInc == 5 && _k == 10)){
        _lcdClear = true; 
    }
    else{
        _lcdClear = false; 
    }
    _k = _varInc;  
}

int incLib::varValue(){
    process();
    return _varInc; //retorna el valor de la variable
}

int incLib::lcdValue(){
    process(); 
    return _lcdClear; //retorna el valor de la variable
}
