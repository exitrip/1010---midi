#include "itrip.h"
#include "song.h"
#include "riff.h"

//maybe not use these switches.. maybe they will be bery useful....

///silence for song 0
#ifdef COORD
	RIFF_T code silentSong[2] = {
		{2, 0},
		{wRestCoord, 255}
	};
#else
	RIFF_T code silentSong[2] = {
		{2, 0},
		{wRest, 255}
	};
#endif

//heavy Beats!!!
//byte code 
#ifdef COORD
	RIFF_T code beatSong[10] = {
		{10,0},
		{beatCoord2, 20-1},  //1.5833 min
		{beatCoord1, 10-1},  //1.5833 min
		{beatCoord2, 10-1},
		{wRestCoord, 9-1},	 //38 more beats droning  {31.66 sec}
		{hRestCoord, 1-1},
		{beatCoord2, 20-1},  //1.5833 min
		{beatCoord1, 10-1},  //1.5833 min
		{wRestCoord, 9-1},	 //38 more beats droning  {31.66 sec}
		{hRestCoord, 1-1}
	};
#else
	RIFF_T code beatSong[4] = {
		{4,0},
		{beat1, 255},
		{beat1, 255},
		{beat1, 255}
	};
#endif

//Our body
#ifdef COORD
#elif (MY_L_CHAN == 0)
#elif (MY_L_CHAN == 2)
#elif (MY_L_CHAN == 4)
#elif (MY_L_CHAN == 6)
#elif (MY_L_CHAN == 8)
#elif (MY_L_CHAN == 10)
#elif (MY_L_CHAN == 12)
#elif (MY_L_CHAN == 14)
#endif

//droneStrike
#ifdef COORD
#elif (MY_L_CHAN == 0)
#elif (MY_L_CHAN == 2)
#elif (MY_L_CHAN == 4)
#elif (MY_L_CHAN == 6)
#elif (MY_L_CHAN == 8)
#elif (MY_L_CHAN == 10)
#elif (MY_L_CHAN == 12)
#elif (MY_L_CHAN == 14)
#endif

//omes
#ifdef COORD
#elif (MY_L_CHAN == 0)
#elif (MY_L_CHAN == 2)
#elif (MY_L_CHAN == 4)
#elif (MY_L_CHAN == 6)
#elif (MY_L_CHAN == 8)
#elif (MY_L_CHAN == 10)
#elif (MY_L_CHAN == 12)
#elif (MY_L_CHAN == 14)
#endif

//whole tone and minor scale songs
#ifdef COORD
	//just use silent song
	RIFF_T code wholeToneSong[2] = {
		{2, 0},
		{wRestCoord, 255}
	};
#else
	RIFF_T code wholeToneSong[2] = {
		{2, 0},
		{wholeDrone, 255}
	};
#endif

#ifdef COORD
	//just use silent song
	RIFF_T code minorSong[2] = {
		{2, 0},
		{wRestCoord, 255}
	};
#else
	RIFF_T code minorSong[2] = {
		{2, 0},
		{minorDrone, 255}
	};
#endif

//driving me backwards!!!!!
//timing is basically 1 Root = 4 bars
//8 Vamps first verse, 5 Root solo, 8 Root second verse, then freak to fade out...
//Bass per bar @ 2 Root then to 2 per bar befor solo....
//bring in Vamps around second verse....
//bring in more dissonance towards end....
#ifdef COORD
	RIFF_T code dmbSong[13] = { //255 bars @ 70 bpm is more than 14 minutes
		{13, 0},
		{dmbInit, 1-1}, //pick up beat ?
		{wRestCoord, 4-1}, //one root
		{on10Tx, 1-1},	//1-5	 BDwhole
		{wRestCoord, 16-1}, 
		{on12Tx, 1-1},	//5-11  BDhalf
		{wRestCoord, 24-1}, 
		{on2Tx, 1-1},	//12 evil vamp
		{wRestCoord, 4-1}, 
		{on0Tx, 1-1},	//13-20 more pedal
		{wRestCoord, 28-1}, 
		{on4Tx, 1-1},	//20 onwards nice in crunchy
		{wRestCoord, 255-1}
	};
#elif (MY_L_CHAN == 0)
	RIFF_T code dmbSong[2] = {
		{2, 0},
//		{qRest, 1-1},
		{dmbVamp0, 255}
	};
#elif (MY_L_CHAN == 2)
	RIFF_T code dmbSong[3] = {
		{3, 0},
		{qRest, 1-1},
		{dmbVamp1, 255}
	};
#elif (MY_L_CHAN == 4)
	RIFF_T code dmbSong[2] = {
		{2, 0},
		//{qRest, 1-1},
		{dmbRoot0, 255}
	};
#elif (MY_L_CHAN == 6) /***************MAIN LINE*******************/
	RIFF_T code dmbSong[3] = {
		{3, 0},
		{dmbVamp0, 1-1},
		{dmbRoot1, 255}
	};
#elif (MY_L_CHAN == 8)
	RIFF_T code dmbSong[3] = {
		{3, 0},
		{wRest, 255}
//		{qRest, 1-1},
//		{dmbChord15, 255}
	};
#elif (MY_L_CHAN == 10)
	RIFF_T code dmbSong[3] = {
		{3, 0},
		{qRest, 1-1}, //pickup
//		{wRest, 16-1},
		{dmbBDWh, 255},  //one root
//		{dmbBDHa, 255-1} //five roots deep
//		{qRest, 1-1},

	};
#elif (MY_L_CHAN == 12)
	RIFF_T code dmbSong[3] = {
		{3, 0},
//		{wRest, 255}
		{qRest, 1-1},
		{dmbBDHa, 255}
	};
#elif (MY_L_CHAN == 14)
	RIFF_T code dmbSong[2] = {
		{2, 0},
		{wRest, 255}
//		{qRest, 1-1},
//		{dmbChord53, 255}
	};
#endif

//eunice waymond
#ifdef COORD
#elif (MY_L_CHAN == 0)
#elif (MY_L_CHAN == 2)
#elif (MY_L_CHAN == 4)
#elif (MY_L_CHAN == 6)
#elif (MY_L_CHAN == 8)
#elif (MY_L_CHAN == 10)
#elif (MY_L_CHAN == 12)
#elif (MY_L_CHAN == 14)
#endif

//AamilneBallad
#ifdef COORD
#elif (MY_L_CHAN == 0)
#elif (MY_L_CHAN == 2)
#elif (MY_L_CHAN == 4)
#elif (MY_L_CHAN == 6)
#elif (MY_L_CHAN == 8)
#elif (MY_L_CHAN == 10)
#elif (MY_L_CHAN == 12)
#elif (MY_L_CHAN == 14)
#endif


//#define TEST_SS1 6+1
RIFF_T code testS1[TEST_SS1] = {
	{TEST_SS1, 0}, //songLen, songNum!!!!  songNum for building of songBook!!!
	{upR1, 8-1},
	{upR2, 8-1},
	{upR3, 8-1},
	{upR4, 8-1},
	{upR5, 8-1},
	{upR1, 8-1}
};

//#define TEST_SS2 6+1
RIFF_T code testS2[TEST_SS2] = {
	{TEST_SS2, 0}, //songLen, songNum!!!!  songNum for building of songBook!!!
	{downR4, 2-1},
	{downR5, 2-1},
	{downR4, 2-1},
	{downR5, 2-1},
	{downR4, 2-1},
	{downR5, 2-1}
};

RIFF_T code testSCo1[7] = {
	{7, 0},
	{testCo3, 1-1},
	{testCo1, 15-1},
	{testCo3, 1-1},
	{testCo1, 15-1},
	{testCo3, 1-1},
	{testCo1, 15-1}
};

RIFF_T code testSCo2[3] = {
	{3, 0},
	{testCo4, 3-1},
	{testCo2, 3-1}
};