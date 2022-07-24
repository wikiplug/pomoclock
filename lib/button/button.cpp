#include "button.h"
#include "multitask.h"  

/*  LA FUNCIÓN BUTTON TIENE COMO ARGUMENTO AL PIN AL QUE CONECTAMOS AL PULSADOR
    Y AL DEBOUNCE DELAY. DENTRO DE LA FUNCION DECLARAMOS AL PIN COMO: INPUT */
    
button::button(byte pin, int debounceDelay){
    _pin = pin;    
    _debounceDelay = debounceDelay; 
    pinMode(_pin, INPUT); 
}

/*  LA FUNCIÓN BUTTON ACTUALIZA EL ESTADO DEL PULSADOR SI ES APRETADO POR UN TIEMPO MAYOR AL DEBOUNCE DELAY */ 
void button::updateState(){
    int reading = digitalRead(_pin);
    multitaskButton.init(_debounceDelay);
    if(reading == HIGH){
        if(multitaskButton.delay()){
            _buttonState = reading;
        }
        else{
            _buttonState = LOW; 
        }
    }  
    else{
        _buttonState = LOW;
    }
}
/*  OBTENEMOS EL ESTADO DEL PULSADOR EN BASE A LA FUNCIÓN UPDATE STATE */ 
int button::getState(){
    updateState();
    return _buttonState; 
} 