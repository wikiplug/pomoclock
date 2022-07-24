#ifndef multitask_h
#define multitask_h
#include <Arduino.h> 

//  FUNCION PARA HACER DELAY CON MULTITASKING
/*  CREAMOS LA CLASE, EN LO PRIVADO ESTABLECEMOS LAS VARIABLES
    EN LO PUBLICO ESTABLECEMOS LAS FUNCIONES Y EL CONSTRUCTOR   */
class multitask{
    private:
        long _time; 
        int _timeState;
        long _TP; 
        
    public: 
        multitask();
        void init(long time); 
        void countTime(); 
        int delay(); 
}; 

#endif