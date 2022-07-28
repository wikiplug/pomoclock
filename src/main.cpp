#include "header.h"
#include "objects.h"

#define pomoSwitch 16
bool pomoSwitchRead;
byte startPomo = LOW;
bool selectButton;
bool selectButtonRead;
byte menuPosition;
int workTime; 
int breakTime;

void setup(){
    Serial.begin(115200); 
    lcd.begin(16, 2);      //Iniciamos el lcd
    lcd.backlight();       //Encendemos la luz de fondo
    lcd.clear();           //Limpiamos la pantalla
}

void loop(){
    pomodoro();
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
            //work_or_break(); //FUNCION QUE DICTAMINA SI ES TIEMPO DE TRABAJO O DESCANSO 
        }
    }

    else{ //REGRESO TODAS LAS VARIABLES NECESARIAS PARA EL CORRECTO INICIO DEL POMODORO A SU VALOR DEFAULT.
        startPomo = LOW;
    }
}

void pomo_menu(){
    if(button_3.getState()){
        menuPosition++;
    } 
    if(menuPosition > 3){
        menuPosition = 0;
    }

    if(menuPosition == 0){
        select_work();
    }
    
    if(menuPosition == 1){
        select_shortBreak();
    }
    select_longBreak();
    select_sessionsLongBreak();
    select_sessions();
    select_start();

}

void select_work(){
    // INGRESAMOS LA PALABRA DE LA OPCIÓN DEL MENÚ EN LA QUE ESTAMOS, LA LIBRERIA
    // VA A HACER QUE PARPADEE CADA 1 SEG, IMPRIMIMOS ESA PALABRA EN EL DISPLAY.
    blinkMenu1.alternate("WORK", "    ", 1000); 
    lcd.setCursor(0, 0);
    lcd.print(blinkMenu1.getWord());   

    // INCREMENTAMOS/DECREMENTAMOS Y LEEMOS EL VALOR DE "WORK TIME" DEPENDIENDO DE QUE PULSADOR SE PRESIONE
    incLibWorkTime.incThisVar(workTime); 
    
    // REALIZAMOS UN LCD CLEAR DEPENDIENDO DE SI LA VARIABLE PASA DE UNIDADES A DECENAS, CENTENAS, ETC. 
    if(incLibWorkTime.lcdValue()){
        lcd.clear(); 
    }
    // IMPRIMIMOS TODO EL RESTO DEL MENÚ.
    lcd.setCursor(0, 1);
    lcd.print(incLibWorkTime.varValue());   

}


void select_shortBreak(){


    
}

void select_longBreak(){}
void select_sessionsLongBreak(){}
void select_sessions(){}
void select_start(){}