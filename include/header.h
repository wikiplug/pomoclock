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

void pomodoro();
void pomo_menu();
void select_work();    
void select_shortBreak();
void select_longBreak();
void select_sessionsLongBreak();
void select_sessions();
void select_start();

int incrementador(); 