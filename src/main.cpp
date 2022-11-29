#include "header.h"
#include "objects.h"
#include "webpage.h"

uint8_t check[] = {
    B00000,
    B00000,
    B00001,
    B00010,
    B10100,
    B01000,
    B00000,
    B00000
};

uint8_t temp[] = {
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
 
WebSocketsServer webSocket = WebSocketsServer(81);
AsyncWebServer server(80);

IPAddress ip; // Creamos el objeto para la dirección IP.
String wifi; //se almacena los valores de WiFi.SSID().

void handleRoot(AsyncWebServerRequest *request)
{
    request->send(200, "text/html", pomoclock);
}

void hora_pagina()
{
    DateTime fecha = rtc.now();
    server.on("/tiempo", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    if (request->hasParam(PARAM_HORA)) {
      inputMessage4 = request->getParam(PARAM_HORA)->value();//OBTENEMOS VALOR HORA
      inputParam = PARAM_HORA;
    }
    if (request->hasParam(PARAM_MIN)) {
      inputMessage5 = request->getParam(PARAM_MIN)->value();//OBTENEMOS VALOR HORA
      inputParam = PARAM_MIN;
    }
    if (request->hasParam(PARAM_SET)) {
      buttonMessage3 = request->getParam(PARAM_SET)->value();//OBTENEMOS VALOR HORA
      inputParam = PARAM_SET;
    }

    request->send(200, "text/html", pomoclock);//REDIRECCIÓN A LA PÁGINA PRINCIPAL

    //-------------------------------CONVERSIÓN A VALORES EN INT------------------------------------------------
    h_time = inputMessage4.toInt();
    m_time = inputMessage5.toInt();
    set_time = buttonMessage3.toInt(); 
    EEPROM.write(19, h_time);
    EEPROM.commit();
    EEPROM.write(20, m_time);
    EEPROM.commit();
    
    rtc.adjust(DateTime(year, month, day, h_time, m_time, 00));
    });
}

void alarmas_pagina () {
    server.on("/alarma", HTTP_GET, [](AsyncWebServerRequest *request) { // SOLICITUD PARA LAS ALARMAS
        if (request->hasParam(HOUR_ALARM))
        {
            inputMessage = request->getParam(HOUR_ALARM)->value(); // OBTENEMOS VALOR HORA
            inputParam = HOUR_ALARM;
        }

        if (request->hasParam(MIN_ALARM))
        {
            inputMessage2 = request->getParam(MIN_ALARM)->value(); // OBTENEMOS VALOR MINUTO
            inputParam = MIN_ALARM;
        }

        if (request->hasParam(PARAM_BUTTON1))
        {
            buttonMessage1 = request->getParam(PARAM_BUTTON1)->value();
            inputParam = PARAM_BUTTON1;
        }
        if (request->hasParam(PARAM_BUTTON2))
        {
            buttonMessage2 = request->getParam(PARAM_BUTTON2)->value();
            inputParam = PARAM_BUTTON2;
        }
        if (request->hasParam(PARAM_ALARM))
        {
            inputMessage3 = request->getParam(PARAM_ALARM)->value();
            inputParam = PARAM_ALARM;
        }
        request->send(200, "text/html", pomoclock); ////REDIRECCIÓN A LA PÁGINA PRINCIPAL

        //-------------------------------CONVERSIÓN A VALORES EN INT------------------------------------------------
        h = inputMessage.toInt();
        m = inputMessage2.toInt();
        b1 = buttonMessage1.toInt();
        alarma = inputMessage3.toInt();
        lcd.clear(); 
    });
}

void fecha_pagina () {
  server.on ("/fecha", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (request->hasParam(PARAM_DIA)) {
      inputMessage6 = request->getParam(PARAM_DIA)->value();//OBTENEMOS VALOR HORA
      inputParam = PARAM_DIA;
    }
    if (request->hasParam(PARAM_MES)) {
      inputMessage7 = request->getParam(PARAM_MES)->value();//OBTENEMOS VALOR HORA
      inputParam = PARAM_MES;
    }
    if (request->hasParam(PARAM_ANO)) {
      inputMessage8 = request->getParam(PARAM_ANO)->value();//OBTENEMOS VALOR HORA
      inputParam = PARAM_ANO;
    }

    request->send(200, "text/html", pomoclock);//REDIRECCIÓN A LA PÁGINA PRINCIPAL

    //-------------------------------CONVERSIÓN A VALORES EN INT------------------------------------------------
    f_dia = inputMessage6.toInt(); f_mes = inputMessage7.toInt(); f_ano = inputMessage8.toInt();
    //----------------------------IMPRIMIR VALORES EN LCD---------------------------------------------------

    rtc.adjust(DateTime(f_ano, f_mes, f_dia, hourRTC, minutesRTC, secondsRTC));
  });
}

//CDIGO SEMI-INUTIL
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength)
{
  String payloadString = (const char *)payload;
  //--------------------------------------------------
  if(type == WStype_TEXT) //receive text from client
  {
    byte separator=payloadString.indexOf('=');
    String var = payloadString.substring(0,separator);
    String val = payloadString.substring(separator+1);
  
  //ESTO ES LO INUTIL
    if(var == "LEDonoff")
    {
      LEDonoff = false;
      if(val == "ON") LEDonoff = true;
    }
}
}

void setupWiFi(){
    WiFi.mode(WIFI_STA); //es un set mode, el esp está preterminado en STA+AP
    WiFiManager wm; //Creamos la instancia o al modo de configuración: "); //LCD
    wm.setConfigPortalTimeout(180); //Se establece un tiempo de espera para evitar que el ESP no se cuelgue a ser configurado

    lcd.setCursor(0, 0);
    lcd.print("Connecting pomoclock");
    lcd.setCursor(0, 1); 
    lcd.print("to a wifi network...");
    delay(3000); 
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Pomoclock network: ");
    lcd.setCursor(19, 0); 
    lcd.print((char)0x01); 
    lcd.setCursor(0, 2);
    lcd.print("Join to the network");
    lcd.setCursor(0, 3); 
    lcd.print("with your phone :)");
    
    //Si no hay datos guardados, wm levanta un AP. LCD
    if(!wm.autoConnect("POMOCLOCK")){  
        lcd.clear();   
        lcd.setCursor(1, 1);
        lcd.print("CONNECTION FAILED.");  
        lcd.setCursor(0, 3); 
        lcd.print("Restart to try again"); 
        delay(5000); 
        lcd.clear(); 
        } 
        
    else{ 
        lcd.clear(); 
        lcd.setCursor(0, 0);
        lcd.print("--CONNECTED--");
        wifi = WiFi.SSID();
        lcd.setCursor(0, 1);
        lcd.print ("network: ");
        lcd.print(wifi);
        ip = WiFi.localIP();
        lcd.setCursor(0, 2);
        lcd.print("IP: "); 
        lcd.print(ip); 
        server.on("/", handleRoot);
        hora_pagina(); // función dedicado a imprimir el valor del tiempo
        alarmas_pagina(); //función dedicado a imprimir el valor de las alarmas
        fecha_pagina();
        server.begin(); 
        webSocket.begin();
        webSocket.onEvent(webSocketEvent);
        delay(5000);
        lcd.clear();
    }
}

void loopWiFi(void *pvParameters)
{
    for (;;)
    { // permite el dual core
        webSocket.loop();
        //-----------------------------------------------
        static unsigned long l = 0;
        unsigned long t = millis();
        if ((t - l) > 1000)
        {
            if (LEDonoff == false)
                digitalWrite(LED, LOW);
            else
                digitalWrite(LED, HIGH);
            String LEDstatus = "OFF";
            if (LEDonoff == true)
                LEDstatus = "ON";
            //-----------------------------------------------
            String TEMPvalString = String(temperature);
            String HUMvalString = String(humidity);
            //-----------------------------------------------
            JSONtxt = "{\"TEMP\":\"" + TEMPvalString + "\",";
            JSONtxt += "\"HUM\":\"" + HUMvalString + "\",";
            JSONtxt += "\"LEDonoff\":\"" + LEDstatus + "\"}";
            webSocket.broadcastTXT(JSONtxt);
        }
        // vTaskDelay(10);
    }
}

void setup(){
    Serial.begin(115200);

    EEPROM.begin(EEPROM_SIZE);
    
    //pomodoro 
    workTime = EEPROM.read(0);  
    shortBreakTime = EEPROM.read(1);
    longBreakTime = EEPROM.read(2); 
    longBreakDelay = EEPROM.read(3); 
    
    hourAlarmOne = EEPROM.read(4);
    minuteAlarmOne = EEPROM.read(5);
    stateAlarmOne = EEPROM.read(6); 
    hourAlarmTwo = EEPROM.read(7);
    minuteAlarmTwo = EEPROM.read(8);
    stateAlarmTwo = EEPROM.read(9); 
    hourAlarmThree = EEPROM.read(10);
    minuteAlarmThree = EEPROM.read(11);
    stateAlarmThree = EEPROM.read(12);  
    hourAlarmFour = EEPROM.read(13); 
    minuteAlarmFour = EEPROM.read(14);
    stateAlarmFour = EEPROM.read(15);  

    f_dia = EEPROM.read(16);
    f_mes = EEPROM.read(17);
    f_ano = EEPROM.read(18); 

    h_time = EEPROM.read(19);
    m_time = EEPROM.read(20);
    
    if(! rtc.begin()) {				// si falla la inicializacion del modulo
        Serial.println("Modulo RTC no encontrado !");	// muestra mensaje de error
        while (1);					// bucle infinito que detiene ejecucion del programa
    }
    dht.begin();
    display.setBrightness(1);

    lcd.begin(20, 4);      //Iniciamos el lcd
    lcd.backlight();       //Encendemos la luz de fondo
    lcd.clear();           //Limpiamos la pantalla
    lcd.createChar(1, check);
    lcd.createChar(2, temp); 

    pinMode(pomoSwitch, INPUT); 
    pinMode(buzzerPin, OUTPUT);
    //activa todas las funciones de configuración inicial del equipo si esta en "1"!
    // firstON = EEPROM.read(4); 
    // if(firstON == true){
    //     firstON = false; 
    //     EEPROM.write(4, firstON);
    //     EEPROM.commit();
    //     //AGREGAR FUNCIONES DE INICIO (WIFI MANAGER, ETC.) TENER EN CUENTA METER TODO EN UN WHILE
    // }
    
    //pantalla de "arranque"
    lcd.setCursor(6, 1);
    lcd.print("WELCOME.");
    delay(3000);
    lcd.clear(); 

    setupWiFi(); 
    
    //inicializamos el dual core
    xTaskCreatePinnedToCore(
        loopWiFi,   /* Task function. */
        "Task2",     /* name of task. */
        10000,       /* Stack size of task */
        NULL,        /* parameter of the task */
        0,           /* priority of the task */
        &Task2,      /* Task handle to keep track of created task */
        0);          /* pin task to core 1 */
}
byte alarmsMenuState; 
void loop(){ 
    hour(); 
    alarms(); 

    if(alarmsMenuState == true){
        alarmsMenu(); 
    }
    if(pomoSwitchRead == LOW && alarmsMenuState == false){
        lcdStandard(); 
    }
    else{
        if(lcdStandardState == true){
            lcd.clear(); 
            lcdStandardState = false;
        }
    }

    pomodoro();
}

void hour(){
    DateTime fecha = rtc.now();
    hourRTC = fecha.hour();
    minutesRTC = fecha.minute(); 
    secondsRTC = fecha.second(); 

    display.showNumberDecEx(hourRTC, 0b01000000, true, 2, 0); 
    display.showNumberDec(minutesRTC, true, 2, 2); 
}

void lcdStandard(){
    if(button_2.getState() || settingsState == true){
        menuCleaner = true; 
        if(settingsState == false){
            tone(buzzerPin, 1000, 100);
            lcd.clear(); 
            
        }
        menu(); 
    }
    else{
        lcdStandardState = true;
        
        //imprimimos la temperatura y humedad de la sala
        lectureTemp.init(3000); 
        if(lectureTemp.delay()){
            temperature = dht.readTemperature();
            humidity = dht.readHumidity() - 50.00;
        }     
         
        lcd.setCursor(0, 0); 
        lcd.print(temperature); 
        lcd.print((char)0x02); 
        lcd.print("C"); 
        lcd.setCursor(0, 1);
        lcd.print(humidity); 
        lcd.print("%");  

        DateTime fecha = rtc.now();
        day = fecha.day(); 
        month = fecha.month(); 
        year = fecha.year(); 

        lcd.setCursor(10, 0);
        if(day < 10){
            lcd.print("0");  
        }
        lcd.print(day); 
        lcd.print("/");
        if(month < 10){
            lcd.print("0");
        }
        lcd.print(month);
        lcd.print("/");
        lcd.print(year);
        lcd.setCursor(0, 3);
        lcd.print("IP: "); 
        lcd.print(ip);
    }
}
 
void menu(){
    settingsState = true; 
    if(button_3.getState()){ 
        tone(buzzerPin, 1000, 100); 
        position++;  
        if(position > 2){
            position = 0; 
        }
        lcd.clear();
    }
    
    switch(position){
        case 0:
            deleteSSID(); 
            break;
        case 1:
            seeAlarms();
            break; 
        case 2:
            exit_menu();   
            break; 
    }
}

void menu_display(){
    lcd.setCursor(0, position); 
    lcd.print("-");
    lcd.setCursor(2, 0); 
    lcd.print("forget network.");
    lcd.setCursor(2, 1); 
    lcd.print("show alarms.");
    lcd.setCursor(2, 2); 
    lcd.print("exit."); 
}

void deleteSSID(){
    menu_display(); 
    if(button_1.getState()){
        tone(buzzerPin, 1000, 100); 
        WiFiManager wm; //Se crea nuevamente la instancia del wm para el reset.
        wm.resetSettings();
        lcd.clear();
        lcd.setCursor(2, 2); 
        lcd.print("NETWORK FORGETED"); 
        delay(3000);
        ESP.restart();
    }
}

void seeAlarms(){
    menu_display();
    if(button_1.getState()){
        lcd.clear(); 
        delay(200); 
        alarmsMenuState = true; 
    }
}

void exit_menu(){
    menu_display(); 
    if(button_1.getState()){
        tone(buzzerPin, 1000, 100); 
        settingsState = false; 
        lcd.clear(); 
        delay(250); 
    }
}

void alarmsMenu(){
    lcd.setCursor(0, 0); 
    lcd.print("h: "); 
    lcd.print(hourAlarmOne);
    lcd.setCursor(7, 0); 
    lcd.print("m: ");
    lcd.print(minuteAlarmOne);
    lcd.setCursor(13, 0); 
    lcd.print("s: ");
    lcd.print(stateAlarmOne); 

    lcd.setCursor(0, 1); 
    lcd.print("h: "); 
    lcd.print(hourAlarmTwo);
    lcd.setCursor(7, 1); 
    lcd.print("m: ");
    lcd.print(minuteAlarmTwo);
    lcd.setCursor(13, 1); 
    lcd.print("s: ");
    lcd.print(stateAlarmTwo);


    lcd.setCursor(0, 2); 
    lcd.print("h: "); 
    lcd.print(hourAlarmThree);
    lcd.setCursor(7, 2); 
    lcd.print("m: ");
    lcd.print(minuteAlarmThree);
    lcd.setCursor(13, 2); 
    lcd.print("s: ");
    lcd.print(stateAlarmThree);

    lcd.setCursor(0, 3); 
    lcd.print("h: "); 
    lcd.print(hourAlarmFour);
    lcd.setCursor(7, 3); 
    lcd.print("m: ");
    lcd.print(minuteAlarmFour);
    lcd.setCursor(13, 3); 
    lcd.print("s: ");
    lcd.print(stateAlarmFour);

    if(button_3.getState()){
        alarmsMenuState = false; 
        lcd.clear();
        delay(200); 
    }
}

void alarms(){
    //almaceno las alarmas en distintos "slots"
    switch (alarma)
    {
    case 1:
        hourAlarmOne = h;
        minuteAlarmOne = m; 
        stateAlarmOne = b1; 
        if(hourAlarmOne != EEPROM.read(4)){
            EEPROM.write(4, hourAlarmOne); 
            EEPROM.commit(); 
        }
        if(minuteAlarmOne != EEPROM.read(5)){
            EEPROM.write(5, minuteAlarmOne); 
            EEPROM.commit(); 
        }
        if(stateAlarmOne != EEPROM.read(6)){
            EEPROM.write(6, stateAlarmOne); 
            EEPROM.commit(); 
        }
        break;
    
    case 2:
        hourAlarmTwo = h; 
        minuteAlarmTwo = m;
        stateAlarmTwo = b1; 
        if(hourAlarmTwo != EEPROM.read(7)){
            EEPROM.write(7, hourAlarmTwo); 
            EEPROM.commit(); 
        }
        if(minuteAlarmTwo != EEPROM.read(8)){
            EEPROM.write(8, minuteAlarmTwo); 
            EEPROM.commit(); 
        }
        if(stateAlarmTwo != EEPROM.read(9)){
            EEPROM.write(9, stateAlarmTwo); 
            EEPROM.commit(); 
        }
        break;
    
    case 3:
        hourAlarmThree = h; 
        minuteAlarmThree = m; 
        stateAlarmThree = b1; 
        if(hourAlarmThree != EEPROM.read(10)){
            EEPROM.write(10, hourAlarmThree); 
            EEPROM.commit(); 
        }
        if(minuteAlarmThree != EEPROM.read(11)){
            EEPROM.write(11, minuteAlarmThree); 
            EEPROM.commit(); 
        }
        if(stateAlarmThree != EEPROM.read(12)){
            EEPROM.write(12, stateAlarmThree); 
            EEPROM.commit(); 
        }
        break; 

    case 4:
        hourAlarmFour = h;
        minuteAlarmFour = m; 
        stateAlarmFour = b1;
        if(hourAlarmFour != EEPROM.read(13)){
            EEPROM.write(13, hourAlarmFour); 
            EEPROM.commit(); 
        }
        if(minuteAlarmFour != EEPROM.read(14)){
            EEPROM.write(14, minuteAlarmFour); 
            EEPROM.commit(); 
        }
        if(stateAlarmFour != EEPROM.read(15)){
            EEPROM.write(15, stateAlarmFour); 
            EEPROM.commit(); 
        }
        break; 
    }

    alarm_one.setAlarm(hourRTC, minutesRTC, hourAlarmOne, minuteAlarmOne, stateAlarmOne); 
    alarm_one.alarmTriggered();

    alarm_two.setAlarm(hourRTC, minutesRTC, hourAlarmTwo, minuteAlarmTwo, stateAlarmTwo);
    alarm_two.alarmTriggered(); 

    alarm_three.setAlarm(hourRTC, minutesRTC, hourAlarmThree, minuteAlarmThree, stateAlarmThree);
    alarm_three.alarmTriggered();

    alarm_four.setAlarm(hourRTC, minutesRTC, hourAlarmFour, minuteAlarmFour, stateAlarmFour);
    alarm_four.alarmTriggered();
}

// EN ESTA FUNCIÓN SE CORROBORA SI SE ACTIVA LA OPCION POMODORO O NO
// A SU VEZ, EJECUTA TODAS LAS FUNCIONES QUE CORREN DENTRO DEL POMODORO
// SE SEGMENTA EL CODIGO EN BLOQUES PARA FACILITAR SU LEGIBILIDAD Y PROGRAMACION
void pomodoro(){ 
    pomoSwitchRead = digitalRead(pomoSwitch);
    if(pomoSwitchRead == HIGH){ 
        if(alarmsMenuState == true){
            lcd.clear(); 
            alarmsMenuState = false;
        } 
        if(menuCleaner == true){
            lcd.clear();
            menuCleaner = false;
        }
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
                tone(buzzerPin, 1000, 100);
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
    incLibSessions.incThisVar(sessions, 99);
    if(incLibSessions.lcdValue()){
        lcd.clear(); 
    }
    sessions = incLibSessions.varValue();
    finishTime(); 
    pomo_menu_display();
}

void select_settings(){
    finishTime();
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
    finishTime();
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
    lcd.setCursor(0, settingsPosition-2);
    lcd.print("- ");
    lcd.setCursor(2, 0);
    lcd.print("longBreak: "); 
    lcd.print(longBreakTime); 
    lcd.print("min."); 
    lcd.setCursor(2, 1);
    lcd.print("longBreakDelay: ");
    lcd.print(longBreakDelay);
    lcd.setCursor(2, 2);
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
    pomo_settings_display2(); 
}

void select_longBreakDelay(){
    incLibLongBreakDelay.incThisVar(longBreakDelay, 99);
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
            breaksForLongBreak = 0; 
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
            statePomodoroLCD = 2; // LONG BREAK
            minutes = longBreakTime;
            breaksForLongBreak = 0;        
        }
        else{
            statePomodoroLCD = 1; // SHORT BREAK
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
        tone(buzzerPin, 1000, 3000);
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