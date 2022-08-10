#include "header.h"
#include "objects.h"



#define pomoSwitch 16
bool pomoSwitchRead;
byte startPomo = LOW; //temporal el "HIGH"
bool selectButton;
bool selectButtonRead;
byte menuPosition;


// EJECUCIÓN DE POMODORO
int statePomodoro;
int pomodoroCountFinish;
int timePomodoro;   
int stateBreak; 

int sessions; 
int workTime; 
int shortBreakTime; 
int longBreakTime; 
byte sessionsBtwLongBreak;
int seconds;

 

void setup(){
    pomodoroCountFinish = true; //temporal

    Serial.begin(115200); 
    lcd.begin(20, 4);      //Iniciamos el lcd
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
            work_or_break(); //FUNCION QUE DICTAMINA SI ES TIEMPO DE TRABAJO O DESCANSO
            pomodoro_timer(); 

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
        select_sessions();
    }
    if(menuPosition == 1){
        select_settings(); 
    }
    if(menuPosition == 2){
        select_start();
    }
    
    select_longBreak();
    select_sessionsLongBreak();

}

void select_sessions(){
    lcd.setCursor(0, 0);
    blinkMenu1.alternate("- ", "  ", 750); 
    lcd.print(blinkMenu1.getWord());
    lcd.print("sessions: "); 
    incLibSessions.incThisVar(sessions);
    if(incLibSessions.lcdValue()){
        lcd.clear(); 
    }
    lcd.print(incLibSessions.varValue());
    
    lcd.setCursor(0, 1);
    lcd.print("  start");
    lcd.setCursor(0, 2); 
    lcd.print("  settings"); 
    lcd.setCursor(0, 3); 
    lcd.print("(FINISH TIME: 00:00)");
    //print: finish time: 00:00 
}

void select_settings(){}

void select_work(){
    // INGRESAMOS LA PALABRA DE LA OPCIÓN DEL MENÚ EN LA QUE ESTAMOS, LA LIBRERIA
    // VA A HACER QUE PARPADEE CADA 1 SEG, IMPRIMIMOS ESA PALABRA EN EL DISPLAY.
    blinkMenu1.alternate("pomodoro: ", "          ", 1000); 
    lcd.setCursor(0, 0);
    lcd.print(blinkMenu1.getWord());   

    // INCREMENTAMOS/DECREMENTAMOS Y LEEMOS EL VALOR DE "WORK TIME" DEPENDIENDO DE QUE PULSADOR SE PRESIONE
    incLibWorkTime.incThisVar(workTime); 
    
    // REALIZAMOS UN LCD CLEAR DEPENDIENDO DE SI LA VARIABLE PASA DE UNIDADES A DECENAS, CENTENAS, ETC. 
    if(incLibWorkTime.lcdValue()){
        lcd.clear(); 
    }
    // IMPRIMIMOS TODO EL RESTO DEL MENÚ.
    lcd.setCursor(14, 0);
    lcd.print(incLibWorkTime.varValue());
    lcd.print("min");
    
    lcd.setCursor(0, 1); 
    lcd.print("short break:");
    lcd.setCursor(0, 2);
    lcd.print("long break:"); 
    lcd.setCursor(0, 3); 
    lcd.print("longBreakDelay:"); 
    
}


void select_shortBreak(){



}
void select_longBreak(){}
void select_sessionsLongBreak(){}

void select_start(){}

void work_or_break(){
    // alterna entre dos estados: work/break, si está en break alterna entre short o long
    // alterna entre short o long en base a si una var es igual al longBreakTime seleccionado
    // en el menú. 
    if(pomodoroCountFinish == true){
        statePomodoro = workOrBreak.getState();
    }
    if(statePomodoro == true && pomodoroCountFinish == true){ 
        timePomodoro = workTime;
        pomodoroCountFinish = false;
    }
    if(statePomodoro == false && pomodoroCountFinish == true){ //estamos en break, se decide si es short o long
        static byte inc; 
        inc++;
        if(inc == sessionsBtwLongBreak){
            timePomodoro = longBreakTime;
            inc = 0;
        }
        else{
            timePomodoro = shortBreakTime; 
        }
        pomodoroCountFinish = false; 
    }
}

 
void pomodoro_timer(){
    // cuenta el tiempo hacia atras con la libreria multitasking, una vez llega a 0, timePomodoro
    // actualiza su valor a su nuevo estado (work, break) y empieza a contar de nuevo
    // ademas, se visualiza el tiempo en pantalla. 
    pomoTimer.init(1000);
    if(pomoTimer.delay()){
        seconds--; 
    }
    if(seconds < 0){
        seconds = 59; 
        timePomodoro--; 
    }
    if(timePomodoro == 0 && seconds == 0){
        pomodoroCountFinish = true; 
    }
    lcd.setCursor(0, 0); 
    if(timePomodoro < 10){
        lcd.print("0"); 
    }
    lcd.print(timePomodoro);
    lcd.print(":");
    if(seconds < 10){
        lcd.print("0"); 
    }
    lcd.print(seconds); 
}