#include "header.h"
#include "button.h"
#include "multitask.h"

bool button_2;
bool pomoSwitch;
bool pomoSwitchRead;
bool startPomo;
bool selectButton;
bool selectButtonRead;
byte menuPosition;

button button_1(3); 
multitask multitask_1(1000);

int num;  // borrar
void setup(){
    Serial.begin(115200); 
}

void loop(){
    // pomodoro();

    if(multitask_1.getState()){
        num++; 
        Serial.println(num); 
    }
}

// EN ESTA FUNCIÓN SE CORROBORA SI SE ACTIVA LA OPCION POMODORO O NO
// A SU VEZ, EJECUTA TODAS LAS FUNCIONES QUE CORREN DENTRO DEL POMODORO
// SE SEGMENTA EL CODIGO EN BLOQUES PARA FACILITAR SU LEGIBILIDAD Y PROGRAMACION
     void pomodoro(){ 
    pomoSwitchRead = digitalRead(pomoSwitch);
    
    if(pomoSwitchRead == HIGH){
        if(startPomo == LOW){ //SI LA OPCION DE START NO FUE SELECCIONADA ANTERIORMENTE SE MUESTRA EL MENU POMODORO
            pomo_menu();
        }
        else{
            work_or_break(); //FUNCION QUE DICTAMINA SI ES TIEMPO DE TRABAJO O DESCANSO 
        }
    }

    else{ //REGRESO TODAS LAS VARIABLES NECESARIAS PARA EL CORRECTO INICIO DEL POMODORO A SU VALOR DEFAULT.
        startPomo = LOW;
    }
}

void pomo_menu(){
    selectButtonRead = digitalRead(button_2);
    if(selectButtonRead == HIGH){
        delay(15);
        menuPosition++;
    } 
    if(menuPosition > 3){
        menuPosition = 0;
    }
    
    select_work();    
    select_break();
    select_sessions();
    select_start();

}

void select_work(){
    if(menuPosition == 0){
        //parpadee e incremente
        if(menuPosition)

    }
    lcd.setCursor(0, 0);
    lcd.print("WORK");

    lcd.setCursor(0, 1);
    lcd.print(WORK_TIME);
}

*/ 