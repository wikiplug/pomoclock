#include "blinkMenu.h"
#include "multitask.h"

blinkMenu::blinkMenu(){

}
// OBTIENE LOS PARAMETROS Y LOS COPIA EN VARIABLES DE CARACTER PRIVADO
// ES DECIR, NO SON ACCESIBLES EN LA PROGRAMACIÓN DEL MAIN.
void blinkMenu::alternate(char firstWord [30], char secondWord [30], int time){
    strncpy(_firstWord, firstWord, sizeof(_firstWord)); 
    strncpy(_secondWord, secondWord, sizeof(_secondWord));  
    _time = time; 
}   

// ALTERNA ENTRE LAS DOS PALABRAS EN BASE AL TIEMPO SELECCIONADO
void blinkMenu::updateState(){
    multitaskBlinkMenu.init(_time); 
    if(multitaskBlinkMenu.delay()){
        _inc++; 
        if(_inc > 100){
            _inc = 0;
        }
    }
    _div = _inc % 2;
    if(_div != 0){
        strncpy(_word, _firstWord, sizeof(_word));   
    } 
    else{
        strncpy(_word, _secondWord, sizeof(_word));  
    }
}

// RETORNA LA PALABRA QUE NOS ENTREGA LA FUNCION updateState. 
char* blinkMenu::getWord(){
    updateState(); 
    return _word; 
}
