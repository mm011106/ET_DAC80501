//


#include <Arduino.h>
#include "DAC80501.h"


void setup(){
    DAC80501* testDAC= new DAC80501;
    Serial.begin(115200);
    Serial.println("INIT:--");
    Serial.println(testDAC->begin());
    Serial.println(testDAC->init());

}

void loop(){

}