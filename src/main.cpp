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
    
    select_shortBreak();
    select_longBreak();
    select_sessionsLongBreak();
    select_sessions();
    select_start();

}
 //  SI ESTOY EN POS. WORK: WORK PARPADEA Y ME PERMITE INCREMENTAR, SI SUPERA 9999MIN VUELVE A 0
void select_work(){
    blinkMenu1.alternate("WORK", "    ", 750); 
    lcd.setCursor(0, 0);
    lcd.print(blinkMenu1.getWord());   

    workTime = incrementador();
    lcd.setCursor(0, 1);
    lcd.print(workTime);   
}

int incrementador(){
    static int n;
    static int k; 
    if(button_1.getState()){
        n = n + 5;
    }
    if(button_2.getState()){
        n = n - 5; 
    }
    if(n > 9999 || n < 0){
        lcd.clear(); 
        n = 0;
    }
    if((n == 5 && k == 10)|| (n == 95 && k == 100) || (n == 995 && k == 1000)){
        lcd.clear(); 
    }
    k = n; 
    return n; 
} 
/*void select_work(){
     
    if(menuPosition == 0){
        libMenuSelectWork.display(0, "WORK", "    ", 0); 
        libMenuSelectWork.displayPrint(); 
        workTime = libMenuSelectWork.varInc; 
        
        lcd.setCursor(4, 0);
        lcd.print("ShBr LgBr ");

    }
}
*/ 

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