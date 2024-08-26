### Setting up the programmer
I uses a small "ProMini" Arduino, cause thats what I had lying around, but any Arduino should do...  I've tested on an Uno and weirdo littlebits Arduino.  Arduino's documentation is great, so I'm not going to go into detail about the environment or the C language.  The supplied `arduino\exitrip_flash_programmer\exitrip_flash_programmer.ino` should open right up in the Arduion IDE and you should only need to make a few simple edits to the header file "arduino\exitrip_flash_programmer\progdef.h" to get it working with any board. 

The top of `progdef.h` starts with this code:
```
//***************************************************************************
//* What board are we programming with?
//***************************************************************************
#define PRO_MINI
//#define UNO
//#define LITTLEBITS  //TODO test
```
but that define just controls the pinout defined below it:
```
//***************************************************************************
//* Pin Definitions, ported to Arduino pin numbers on boards
//***************************************************************************
#if  defined(PRO_MINI)
#define PDA     5           // define PDA pin
#define PCL     4           // define PCL pin
#define RESET   6           // define RESET control pin
#define VDD     3           // define VDD control pin

#elif defined(UNO)          
#define PDA     10					// define PDA pin
#define PCL     11 					// define PCL pin
#define RESET   9  				// define RESET control pin
#define VDD     12					// define VDD control pin

#elif defined(LITTLEBITS)   // needs testing TODO
#define PDA     10          // define PDA pin
#define PCL     11          // define PCL pin
#define RESET   9           // needs to be broken out from bottom output
                            // for more mA... should test with ICSP outs
#define VDD     13          // define VDD control pin
#define LED_BUILTIN 1       //use the output 1 pin
#else
#error "Define board used as programmer!!!!"
#endif
```
The only trick is to make sure that the programming cable correctly maps 5 pins from the iTrip (LPC936 programming port) to the Arduino as defined above.  
- GND to GND
- VDD to iTrip supply (e.g. Ardunio Uno pin 12 to J4 pin 4)
- PDA to PDA (data)
- PCL to PCL (clock)
- RESET to nRST
![Programming Port Pinout](/arduino/exitrip_flash_programmer/progPortPinout.png "Programming Port Pinout")

If I was gonna use an "UNO" instead of a "PRO MINI", I'd just uncomment the line `#define UNO`, comment the line `//#define PRO_MINI`, and plug the wires of the custom programming cable into the UNO's pins 9 - 12 (plus GND).

If I only had a "Mega 2560" let's say, and wanted to used pins 10 - 13...  Just modify the code block like this:
```
//***************************************************************************
//* What board are we programming with?
//***************************************************************************
//#define PRO_MINI
// EXAMPLE
#define MEGA_2560 
//#define UNO
//#define LITTLEBITS  //TODO test

//***************************************************************************
//* Pin Definitions, ported to Arduino pin numbers on boards
//***************************************************************************
#if  defined(PRO_MINI)
#define PDA     5           // define PDA pin
#define PCL     4           // define PCL pin
#define RESET   6           // define RESET control pin
#define VDD     3           // define VDD control pin

#elif defined(MEGA2560)          
#define PDA     11					// define PDA pin
#define PCL     12 					// define PCL pin
#define RESET   10  				// define RESET control pin
#define VDD     13					// define VDD control pin

...
```
# claro?


Note about the programming header:  J4 is 2.0mm pitch!!!  Not 2.54mm (0.1") header.  The simplest thing to do is use a [2x5 2mm header](https://www.digikey.com/en/products/filter/headers-male-pins/314?s=N4IgjCBcoEwBxVAYygMwIYBsDOBTANCAPZQDaIAzAKzUwUiHW0BsIAuoQA4AuUIAytwBOASwB2AcxABfQnATQQKSBhwFiZEMwoBOOKw4gefQaMkzCOgAyIlaLHkIlI5MDDAUYBrr0gDh4lKyIFRutsqqjhoulADsHjTsPiYB5sFgsdbh9mpOmnAALHA6SUa%2B-mZBhGB6JYoRDurO5DZswQC0MNmQwgCuTZpU7NIjQA), otherwise there's a bunch of bending, tweaking and testing.  Test it regardless!  The programmer cable must be solidly connected to the port in order to work.
