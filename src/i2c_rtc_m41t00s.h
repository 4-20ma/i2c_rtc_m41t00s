/**
@file
Arduino library for ST M41T00S real-time clock.
*/
/*

  i2c_rtc_m41t00s.h - Arduino library for ST M41T00S real-time clock

  Library:: i2c_rtc_m41t00s
  Author:: Doc Walker <4-20ma@wvfans.net>

  Copyright:: 2009-2016 Doc Walker

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/


#ifndef i2c_rtc_m41t00s_h
#define i2c_rtc_m41t00s_h


/* _____STANDARD INCLUDES____________________________________________________ */
// include types & constants of Wiring core API
#include "Arduino.h"

// include twi/i2c library
#include <Wire.h>


/* _____UTILITY MACROS_______________________________________________________ */
/**
@def BOUND(Value,Min,Max).
Macro to check if a value is within bounds (Min <= Value <= Max ?)
*/
#define BOUND(Value,Min,Max)    (((Value)>=(Min))&&((Value)<=(Max)))


/* _____CLASS DEFINITIONS____________________________________________________ */
/**
Arduino library for ST M41T00S real-time clock.

The M41T00S Serial Access TIMEKEEPER SRAM is a low power serial RTC 
with a builtin 32.768 kHz oscillator (external crystal controlled). 
Eight bytes of the SRAM are used for the clock/calendar function and are 
configured in binary coded decimal (BCD) format. Addresses and data are 
transferred serially via a two line, bidirectional I2C interface. The 
built-in address register is incremented automatically after each WRITE 
or READ data byte.

The M41T00S has a built-in power sense circuit which detects power 
failures and automatically switches to the battery supply when a power 
failure occurs. The energy needed to sustain the clock operations can be 
supplied by a small lithium button supply when a power failure occurs. 
The eight clock address locations contain the century, year, month, 
date, day, hour, minute, and second in 24-hour BCD format. Corrections 
for 28, 29 (leap year - valid until year 2100), 30 and 31 day months are 
made automatically.

@author Doc Walker
@date 8 Feb 2010
@note I2C: SDA --> pin 4; SCL --> pin 5
*/
class i2c_rtc_m41t00s
{
  public:
    /**
    Time structure for storing current time.
    */
    struct time_t
    {
      uint8_t sec;   ///< second (0.59)
      uint8_t min;   ///< minute (0..59)
      uint8_t hour;  ///< hour (0..23)
      uint8_t dow;   ///< day of week (1..7)
      uint8_t day;   ///< day (1..31)
      uint8_t month; ///< month (1..12)
      uint8_t year;  ///< year (00..99)
      uint8_t cal;   ///< calibration byte (0x00..0xFF)
    } time;

    /**
    I2C/TWI success.

    Transaction was successful.
    */
    static const uint8_t ku8TWISuccess                   = 0;

    /**
    I2C/TWI device not present.

    Address sent, NACK received.
    */
    static const uint8_t ku8TWIDeviceNACK                = 2;

    /**
    I2C/TWI data not received.

    Data sent, NACK received.
    */
    static const uint8_t ku8TWIDataNACK                  = 3;

    /**
    I2C/TWI other error.
    */
    static const uint8_t ku8TWIError                     = 4;

    i2c_rtc_m41t00s();

    void    begin();
    uint8_t get();
    uint8_t set(time_t *);
    uint8_t isStopped();
    uint8_t isRunning();
    uint8_t isFailed();
    uint8_t setCalibration(uint8_t);
    uint8_t start();
    uint8_t stop();
    uint8_t clearFault();

  private:
    /**
    I2C base address for the M41T00S real-time clock.
    */
    static const uint8_t _ku8BaseAddress                 = 0x68;

    /**
    Seconds register.
    */
    static const uint8_t _ku8Sec                         = 0x00;

    /**
    Stop bit within seconds register.
    */
    static const uint8_t _ku8Bit_ST                      = 7;

    /**
    Minutes register.
    */
    static const uint8_t _ku8Min                         = 0x01;

    /**
    Oscillator fail bit within minutes register.
    */
    static const uint8_t _ku8Bit_OF                      = 7;

    /**
    Hour register.
    */
    static const uint8_t _ku8Hour                        = 0x02;

    /**
    Century enable bit within hour register.
    */
    static const uint8_t _ku8Bit_CEB                     = 7;

    /**
    Century bit within hour register.
    */
    static const uint8_t _ku8Bit_CB                      = 6;

    /**
    Day of week register.
    */
    static const uint8_t _ku8DOW                         = 0x03;

    /**
    Day of month register.
    */
    static const uint8_t _ku8Day                         = 0x04;

    /**
    Month register.
    */
    static const uint8_t _ku8Month                       = 0x05;

    /**
    Year register.
    */
    static const uint8_t _ku8Year                        = 0x06;

    /**
    Calibration register.
    */
    static const uint8_t _ku8Calibration                 = 0x07;

    /**
    Output level bit within calibration register.
    */
    static const uint8_t _ku8Bit_OUT                     = 7;

    /**
    Frequency test bit within calibration register.
    */
    static const uint8_t _ku8Bit_FT                      = 6;

    /**
    Sign bit bit within calibration register.
    */
    static const uint8_t _ku8Bit_S                       = 5;

    /**
    Calibration mask.
    */
    static const uint8_t _ku8Mask                        = 0x1F;

    /**
    Number of bytes of clock data.
    */
    static const uint8_t _ku8Length                      = 8;

    uint8_t bcd2dec(uint8_t);
    uint8_t dec2bcd(uint8_t);
    uint8_t read(uint8_t);
    uint8_t write(uint8_t);

    /**
    Clock data in BCD format.
    */
    byte    _rtc_bcd[_ku8Length];
};
#endif

/**
@example examples/M41T00S_example/M41T00S_example.ino
*/
