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
GENERATED: On "Sep 30 2010" at "21:24:02" by Code Architect 2.06
***********************************************************************/

// SFR description needs to be included
#include <reg936.h>
#include "power.h"

/***********************************************************************
DESC:    Enables brownout detection to generate either a reset or
         interrupt
RETURNS: Nothing
CAUTION: If interrupts are being used then EA must be set to 1
         after calling this function
	 UCFG1.5 (BOE) must be set to 1
	 Turns off any power reduction mode currently in effect
************************************************************************/
void power_brownoutenable
  (
  unsigned char type    // POWER_BORESET or POWER_BOINTERRUPT
  )
{
  if (type == POWER_BORESET)
  {
    // no power reduction, enable brownout, disable interrupt
    PCON &= 0xCC;
    // enable brownout detect
    EBO = 1;
  }
  else if (type == POWER_BOINTERRUPT)
  {
    // no power reduction, enable brownout, enable interrupt
    PCON &= 0xCC;
    PCON |= 0x10;

    // set isr priority to 0
    IP0 &= 0xDF;
    IP0H &= 0xDF;

    // enable brownout detect
    EBO = 1;
  }
} // power_brownoutenable

/***********************************************************************
DESC:    Disables brownout detection
RETURNS: Nothing
CAUTION: UCFG1.5 (BOE) is ignored
************************************************************************/
void power_brownoutdisable
  (
  void
  )
{
  // disable brownout
  PCON |= 0x20;
} // power_brownoutdisable

/***********************************************************************
DESC:    Indicates if the last reset was caused by a brownout reset
         Only use this if brownout is enabled with POWER_BORESET
RETURNS: 0 if the reset was not a brownout reset
         1 if the reset was a brownout reset
************************************************************************/
unsigned char power_isbrownoutreset
  (
  void
  )
{
  unsigned char bof;

  // get bof
  bof = (RSTSRC >> 5) & 0x01;

  // clear bof
  RSTSRC &= ~0x20;

  // return bof
  return bof;
} // power_isbrownoutreset

/***********************************************************************
DESC:    Brownout Interrupt
RETURNS: Nothing
CAUTION: uart_init must be called first
         EA must be set to 1
************************************************************************/
void power_brownoutisr
  (
  void
  ) interrupt 5 using 0
{
  // clear bof
  RSTSRC &= ~0x20;
} // power_brownoutisr

/***********************************************************************
DESC:    Indicates if the last reset was caused by power on
RETURNS: 0 if the reset was not power on
         1 if the reset was power on
************************************************************************/
unsigned char power_ispoweronreset
  (
  void
  )
{
  unsigned char pof;

  // get pof
  pof = (RSTSRC >> 4) & 0x01;

  // clear pof
  RSTSRC &= ~0x10;

  // return pof
  return pof;
} // power_ispoweronreset

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
  )
{
  // disable power reduction
  PCON &= 0xFC;

  if (mode == POWER_IDLE)
    PCON |= 0x01;
  else if (mode == POWER_POWERDOWN)
    PCON |= 0x02;
  else if (mode == POWER_TOTALPOWERDOWN)
    PCON |= 0x03;
} // power_mode

/***********************************************************************
DESC:    Powers down one or more peripherals
RETURNS: nothing
************************************************************************/
void power_powerdown
  (
  unsigned char peripherals   // ORd list of peripherals to power down
                              // e.g. POWER_RTC | POWER_SPI
  )
{
  // power down peripherals
  PCONA |= peripherals;
} // power_powerdown

/***********************************************************************
DESC:    Powers up one or more peripherals that were previously powered
         down
RETURNS: nothing
************************************************************************/
void power_powerup
  (
  unsigned char peripherals   // ORd list of peripherals to power up
                              // e.g. POWER_RTC | POWER_SPI
  )
{
  // power up peripherals
  PCONA &= ~peripherals;
} // power_powerup


