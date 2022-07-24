#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>		// incluye libreria para interfaz I2C
#include <RTClib.h>		// incluye libreria para el manejo del modulo RTC
#include <TwiLiquidCrystal.h>


void pomodoro();
void pomo_menu();
void select_work();    
void select_shortBreak();
void select_longBreak();
void select_sessionsLongBreak();
void select_sessions();
void select_start();