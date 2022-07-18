#include <Arduino.h>
#include "button.h"

/*  LA FUNCIÓN BUTTON TIENE COMO ARGUMENTO AL PIN AL QUE CONECTAMOS AL PULSADOR
    DENTRO DE LA FUNCION DECLARAMOS AL PIN COMO: INPUT */
button::button(byte pin){
    _pin = pin;    
    pinMode(_pin, INPUT); 
}

/*  LA FUNCIÓN BUTTON ACTUALIZA EL ESTADO DEL PULSADOR SI ES APRETADO POR UN TIEMPO MAYOR AL DEBOUNCE DELAY */ 
void button::updateState(){
    int reading = digitalRead(_pin);
    if(reading != _lastButtonState){
        _lastDobounceTime = millis();
    }
    if((millis() - _lastDobounceTime) > _debounceDelay){
        _buttonState = reading; 
    }
    _lastButtonState = reading;  
}
/*  OBTENEMOS EL ESTADO DEL PULSADOR EN BASE A LA FUNCIÓN UPDATE STATE */ 
int button::getState(){
    updateState();
    return _buttonState; 
} 