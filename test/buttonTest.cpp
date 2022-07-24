#include "header.h"
#include "button.h"
#include "multitask.h"

TwiLiquidCrystal lcd(0x27);

#define pomoSwitch 16
bool pomoSwitchRead;
bool startPomo = LOW;
bool selectButton;
bool selectButtonRead;
byte menuPosition;
int workTime; 
int breakTime;

button button_1(13, 50);
button button_2(14, 50);
button button_1Long(13, 50); 
multitask multitaskMenuPosition(1000);


int num;
void setup(){
    Serial.begin(115200); 
}

void loop(){
    if(button_1.getState()){
        num++;
        Serial.println(num); 
    }
}