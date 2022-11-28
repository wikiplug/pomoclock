#include "alarmsLib.h"
#include "multitask.h"

button button_1_alarmsLib(25, 150);

//constructor
alarmsLib::alarmsLib(){

}
//config the parameters of the alarm
void alarmsLib::setAlarm(int hourToComparate, int minutesToComparate, byte hourAlarm, byte minutesAlarm, byte stateOfAlarm){
    //convierto todos los datos a tipo PRIVADO
    _hourToComparate = hourToComparate;
    _minutesToComparate = minutesToComparate; 
    _hourAlarm = hourAlarm; 
    _minutesAlarm = minutesAlarm; 
    _stateOfAlarm = stateOfAlarm; 
    pinMode(32, OUTPUT); 
}

void alarmsLib::process(){
    
    //wait 60 seconds to return the variable "false" again. 
    if(_alarmOFF == true){
        multitaskAlarmONofOFF_delay.init(60000);
        if(multitaskAlarmONofOFF_delay.delay()){
            _alarmOFF = false; 
        }
    }
    //compare the hour and minutes of the alarm with the hour and minutes irl xD
    if(_hourToComparate == _hourAlarm && _minutesToComparate == _minutesAlarm && _stateOfAlarm == true && _alarmOFF == false){
        while(_inc < 240){
            multitaskAlarm.init(500);
            if(multitaskAlarm.delay()){
                _inc++;
                //activa el pulsador cada 1/2 seg.
                tone(32, 3000, 100);
            }
            if(button_1_alarmsLib.getState()){
                _alarmOFF = true; 
                _inc = 0;
                break; 
            }
        }  
        if(_inc == 240){
            _inc = 0; 
        }
    }
}   

void alarmsLib::alarmTriggered(){
    process();  
}

