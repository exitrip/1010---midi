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
	explicitly TimerPeriod = QuaterNotePeriod [us] / 24 / 0.271 [us]
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

//#define BEAT_ROOT	(48)
//#define BEAT1_TEMPO	(0x6f00/2)  //240
//#define BEAT2_TEMPO	(0x6f00/4)  //240
//#define BEATCOORD1_S	(69)
//#define BEAT1_S		3
//extern unsigned char code beatCoord1[BEATCOORD1_S];
//extern unsigned char code beatCoord2[BEATCOORD1_S];
//extern unsigned char code beat1[BEAT1_S];

//shepStat
#define	SHEP_TEMPO (0x12D68*2) //60BPM
#define SHEP_FASTER_TEMPO (0x6666) //real fast
#define SHEP_FAST_TEMPO (0x2666) //real fast
 
extern unsigned char code shepStatCoordInit[5];
extern unsigned char code shepStatCoordFastInit[5];
extern unsigned char code shepStatCoordFasterInit[5];

extern unsigned char code shepStatCoord[33];
extern unsigned char code shepStat[9];
//shepStatVoiced
extern unsigned char code shepStatVoiced[17];
//peace
#define PEACE_TEMPO	(0x800d)	// >160?
#define PEACEONE_S	(7)
extern unsigned char code peaceCoord[5];
extern unsigned char code peaceOne[PEACEONE_S];
extern unsigned char code peaceTwo[PEACEONE_S];
extern unsigned char code peaceThree[PEACEONE_S];
extern unsigned char code peaceAs4[PEACEONE_S];
extern unsigned char code peaceGs4[PEACEONE_S];

//BODY
#define BODY_TEMPO	(0x12D68*2) //60 BPM						 
extern unsigned char code bodyInit[5];  //uses whole and minor drone

//BUSY
#define BUSY_TEMPO	(0x6f00)
#define BUSY_TEMPO1	(0x7f00)
#define BUSY_TEMPO2	(0x8f00)
#define BUSY_TEMPO3	(0x9f00)
#define BUSY_TEMPO4	(0xaf00)

#define BUSY1_SIZE	(13)
#define BUSY2STAT_SIZE (29)
extern unsigned char code busyInit[5];
extern unsigned char code busySlower1[5];
extern unsigned char code busySlower2[5];
extern unsigned char code busySlower3[5];
extern unsigned char code busySlower4[5];

extern unsigned char code busy1[BUSY1_SIZE];
extern unsigned char code busy2[BUSY1_SIZE-2];
extern unsigned char code busy2Stat[BUSY2STAT_SIZE];

//onStat
#define ONSTAT_TEMPO  	(0xEDED)	 //??
#define ONSTAT1_S		(28+1)
#define ONSTAT2_S		(60+1)
#define ONSTAT3_S		(28+1)
#define ONSTAT4_S		(28+1)
#define ONSTATMEL1_S 	(24+1)
#define ONSTATMEL2_S 	(16+1)

extern unsigned char code OnStatCoordInit[5];
extern unsigned char code OnStat1[ONSTAT1_S];
extern unsigned char code OnStat2[ONSTAT2_S];
extern unsigned char code OnStat3[ONSTAT3_S];
extern unsigned char code OnStat4[ONSTAT4_S];
extern unsigned char code OnStatMel1[ONSTATMEL1_S];
extern unsigned char code OnStatMel2[ONSTATMEL2_S];

//HAPPY
#define	HAPPY1_S 	(177)
#define HAPPY3_S	(15)
#define HAPPY_TEMPO	(0xe20f) //160
extern unsigned char code happyCoordInit[5]; //then whole rests..
extern unsigned char code happy1[HAPPY1_S];
extern unsigned char code happy2[HAPPY1_S];
extern unsigned char code happy3[HAPPY3_S];
extern unsigned char code happyDrone[3];
extern unsigned char code happyDroneTx[3];
extern unsigned char code happyDroneTx2[3];

//extern unsigned char code happy1Tx[HAPPY1_S];
//extern unsigned char code happy2Tx[HAPPY1_S];
//extern unsigned char code happy3[HAPPY1_S];
//extern unsigned char code happy4[HAPPY1_S];

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

//extern unsigned char code stereoTest1[9];

//#define TEST_LEN	10//easier to parse later
//extern unsigned char code downR1[];
//extern unsigned char code downR2[];
//extern unsigned char code downR3[];
//extern unsigned char code downR4[];
//extern unsigned char code downR5[];
//
//extern unsigned char code upR1[];
//extern unsigned char code upR2[];
//extern unsigned char code upR3[];
//extern unsigned char code upR4[];
//extern unsigned char code upR5[];
//
//
//extern unsigned char code testCo1[];
//extern unsigned char code testCo1b[];
//extern unsigned char code testCo2[];
//
//extern unsigned char code testCo3[];
//extern unsigned char code testCo3b[];
//extern unsigned char code testCo3c[];
//
//extern unsigned char code testCo4[];
#endif