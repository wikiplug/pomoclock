TwiLiquidCrystal lcd(0x27);
RTC_DS1307 rtc; 
TM1637Display display(CLK, DIO);

button button_1(25, 150); 
button button_2(26, 150);
button button_3(27, 150); 

//blink selection
blinkMenu blinkMenu1;
blinkMenu blinkMenu2;
blinkMenu blinkMenu3;

//incLib 1
incLibOne incLibSessions(18);
incLibOne incLibLongBreakDelay(18);

// incLib 5
incLib incLibWorkTime(18);
incLib incLibShortBreak(18);
incLib incLibLongBreak(18);

//objetos work_or_break()
twoStates workOrBreak; 
twoStates shortOrLong; 
twoStates pausePom; 

//objetos timer()
multitask pomoTimer; 
