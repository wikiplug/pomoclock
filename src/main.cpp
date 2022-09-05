#include "header.h"
#include "objects.h"

#define pomoSwitch 16
bool pomoSwitchRead;

bool selectButton;
bool selectButtonRead;
byte menuPosition;
byte lcdCleanerPomodoro; 
//POMO MENU
//contadores
byte sessions;

//boolenas 
byte settingsPomo = false; 
byte startPomo; 





// WORK_OR_BREAK y POMO_TIMER
//variables booleanas
int pomodoroCountFinish;
byte firstSession; 
byte statePomodoro; //pomodoro en break o work?
byte sessionFinish;

//contadores 
byte countingSessions; 
byte sessionsBtwLongBreak;
int workTime; 
int shortBreakTime; 
int longBreakTime; 
int minutes;   // carga el tiempo de workTime o shortBreakTime o longBreakTime (depende de statePomodoro)
int seconds;
byte breaksForLongBreak; 
 

// variables de esta funcion (TEMPORAL)
int settingsPosition; 

void setup(){
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
        lcdCleanerPomodoro = true; 
        if(startPomo == false && settingsPomo == false){ //SI LA OPCION DE START NO FUE SELECCIONADA ANTERIORMENTE SE MUESTRA EL MENU POMODORO
            pomo_menu();
        }
        if(startPomo == false && settingsPomo == true){
            pomo_settings(); 
        }
        if(startPomo == true){
            work_or_break(); //FUNCIÓN QUE DICTAMINA SI ES TIEMPO DE TRABAJO O DESCANSO
            if(startPomo == true){
                pomodoro_timer(); //temporizador
            }
        }
    }
    else{ //REGRESO TODAS LAS VARIABLES NECESARIAS PARA EL CORRECTO INICIO DEL POMODORO A SU VALOR DEFAULT.
        if(lcdCleanerPomodoro == true){
            lcd.clear(); 
            lcdCleanerPomodoro = false; 
        }
        startPomo = false;
        settingsPomo = false; 
        pomodoroCountFinish = false; 
        workOrBreak._num = 0; 
        breaksForLongBreak = 0; 
        seconds = 0; 
    }
}

void pomo_menu(){
    if(button_3.getState()){
        menuPosition++;
        if(menuPosition > 2){ 
            menuPosition = 0;
        }
        lcd.clear(); 
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
}

void pomo_menu_display(){
    lcd.setCursor(0, menuPosition);
    lcd.print("- ");
    lcd.setCursor(2, 0);
    lcd.print("sessions: ");
    lcd.print(sessions); 
    lcd.setCursor(2, 1);
    lcd.print("settings.");
    lcd.setCursor(2, 2);
    lcd.print("start");
    lcd.setCursor(0, 3);
    lcd.print("(FINISH TIME: 00:00)"); 
}

void select_sessions(){
    incLibSessions.incThisVar(sessions);
    if(incLibSessions.lcdValue()){
        lcd.clear(); 
    }
    sessions = incLibSessions.varValue();
    pomo_menu_display();
}

void select_settings(){
    pomo_menu_display();
    if(button_1.getState()){
        workTime = workTime - 5; //temporal (ojala) 
        settingsPomo = true; 
        lcd.clear(); 
    }
}

void select_start(){
    pomo_menu_display();
    if(button_1.getState()){
        //ACTIVAR START
        startPomo = true; 
        firstSession = true; 
        countingSessions = sessions;
        // sin embargo, para el usuario las sesiones son las sesiones de trabajo.   
        lcd.clear(); 
        if((sessions == 0)|| (shortBreakTime == 0) || (longBreakTime == 0) || (workTime == 0) || (sessionsBtwLongBreak == 0)){
            startPomo = false; 
            lcd.setCursor(0, 1);
            lcd.print("before start"); 
            lcd.setCursor(0, 2); 
            lcd.print("update settings!");
            delay(1000);
            lcd.clear(); 
            // los unicos delays que el programa lleva estan en las advertencias
            // siempre y cuando no haya ninguna función contando tiempo detras
        }
    }
}


void pomo_settings(){
    if(button_3.getState()){ 
        settingsPosition++; 
        if(settingsPosition > 3){
            settingsPosition = 0; 
        }
        lcd.clear();
    }

    if(settingsPosition == 0){
        select_pomodoro(); //duración del pomodoro (tiempo de trabajo)
    }
    if(settingsPosition == 1){
        select_shortBreak();
    }
    if(settingsPosition == 2){
        select_longBreak(); 
    }
}

void pomo_settings_display1(){
    blinkMenu1.alternate("SETTINGS", "        ", 1000);
    lcd.setCursor(5, 0);
    lcd.print(blinkMenu1.getWord()); 

    lcd.setCursor(0, settingsPosition+1);
    lcd.print("- "); 

    lcd.setCursor(2, 1);
    lcd.print("pomodoro: ");
    lcd.print(workTime); 
    lcd.setCursor(2, 2);
    lcd.print("short break:");
    lcd.print(shortBreakTime);
    lcd.setCursor(2, 3); 
    lcd.print("long break: "); 
    lcd.print(longBreakTime);
    lcd.setCursor(19, 3); 
    lcd.print("↓"); 
}

void pomo_settings_display2(){

}
 
void select_pomodoro(){
    incLibWorkTime.incThisVar(workTime);
    workTime = incLibWorkTime.varValue(); 
    if(incLibWorkTime.lcdValue()){
        lcd.clear(); 
    }   
    pomo_settings_display1(); 
}

void select_shortBreak(){
    incLibShortBreak.incThisVar(shortBreakTime);
    shortBreakTime = incLibShortBreak.varValue(); 
    if(incLibWorkTime.lcdValue()){
        lcd.clear(); 
    }
    pomo_settings_display1(); 
}
void select_longBreak(){
    incLibLongBreak.incThisVar(longBreakTime);
    longBreakTime = incLibLongBreak.varValue(); 
    if(incLibLongBreak.lcdValue()){
        lcd.clear(); 
    }
    pomo_settings_display1(); 
}
void select_sessionsLongBreak(){}
void select_exit(){}


void work_or_break(){
    // alterna entre dos estados: work/break, si está en break alterna entre short o long.
    // alterna entre short o long en base a si una variable es igual al longBreakTime seleccionado
    // en el menú. 
    

    if(sessionFinish == true){ //si el tiempo termino y fue el de work resto sesiones
        sessionFinish = false; 
        countingSessions--;
        if(countingSessions == 0){
            //imprimimos alerta
            lcd.clear(); 
            delay(100);
            lcd.setCursor(3, 1); 
            lcd.print("TIME FINISHED"); 
            delay(900); 
            lcd.clear(); 
            //devuelvo variables de la función a default. 
            startPomo = false; 
            pomodoroCountFinish = false; 
            workOrBreak._num = 0; 
        }
    }
    if(pomodoroCountFinish == true || firstSession == true){
        pomodoroCountFinish = true; //reivindica que la var sea true en caso de que no lo haya sido.
        firstSession = false; 
        statePomodoro = workOrBreak.getState();
    }
    if(statePomodoro == true && pomodoroCountFinish == true){ 
        minutes = workTime; 
        pomodoroCountFinish = false;
    }
    if(statePomodoro == false && pomodoroCountFinish == true){ //estamos en break, se decide si es short o long
        pomodoroCountFinish = false;
        breaksForLongBreak++;
        if(breaksForLongBreak == sessionsBtwLongBreak){
            minutes = longBreakTime;
            breaksForLongBreak = 0;        
        }
        else{
            minutes = shortBreakTime; 
        } 
    }
}

 
void pomodoro_timer(){
    // cuenta el tiempo hacia atras con la libreria multitasking, una vez llega a 0, timePomodoro
    // actualiza su valor a su nuevo estado (work, break) y empieza a contar de nuevo
    // ademas, se visualiza el tiempo en pantalla. 
    pomoTimer.init(100);
    if(pomoTimer.delay()){
        seconds--; 
    }
    if(seconds < 0){
        seconds = 59; 
        minutes--; 
    }
    if(minutes == 0 && seconds == 0){
        pomodoroCountFinish = true; 
        if(statePomodoro == false){
            sessionFinish = true; 
        }
    }
    lcd.setCursor(0, 0); 
    if(minutes < 10){
        lcd.print("0"); 
    }
    lcd.print(minutes);
    lcd.print(":");
    if(seconds < 10){
        lcd.print("0"); 
    }
    lcd.print(seconds); 

    if(startPomo == false){
        lcd.clear(); 
    }
}