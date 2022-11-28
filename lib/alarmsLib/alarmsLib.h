// PERMITE CARGAR MAS DE UNA ALARMA Y COMPARARLAS CON VARIABLES DE HORA Y MINUTOS.
#ifndef alarmsLib_h
#define alarmsLib_h

#include "Arduino.h"
#include "multitask.h"
#include "button.h"

class alarmsLib
{
    private: 
        int _hourToComparate; 
        int _minutesToComparate; 
        byte _hourAlarm; 
        byte _minutesAlarm; 
        byte _stateOfAlarm; //alarma activada/desactivada
        byte _alarmOFF; 
        byte _inc; 
        multitask multitaskAlarm;
        multitask multitaskAlarmONofOFF_delay; 
        void process(); 

    public: 
        //declaramos al constructor
        alarmsLib(); 
        //definimos los parametros de la alarma
        void setAlarm(int hourToComparate, int minutesToComparate, byte hourAlarm, byte minutesAlarm, byte stateOfAlarm); 
        //comparamos la alarma programada con la hora y minutos a comparar
        void alarmTriggered(); 
};

#endif
