/***********************************************************************
MODULE:    POWER MANAGEMENT
VERSION:   1.01
CONTAINS:  Routines for controlling the power features on the Philips
           P89LPC936
COPYRIGHT: Embedded Systems Academy, Inc. - www.esacademy.com
LICENSE:   May be freely used in commercial and non-commercial code
           without royalties provided this copyright notice remains
           in this file and unaltered
WARNING:   IF THIS FILE IS REGENERATED BY CODE ARCHITECT ANY CHANGES
           MADE WILL BE LOST. WHERE POSSIBLE USE ONLY CODE ARCHITECT
           TO CHANGE THE CONTENTS OF THIS FILE
GENERATED: On "Apr 04 2011" at "16:36:32" by Code Architect 2.06
***********************************************************************/

#ifndef _POWERH_
#define _POWERH_

// brownout detection types
#define POWER_BORESET     0
#define POWER_BOINTERRUPT 1

// power reduction modes
#define POWER_NORMAL
#define POWER_IDLE           0
#define POWER_POWERDOWN      1
#define POWER_TOTALPOWERDOWN 2

// peripherals that can be powered up or down
// note: do not change the values of the defines!
#define POWER_CCU         0x01
#define POWER_UART        0x02
#define POWER_SPI         0x04
#define POWER_I2C         0x08
#define POWER_ADC         0x10
#define POWER_COMPARATORS 0x20
#define POWER_EEPROM      0x40
#define POWER_RTC         0x80

/***********************************************************************
DESC:    Enables brownout detection to generate either a reset or
         interrupt
RETURNS: Nothing
CAUTION: If interrupts are being used then EA must be set to 1
         after calling this function
	 UCFG1.5 (BOE) must be set to 1
************************************************************************/
void power_brownoutenable
  (
  unsigned char type    // POWER_BORESET or POWER_BOINTERRUPT
  );

/***********************************************************************
DESC:    Disabled brownout detection
RETURNS: Nothing
CAUTION: UCFG1.5 (BOE) is ignored
************************************************************************/
void power_brownoutdisable
  (
  void
  );

/***********************************************************************
DESC:    Indicates if the last reset was caused by a brownout reset
         Only use this if brownout is enabled with POWER_BORESET
RETURNS: 0 if the reset was not a brownout reset
         1 if the reset was a brownout reset
************************************************************************/
unsigned char power_isbrownoutreset
  (
  void
  );

/***********************************************************************
DESC:    Indicates if the last reset was caused by power on
RETURNS: 0 if the reset was not power on
         1 if the reset was power on
************************************************************************/
unsigned char power_ispoweronreset
  (
  void
  );

/***********************************************************************
DESC:    Selects a power reduction mode
RETURNS: nothing
CAUTION: Some modes will cause various peripherals to either work
         differently or stop working
************************************************************************/
void power_mode
  (
  unsigned char mode  // power reduction mode POWER_NORMAL, POWER_IDLE
                      // POWER_POWERDOWN or POWER_TOTALPOWERDOWN
  );

/***********************************************************************
DESC:    Powers down one or more peripherals
RETURNS: nothing
************************************************************************/
void power_powerdown
  (
  unsigned char peripherals   // ORd list of peripherals to power down
                              // e.g. POWER_RTC | POWER_SPI
  );

/***********************************************************************
DESC:    Powers up one or more peripherals that were previously powered
         down
RETURNS: nothing
************************************************************************/
void power_powerup
  (
  unsigned char peripherals   // ORd list of peripherals to power up
                              // e.g. POWER_RTC | POWER_SPI
  );

#endif // _POWERH_
