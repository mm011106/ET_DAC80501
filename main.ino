//


#include <Arduino.h>
#include "DAC80501.h"

DAC80501* testDAC= new DAC80501;

float out_v[23]={
    0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
    10.0, 15.0, 20.0, 25.0, 
    30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0 };

const size_t n_out_v=sizeof(out_v)/sizeof(out_v[0]);

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

    for (uint8_t i; i < n_out_v ; i++)
    {
        testDAC->setVoltage((float)(out_v[i]/100.0+0.1-0.0021));
        Serial.println(out_v[i]);
        delay(5000);
    }
    
    // delay(5000);
}