#ifndef RIFF_H
#define RIFF_H

//utility riffs
extern unsigned char code sthRest[5];
extern unsigned char code eiRest[5];
extern unsigned char code qRest[5];
extern unsigned char code hRest[5];
extern unsigned char code wRest[5];

//single Piteches plus switches
#define MINORDRONE_ROOT		29
#define WHOLEDRONE_ROOT		30
extern unsigned char code wholeDrone[5];
extern unsigned char code minorDrone[5];

//COORD UTIL
#define RECO_S	(2+1)
extern unsigned char code sthRestCoord[RECO_S];
extern unsigned char code eiRestCoord[RECO_S];
extern unsigned char code qRestCoord[RECO_S];
extern unsigned char code hRestCoord[RECO_S];
extern unsigned char code wRestCoord[RECO_S]; //one empty bar

#define CRTLTX_S	(4+1)
extern unsigned char code on0Tx[CRTLTX_S];
extern unsigned char code on2Tx[CRTLTX_S];
extern unsigned char code on4Tx[CRTLTX_S];
extern unsigned char code on6Tx[CRTLTX_S];
extern unsigned char code on8Tx[CRTLTX_S];
extern unsigned char code on10Tx[CRTLTX_S];
extern unsigned char code on12Tx[CRTLTX_S];
extern unsigned char code on14Tx[CRTLTX_S];

extern unsigned char code off0Tx[CRTLTX_S];
extern unsigned char code off2Tx[CRTLTX_S];
extern unsigned char code off4Tx[CRTLTX_S];
extern unsigned char code off6Tx[CRTLTX_S];
extern unsigned char code off8Tx[CRTLTX_S];
extern unsigned char code off10Tx[CRTLTX_S];
extern unsigned char code off12Tx[CRTLTX_S];
extern unsigned char code off14Tx[CRTLTX_S];

//special riffs

///////////COORD SONG////////////////
/*
	Spec for COORD song
	word songLen, byte???,
	word riffAddy, byte repeats... 
*/
/*
	spec for COORD riff
	byte deltaPos, byte MIDI / CC+Ch, byte val
				   o
				   MIDI / Sys or RT,
				   o
				   tempo [hiNibble] val [loNibble], 2 bytes
				   [e.g. 0x7F, 0xF3, 0xFF -> cnt0 = 0f, periodH0 = f3, periodL0 = ff
	ideal 77160 [0x12D68] is 120 bpm <- theres a mystery factor of two, but thats a godd thing!!!!
	Tempo and future file meta events...  
	we reserve the high nibble for meta events
	and the low nibble for data...
	Meta events are sparse and easily mapped and
	even extended to 8 states... (high bit is for real midi)
*/

/////////////WORKER SONG//////////////////
/*
Spec for song:

  word songLen, byte ???,
  (word) riffAddress, byte repeats,	 (riff_t)
  (word) riffAddress, byte repeats,
  ... 
*/
/*
Spec for riff:

	byte riffLen,
	byte deltaSongPos, byte 0-126 Notes [ 127 = NoteOff, 0x80 = V_Chan ]
	byte deltaSongPos, byte 0-126 Notes [ 127 = NoteOff, 0x80 = V_Chan ]
	...
*/

#define BEAT_ROOT	(48)
#define BEAT1_TEMPO	(0x6f00/2)  //240
#define BEAT2_TEMPO	(0x6f00/4)  //240
#define BEATCOORD1_S	(69)
#define BEAT1_S		3
extern unsigned char code beatCoord1[BEATCOORD1_S];
extern unsigned char code beatCoord2[BEATCOORD1_S];
extern unsigned char code beat1[BEAT1_S];

//Driving me back...
#define DMB_ROOT 	(25) //C# - yeah we in tune!
#define DMB_PEDAL	(DMB_ROOT-1)
#define DMB_TEMPO	(0x20B61) //~69-70 BPM 0x20B61

#define DMBINIT_S	37
extern unsigned char code dmbInit[37];//tempo ... does pickup!!!

#define DMBVAMP_S	(4+1)
extern unsigned char code dmbVamp0[DMBVAMP_S]; //sans downbeat
extern unsigned char code dmbVamp1[DMBVAMP_S]; //cum downbeat

#define DMBROOT_S	((104-72)*4+1)
extern unsigned char code dmbRoot0[DMBROOT_S]; //sans downbeat
extern unsigned char code dmbRoot1[DMBROOT_S];

#define DMBBD_S		7	
extern unsigned char code dmbBDHa[DMBBD_S];
extern unsigned char code dmbBDWh[DMBBD_S];

#define TEST_LEN	10//easier to parse later
extern unsigned char code downR1[];
extern unsigned char code downR2[];
extern unsigned char code downR3[];
extern unsigned char code downR4[];
extern unsigned char code downR5[];

extern unsigned char code upR1[];
extern unsigned char code upR2[];
extern unsigned char code upR3[];
extern unsigned char code upR4[];
extern unsigned char code upR5[];


extern unsigned char code testCo1[];
extern unsigned char code testCo1b[];
extern unsigned char code testCo2[];

extern unsigned char code testCo3[];
extern unsigned char code testCo3b[];
extern unsigned char code testCo3c[];

extern unsigned char code testCo4[];

/*
#define SAUCER_VOLCANO_SONG_SIZE 3
SONG_T saucerVolcano[SAUCER_VOLCANO_SONG_SIZE] = {
	(word) saucer1, 8-1, SAUCER_SIZE/2
//	(word) volcano1, 2-1, VOLCANO_SIZE/2
};

#define HEAVY_11_SONG_SIZE 6	  
volatile word code heavy1Song[6] = {
	(word) heavy111, 4 - 1, HEAVY_11_SIZE/2,	//4*11
	(word) heavy121, 1 - 1, HEAVY_12_SIZE/2		//1*22
};

volatile word code heavy2Song[6] = {
	(word) heavy112, 4 - 1, HEAVY_11_SIZE/2,
	(word) heavy122, 1 - 1, HEAVY_12_SIZE/2
};

#define DRIVE_BACK_SONG0_SIZE 3	  
volatile word code driveBackSong0[3] = {
	(word) driveBack0, 48 - 1, DRIVE_BACK_0SIZE/2
};

#define DRIVE_BACK_SONG1_SIZE 3
volatile word code driveBackSong1[3] = {
	(word) driveBack1, 48 - 1, DRIVE_BACK_1SIZE/2	
};

#define DRIVE_BACK_SONG2_SIZE 3	  
volatile word code driveBackSong2[3] = {
	(word) driveBack2, 256 - 1, DRIVE_BACK_2SIZE/2
};

#define DRIVE_BACK_SONG3_SIZE 3	  
volatile word code driveBackSong3[3] = {
	(word) driveBack3, 256 - 1, DRIVE_BACK_3SIZE/2
};

#define FIRST_SONG_SIZE	24
volatile word code firstSong[FIRST_SONG_SIZE] = {
	(word) twoRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 1-1, ONEROCKMOD_SIZE/2, //8 - 8
	(word) twoRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 3-1, ONEROCKMOD_SIZE/2, //8 - 24	
	(word) fourFloor, 2 - 1, FOURFLOOR_SIZE/2,	 //4 - 8
	(word) fourFloorTX, 2 - 1, FOURFLOORTX_SIZE/2,	 //4 - 8
	(word) fourFloor, 2 - 1, FOURFLOOR_SIZE/2,	 //4 - 8
	(word) fourFloorTX, 2 - 1, FOURFLOORTX_SIZE/2	 //4 - 8
};

#define SEC_SONG_SIZE	24 
volatile word code secSong[SEC_SONG_SIZE] = {
	(word) twoRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 1-1, ONEROCKMOD_SIZE/2, //8 - 8
	(word) twoRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 2-1, ONEROCKMOD_SIZE/2, //8 - 8	
	(word) fourFloor, 2 - 1, FOURFLOOR_SIZE/2,	 //4 - 8
	(word) fourFloorTX, 2 - 1, FOURFLOORTX_SIZE/2,	 //4 - 8
	(word) fourFloor, 2 - 1, FOURFLOOR_SIZE/2,	 //4 - 8
	(word) fourFloorTX, 3 - 1, FOURFLOORTX_SIZE/2	 //4 - 8
};
#endif

SONG_T testSong[6] = {
	(word) test, 1-1, TEST_SIZE/2,
	(word) test, 1-1, TEST_SIZE/2
};

//begin thumpDream song	- not sure about freqs - maybe add high pitch drone?
#define THUMP1_SONG_SIZE	6	 
SONG_T thump1Song[THUMP1_SONG_SIZE] = {
		(word) thumpThump, 4 - 1, THUMP_THUMP_SIZE/2, //4 - 16
	(word) thumpFall8, 4 - 1, THUMP_FALL8_SIZE/2	 //4 - 16
};

#define THUMP2_SONG_SIZE 18	 
SONG_T thump2Song[THUMP2_SONG_SIZE] = {
		(word) thumpThump, 4 - 1, THUMP_THUMP_SIZE/2, //4 - 16
	(word) thumpFall8, 4 - 1, THUMP_FALL8_SIZE/2,	 //4 - 16
		(word) thumpThump, 4 - 1, THUMP_THUMP_SIZE/2, //4 - 16
	(word) thump2, 4 - 1, THUMP_2_SIZE/2,	 //4 - 16
		(word) thumpThump, 4 - 1, THUMP_THUMP_SIZE/2, //4 - 16
	(word) thump2, 4 - 1, THUMP_2_SIZE/2	 //4 - 16
};

#define THUMP3_SONG_SIZE 24	 
SONG_T thump3Song[THUMP3_SONG_SIZE] = {
		(word) thumpThump, 4 - 1, THUMP_THUMP_SIZE/2, //4 - 16
	(word) thumpFall8, 4 - 1, THUMP_FALL8_SIZE/2,	 //4 - 16
		(word) thumpThump, 4 - 1, THUMP_THUMP_SIZE/2, //4 - 16
	(word) thumpFall8, 4 - 1, THUMP_FALL8_SIZE/2,	 //4 - 16
		(word) thumpThump, 4 - 1, THUMP_THUMP_SIZE/2, //4 - 16
	(word) thump3, 4 - 1, THUMP_3_SIZE/2,	 //4 - 16
		(word) thumpThump, 4 - 1, THUMP_THUMP_SIZE/2, //4 - 16
	(word) thump3, 4 - 1, THUMP_3_SIZE/2	 //4 - 16
};

//Begin altSong - space two songs at 3 freqs - slowish interlocking riffage 
#define FIR_SONG_ALT_SIZE	15
volatile word code firSongAlt[FIR_SONG_ALT_SIZE] = {
	(word) twoRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 1-1, ONEROCKMOD_SIZE/2, //8 - 8
	(word) twoRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 3-1, ONEROCKMOD_SIZE/2, //8 - 16
	(word) oneRockB, 8-1, ONEROCKB_SIZE/2	   //4 - 32
};

#define SEC_SONG_ALT_SIZE	18 
volatile word code secSongAlt[SEC_SONG_ALT_SIZE] = {
	(word) oneRockMod, 1-1, ONEROCKMOD_SIZE/2, //8 - 8
	(word) twoRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 1-1, ONEROCKMOD_SIZE/2, //8 - 8
	(word) twoRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 2-1, ONEROCKMOD_SIZE/2, //8 - 8
	(word) twoRockB, 8-1, TWOROCKB_SIZE/2	   //4 - 32
};

#define THI_SONG_ALT_SIZE	18 
volatile word code thiSongAlt[THI_SONG_ALT_SIZE] = {
	(word) oneRockB, 10-1, ONEROCKB_SIZE/2,	   //4 - 40
	(word) oneRockMod, 1-1, ONEROCKMOD_SIZE/2, //8 - 8
	(word) twoRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 1-1, ONEROCKMOD_SIZE/2, //8 - 8
	(word) twoRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 1-1, ONEROCKMOD_SIZE/2 //8 - 8
};


#define FOR_SONG_ALT_SIZE	18 
volatile word code forSongAlt[FOR_SONG_ALT_SIZE] = {
	(word) twoRockB, 10-1, TWOROCKB_SIZE/2,	   //4 - 40
	(word) twoRockMod, 1-1, ONEROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) twoRockMod, 1-1, ONEROCKMOD_SIZE/2, //8 - 8
	(word) oneRockMod, 1-1, TWOROCKMOD_SIZE/2, //8 - 8
	(word) twoRockMod, 1-1, ONEROCKMOD_SIZE/2 //8 - 8
};
*/
#endif