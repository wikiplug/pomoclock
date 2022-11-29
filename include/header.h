#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>		
#include <TwiLiquidCrystal.h>
#include <RTClib.h>		
#include <EEPROM.h>
#include <TM1637Display.h>

//LIBRERIAS WIFI
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <WiFiManager.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//LIBRERIAS LOCALES
#include "button.h"
#include "multitask.h"
#include "blinkMenu.h"
#include "incLib.h"
#include "twoStates.h"
#include "incLibOne.h"
#include "alarmsLib.h"

void hour(); 
void alarms();
void lcdStandard();

void menu(); 
void deleteSSID(); 
void seeAlarms(); 
void exit_menu(); 

void alarmsMenu(); 

void pomodoro();
void pomo_menu();
void pomo_settings(); 
void pomo_menu_display();

void select_pomodoro();    
void select_shortBreak();
void select_longBreak();
void select_longBreakDelay();
void select_exit_and_save();

void select_sessions();
void select_settings(); 
void select_start();
void finishTime();

void work_or_break(); 
void pomodoro_timer();
void pause_pomodoro(); 

//DUAL CORE
TaskHandle_t Task2;

//VARIABLES ALARMAS
const char* HOUR_ALARM = "a_hour";
const char* MIN_ALARM = "a_min";
const char* PARAM_BUTTON1 = "state";
const char* PARAM_BUTTON2 = "state";
const char* PARAM_ALARM = "alarm";
String inputMessage;//alarma hora
String inputMessage2;//alarma minuto
String inputMessage3;//alarma
String buttonMessage1;//set
String buttonMessage2;//reset
int h = 0; //se almacenan datos de las horas.
int m = 0; //se almacenan datos de los minutos.
int b1 = 0;
int alarma = 0;

String inputParam; //variable común

//VARIABLES HORA
const char* PARAM_HORA = "t_hour";
const char* PARAM_MIN = "t_min";
const char* PARAM_SET = "set-time1";
String inputMessage4;//hora
String inputMessage5;//minuto
String buttonMessage3;//set
int h_time = 0;
int m_time = 0;
int set_time = 0;
int hourRTC; 
int minutesRTC; 
int secondsRTC; 

// VARIABLES FECHA
const char* PARAM_DIA = "dia";
const char* PARAM_MES = "mes";
const char* PARAM_ANO = "año";
String inputMessage6;//DIA
String inputMessage7;//MES
String inputMessage8;//AÑO
int f_dia = 0;
int f_mes = 0;
int f_ano = 0;
int day;
int month; 
int year; 

//variables sensor dht11 (humedad y temperatura)
String JSONtxt; //se almacenan los valores de temperatura y humedad.
DHT dht(18, DHT11); //Definimos el pin del DHT11
//variables de codigo DHT11 INUTILES
#define LED 2
boolean LEDonoff=false;
//lecturas DHT11
float temperature; 
float humidity;


//ASIGNACIÓN PINES
//7SEGM.
#define CLK 16				
#define DIO 17		
//BUZZER Y SWITCH
#define buzzerPin 32
#define pomoSwitch 33

//EEPROM
#define EEPROM_SIZE 512



// variables lcd standard
byte lcdStandardState;
byte settingsState;
//menu
byte position;
byte menuCleaner; 
//alarmas 
byte hourAlarmOne; 
byte minuteAlarmOne; 
byte hourAlarmTwo;
byte minuteAlarmTwo;
byte hourAlarmThree;
byte minuteAlarmThree;
byte hourAlarmFour; 
byte minuteAlarmFour; 
byte alarmOFF;  
byte stateAlarmOne; 
byte stateAlarmTwo; 
byte stateAlarmThree; 
byte stateAlarmFour; 

//pomodoro
bool pomoSwitchRead;
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
byte statePomodoroLCD; 
//contadores 
byte countingSessions; 
byte workTime; byte shortBreakTime; byte longBreakTime; byte longBreakDelay; 
byte minutes;   // carga el tiempo de workTime o shortBreakTime o longBreakTime (depende de statePomodoro)
byte lastMinute; 
int seconds;
byte breaksForLongBreak; 
// variables settings
byte settingsPosition; 
// VARIABLES PAUSA
byte pausePomodoro;
// variables time finish 
int horaFinal; 
int minutosFinal;