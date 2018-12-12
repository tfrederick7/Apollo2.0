#include "Arduino.h"

#include "Apollo2.h" 

#define debug 1

Apollo2::Apollo2(){
	Serial.begin(115200);
	pinMode(_LED, OUTPUT);
}


void Apollo2::enableDebug(bool state){
	debugState = state;
}

void Apollo2::setLED(bool state){
	if(debugState){
		Serial.print("LED State ");
		Serial.println(state);
	}
	digitalWrite(_LED, state);
}