//


#include <Arduino.h>
#include "DAC80501.h"

DAC80501* testDAC= new DAC80501;

void setup(){
    Serial.begin(115200);
    Serial.println("INIT:--");
    Serial.println(testDAC->begin());
    Serial.println(testDAC->init());
    Serial.println("set DAC to 0V");
    Serial.println(testDAC->setVoltage((uint16_t)0x0000));

    delay(10000);
}

void loop(){
    // for (uint16_t i = 0; i < 0xF000; i=i+256)
    // {
    //     testDAC->setVoltage(i);
    //     delay(100);
    // }

    for (float v = 0.090; v < 1.1 ; v=v+0.01)
    {
        testDAC->setVoltage(v);
        delay(5000);
    }
    
    // delay(5000);
}