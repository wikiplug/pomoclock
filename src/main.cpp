#include "header.h"
#include "button.h"
#include "multitask.h"
#include "blinkMenu.h"

TwiLiquidCrystal lcd(0x27);

#define pomoSwitch 16
bool pomoSwitchRead;
byte startPomo = LOW;
bool selectButton;
bool selectButtonRead;
byte menuPosition;
int workTime; 
int breakTime;

button button_1(13, 150);
button button_2(14, 150);
blinkMenu blinkMenu1; 


 
multitask multitaskMenuPosition;

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
    if(button_2.getState()){
        menuPosition++;
    } 
    if(menuPosition > 3){
        menuPosition = 0;
    }
    
    select_work();    
    select_shortBreak();
    select_longBreak();
    select_sessionsLongBreak();
    select_sessions();
    select_start();

}

void select_work(){
//  SI ESTOY EN POS. WORK: WORK PARPADEA Y ME PERMITE INCREMENTAR, SI SUPERA 9999MIN VUELVE A 0
    if(menuPosition == 0){ 
        blinkMenu1.alternate("WORK", "    ", 750); 
        lcd.setCursor(0, 0);
        lcd.print(blinkMenu1.getWord()); 
        
        if(button_1.getState()){
            workTime++;         
        }
        if(workTime > 9999){
            lcd.setCursor(0, 1);
            lcd.println("MAX!");
            delay(1000);
            workTime = 0;
        }
    }
    lcd.setCursor(0, 1);
    lcd.print(workTime);
}

/* void select_shortBreak(){

    if(menuPosition == 1){
        if(multitaskMenuPosition.delay()){
            lcd.setCursor(5, 0);
            lcd.print("     "); 
        }
        if(button_1.getState()){
            breakTime++;
        }
    }
}
*/
void select_shortBreak(){}
void select_longBreak(){}
void select_sessionsLongBreak(){}
void select_sessions(){}
void select_start(){}