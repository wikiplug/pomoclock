#include "blinkMenu.h"
#include "multitask.h"

blinkMenu::blinkMenu(){

}

void blinkMenu::alternate(char firstWord [30], char secondWord [30], int time){
    strncpy(_firstWord, firstWord, sizeof(_firstWord)); 
    strncpy(_secondWord, secondWord, sizeof(_secondWord));  
    _time = time; 
}   

void blinkMenu::updateState(){
    multitaskBlinkMenu.init(_time); 
    if(multitaskBlinkMenu.delay()){
        _inc++; 
        if(_inc > 254){
            _inc = 0;
        }
    }
    _div = _inc % 2;
    if(_div == 0){
        strncpy(_word, _firstWord, sizeof(_word));   
    } 
    else{
        strncpy(_word, _secondWord, sizeof(_word));  
    }
}

char* blinkMenu::getWord(){
    updateState(); 
    return _word; 
}
