/* Blinky.C - LED Fla+-
 sher for the Keil LPC900 EPM Emulator/Programmer Module */

#include <REG936.H>			// register definition
#include <LIMITS.H>
#include <INTRINS.H>   
#include <STDIO.H> 
#include <CTYPE.H>
#include "power.h"
#include "uart.h"
#include "adc.h"
#include "ee.h"
#include "midi_spec.h"
#include "LUTFreq.h"  
#include "LUTsin.h" 
#include "itrip.h"
#include "song.h"

/******************************* GLOBALS**************************************/
volatile byte xdata sysEx[SYS_LEN];
volatile word sysIx = 0;

volatile byte songNum = 0; 
volatile word midiClk = 0;

//state flags -- maybe change to sbit????
volatile byte bdata midiFlags;
sbit AUDIO_L_ON = midiFlags^0;	//(0x01)	//allow wiggling the Laudio (attached to noteOn and sequencer)
sbit TX_VCC_ON = midiFlags^1; 	//(0x02)	//allow wiggle the txVCC	(attached to noteOn and sequencer)
sbit STEREO = midiFlags^2;		//(0x04)	//keep track of tx number of channels
sbit PLAYING = midiFlags^3;		//(0x08)	//am I playing now?  //not Ignoring midiClk
sbit BUTT_EN = midiFlags^4;		//(0x10)	//todo test
sbit OMNI = midiFlags^5;		//(0x20)	//todo ?test
//sbit SONG_DONE = midiFlags^6;	//0x40
//sbit LOOP_SONGS = midiFlags^7;	//instead of naziMidi stop...  just one?  everyone??  deviant!!!

volatile byte bdata songFlags;
sbit STATE_0 = songFlags^0;	  //MODE0 or MODE1 for unit11
sbit STATE_1 = songFlags^1;	  //TURN ON? SONGS CODE!?!
sbit STATE_2 = songFlags^2;
sbit STATE_3 = songFlags^3;
sbit SONG_DONE = songFlags^4;	//0x40
sbit LOOP_SONGS = songFlags^5;	//instead of naziMidi stop...  just one?  everyone??  deviant!!!
sbit AUTO_START = songFlags^6; //you know, start on power up after a delay, for master....  maybe also function as a watchdog
sbit WRAP_FREQ = songFlags^7; //if told to move beyond limits of txFreq, wrap around...  maybe break into top and bottom flags...

//try moving to locals!!!
//#define NUM_RIFFS HEAVY_11_SONG_SIZE//SAUCER_VOLCANO_SONG_SIZE//THUMP1_SONG_SIZE//3//FOR_SONG_ALT_SIZE//FIRST_SONG_ALT_SIZE//THIRD_SONG_SIZE//
volatile RIFF_T* curSong;
volatile word nextRiff = 0;
volatile byte curRiffCnt = 0;
volatile word numRiffs = 0;
volatile byte code* riff;
//deltaSongPos ... just ... cant..  be ...  a ...  byte....
volatile word deltaPos = 0;
volatile byte numNotes = 0;
volatile byte nextNote = 0;

//end exclusive defines
#define SPEED_DIV	1
//#if (MY_L_CHAN > 4)
//#define FREQ_START	(882)
//#else
//#define FREQ_START	(879)
//#endif
#define FREQ_START	(879 + (MY_L_CHAN*2))
			   

//timing globals
//REMEMBER!!!  these are up timers... period = 0x0 - values...
//tempo or txVcc pitch
volatile byte periodH0 = 0; 
volatile byte periodL0 = 0;   
volatile byte cnt0 = 0;
#ifdef COORD
	volatile byte temp0 = 0;
#endif

//pitch
volatile byte periodH1 = 0; 
volatile byte periodL1 = 0;

//helpful shadows...
volatile word LPeriod;
volatile word VPeriod;

volatile word lDelta = 0;
volatile word txDelta = 0;
volatile bit deltaLUp = 0;
volatile bit deltaTxUp = 0;

//////   ADC
//volatile byte adcFlag;
#ifdef ADC_IN
	volatile byte newADC0 = 0;
	byte oldADC0 = 0;
	volatile byte newADC1 = 0;
	//byte oldADC1 = 0;
#endif
//volatile byte adcVal[2];

///DAC
#ifdef DAC0_OUT
	byte dac0LUTdex = 0;
#endif
#ifdef DAC1_OUT
	byte dac1LUTdex = 0;
#endif

/****************************BH141* instruction*******************************/

volatile word bdata txState;
sbit stereoTx = txState^3;
sbit phaseMode0 = txState^4;
sbit phaseMode1 = txState^5;
sbit test0 = txState^6;
sbit test1 = txState^7;

volatile bit txOffSwitch = 0; 

volatile word station = FREQ_START;

/***********************************8MAIN????????????????????????*****************/
void main() {	
/**************LOCALS****************************/
	byte i = 0;
	//power_brownoutenable(POWER_BORESET);
/**************SETUP++***************************************/
	setup();
	//Config boot-up
	while (midButt == 0) {  //debounced midButt switches COORD's PLAYING
		LED ^= 1;
		delay(UINT_MAX/3);	
		if (cnt0++ > 80) {	//hold middle button at boot for ~2.5s
			//add a gang sign to enter flash programming mode, cause it will be hard to recover from...
			while (midButt == 0) {};
			while (1) {
				if (hiButt == 0 ) { 
					no_touch();
				} else if (loButt == 0) {
					cnt0 = 0;
					break;
				}
			}
		}
		//hopefully a graceful recovery from the threat of flash programming
		//TODO for later peeps
		//read butts
		//if butts
		//	write eeprom
		//else read eeprom
	}

	while (hiButt == 0) {
#ifdef COORD
#else
#endif
	}
	while (loButt == 0) {
#ifdef COORD
#else
#endif
	}
	// End Config boot-up
	cnt0 = 0;
	txVcc = 0; //on
	setFreq(station);
	uart_init();											 
	//init first song... just incase its the first one we play
	//nextRiff = 0;	//to be explicit
	curSong = songBook[songNum];
	numRiffs = (curSong[nextRiff]).rAddy;  //grab song length!  update will inc nextRiff!!!
	if ((curSong[nextRiff]).repeats & LOOP_SONG_F) {
		LOOP_SONGS = 1;
	} else {
		LOOP_SONGS = 0;
	}
	EA = 1;
	BUTT_EN = 1;
	//LOOP_SONGS = 0;
	//autoStart
	AUTO_START = 0;
	STATE_0 = 0;
	STATE_1 = 1;
	STEREO = 0;

#ifdef COORD
	TR0 = 0;
	TR1 = 0;
//	while (1) {
//		uart_transmit(CONTROL);
//		uart_transmit(GENERAL_SLIDER_1_lo);
//		uart_transmit((i++ << 5) & ~(0x80));
//		delay(1000);
//	}
	//makes for a happy synth!!!!
	delay(50000);
	if (STATE_1 == 1) {
		uart_transmit(SONG_SELECT);
		uart_transmit(songNum);
		delay(50000);
		for (i = 0; i < 16; i += 2) {
			uart_transmit(CONTROL+i);
			uart_transmit(GENERAL_SLIDER_1_lo);
			uart_transmit(STATION_TO_LO((879 + (i*2))));
			delay(1000);
			uart_transmit(CONTROL+i);
			uart_transmit(GENERAL_SLIDER_1_hi);
			uart_transmit(STATION_TO_HI((879 + (i*2))));
			delay(1000);
			uart_transmit(CONTROL+i);
			uart_transmit(GENERAL_BUTTON_1_on);
			uart_transmit(127);
		}
		LED = 0;
		if (AUTO_START == 1) {
			curSong = songBook[songNum];
			nextRiff = 0;
			deltaPos = 0; //trigger update
			numRiffs = (curSong[nextRiff]).rAddy;  //grab song length and flags!  dont inc it.. update will
			if ((curSong[nextRiff]).repeats & LOOP_SONG_F) {
				LOOP_SONGS = 1;
			} else {
				LOOP_SONGS = 0;
			}
			uart_transmit(STOP);
			uart_transmit(SONG_SELECT);
			uart_transmit(songNum);
			uart_transmit(START);
			PLAYING = 1;
			curRiffCnt = 0;
			numNotes = 0;
			nextNote = 0;
			LED = PLAYING;
			TR0 = PLAYING;
		}
	}
#else
	delay(65000);
	delay(65000);
	TR1 = 1;
	TR0 = 1;
#endif
	//UNIT!! only has onboard LEDS
	LED = 1;
	setFreq(station);
/****************LOOP*****************************************/
	for(;;) {
#ifdef COORD
#ifdef ADC_IN
		if (ADCON0 & 0x08) {
		    // clear ADCI0 flag
		    ADCON0 &= ~0x08;
		    // read results from AD0DAT0 - AD0DAT3
			newADC0 = AD0DAT0;// >> 3;
			newADC1 = AD0DAT2;
		}
//		if (oldADC0 != newADC0) { //totally arbitrary, TODO test!!!
//			//VPeriod is fixed record, LPeriod is scratch, newADC0 is basically periodH0
//			LPeriod = VPeriod + newADC0;
//			temp0 = (LPeriod >> 8) & 0xff;
//			periodH0 = LPeriod & 0xff;
//		}
		//this has to be a mode because it dominates functionality with no signal....
		//ring adc switches play on/off
		if (STATE_1 == 1) {
			if (newADC1 > 55) {
				uart_transmit(STOP);
				PLAYING = 0;
			}
		} else {
			if (newADC1 > 55) {
				if (STATE_0 == 0) {
					uart_transmit(SYSTEM_EXCLUSIVE);
					uart_transmit(REAL_TIME_ID);
					uart_transmit(0x01);
					uart_transmit(0x0e);
					uart_transmit(0x0d);
					uart_transmit(SYS_EX_MODE_2_UNIT11);
					uart_transmit(EOX);	
				}
				STATE_0 = 1;
			} else {
				if (STATE_0 == 1) {
					uart_transmit(SYSTEM_EXCLUSIVE);
					uart_transmit(REAL_TIME_ID);
					uart_transmit(0x01);
					uart_transmit(0x0e);
					uart_transmit(0x0d);
					uart_transmit(SYS_EX_MODE_1_UNIT11);
					uart_transmit(EOX);	
				}
				STATE_0 = 0;
			}
		} 
		//else {
//			if (midiClk == 0) { //were we playing once?
//				curSong = songBook[songNum];
//				nextRiff = 0;
//				deltaPos = 0; //trigger update
//				numRiffs = (curSong[nextRiff]).rAddy;  //grab song length and flags!  dont inc it.. update will
//				if ((curSong[nextRiff]).repeats & LOOP_SONG_F) {
//					LOOP_SONGS = 1;
//				} else {
//					LOOP_SONGS = 0;
//				}
//				uart_transmit(STOP);
//				uart_transmit(SONG_SELECT);
//				uart_transmit(songNum);
//				uart_transmit(START);
//				PLAYING = 1;
//				curRiffCnt = 0;
//				numNotes = 0;
//				nextNote = 0;
//			} else {
//				uart_transmit(CONTINUE);
//				PLAYING = 1;
//			}
//		}
#endif
		txVcc = 1; //assert tx off...
		if (BUTT_EN == 1 && STATE_1 == 1) {
			if (midButt == 0) {  //debounced midButt switches COORD's PLAYING
				delay(50000);	  //cant functionalize this says the internet...
				if (midButt == 0) {
					delay(50000);
					if(midButt == 0) {
						if (PLAYING) { //we are already playing
							uart_transmit(STOP);
							PLAYING = 0;
						} else if (midiClk == 0) { //were we playing once?
							curSong = songBook[songNum];
							nextRiff = 0;
							deltaPos = 0; //trigger update
							numRiffs = (curSong[nextRiff]).rAddy;  //grab song length and flags!  dont inc it.. update will
							if ((curSong[nextRiff]).repeats & LOOP_SONG_F) {
								LOOP_SONGS = 1;
							} else {
								LOOP_SONGS = 0;
							}
							uart_transmit(STOP);
							uart_transmit(SONG_SELECT);
							uart_transmit(songNum);
							uart_transmit(START);
							PLAYING = 1;
							curRiffCnt = 0;
							numNotes = 0;
							nextNote = 0;
						} else {
							uart_transmit(CONTINUE);
							PLAYING = 1;
						}
					}
				}
				LED = PLAYING;
				TR0 = PLAYING;
				//TR1 = PLAYING;
				delay(50000);
			} else if (hiButt == 0) {	 //switch to previous song
				delay(50000);	  //cant functionalize this says the internet...
				if (hiButt == 0) {
					delay(50000);
					if(hiButt == 0) {
						LED = 1;
						delay(50000);
						if (++songNum >= NUM_SONGS) {	 //have we gone past song 0 or 127?
							songNum = NUM_SONGS-1;
						}
						midiClk = 0;
						PLAYING = 0;
						TR0 = 0;
						//TR1 = 0;
						uart_transmit(STOP);
						uart_transmit(SONG_SELECT);
						uart_transmit(songNum);
						curSong = songBook[songNum];
						nextRiff = 0;
						deltaPos = 0; //trigger update
						numRiffs = (curSong[nextRiff]).rAddy;  //grab song length!  dont inc it.. update will
						if ((curSong[nextRiff]).repeats & LOOP_SONG_F) {
							LOOP_SONGS = 1;
						} else {
							LOOP_SONGS = 0;
						}
						curRiffCnt = 0;
						numNotes = 0;
						nextNote = 0;
						LED = 0;
					}
				}
				delay(50000);
			} else if (loButt == 0) {	//switch to previous song
				delay(50000);	  //cant functionalize this says the internet...
				if (loButt == 0) {
					delay(50000);
					if(loButt == 0) {
						LED = 1;
						delay(50000);
						if (--songNum > 127) {  //have we gone past song 0 or 127?
							songNum = 0;
						}
						midiClk = 0;
						PLAYING = 0;
						TR0 = 0;
						//TR1 = 0;
						uart_transmit(STOP);
						uart_transmit(SONG_SELECT);
						uart_transmit(songNum);
						curSong = songBook[songNum];
						nextRiff = 0;
						deltaPos = 0; //trigger update
						numRiffs = (curSong[nextRiff]).rAddy;  //grab song length!  dont inc it.. update will
						if ((curSong[nextRiff]).repeats & LOOP_SONG_F) {
							LOOP_SONGS = 1;
						} else {
							LOOP_SONGS = 0;
						}
						curRiffCnt = 0;
						numNotes = 0;
						nextNote = 0;
						LED = 0;
					}
				}
				delay(50000);
			}
		}

#else
	if (curSong != songBook[songNum] && STATE_1 == 1) {
		setFreq(station);
		curSong = songBook[songNum];
		midiClk = 0;
		nextRiff = 0;
		deltaPos = 0; //trigger update
		numRiffs = (curSong[nextRiff]).rAddy;  //grab song length!  dont inc it.. update will
		if ((curSong[nextRiff]).repeats & LOOP_SONG_F) {
			LOOP_SONGS = 1;
		} else {
			LOOP_SONGS = 0;
		}		
	} else {
	//low priority stuff
#ifdef ADC_IN
		//adc_startadc0conversion(ADC_IMMEDIATE, ADC_FIXEDSINGLE, ADC0_CHANNEL0);
		//while (ADCON0 & 0x08 == 0x0) {}; 
		//newADC0 = AD0DAT0;
		if (ADCON0 & 0x08) {
		    // clear ADCI0 flag
		    ADCON0 &= ~0x08;
		    // read results from AD0DAT0 - AD0DAT3
			newADC0 = AD0DAT0 >> 1;
			newADC1 = AD0DAT2;
		}
		if (oldADC0 != newADC0) {
			if (newADC0 >= 3) {	//~70mV "off"
				i = newADC0 - 3;
				if (i >= LUT_NUM_NOTES) { 
					i = LUT_NUM_NOTES-1;
				}
				LPeriod = LUTFreq[i];
				periodH1 = (0xff & (LUTFreq[i] >> 8));
				periodL1 = (0xff & LUTFreq[i]);
				i = 0;
				if (STATE_0 == 1) {
					AUDIO_L_ON = 1;
				} else if (txOffSwitch == 0) {
					if (oldADC0 >> 2 != newADC0 >> 2) {
						setFreq(station + (newADC0 >> 2)); //vary station by 3.2 Mhz max [a 0.8 MHz swing w/ 3V into HVCV]
					}
				}
			} else {
				if (STATE_0 == 0) {
					AUDIO_L_ON = 0;
				} else {
					setFreq(station);
				}
			}
			oldADC0 = newADC0;
		}		 
		if (newADC1 > 55) {	//1.2Volts at input ~ 5V gate through -12dB pad
			txOffSwitch = 1;
			//LED = 0;
			//txVcc = 1;	//tx off
		} else {
			txOffSwitch = 0;
			//LED = 1;
			//txVcc = 0;
		}
#endif
#ifdef BASIC_TX 
		//was number of transmit channels changed
		if (stereoTx != STEREO) {
			stereoTx = STEREO;
			txProg();
		}
		if (BUTT_EN == 1) {
			if (midButt == 0) {
	//			LED ^= 1;
				txVcc ^= 1;
				if(txVcc == 1) {
					txOffSwitch = 1;
					LED = 0;
				} else {
					txOffSwitch = 0;
					LED = 1;
					delay(50);
					setFreq(station);
				}
				delay(UINT_MAX); 
			}
			if (txVcc == 0) {
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
					station = MIN_FREQ;
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
					station = MAX_FREQ;
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
#endif
	}
#endif
	}
}
/*******************SETUP FUNCTION*********************/
void setup() {

	//power_brownoutenable(POWER_BOINTERRUPT);

	//eeprom_init();

	P0M1 = 0x07;	 //input for buttons and audioN, push pull for audioL
	P0M2 = 0x08;
	P1M1 = 0;		//uart_init takes care of TX/RX
//	P1M2 |= 0x04;	//configure t0 [p1^2] as push pull
	P2M1 = 0;		
	P3M1 = 0;
	//adc and dac taken care of later

	midButt = 1; //pull up resistors on the button inputs
	hiButt = 1;
	loButt = 1;
	LED = 1;  	//LED on
	txVcc = 1;	//transmitter off
	CE = 0;		//serial input inable for transmitter
	stereoTx = STEREO;
	audioL = 0;
	test0 = 1; 	//always


	test1 = 0; 	//always
	phaseMode0 = 0;	//?
	phaseMode1 = 0;	//?

#ifdef DAC0_OUT
	//configure DAC1 out
	  // set dac0 pin to input only (disables digital output)
	P2M1 |= 0x01;
	P2M2 &= ~0x01;
	// init dac0 value to zero
	AD0DAT3 = 0x00;
	// enable dac0 output
	ADMODB |= 0x04;
	// enable adc0 (also enables dac0)
	ADCON0 |= 0x04;
#else  ///  need to set DAC pins hiZ
//	P2M1 |= 0x01;
//	P2M2 &= ~0x01;	
#endif

#ifdef DAC1_OUT
	//configure DAC1 out
	  // set dac1 pin to input only (disables digital output)
	P0M1 |= 0x10;
	P0M2 &= ~0x10;
	// init dac1 value to zero
	AD1DAT3 = 0x00;
	// enable dac1 output
	ADMODB |= 0x08;
	// enable adc1 (also enables dac1)
	ADCON1 |= 0x04;
#ifdef COORD
	AD1DAT3 = 0xFF; //LUTSIN128[dac1LUTdex++ & 0x7F];	 //todo add counter to not multiply clk
#endif
#else	 //set hiZ
//	P0M1 |= 0x10;
//	P0M2 &= ~0x10;
#endif				 

	  // configure timers
	TMOD &= 0x00;	 //clear conf for timers
	TAMOD &= 0xEE;	 //clear conf for timers
	TMOD |= 0x11;	 //16bit mode for both

	//TAMOD |= 0x10;
	periodH1 = 0;
	periodL1 = 0;
	// timer values		   	
	TH0 = 0;
	TL0 = 0;
	
	TH1 = periodH1;
	TL1 = periodL1;
	//timer 0 interrupt is higher than timer 1 thus timer 0 is tempo and t1 is pitch
#ifdef COORD
	//set timer0 priority to 2, below tx
	IP0 &= ~(0x02);
	IP0H &= ~(0x02);
	//CLK OUT
#endif
	// set timer 1 isr priority to 2 and timer 0 to priority 3
	IP0 &= ~(0x80);
	IP0H &= ~(0x00);
	//  // enable timer 1 interrupt
	ET1 = 1;
	ET0 = 1;

#ifdef ADC_IN
	adc_init();
	adc_startadc0conversion(ADC_IMMEDIATE, ADC_AUTOSCANCONT, ADC0_CHANNEL0 | ADC0_CHANNEL2);

//	// configure clock divider 
//	ADMODB |= 0x40;
//	//configure pins
//	P1M1 |= 0x80; //input only for AD00, P1.7, pin 4, ADC1
//	P1M2 &= ~0x80;
//	P2M1 |= 0x02; //input only for AD02, P2.1, pin 2, ADC0
//	P2M2 &= ~0x02;
//	//setup rolling two channel conversion
//	// disable all triggers
//  	// ADCON0 &= 0xDC;
//	// clear mode bits and boundary interrupt flag
//  	ADMODA &= 0x0F;
//	//autoscan, continuously on adc0 and adc1
//	ADINS = (ADC0_CHANNEL0 | ADC0_CHANNEL2);
//	ADMODA |= 0x04; //set burst flag, try the alternate bit conf if this doesnt work...
//	//start now
//	ADCON0 |= 0x01;
//	//data should be in AD0DAT0 and AD0DAT2
#endif
//	// set isr priority to 0
//	IP1 &= 0x7F;
//	IP1H &= 0x7F;
//	// enable adc interrupt	???
//	EAD = 1;
}	
/*********************TIMER interrupts****************************/

void timers_isr1 (void) interrupt 3 using 2
{
#ifdef COORD
		//reload with som const todo
		//todo explore 8 bit timer mode
//		TH1 = 0xfe;//periodH1;
		//TL1 = periodL1;	//is 0xff - the following
//		TL1 = 0x2e; // we think is close to 256us
		//TL0++; //didint work....
		//TL0 = TL0 + 1; //didnt work either...
		//T0 = 0;
//		P1^2 ^= 1; //also didnt work in conjunction with count mode...
		//todo test...
//#ifdef DAC0_OUT				//todo test moving before ifdef
//		AD0DAT3 = LUTSIN128[dac0LUTdex++ & 0x7F];
//#endif
#else
		//reload
		TH1 = periodH1;	//remember this only counts up!!!!
		TL1 = periodL1;
		//generate square waves
		_nop_(); //matching cycles to t0 rupt
		_nop_();
		_nop_();
		if(AUDIO_L_ON) { //could play with nops here
			audioL ^= 1; 
		}
#ifdef DAC1_OUT
		AD1DAT3 = LUTSIN128[dac1LUTdex++ & 0x7F];
#endif
//#ifdef DAC0_OUT
//		AD0DAT3 = LUTSIN128[dac0LUTdex++ & 0x7F];
//#endif
#endif
}

void timers_isr0 (void) interrupt 1 using 3
{
#ifdef COORD
		if (cnt0-- == 0) {
			uart_transmit(TIMING_CLOCK);
			if (deltaPos == 0) {
				updateNote();
			} else { //parse song
				--deltaPos;	 	
			}
			cnt0 = temp0;
			TH0 = periodH0;
			TL0 = periodL0;
//#ifdef DAC1_OUT
//			if ( (++midiClk % 0x0C) == 0 ) {
//				AD1DAT3 ^= 0xFF; //LUTSIN128[dac1LUTdex++ & 0x7F];	 //todo add counter to not multiply clk
//			}
//#else 
			++midiClk;
//#endif 
		} else {
			TH0 = 0;
			TL0 = 0;
		}
//#ifdef DAC0_OUT				
//	AD0DAT3 = LUTSIN128[dac0LUTdex++ & 0x7F];
//#endif
#else
		//reload
		TH0 = periodH0;
		TL0 = periodL0;
		//generate square waves
		if (!txOffSwitch) {
			if(TX_VCC_ON) {
				txVcc ^= 1;
			} else {
				txVcc = 0; //keep the transmitter ON!!!
			}
		} else {
			txVcc = 1; //tx OFF!  station???
		}
//#ifdef DAC1_OUT
//	AD1DAT3 = LUTSIN128[dac1LUTdex++ & 0x7F];
//#endif
#endif
}

//Plays first riff one extra time!!!
void updateNote(void) {
	byte temp, temp2;
	word thisDelta = 0;
	bit thisUp = 0, VnotL = 0;
UPDATE_NOTE:
	if (nextNote >= numNotes) {	 //equal to catches init!!!
		nextNote = 1; //skip the riff len header
		if (curRiffCnt-- == 0) {
			if (++nextRiff >= numRiffs) { //next riff is newRiff
				//end of SONG!!!!
				PLAYING = 0; //midi says stop
				midiClk = 0;
				LED = 0;
				//going silent but leave transmitter on for less static
				AUDIO_L_ON = 0;
				TX_VCC_ON = 0;
				txOffSwitch = 0;
				//ensure that we always fall through to this point
				nextRiff = numRiffs - 1;
				curRiffCnt = 0;
				nextNote = numNotes;
				SONG_DONE = 1;
				if (LOOP_SONGS == 1) { //looP songs, reset everybody, looPSongs only for coord 
//					uart_transmit(SONG_SELECT);
//					uart_transmit(songNum);
//					uart_transmit(START);
					//curSong = songBook[songNum];
					nextRiff = 0;
					deltaPos = 0; //trigger update
					numRiffs = (curSong[nextRiff]).rAddy;  //grab song length!  dont inc it.. update will
					//loop song is set already, but this would parse other flags...  And we will consitently inc here
					if ((curSong[nextRiff++]).repeats & LOOP_SONG_F) {
						LOOP_SONGS = 1;
					} else {
						LOOP_SONGS = 0;
					}
					numNotes = 0; //numNotes=nextNote skiPs songlength header, maybe hide init info like looPsongs in rePs field
					nextNote = 1; //but this breaks that flow so we have to force it forward
					riff = (byte*) (curSong[nextRiff]).rAddy;//grab the physical addy of first riff
					curRiffCnt = (curSong[nextRiff]).repeats;//grabs number of time riff repeats  
					numNotes = riff[0];				//grab the length of the riff
					SONG_DONE = 0;
					PLAYING = 1;
//					TR0 = 1;  //start playing
					LED = 1;
					goto UPDATE_NOTE;
				}
#ifdef COORD	
				else {
					TR0 = 0;  //stop playing
					uart_transmit(STOP);
				}	
#endif
			} else {
				riff = (byte*) (curSong[nextRiff]).rAddy;//grab the physical addy of first riff
				curRiffCnt = (curSong[nextRiff]).repeats;//grabs number of time riff repeats  
				numNotes = riff[0];				//grab the length of the riff
			}
		}
	}
	deltaPos = riff[nextNote++];				//grab deleta T for note
	temp = (riff[nextNote++]);				//nextNote is now next note
#ifdef COORD
	//this can likely be very much more optomized!!!!!  todo
	if (PLAYING) {
		if (temp & 0x80) {
			if (temp < 0xf0) { 
				switch (temp & 0xf0) { //find CC and PC and the future todos...
				
					case CONTROL:
						
						temp2 = riff[nextNote++]; 
						switch(temp2) { //this could become a big switch!!!
	 						
							case GENERAL_BUTTON_1_on:
								//delay(900); //didnt help with bad sync on txToggle
							case GENERAL_SLIDER_1_hi: //todo keep thinking about 14 bit values...
							case GENERAL_SLIDER_1_lo:
							case PAN_POSN_hi:
							default:
								uart_transmit(temp);
								uart_transmit(temp2);
								uart_transmit(riff[nextNote++]);
							break;
	
	//						case SOUND_RELEASE_TIME: //todo a sustain structure!
	//						break;
	
						}
						break;
			
					case PROGRAM:
					case PITCH_WHEEL:
					case NOTE_ON:
					case NOTE_OFF:
					case CHAN_PRESSURE:
					case KEY_PRESSURE:
					default:
						break;
				}
			} else {
				switch (temp) {
					case SYSTEM_EXCLUSIVE: // variable length until terminated by an EOX or any status byte
				  		sysIx = 0;
						//todo in COORD/file sysEx
						//uart_transmit(temp);
					break;
		
		        	case SONG_POSITION: //beam out the 14-16 bit songPos  LSB first
//						uart_transmit(temp);
//						uart_transmit(riff[nextNote++]);
//						uart_transmit(riff[nextNote++]);
						//todo COORD scan and fix for everybody...
				  	break;
		
		        	case SONG_SELECT: //new Song in this Song!!!!! Untested
						curSong = songBook[nextNote]; //nextNote is song number!!!
						uart_transmit(temp);
				  		uart_transmit(riff[nextNote++]);
						midiClk = 0;
						deltaPos = 0;
						nextRiff = 0;
						numRiffs = (curSong[nextRiff]).rAddy;
						if ((curSong[nextRiff]).repeats & LOOP_SONG_F) {
							LOOP_SONGS = 1;
						} else {
							LOOP_SONGS = 0;
						}
						curRiffCnt = 0;
						numNotes = 0;
						nextNote = 0;
						PLAYING = 0;
						TR0 = 0;
					break;
		
		        	case START:	 //from the beginning
				  		midiClk = 0;
						deltaPos = 0;
						nextRiff = 0;
						numRiffs = (curSong[nextRiff]).rAddy;
						if ((curSong[nextRiff]).repeats & LOOP_SONG_F) {
							LOOP_SONGS = 1;
						} else {
							LOOP_SONGS = 0;
						}
						curRiffCnt = 0;
						numNotes = 0;
						nextNote = 0;
						uart_transmit(temp);
				  		PLAYING = 1;
						TR0 = 1;
		          	break;
		
		        	case STOP:  //this will cease the whole #! till the button is pressed again
				  		PLAYING = 0;
						uart_transmit(temp);
						TR0 = 0;
						break;
	
		        	case CONTINUE:
				  		PLAYING = 1;
						uart_transmit(temp);
						TR0 = 1;
						break;
							 
		        	case SYSTEM_RESET:
						uart_transmit(temp);
	//					AUXR1 |= 0x08; //soft reset, maybe not me...	
		          		break;
					
					case EOX:			//also we will find this before the switch!	
					case TIMING_CLOCK: //the thing that should not be
					case TUNE_REQUEST:
					case ACTIVE_SENSING:
					default:
				  		break;
				}
			}
		} else { //we are disastrously misaligned or have 127 values to play with ...
			switch (temp & 0x70) {
				
				case TEMPO_SET: //tempo!!!
					temp0 = (temp & 0x0f); //MSN first
					periodH0 = 0xFF - riff[nextNote++];
					periodL0 = 0xFF - riff[nextNote++];
					cnt0 = 0;
					//use LPeriod as tempo shadow for ADC time bending
					LPeriod = (temp0 << 8) + periodH0;
					VPeriod = LPeriod;
					break;
			}
		}
		if (deltaPos == 0) {
			goto UPDATE_NOTE;
		}
	}
#else
	if (PLAYING) { //todo test switches for cool TX stuff...  
		if (temp & 0x80) {
			VnotL = 1;
		}
		temp &= 0x7f;
		switch (temp) {

			case TX_OFF:
				LED = 0;
				txOffSwitch = 1;	//	TX off
			break;
			
			case TX_ON:
				LED = 1;
				txOffSwitch = 0;	//	TX on
			break;
			
			case UP1:
				thisUp = 1;
			case DOWN1:
				thisDelta = 10;
			break;
			
			case UP2:
				thisUp = 1;
			case DOWN2:
				thisDelta = 9;
			break;
			
			case UP3:
				thisUp = 1;
			case DOWN3:
				thisDelta = 8;
			break;
			
			case UP4:
				thisUp = 1;
			case DOWN4:
				thisDelta = 7;
			break;
			
			case UP5:
				thisUp = 1;
			case DOWN5:
				thisDelta = 6;
			break;
		
			case UPDOWN_OFF:
				thisDelta = 0;
				if (VnotL == 1) {
					txDelta = 0;
				} else {
					lDelta = 0;
				}
			break;
			
			case STATION_UP6:
				++station;
			case STATION_UP5:
				++station;
			case STATION_UP4:
				++station;
			case STATION_UP3:
				++station;
			case STATION_UP2:
				++station;
			case STATION_UP:
				setFreq(++station);
			break;
			
			case STATION_DOWN6:
				--station;
			case STATION_DOWN5:
				--station;
			case STATION_DOWN4:
				--station;
			case STATION_DOWN3:
				--station;
			case STATION_DOWN2:
				--station;
			case STATION_DOWN:
				setFreq(--station);
			break;
			
			case HOLD1:
			case HOLD2:
			break;

			case NOTE_OFF_MEM:
				if (VnotL == 1) {
					TX_VCC_ON = 0;
				} else {
					AUDIO_L_ON = 0;
				}
			break;

			case STEREO_TOG_MEM:
				STEREO ^= 1;
			break;

			default:
				temp -= LUT_MIDI_NOTE_SHIFT;
				if (VnotL == 1) {
					TX_VCC_ON = 1;
					VPeriod = LUTFreq[temp];
					periodH0 = (0xff & (LUTFreq[temp] >> 8));
					periodL0 = (0xff & LUTFreq[temp]);
				} else {
					AUDIO_L_ON = 1;
					LPeriod = LUTFreq[temp];
					periodH1 = (0xff & (LUTFreq[temp] >> 8));
					periodL1 = (0xff & LUTFreq[temp]);
				}
			break;
		}
		if (thisDelta) {
			if (VnotL == 1) {	 //not OMNIfied!!!! todo
				txDelta = thisDelta;
				deltaTxUp = thisUp;
			} else {
				lDelta = thisDelta;
				deltaLUp = thisUp;
			}
		}
		//should just work.... and does...
		if (deltaPos == 0) {
			thisDelta = 0;
			thisUp = 0; 
			VnotL = 0;
			goto UPDATE_NOTE;
		}
	}
#endif
}

/*****************TEST SETUP***************************************/

/********************SETTERS****************************/  
void setFreq (word freq) { //takes
	if (txOffSwitch || freq > MAX_FREQ || freq < MIN_FREQ) return;  //out of bounds, do-over
 	//if (freq > MAX_FREQ || freq < MIN_FREQ) return;  //out of bounds, do-over
 	else {
		word temp = freq;
		//EA = 0;		//Disable interrupts for tuning
		temp += (txState & 0xF800);  //keep phase cntrl, channels, and test bits
		txState = temp;	 //return or sorts
		txProg();
		//EA = 1;		//resume interrupt service
	}	
}
/*********************8CEREAL***************************/
void txProg() {	//shift out txState to the transmitter
	word i = 0x01;
	bit tempTX = TX_VCC_ON;
	TX_VCC_ON = 0;
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
	TX_VCC_ON = tempTX; 
}

						   
void delay (word cnt) {	//2.17 us * cnt
  while (--cnt);
}