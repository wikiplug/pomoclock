#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>		
#include <TwiLiquidCrystal.h>
#include <RTClib.h>		
#include <EEPROM.h>

//LIBRERIAS LOCALES
#include "button.h"
#include "multitask.h"
#include "blinkMenu.h"
#include "incLib.h"
#include "twoStates.h"
#include "incLibOne.h"

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


#define pomoSwitch 25

#define EEPROM_SIZE 512
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