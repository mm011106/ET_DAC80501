/**************************************************************************/
/*!
    @file     DAC80501.h
*/
/**************************************************************************/

#ifndef _DAC80501_H_
#define _DAC80501_H_

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Wire.h>

#define DAC80501_I2CADDR_DEFAULT (0x62) ///< Default i2c address
#define DAC80501_CMD_WRITEDAC (0x40)    ///< Writes data to the DAC
#define DAC80501_CMD_WRITEDACEEPROM                                             \
  (0x60) ///< Writes data to the DAC and the EEPROM (persisting the assigned
         ///< value after reset)

/**************************************************************************/
/*!
    @brief  Class for communicating with an MCP4725 DAC
*/
/**************************************************************************/
class DAC80501 {
public:
  DAC80501();
  bool begin(uint8_t i2c_address = DAC80501_I2CADDR_DEFAULT,
             TwoWire *wire = &Wire);
  bool setVoltage(uint16_t output, bool writeEEPROM,
                  uint32_t dac_frequency = 400000);

private:
  Adafruit_I2CDevice *i2c_dev = NULL;
};

#endif
