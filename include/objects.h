TwiLiquidCrystal lcd(0x27);

button button_1(13, 150); 
button button_2(14, 150);
button button_3(15, 150); 

//blink selection
blinkMenu blinkMenu1;

//incLib 1
incLibOne incLibSessions; 


// incLib 5
incLib incLibWorkTime;
incLib incLibShortBreak; 

//objetos work_or_break()
twoStates workOrBreak; 
twoStates shortOrLong; 

//objetos timer()
multitask pomoTimer; 
