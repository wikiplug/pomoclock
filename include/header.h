#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>		
#include <TwiLiquidCrystal.h>
#include <RTClib.h>		


//LIBRERIAS LOCALES
#include "button.h"
#include "multitask.h"
#include "blinkMenu.h"
#include "incLib.h"
#include "twoStates.h"
#include "incLibOne.h"

void pomodoro();
void pomo_menu();
void select_work();    
void select_shortBreak();
void select_longBreak();
void select_sessionsLongBreak();
void select_sessions();
void select_start();
void select_settings(); 

void work_or_break(); 
void pomodoro_timer();