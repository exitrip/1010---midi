/*
itrip HEADERZ v1e-9
*/

#ifndef ITRIP_H
#define	ITRIP_H 

#include <REG936.H>

/**************************TYPES*******************************************/
typedef unsigned char byte;
typedef unsigned int word; // 16 bits (is short)

#define SYS_LEN	256

typedef struct Riff_s {
	word rAddy; //the physical address of riff
	byte repeats;
} RIFF_T;


/***********************DEFINE SWITCHES**********************/
//a totally different program actually!!!!
//#define COORD		//blast midi clock out of UArt and drive RT messages
#define BASIC_TX
//#define DEBUG_SIM

//DAC/ADC stuff
#define DAC1_OUT_AUDIO
//#define DAC1_OUT_VCC
#define LUTSIN	LUTSIN64
#define LUTSINMASK	0x3f
//#define LUTSIN	LUTSIN128
//#define LUTSINMASK	0x7f
//#define ADC_IN
//#define UNIT_11
#define UNIT_XII

///MIDI STUFF
//fall back channels
#define MY_L_CHAN   14  //FIXME to keep song.c and riff.c compiling
#define MY_V_CHAN	  (MY_L_CHAN+1)

#ifdef COORD
	#define MY_ID_H		'C'
	#define MY_ID_L		'o'	  //stick to ascii ex: "Co" or "14"
#else //convert to decimal ascii no.
	#define MY_ID_H		(30 + (MY_L_CHAN/10))
	#define MY_ID_L		(30 + (MY_L_CHAN%10))	  
#endif

//SYS_EX_MAGIC
#define SYS_EX_MODE_1_UNIT	0x01
#define SYS_EX_MODE_2_UNIT	'!'

#define MAX_FREQ	1200
#define	MIN_FREQ	700
#define NUM_NOTE_CMDS	(127-LUT_NUM_NOTES) //28

#define VEL_EQUIV_OFF	16  //velocity below which a note on is a note off

//we can either stuff cmds in 0-9 and 110-127 or rewrite storage...
//seems tricky to rewrite, we just map low and hi notes to cmds
//woah!!!  we could double these if we teamed up with NOTE_OFF...
//not ideal for storage....  maybe for todo
enum {
	TX_OFF = 0,	//npc
	TX_ON = 1,  //npc
	STEREO_TOG_MEM = 2,
	UPDOWN_OFF = 3,
	DOWN1 = 4,  //todo make relative...   align with pitch wheel
	DOWN2 = 5,	
	DOWN3 = 6,	
	DOWN4 = 7,
	DOWN5 = 8,
	//notes 10-107
	UP1 = 108,
	UP2 = 109,
	UP3 = 110,
	UP4 = 111,
	UP5 = 112,
	RESERVED = 113,
	STATION_UP = 114,
	STATION_DOWN = 115,
	STATION_UP2 = 116,			//npc
	STATION_DOWN2 = 117,			 //npc//npc
	STATION_UP3 = 118,
	STATION_DOWN3 = 119,					  //npc
	STATION_UP4 = 120,							  //npc
	STATION_DOWN4 = 121,							  //npc
	STATION_UP5 = 122,	//npc
	STATION_DOWN5 = 123,	 //npc
	STATION_UP6 = 124,			 //npc
	STATION_DOWN6 = 125,				  //npc
	SET_DAC = 126,
	NOTE_OFF_MEM = 127
};


/***************************GLOBALS******************************************/
extern volatile byte songNum; //127
extern volatile word midiClk;
extern volatile byte xdata sysEx[SYS_LEN];
extern volatile word sysIx;

extern volatile RIFF_T* curSong;
extern volatile word xdata nextRiff;
extern volatile byte xdata curRiffCnt;
extern volatile word xdata numRiffs;
extern volatile byte code* riff;
extern volatile word deltaPos;
extern volatile byte numNotes;
extern volatile byte nextNote;

#ifdef ADC_IN
extern volatile byte newADC0;
extern volatile byte newADC1;
#endif

extern volatile byte bdata midiFlags;
//state flags -- maybe change to sbit????
extern bit AUDIO_L_ON;	
extern bit TX_VCC_ON; 	
extern bit STEREO;		
extern bit PLAYING;		
extern bit BUTT_EN;		
extern bit OMNI;		
//extern bit SONG_DONE;	
//extern bit SYS_EX_DONE;

extern volatile byte bdata SongFlags;
//state flags -- maybe change to sbit????
extern bit STATE_0;
extern bit STATE_1;		
extern bit SONG_DONE;
extern bit LOOP_SONGS;
//flags for repeat section of first riff in song
#define LOOP_SONG_F	(0x01)

extern byte data myLChan;
extern byte data myVChan;
extern const byte code myLChanFlash;
extern const byte code myVChanFlash;

extern volatile word LPeriod;
extern volatile word VPeriod;
extern volatile byte periodH0;
extern volatile byte periodL0;
extern volatile byte periodH1;
extern volatile byte periodL1;
extern volatile word lDelta;   //a proportion of sorts
extern volatile word txDelta;
extern volatile bit deltaLUp;
extern volatile bit deltaTxUp;
//extern volatile byte volume;  //only 4 left out..

//extern volatile byte deltaLMount; 
//extern volatile byte deltaTxMount;

extern volatile bit txOffSwitch;
extern volatile bit enableTxCVGate;
extern word station;

/****************************PROTOS*********************/
extern void no_touch(void); //set the bootstat and reset to program
void setup ();  //name and turn on
void delay (word cnt);	 //~2.17us to a tick
void shiftout8 (byte d);
//	void shiftout16 (word d);
//	void shiftout32 (word dh, word dl);
void txProg ();
void setFreq (word freq);
void delayT (word t);
void updateNote(void);

//called by sysEx after checking the sysEx header and ':'
char progMemSysEx();
/************************EMPTY Protos****************/	


/******************PIN NAMES****************************/	
sbit txVcc = P2^7;
sbit txData = P2^2;
sbit txClk = P2^3;
sbit LED = P2^5;
sbit CE = P2^4;
sbit midButt = P0^0;
sbit hiButt = P0^1;
sbit loButt = P0^2;
sbit audioL = P0^3;
sbit audioN = P0^4; 	//must be soldered and AC coupled (DC blocked) with 1 uF

#endif