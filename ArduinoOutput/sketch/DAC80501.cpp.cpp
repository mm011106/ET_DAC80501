#include <Arduino.h>
#line 8 "/Users/masakazumiyamoto/Box/Arduino/Scripts/ET_DAC80501/main.ino"
void setup();
#line 17 "/Users/masakazumiyamoto/Box/Arduino/Scripts/ET_DAC80501/main.ino"
void loop();
#line 0 "/Users/masakazumiyamoto/Box/Arduino/Scripts/ET_DAC80501/main.ino"
#line 1 "/Users/masakazumiyamoto/Box/Arduino/Scripts/ET_DAC80501/DAC80501.cpp"
/**************************************************************************/
/*!
    @file     DAC80501.cpp
    @author   Masa

        I2C Driver for DAC80501/TI

        @section  HISTORY

*/
/**************************************************************************/

#include "DAC80501.h"




/**************************************************************************/
/*!
    @brief  Instantiates a new DAC80501 class
*/
/**************************************************************************/
DAC80501::DAC80501() {}

/**************************************************************************/
/*!
    @brief  Setups the hardware and checks the DAC was found
    @param i2c_address The I2C address of the DAC, defaults to 0x90
    @param wire The I2C TwoWire object to use, defaults to &Wire
    @returns True if DAC was found on the I2C address.
*/
/**************************************************************************/
bool DAC80501::begin(uint8_t i2c_address, TwoWire *wire) {
  if (i2c_dev) {
    delete i2c_dev;
  }

  i2c_dev = new Adafruit_I2CDevice(i2c_address, wire);

  if (!i2c_dev->begin()) {
    return false;
  }

  return true;
}
/**************************************************************************/
/*!
    @brief  Sets the output voltage to a fraction of source vref.  (Value
            can be 0..4095)

    @param[in]  output
                The 12-bit value representing the relationship between
                the DAC's input voltage and its output voltage.
    @param[in]  writeEEPROM
                If this value is true, 'output' will also be written
                to the DAC80501's internal non-volatile memory, meaning
                that the DAC will retain the current voltage output
                after power-down or reset.
    @param i2c_frequency What we should set the I2C clock to when writing
    to the DAC, defaults to 400 KHz
    @returns True if able to write the value over I2C
*/
/**************************************************************************/
bool DAC80501::init(void) {

  uint8_t packet[3];

  packet[0] = DAC80501_CMD::CMD_SYNC;
  packet[1] = 0x00;
  packet[2] = DAC80501_DAC_SYNC_EN::UPDATE_ASYNC; //the output is update immedietely

  if (!i2c_dev->write(packet, 3)) {
    return false;
  }

  packet[0] = DAC80501_CMD::CMD_CONFIG;
  packet[1] = DAC80501_REF_PWDWN::REFPWDWN_DISABLE; //use internal VREF 2.5V
  packet[2] = DAC80501_DAC_PWDWN::DACPWDN_DISABLE; //activate DAC

  if (!i2c_dev->write(packet, 3)) {
    return false;
  }

  packet[0] = DAC80501_CMD::CMD_GAIN;
  packet[1] = DAC80501_REF_DIV::REFDIV_1;     //REF divider = 1 
  packet[2] = DAC80501_BUFF_GAIN::BUFGAIN_1;  // DAC Buffer gain =1 ,thus VFS=2.5V

  if (!i2c_dev->write(packet, 3)) {
    return false;
  }


  return true;
}

/**************************************************************************/
/*!
    @brief  Sets the output voltage to a fraction of source vref.  (Value
            can be 0..4095)

    @param[in]  output
                The 12-bit value representing the relationship between
                the DAC's input voltage and its output voltage.
    @param[in]  writeEEPROM
                If this value is true, 'output' will also be written
                to the DAC80501's internal non-volatile memory, meaning
                that the DAC will retain the current voltage output
                after power-down or reset.
    @param i2c_frequency What we should set the I2C clock to when writing
    to the DAC, defaults to 400 KHz
    @returns True if able to write the value over I2C
*/
/**************************************************************************/
bool DAC80501::setVoltage(uint16_t output, bool writeEEPROM,
                                  uint32_t i2c_frequency) {
  i2c_dev->setSpeed(i2c_frequency); // Set I2C frequency to desired speed

  uint8_t packet[3];


  packet[0] = DAC80501_CMD::CMD_DAC;
  packet[1] = output / 16;        // Upper data bits (D15.....D8)
  packet[2] = (output % 16);      // Lower data bits (D7......D0)

  if (!i2c_dev->write(packet, 3)) {
    return false;
  }

  i2c_dev->setSpeed(100000); // reset to arduino default
  return true;
}

#line 1 "/Users/masakazumiyamoto/Box/Arduino/Scripts/ET_DAC80501/main.ino"
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
