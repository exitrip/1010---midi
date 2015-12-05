/* Blinky.C - LED Fla+-
 sher for the Keil LPC900 EPM Emulator/Programmer Module */

#include <REG936.H>			// register definition
#include <LIMITS.H>
#include <INTRINS.H>   
#include <STDIO.H> 
#include <CTYPE.H>   
#include "ITRIP.H"


/******************************* GLOBALS**************************************/
/****************************BH141* instruction*******************************/
volatile word bdata txState;
sbit stereo = txState^3;
sbit phaseMode0 = txState^4;
sbit phaseMode1 = txState^5;
sbit test0 = txState^6;
sbit test1 = txState^7;	


/***********************************8MAIN????????????????????????*****************/
void main() {	
   
/**************LOCALS****************************/
	
	word station = 870;

/**************SETUP++***************************************/
	setup();											 
	setFreq(station);
/****************LOOP*****************************************/
	for(;;) {
		delay(UINT_MAX);
		if (midButt == 0) {
			LED ^= 1;
			txVcc ^= 1; 
		}
		delay(UINT_MAX);
		if (LED) {
			if (hiButt == 0) {
				LED = 0;
				delay(UINT_MAX);
				station++;
				setFreq(station);
				LED = 1;
				delay(UINT_MAX);
			} 
			else if (loButt == 0) {
				LED = 0;
				delay(UINT_MAX);
				--station;
				setFreq(station);
				LED = 1;
				delay(UINT_MAX);
			}
			if (station < MIN_FREQ) {
				station = 700;
				LED = 0;
				delay(UINT_MAX);
				LED = 1;
				delay(UINT_MAX);
				LED = 0;
				delay(UINT_MAX);
				LED = 1;
				delay(UINT_MAX);
				LED = 0;
				delay(UINT_MAX);
				LED = 1;
				delay(UINT_MAX);
				LED = 0;
				delay(UINT_MAX);
				LED = 1;
				delay(UINT_MAX);
			}
			if (station > MAX_FREQ) {
				station = 1080;
				LED = 0;
				delay(UINT_MAX);
				LED = 1;
				delay(UINT_MAX);
				LED = 0;
				delay(UINT_MAX);
				LED = 1;
				delay(UINT_MAX);
				LED = 0;
				delay(UINT_MAX);
				LED = 1;
				delay(UINT_MAX);
				LED = 0;
				delay(UINT_MAX);
				LED = 1;
				delay(UINT_MAX);
			}						  
		}
	}
}
/*******************SETUP FUNCTION*********************/
void setup() {

	P0M1 = 0x17;	 //input for buttons and audioN, output for audioL
	P1M1 = 0;		//quasi-bidirectional pins or inputs
	P2M1 = 0;
	P3M1 = 0;
	midButt = 1; //pull up resistors on the button inputs
	hiButt = 1;
	loButt = 1;
	LED = 1;  	//LED on
	txVcc = 0;	//transmitter off
	CE = 0;		//serial input inable for transmitter
	stereo = 0;
	audioL = 0;
	test0 = 1; 	//always
	test1 = 0; 	//always
	phaseMode0 = 0;	//?
	phaseMode1 = 0;	//?
}	

/*****************TEST SETUP***************************************/

/********************SETTERS****************************/  
void setFreq (word freq) { //takes
	if (freq > MAX_FREQ || freq < MIN_FREQ) return;  //out of bounds, do-over
 	else {
		word temp = freq;
		EA = 0;		//Disable interrupts for tuning
		temp += (txState & 0xF800);  //keep phase cntrl, channels, and test bits
		txState = temp;	 //return or sorts
		txProg();
		EA = 1;		//resume interrupt service
	}	
}

/*********************8CEREAL***************************/
void txProg() {	//shift out txState to the transmitter
	word i = 0x01;
	EA = 0;
	txVcc = 0;	//	TX on
	txClk = 0;   
	CE = 0;   
	CE = 1;   
	for(i = 0x01; i != 0; i <<= 1) {  
		txData = txState & i;
		txClk = 1;   
		txClk = 0;   
	}       
	CE = 0;
	EA = 1;   
}

						   
void delay (word cnt) {	//2.17 us * cnt
  while (--cnt);
}