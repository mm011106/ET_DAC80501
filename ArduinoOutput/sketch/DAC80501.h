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

#define DAC80501_I2CADDR_DEFAULT (0x48) ///< Default i2c address
// A0 pin = GND (0x48 = Default)
// A0 pin = VDD (0x49)
// A0 pin = SDA (0x50)
// A0 pin = SCL (0x51)
#define DAC80501_CMD_WRITEDAC (0x40)    ///< Writes data to the DAC
#define DAC80501_CMD_WRITEDACEEPROM                                             \
  (0x60) ///< Writes data to the DAC and the EEPROM (persisting the assigned
         ///< value after reset)

enum DAC80501_CMD{
  CMD_NOOP,     //0[W]
  CMD_DEVID,    //1[R] device identification : read resolution & Reset Setting
  CMD_SYNC,     //2[RW] synchronization : DAC output sync setting
  CMD_CONFIG,   //3[RW] configuration :
  CMD_GAIN,     //4[RW] Gain
  CMD_TRIGGER,  //5[W] Trigger
  CMD_NA6,      //6 :not appicable.
  CMD_STATUS,   //7[R] Status
  CMD_DAC       //8[RW] DAC
};

// for DEVID command
enum DAC80501_RESOLUTION{
  RESOLUTION_16BIT,  //0x0
  RESOLUTION_14BIT,  //0x1
  RESOLUTION_12BIT   //0x2
};

enum DAC80501_RSTSEL{
  ZERO,   // 0 : set to Zero at RESET
  MID     // 1 : set to midscale at RESET
};

// for SYNC command
enum DAC80501_DAC_SYNC_EN{
  UPDATE_ASYNC,  // 0 : the output is updated immediately (DEFAULT)
  UPDATE_SYNC    // 1 : the output is updated in respond to LDAC signal
};

// for CONFIG command
enum DAC80501_REF_PWDWN{
  REFPWDWN_DISABLE,  // 0 : Activate internal VREF (2.5V)
  REFPWDWN_ENABLE    // 1 : PowerDown(de-activate) internal VREF (2.5V)
};

enum DAC80501_DAC_PWDWN{
  DACPWDN_DISABLE,  // 0 : Activate DAC 
  DACPWDN_ENABLE    // 1 : PowerDown(de-activate) the DAC 
};

// for GAIN command
enum DAC80501_REF_DIV{
  REFDIV_1,     // 0 : VREF Divider set to x1 (THROUGH)
  REFDIV_2    // 1 : VREF Divider set to 1/2 (Half of Vref is applied to the DAC)
};

enum DAC80501_BUFF_GAIN{
  BUFGAIN_1,     // 0 : the gain of DAC BufferAmp is set to x1
  BUFGAIN_2      // 1 : the gain of DAC BufferAmp is set to x2
};

// for TRIGGER command
enum DAC80501_LDAC{
  LDAC_NA,   // 0 : !NOT APPLICABLE! 
  LDAC_SET   // 1 : Activate LDAC
};

constexpr uint16_t DAC80501_SOFT_RES=0x6; // Soft Reset code


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
  
  bool init(void);

  bool setVoltage(uint16_t output, bool writeEEPROM,
                  uint32_t dac_frequency = 400000);

private:
  Adafruit_I2CDevice *i2c_dev = NULL;
};

#endif
