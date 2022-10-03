TwiLiquidCrystal lcd(0x27);

button button_1(14, 150); 
button button_2(27, 150);
button button_3(26, 150); 

//blink selection
blinkMenu blinkMenu1;
blinkMenu blinkMenu2;
blinkMenu blinkMenu3;

//incLib 1
incLibOne incLibSessions;
incLibOne incLibLongBreakDelay;

// incLib 5
incLib incLibWorkTime;
incLib incLibShortBreak;
incLib incLibLongBreak;

//objetos work_or_break()
twoStates workOrBreak; 
twoStates shortOrLong; 

//objetos timer()
multitask pomoTimer; 
