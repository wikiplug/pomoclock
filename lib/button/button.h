#ifndef button_h
#define button_h

#include <Arduino.h> //incluyo la libreria arduino porque voy a usar funciones de arduino
#include "multitask.h" 

class button
{
    private:
        byte _pin; //pongo "_" en los parametros privados (convención), declaro variables
        int _buttonState;
        int _debounceDelay;  //tiempo que el botón tiene que estar presionado para que detecte la pulsación
        multitask multitaskButton;
    public:
        button(byte pin, int debounceDelay); //constructor; tiene de parametro al pin del botón 
        void updateState();  //declaro funciones
        int getState();
};

#endif