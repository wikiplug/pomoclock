#include "header.h"
#include "objects.h"
#include "webpage.h"

void handleRoot()
{
  server.send(200,"text/html", webpageCont);
}

void setupWiFi(){
  WiFi.mode(WIFI_STA); //es un set mode, el esp está preterminado en STA+AP
  WiFiManager wm; //Creamos la instancia o al modo de configuración: "); //LCD
  Serial.println(WiFi.softAPIP());
  Serial.println ("Configurar wifi"); //LCD
  wm.setConfigPortalTimeout(180); //Se establece un tiempo de espera para evitar que el ESP no se cuelgue a ser configurado en caso de un corte de suministro electrico. 
  if(!wm.autoConnect("RED-ESP32")){
        Serial.print("No hay datos guardados");} //Si no hay datos guardados, wm levanta un AP. LCD
  else { 
          Serial.print ("Existen datos guardados");} //Nos conectamos de forma automática. LCD
          wifi= WiFi.SSID();
          Serial.println ("Conectado a la red Wifi: "); //LCD
          Serial.println(wifi);
          ip = WiFi.localIP();
          Serial.print("IP: "); //LCD
          Serial.println(ip);
          server.on("/", handleRoot);
          server.begin(); webSocket.begin();
}

void loopWiFi(){
  webSocket.loop(); server.handleClient();
//====================================================================
//Función para resetear(borrar)credenciales de red(ingresando'a'en el monitor serie)
//====================================================================
  char option = ' ';
    if(Serial.available() != 0){
      option = Serial.read(); 
    if(option == 'a'){
      WiFiManager wm; //Se crea nuevamente la instancia del wm para el reset.
      wm.resetSettings();  
      Serial.println ("Reiniciar equipo");} //LCD
    }
}

void setup(){
    Serial.begin(115200);

    EEPROM.begin(EEPROM_SIZE);
    workTime = EEPROM.read(0);  
    shortBreakTime = EEPROM.read(1);
    longBreakTime = EEPROM.read(2); 
    longBreakDelay = EEPROM.read(3); 
    
    if (! rtc.begin()) {				// si falla la inicializacion del modulo RTC
        Serial.println("Modulo RTC no encontrado !");	// muestra mensaje de error
        while (1);					// bucle infinito que detiene ejecucion del programa
    }
    rtc.adjust(DateTime(__DATE__, __TIME__)); //TEMPORAL

    display.setBrightness(1);

    lcd.begin(20, 4);      //Iniciamos el lcd
    lcd.backlight();       //Encendemos la luz de fondo
    lcd.clear();           //Limpiamos la pantalla
    
    pinMode(pomoSwitch, INPUT); 
    
    // //activa todas las funciones de configuración inicial del equipo si esta en "1"!
    // firstON = EEPROM.read(4); 
    // if(firstON == true){
    //     firstON = false; 
    //     EEPROM.write(4, firstON);
    //     EEPROM.commit();
    //     //AGREGAR FUNCIONES DE INICIO (WIFI MANAGER, ETC.) TENER EN CUENTA METER TODO EN UN WHILE
    // }
    setupWiFi(); 
}

void loop(){
    loopWiFi(); 
    hour(); 
    if(pomoSwitchRead == LOW){
        lcdStandard();
    } 
    alarms(); 
    pomodoro();
}

void hour(){
    DateTime fecha = rtc.now();
    display.showNumberDecEx(fecha.hour(), 0b01000000, true, 2, 0); 
    display.showNumberDec(fecha.minute(), true, 2, 2); 
}

void lcdStandard(){
    DateTime fecha = rtc.now();
    lcd.setCursor(0, 0);
    lcd.print(fecha.day()); 
    lcd.print("/");
    lcd.print(fecha.month());
    lcd.print("/");
    lcd.print(fecha.year()); 
}
int AlarmHour;
int AlarmMinute;
void alarms(){
    DateTime fecha = rtc.now();
    if(fecha.hour() == AlarmHour && fecha.minute() == AlarmMinute){
        //genero un tono. INTERRUMPO CUALQUIER COSA QUE ESTE OCURRIENDO E IMPRIMO MENSAJE EN PANTALLA. 
    }
    
}

// EN ESTA FUNCIÓN SE CORROBORA SI SE ACTIVA LA OPCION POMODORO O NO
// A SU VEZ, EJECUTA TODAS LAS FUNCIONES QUE CORREN DENTRO DEL POMODORO
// SE SEGMENTA EL CODIGO EN BLOQUES PARA FACILITAR SU LEGIBILIDAD Y PROGRAMACION
void pomodoro(){ 
    pomoSwitchRead = digitalRead(pomoSwitch);
    if(pomoSwitchRead == HIGH){
        lcdCleanerPomodoro = true; 
        if(startPomo == false && settingsPomo == false){ 
            pomo_menu();
        }
        if(startPomo == false && settingsPomo == true){
            pomo_settings(); 
        }
        if(startPomo == true){
            work_or_break(); //FUNCIÓN QUE DICTAMINA SI ES TIEMPO DE TRABAJO O DESCANSO
            if(button_3.getState()){
                lcd.clear();
                pause_pomodoro();  
            }
            if(startPomo == true && pausePomodoro == false){
                pomodoro_timer(); //temporizador
            }
        }
    }
    else{ //REGRESO TODAS LAS VARIABLES NECESARIAS PARA EL CORRECTO INICIO DEL POMODORO A SU VALOR DEFAULT.
        if(lcdCleanerPomodoro == true){
            lcd.clear(); 
            lcdCleanerPomodoro = false; 
        }
        menuPosition = 0; 
        startPomo = false;
        settingsPomo = false; 
        pomodoroCountFinish = false; 
        workOrBreak._num = 0; 
        breaksForLongBreak = 0; 
        seconds = 0; 
        pausePom._num = 0; 
        pausePomodoro = false; 
    }
}

void pomo_menu(){
    if(button_3.getState()){
        menuPosition++;
        tone(buzzerPin, 1000, 100);
        if(menuPosition > 2){ 
            menuPosition = 0;
        }
        lcd.clear(); 
    } 

    switch (menuPosition){
    case 0:
        select_sessions();
        break;
    
    case 1:
        select_settings();
        break;
    case 2:
        select_start();
        break;
    }
}

void pomo_menu_display(){
    lcd.setCursor(0, menuPosition);
    lcd.print("- ");
    lcd.setCursor(2, 0);
    lcd.print("sessions: ");
    lcd.print(sessions); 
    lcd.setCursor(2, 1);
    lcd.print("settings");
    lcd.setCursor(2, 2);
    lcd.print("start");
    lcd.setCursor(0, 3);
    lcd.print("(FINISH TIME: ");
    if(horaFinal < 10){
        lcd.print("0"); 
    }
    lcd.print(horaFinal);
    lcd.print(":");  
    if(minutosFinal < 10){
        lcd.print("0");
    }
    lcd.print(minutosFinal); 
    lcd.print(")"); 
}

void select_sessions(){
    incLibSessions.incThisVar(sessions);
    if(incLibSessions.lcdValue()){
        lcd.clear(); 
    }
    sessions = incLibSessions.varValue();
    finishTime(); 
    pomo_menu_display();
}

void select_settings(){
    pomo_menu_display();
    if(button_1.getState()){
        tone(buzzerPin, 1000, 100);
        settingsPosition = 0; 
        settingsPomo = true; 
        lcd.clear();
        delay(250); 
    }
}

void select_start(){
    pomo_menu_display();
    if(button_1.getState()){
        tone(buzzerPin, 1000, 100);
        //ACTIVAR START
        startPomo = true; 
        firstSession = true; 
        countingSessions = sessions; 
        lcd.clear(); 
        
        if((sessions == 0)|| (shortBreakTime == 0) || (longBreakTime == 0) || (workTime == 0) || (longBreakDelay == 0)){
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

void finishTime(){
    DateTime fecha = rtc.now();
    int minutosTotal = workTime * sessions + shortBreakTime * (sessions - (sessions / longBreakDelay)) + longBreakTime * (sessions / longBreakDelay);
    int horaPomodoro = minutosTotal / 60; 
    float minutosPomodoroDecimal = minutosTotal / 60.0 - horaPomodoro;
    float minutosPomodoro = minutosPomodoroDecimal * 60.0;
    int n = ((horaPomodoro + fecha.hour()) / 24); 
    horaFinal = (horaPomodoro + fecha.hour()) - (n * 24);
    minutosFinal = minutosPomodoro + fecha.minute();  
    if(minutosFinal > 59){
        minutosFinal = minutosFinal - 60;
        horaFinal = horaFinal + 1;  
    }  
}

void pomo_settings(){
    if(button_3.getState()){
        tone(buzzerPin, 1000, 100); 
        settingsPosition++; 
        if(settingsPosition > 4){
            settingsPosition = 0; 
        }
        lcd.clear();
    }

    switch(settingsPosition){
        case 0:
            select_pomodoro(); 
            break; 
        case 1: 
            select_shortBreak(); 
            break; 
        case 2:
            select_longBreak(); 
            break;
        case 3:
            select_longBreakDelay();  
            break; 
        case 4:
            select_exit_and_save(); 
            break; 
    }
}

void pomo_settings_display1(){
    lcd.setCursor(6, 0);
    lcd.print("SETTINGS"); 

    lcd.setCursor(0, settingsPosition+1);
    lcd.print("- "); 

    lcd.setCursor(2, 1);
    lcd.print("pomodoro: ");
    lcd.print(workTime); 
    lcd.print("min");
    lcd.setCursor(2, 2);
    lcd.print("shortBreak: ");
    lcd.print(shortBreakTime);
    lcd.print("min");
    lcd.setCursor(2, 3); 
    lcd.print("longBreak: "); 
    lcd.print(longBreakTime); 
    lcd.print("min");
}

void pomo_settings_display2(){
    lcd.setCursor(0, settingsPosition-3);
    lcd.print("- ");
    lcd.setCursor(2, 0);
    lcd.print("longBreakDelay: ");
    lcd.print(longBreakDelay);
    lcd.setCursor(2, 1);
    lcd.print("exit & save"); 
}
 
void select_pomodoro(){
    incLibWorkTime.incThisVar(workTime);
    if(incLibWorkTime.lcdValue()){
        lcd.clear(); 
    }
    workTime = incLibWorkTime.varValue();    
    pomo_settings_display1(); 
}

void select_shortBreak(){
    incLibShortBreak.incThisVar(shortBreakTime); 
    if(incLibShortBreak.lcdValue()){
        lcd.clear(); 
    }
    shortBreakTime = incLibShortBreak.varValue();
    pomo_settings_display1(); 
}

void select_longBreak(){
    incLibLongBreak.incThisVar(longBreakTime); 
    if(incLibLongBreak.lcdValue()){
        lcd.clear(); 
    }
    longBreakTime = incLibLongBreak.varValue();
    pomo_settings_display1(); 
}

void select_longBreakDelay(){
    incLibLongBreakDelay.incThisVar(longBreakDelay);
    if(incLibLongBreakDelay.lcdValue()){
        lcd.clear();
    }
    longBreakDelay = incLibLongBreakDelay.varValue(); 
    pomo_settings_display2();
}

void select_exit_and_save(){
    pomo_settings_display2();
    if(button_1.getState()){
        tone(buzzerPin, 1000, 100);
        if(workTime != EEPROM.read(0)){
            EEPROM.write(0, workTime);
            EEPROM.commit();
        }
        if(shortBreakTime != EEPROM.read(1)){
            EEPROM.write(1, shortBreakTime);
            EEPROM.commit();
        }
        if(longBreakTime != EEPROM.read(2)){
            EEPROM.write(2, longBreakTime);
            EEPROM.commit(); 
        }
        if(longBreakDelay != EEPROM.read(3)){
            EEPROM.write(3, longBreakDelay);
            EEPROM.commit(); 
        }   
        
        settingsPomo = false;
        menuPosition = 0; 
        lcd.clear();
        delay(250);
    }
}


void work_or_break(){
    // alterna entre dos estados: work/break, si está en break alterna entre short o long.
    // alterna entre short o long en base a si una variable es igual al longBreakTime seleccionado
    // en las settings.
    if(sessionFinish == true){ //si el tiempo termino y fue el de work resto sesiones
        sessionFinish = false; 
        countingSessions--;
        lcd.clear(); 
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
        statePomodoroLCD = 0; // WORK
        minutes = workTime; 
        pomodoroCountFinish = false;
    }
    if(statePomodoro == false && pomodoroCountFinish == true){ //estamos en break, se decide si es short o long
        pomodoroCountFinish = false;
        breaksForLongBreak++;
        if(breaksForLongBreak == longBreakDelay){
            statePomodoroLCD = 1; // LONG BREAK
            minutes = longBreakTime;
            breaksForLongBreak = 0;        
        }
        else{
            statePomodoroLCD = 2; // SHORT BREAK
            minutes = shortBreakTime; 
        } 
    }
}
 
void pomodoro_timer(){
    // cuenta el tiempo hacia atras con la libreria multitasking 
    pomoTimer.init(1000);
    if(pomoTimer.delay()){
        seconds--; 
    }
    if(seconds < 0){
        seconds = 59; 
        minutes--; 
    }
    // si el tiempo termina actualiza el estado de pomodoro
    if(minutes == 0 && seconds == 0){
        pomodoroCountFinish = true; 
        if(statePomodoro == false){
            sessionFinish = true; 
        }
    }
    //actualizacion al cambiar de centenas a decenas
    if(minutes == 99 && lastMinute == 100){
        lcd.clear(); 
    }
    //imprime en que estado del pomodoro nos encontramos (pomodoro, sh break o long break)
    switch (statePomodoroLCD){
        case 0:
            lcd.setCursor(3, 1);
            lcd.print("POMODORO"); 
            break; 
        case 1:
            lcd.setCursor(3, 1);
            lcd.print("SHORT BREAK");   
            break; 
        case 2: 
            lcd.setCursor(3, 1);
            lcd.print("LONG BREAK");
            break;   
    }
    // imprime el tiempo pomodoro en el lcd
    lcd.setCursor(3, 2); 
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
    lastMinute = minutes; 
}

void pause_pomodoro(){
    pausePomodoro = pausePom.getState(); 
    if(pausePomodoro == true){
        lcd.setCursor(15, 3);
        lcd.print("PAUSE"); 
    }
    
    switch (statePomodoroLCD){
        case 0:
            lcd.setCursor(3, 1);
            lcd.print("POMODORO"); 
            break; 
        case 1:
            lcd.setCursor(3, 1);
            lcd.print("SHORT BREAK");   
            break; 
        case 2: 
            lcd.setCursor(3, 1);
            lcd.print("LONG BREAK");
            break;   
    }
    
    lcd.setCursor(3, 2); 
    if(minutes < 10){
        lcd.print("0"); 
    }
    lcd.print(minutes);
    lcd.print(":");
    if(seconds < 10){
        lcd.print("0"); 
    }
    lcd.print(seconds);
}