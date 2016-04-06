/*
itrip HEADERZ v1e-9
*/

#ifndef ITRIP_H
#define	ITRIP_H 

#include <REG936.H>

/**************************TYPES*******************************************/
typedef unsigned char byte;
typedef unsigned int word; // 16 bits (is short)

#define SYS_LEN	512

typedef struct Riff_s {
	word rAddy; //the physical address of riff
	byte repeats;
} RIFF_T;


/***********************DEFINE SWITCHES**********************/
//a totally different program actually!!!!
#define COORD		//blast midi clock out of UArt and drive RT messages
//#define BASIC_TX
//#define DEBUG_SIM

//KEIL!!!!  you get the point!!!
//#ifdef (COORD && BASIC_TX)
//	#error "DUMB!!! L00K UP!!!"
//#endif


///MIDI STUFF
#define MY_L_CHAN   0//[0-15] //base channel
#define MY_V_CHAN	(MY_L_CHAN+1) //always Lchan++
#define MY_ID_H		"C"
#define MY_ID_L		"o"	  //stick to ascii ex: "Co" or "14"

#define MAX_FREQ	1200
#define	MIN_FREQ	700
#define NUM_NOTE_CMDS	(127-LUT_NUM_NOTES) //28
//we can either stuff cmds in 0-9 and 110-127 or rewrite storage...
//seems tricky to rewrite, we just map low and hi notes to cmds
//woah!!!  we could double these if we teamed up with NOTE_OFF...
//not ideal for storage....  maybe for todo
enum {
	TX_OFF = 0,	//npc
	TX_ON = 1,  //npc
	UPDOWN_OFF = 2,
	STATION_UP = 3,
	STATION_DOWN = 4,
	DOWN1 = 5,  //todo make relative...   align with pitch wheel
	DOWN2 = 6,	
	DOWN3 = 7,	
	DOWN4 = 8,
	DOWN5 = 9,
	HOLD0 = 109,
	UP1 = 110,
	UP2 = 111,
	UP3 = 112,
	UP4 = 113,
	UP5 = 114,
	STATION_UP2 = 115,			//npc
	STATION_DOWN2 = 116,			 //npc//npc
	STATION_UP3 = 117,
	STATION_DOWN3 = 18,					  //npc
	STATION_UP4 = 119,							  //npc
	STATION_DOWN4 = 120,							  //npc
	STATION_UP5 = 121,	//npc
	STATION_DOWN5 = 122,	 //npc
	STATION_UP6 = 123,			 //npc
	STATION_DOWN6 = 124,				  //npc
	HOLD1 = 125,
	HOLD2 = 126,
	NOTE_OFF_MEM = 127
};


/***************************GLOBALS******************************************/
extern volatile byte songNum; //127
extern volatile word midiClk;
extern volatile byte xdata sysEx[SYS_LEN];
extern volatile word sysIx;

extern volatile RIFF_T* curSong;
extern volatile word nextRiff;
extern volatile byte curRiffCnt;
extern volatile word numRiffs;
extern volatile byte code* riff;
extern volatile word deltaPos;
extern volatile byte numNotes;
extern volatile byte nextNote;

extern volatile byte bdata midiFlags;
//state flags -- maybe change to sbit????
extern bit AUDIO_L_ON;	
extern bit TX_VCC_ON; 	
extern bit STEREO;		
extern bit PLAYING;		
extern bit BUTT_EN;		
extern bit OMNI;		
extern bit SONG_DONE;	
//extern bit SYS_EX_DONE;

extern volatile byte periodH0;
extern volatile byte periodL0;
extern volatile byte periodH1;
extern volatile byte periodL1;
extern volatile word lDelta;   //a proportion of sorts
extern volatile word txDelta;
extern volatile bit deltaLUp;
extern volatile bit deltaTxUp;
//extern volatile byte deltaLMount; 
//extern volatile byte deltaTxMount;

extern volatile bit txOffSwitch;
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