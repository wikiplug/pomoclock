#ifndef button_h
#define button_h

#include <Arduino.h> //incluyo la libreria arduino porque voy a usar funciones de arduino

class button
{
    private:
        byte _pin; //pongo "_" en los parametros privados (convención), declaro variables
        int _buttonState;
        int _lastButtonState = LOW; //el boton arranca en estado bajo
        unsigned long _lastDobounceTime = 0;
        unsigned long _debounceDelay;  //tiempo que el botón tiene que estar presionado para que detecte la pulsación
    public:
        button(byte pin, int debounceDelay); //constructor; tiene de parametro al pin del botón 
        void updateState();  //declaro funciones
        int getState();
};

#endif
