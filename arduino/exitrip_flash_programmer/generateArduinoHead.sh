#!/bin/bash
echo "#ifndef ___BLINKY_HEX
#define ___BLINKY_HEX
#include <avr/pgmspace.h>
unsigned int hexIter = 0;
const PROGMEM " > Blinky_hex.h
xxd -i Blinky.hex >> Blinky_hex.h
echo "#endif" >> Blinky_hex.h
#EOF
