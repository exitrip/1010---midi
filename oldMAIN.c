/* Blinky.C - LED Fla+-
 sher for the Keil LPC900 EPM Emulator/Programmer Module */

#include <REG936.H>			// register definition
#include <LIMITS.H>
#include <INTRINS.H>   
#include <STDIO.H> 
#include <CTYPE.H>
#include "LUTFreq.h"  
#include "LUTsin.h" 
#include "ITRIP.H"
//#include "test/adc.h"


/******************************* GLOBALS**************************************/
////#define JUST_BUTT 
//#define BUT_DEL
//
//enum {
//	UP_SWEEP,
//	UP_SLOW_POLY,
//	UP_SLOW_EVEN,
//	UP_SYNC,
//	UP_DOWN,
//	UP_ALL_TOGETHER,
//	UP_OFF_BEAT_DELAY,
//	TONES_TWO_STEP,
//	TONES_THREE_STEP,
//	TONES_WIDE
//};
//#define MIN_STATE	TONES_TWO_STEP
////#define MIN_STATE	UP_SWEEP
//#define MAX_STATE	TONES_WIDE
#define SPEED_DIV	1
#define FREQ_MIN	911
#define NUM_TRANS	12
//#define CENTER_FREQ	(FREQ_MIN + NUM_TRANS/2)
#define FREQ_MAX	1011//(FREQ_MIN+SPEED_DIV) //high speed = lots of freqs
#define TUNE_IT		1333 //pumped into delay...  UINT16_MAX ~1.5 HZ
#define TEMPO		16660
#define TEMPO_CNT	(TEMPO/(TUNE_IT/SPEED_DIV))

#define FOUR_SECS		224

//REMEMBER!!!  these are up timers... period = 0x0 - values...
//tempo
volatile byte periodH0 = 0; 
volatile byte periodL0 = 0;   //maybe 56Hz
volatile byte count0   = FOUR_SECS; //56;  //maybe 1 HZ, damn close...
//pitch
volatile byte periodH1 = 0; //(0xff & (LUTFreq[0] >> 8)); 
volatile byte periodL1 = 0; //(LUTFreq[0] & 0xff);
volatile byte LUTDex = 0;

/****************************BH141* instruction*******************************/
//volatile byte adcFlag = 0;
//volatile byte adcVal[2];

volatile word bdata txState;
sbit stereo = txState^3;
sbit phaseMode0 = txState^4;
sbit phaseMode1 = txState^5;
sbit test0 = txState^6;
sbit test1 = txState^7;

/***********************************8MAIN????????????????????????*****************/
void main() {	
   
/**************LOCALS****************************/
	unsigned long tempoCnt = TEMPO_CNT;
	word station = FREQ_MIN;
	byte tempoFlag = 1;
	byte atom = 10;
	byte width = 1;
	byte offTime = 255;
	byte cnt = 0;
	byte i = 0;
	byte state = 0;
	byte enableLED = 1;
/**************SETUP++***************************************/
	setup();											 
	setFreq(station);
	TR1 = 1;
	TR0 = 1;
/****************LOOP*****************************************/
	for(;;) {
		//delay(UINT_MAX);
		//periodL1--;
//		if (tempoCnt-- == 0) {
//			tempoCnt = TEMPO_CNT;
//			if(tempoFlag++ > 4) {
//				tempoFlag = 1;
//			}
//		}
//		delay(1000);
//		//delay(tempoFlag*(TUNE_IT/SPEED_DIV));
//		if (station++ >= MAX_FREQ) {
//			station = MIN_FREQ;
//		}
//		setFreq(station);
//		delay(tempoFlag*(TUNE_IT/SPEED_DIV));
//		setFreq(912);
//#ifdef	JUST_BUTT
//		delay(UINT_MAX);
//		if (midButt == 0) {
//			LED ^= 1;
//			txVcc ^= 1;
//			//LEDout ^= 1; 
//		}
//		delay(UINT_MAX);
//		if (LED) {
//			if (hiButt == 0) {
//				LED = 0;
//				delay(UINT_MAX);
//				station++;
//				setFreq(station);
//				LED = 1;
//				delay(UINT_MAX);
//			} 
//			else if (loButt == 0) {
//				LED = 0;
//				delay(UINT_MAX);
//				--station;
//				setFreq(station);
//				LED = 1;
//				delay(UINT_MAX);
//			}
//	
//			if (station < MIN_FREQ) {
//				station = 700;
//				LED = 0;
//				delay(UINT_MAX);
//				LED = 1;
//				delay(UINT_MAX);
//				LED = 0;
//				delay(UINT_MAX);
//				LED = 1;
//				delay(UINT_MAX);
//				LED = 0;
//				delay(UINT_MAX);
//				LED = 1;
//				delay(UINT_MAX);
//				LED = 0;
//				delay(UINT_MAX);
//				LED = 1;
//				delay(UINT_MAX);
//			}
//			if (station > MAX_FREQ) {
//				station = 1080;
//				LED = 0;
//				delay(UINT_MAX);
//				LED = 1;
//				delay(UINT_MAX);
//				LED = 0;
//				delay(UINT_MAX);
//				LED = 1;
//				delay(UINT_MAX);
//				LED = 0;
//				delay(UINT_MAX);
//				LED = 1;
//				delay(UINT_MAX);
//				LED = 0;
//				delay(UINT_MAX);
//				LED = 1;
//				delay(UINT_MAX);
//			}						  
//		}
//#else
////		adc_startadc1conversion(ADC_IMMEDIATE, ADC_FIXEDSINGLE, ADC1_CHANNEL2);
////		cnt = atom;
////		while(cnt--) {
////			delay(atom);
////		}
////		adc_startadc1conversion(ADC_IMMEDIATE, ADC_FIXEDSINGLE, ADC1_CHANNEL2);
////		cnt = atom;
////		if (adcFlag == 1) {
//////			for (width = 0; (width < adcVal[1]); width++) {
//////				LEDout = 0;
//////				cnt = (255 - width);
//////				while (cnt--) {
//////					delay(atom);
//////				}
//////				LEDout = 1;
//////				cnt = width;
//////				while (cnt--) {
//////					delay(atom);
//////				}
//////				width += 3;
//////			}
//////			offTime = 0;
////			for (width = adcVal[1]; width > 0; width--) {
////				LEDout = 0;
////				cnt = offTime++;
////				while (cnt--) {
////					delay(atom);
////				}
////				LEDout = 1;
////				cnt = width;
////				while (cnt--) {
////					delay(atom);
////				}
////			}
////		adcFlag = 0;
////		LEDout = 0;
////		}
//		if (hiButt == 0) {
//			state++;
//			delay(UINT_MAX);
//#ifndef BUT_DEL
//		} else if (midButt == 0) {
//			txVcc = 1;
//			enableLED ^= 1;
//			if (LED) LED = 0;
//			delay(UINT_MAX);
//#endif
//		} else if (loButt == 0) {
//			state--;
//			delay(UINT_MAX);
//		}
//		if (state > MAX_STATE) {
//			state = MIN_STATE;
//		}
//		switch (state) {
//			case UP_SWEEP :
//				if (enableLED == 1) {
//					delay(UINT_MAX/SPEED_DIV);
//					setFreq(station++);
//					if (enableLED == 1) LED ^= 1;
//					if (station > FREQ_MAX)
//						station = FREQ_MIN;
//				}
//				break;
//		
//			case UP_SLOW_POLY:
//				if (enableLED == 1) {
//					for (i = 0; i < SPEED_DIV; i++) {
//						delay(UINT_MAX/2 + (UINT_MAX/NUM_TRANS * SPEED_DIV/2));
//					}
//					LED ^= 1;
//					setFreq(station++);
//					if (station > FREQ_MAX)
//						station = FREQ_MIN;
//				}
//				break;
//
//			case UP_SLOW_EVEN:
//				if (enableLED == 1) {
//					for (i = 0; i < SPEED_DIV; i++) {
//						delay(UINT_MAX);
//					}
//					if (enableLED == 1) LED ^= 1;
//					setFreq(station++);
//					if (station > FREQ_MAX)
//						station = FREQ_MIN;
//				}
//				break;
//
//			case UP_OFF_BEAT_DELAY:
//				if (enableLED == 1) {
//					delay(UINT_MAX);
//					LED ^= 1;
//					setFreq(station++);
//					if (station > FREQ_MAX)
//						station = FREQ_MIN;
//					delay(UINT_MAX);
//					delay((UINT_MAX/2/NUM_TRANS) * SPEED_DIV/2);
//					LED ^= 1;
//					setFreq(station++);
//					if (station > FREQ_MAX)
//						station = FREQ_MIN;
//					delay(UINT_MAX - ((UINT_MAX/2/NUM_TRANS) * SPEED_DIV/2));
//					LED ^= 1;
//					setFreq(station++);
//					if (station > FREQ_MAX)
//						station = FREQ_MIN;
//				}
//				break;
//	
//			case UP_DOWN:
//				if (enableLED == 1) {
//					delay(UINT_MAX);
//					LED ^= 1;
//					setFreq(station++);
//					if (station > FREQ_MAX)
//						station = FREQ_MIN;
//					delay(UINT_MAX);
//					LED ^= 1;
//					setFreq(station--);
//					if (station > FREQ_MAX)
//						station = FREQ_MIN;
//				}
//				break;
//			case UP_ALL_TOGETHER:
//				if (enableLED == 1) {
//					for (i = 0; i < SPEED_DIV; i++) {
//						delay(UINT_MAX);
//					}
//					if (enableLED == 1) LED ^= 1;
//					setFreq(station++);
//					if (station > FREQ_MAX)
//						station = FREQ_MIN;
//				}
//				break;	
//			case TONES_TWO_STEP:
//				if (enableLED == 1) {
//					delay(TUNE_IT/SPEED_DIV);
//					if (enableLED == 1) LED ^= 1;
//					setFreq(station++);
//					if (station > (FREQ_MIN+1))
//						station = FREQ_MIN;
//				}
//				break;
//			case TONES_THREE_STEP:
//				if (enableLED == 1) {
//					delay(TUNE_IT/SPEED_DIV);
//					if (enableLED == 1) LED ^= 1;
//					setFreq(station++);
//					if (station > (FREQ_MIN+1))
//						station = FREQ_MIN-1;
//				}
//				break;
//			case TONES_WIDE:
//				if (enableLED == 1) {
//					delay(TUNE_IT/SPEED_DIV);
//					if (enableLED == 1) LED ^= 1;
//					setFreq(station++);
//					if (station > (FREQ_MAX - NUM_TRANS/2))
//						station = FREQ_MIN-NUM_TRANS/2;
//				}
//				break;				
//		}
//#endif
	}
}
/*******************SETUP FUNCTION*********************/
void setup() {

	P0M1 = 0x13;	 //input for buttons and audioN, push pull for audioL
	P0M2 = 0x08;
	P1M1 = 0;		//quasi-bidirectional pins or inputs
	P2M1 = 0;
	P3M1 = 0;
	midButt = 1; //pull up resistors on the button inputs
	hiButt = 1;
	loButt = 1;
	LED = 1;  	//LED on
	txVcc = 1;	//transmitter off
	CE = 0;		//serial input inable for transmitter
	stereo = 0;
	audioL = 0;
	test0 = 1; 	//always
	test1 = 0; 	//always
	phaseMode0 = 0;	//?
	phaseMode1 = 0;	//?

	  // configure timers

	TMOD &= 0x00;	 //clear conf for timers

	TAMOD &= 0xEE;	 //clear conf for timers
	TMOD |= 0x11;	 //16bit mode for both

	//TAMOD |= 0x10;
	periodH1 = (0xff & (LUTFreq[0] >> 8)); 
	periodL1 = (LUTFreq[0] & 0xff);
	// timer values
	TH0 = periodH0;
	TL0 = periodL0;

	TH1 = periodH1;
	TL1 = periodL1;

	//timer 0 interrupt is higher than timer 1 thus timer 0 is tempo and t1 is pitch

	// set timer 1 isr priority to 2

	IP0 &= 0xF7;
	IP0H &= 0xFF;
	//  // enable timer 1 interrupt

	ET1 = 1;
	ET0 = 1;

	// start timers

	//TR1 = 1;
	//TR0 = 1;
//	LEDout = 0;
	//adc_init();
}	
/*********************TIMER interrupts****************************/

void timers_isr1 (void) interrupt 3 using 2
{
	TH1 = periodH1;
	TL1 = periodL1;
	audioL ^= 1;
	//LED ^= 1;
}

void timers_isr0 (void) interrupt 1 using 3
{
	TH0 = 0x80;//periodH0;
	TL0 = 0;//periodL0;
	if(count0-- == 0) {
		count0 = 3;//FOUR_SECS;
		if (LUTDex++ >= LUT_LEN) {
			LUTDex = 0;
		}
		periodH1 = (0xff & (LUTFreq[LUTDex] >> 8));
		periodL1 = (0xff & LUTFreq[LUTDex]);
		//TR1 ^= 1;
		LED ^= 1;
//		if (LED == 0) {
//			setFreq(912);
//		} else setFreq(911);
		//audioL ^= 1;
	}
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
#ifdef BUT_DEL
  if(midButt == 0) {}
#endif
}