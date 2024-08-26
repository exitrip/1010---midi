# 1010---midi
Trying organize an otherwise un-organized repo for public consumption:

## Overview
This repo contains everything one needs to repurpose an "iTrip 1G Nano" as a generic radio transmitter, including an adaptor circuit board to simplify the hack, and a "headless" Arduino program to flash firmware on to the iTrip's LPC936 microcontroller.

See the `kicad` directory for a partial schematic of the iTrip and the complete schematic and layout of the adaptor PCB.  I've got lots of the PCBs, so please ask me to send you some instead of making your own for now.

### Required supplies
If you want to replicate this work you'll need:
- iTrips (again ask me for some, I've got hundreds).  It's good to have plenty of extras for a workshop.
- an Arduino and homemade programming cable
- Soldering equipment, wire cutters, a small screw driver helps, etc.
- ~1m electrical wire per transmitter
- to pick a power source for the iTrip:
  - 2x AA/AAA battery pack, try finding them from surplus sites like [Goldmine Electronics](https://theelectronicgoldmine.com/products/g27885?_pos=18&_sid=e9574ebc7&_ss=r)
  - TO-92 or SOT23-5 3.3V, 100mA regulator (e.g. [L78L33ACZ](https://www.digikey.com/en/products/detail/stmicroelectronics/L78L33ACZ/1038304))
  - or the [FTDI FT232RL](https://www.digikey.com/en/products/detail/ftdi-future-technology-devices-international-ltd/FT232RL-REEL/1836385)  USB-to-UART converter with onboard regulator.  This chip is relatively fine pitch SMT TSSOP, so it will be challenging to seat without the right soldering tools and experience.  

A quick note about the FTDI chip:  Seating this chip will allow you to send and recieve MIDI (via serial) commands to the transmitter over USB, in fact each FTDI chip can drive up to 8 transmitters, but there are undocumented details as to how to set this up.  All of the PurrData patches, touchOSC setup, and most of the uVision code target custom modular hardware that is also poorly documented and out of scope of a workshop.  Even without the "onboard" FTDI, you can access all this functionality by using any [3.3V USB-Serial cable](https://www.adafruit.com/product/70) hooked up to the TX/RX on the adpator PCB. Reach out, I happy to discuss further.

Another note about firmware:  The LPC936 firmware programmed by the Arduino is stored in the Arduino firmware directly.  Recompiling new firmware unfortunately requires a licensed copy of KEIL uVision Cx51, which is thousands of dollars last I checked.  The "free" versions of uVision have a prohibitively small size limit, and cannot build the code as is.  I'm still investigating if I can strip the project enough...

### Setting up the programmer
See [README](arduino/exitrip_flash_programmer/README.md) in arduino folder.

## Steps for the hack
- Open up the iTrip.  Easiest way is to slip a flat head above the button and pry the plastic case open like an oyster.  Be a bit careful with the button though.
- Don't put too much stress on the cables inside the now opened iTrip, they can easily break off the PCB.
- Break the connectors from the front plastic shell.  This takes some practice, and there's maybe half a dozen ways to do this.  Notice that there's a seam in the front plastic around connectors, just under the FCC ID number.  Pressing the smaller plastic piece out of the front cover is easy, most of the time.  You can also just cut the front cover up too.
- Cut loose the antenna (black wire soldered, ANT2, to the board closest to the USB port, J3) and push the wire loose out the back of the black plastic
![Antenna to cut](/ant2.jpg "Antenna to cut")
- Solder ~1m of wire to the antenna, this is now a [1/4 whip antenna](https://en.wikipedia.org/wiki/Whip_antenna) at ~75MHz. It's good to cheat it shorter than 1m, as that tunes it up the FM spectrum, but don't go longer.
- Connect the programming cable to the iTrip and Arduino.  Make sure the external power supply PCB is DISCONNECTED from the iTrip to be programmed.
- Power on or RESET the Arduino.  At boot up it will blink slowly, but when it successfully handshakes with the LPC936, the LED will start blinking faster during programming.  Wait until the LED is blinking slow again, which indicates programming is complete.  This is a good time to test the iTrip without the added power supply, as it will recieve power from the Arduino programmer directly.  The iTrip itself is working and correctly programmed if:
  - The red LED in the corner comes on solid 
  - The red LED turns on and off with a middle button press (this turns the transmitter on and off)
  - While the LED is on there's a signal (silence) on 87.9 MHz (every time the iTrip boots up the transmission freqency is reset to 87.9)
  - Pressing the up and down buttons, tunes the transmitter up and down.
- This step can be done at anytime, but once you've tested the iTrip works while connected to the Arduino, you can be sure that further problems are caused by the power supply.
  - Solder the desired power supply to the adaptor PCB (e.g. GND to battery negative, 3.3V to battery positive).  Any of the ICs will take 5V from either the 5V header on the adaptor or the USB port on the iTrip.  A useful 5V and 3.3V will come OUT of those headers too!

  ## Suggestions about workshops
  - FM radios are not as common as they used to be.  BRING SOME, otherwise there's a big sad trombone at the end of the build
  - Have an SDR reciever setup on a laptop to visualize the transmissions.  It will also double as a reciever.  These turnkey [RTL-SDR kits](https://www.rtl-sdr.com/buy-rtl-sdr-dvb-t-dongles/) are awesome for the price.