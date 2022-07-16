#include <Arduino.h>
#include "button.h"

button::button(byte pin){
    _pin = pin;    
    pinMode(_pin, INPUT); 
}

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

int button::getState(){
    updateState();
    return _buttonState; 
}