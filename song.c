#include "itrip.h"
#include "song.h"
#include "riff.h"

//maybe not use these switches.. maybe they will be bery useful....
///////////all songs....   //drive song selection from here...
void* const code songBook[NUM_SONGS] = {
	silentSong,
	busySong,
	//testS1,//testSCo1,////	  todo test updown songs....
	//testS2,//testSCo1,//testSCo2,////
	happySong,
	minorSong,
	wholeToneSong,									 
	bodySong,
	statSong,
	dmbSong
};

///silence for song 0
#ifdef COORD
	RIFF_T const code silentSong[2] = {
		{2, 0},
		{wRestCoord, 255}
	};
#else
	RIFF_T const code silentSong[2] = {
		{2, 0},
		{wRest, 255}
	};
#endif

//heavy Beats!!!
//byte const code 
//#ifdef COORD
//	RIFF_T const code beatSong[10] = {
//		{10,0},
//		{beatCoord2, 20-1},  //1.5833 min
//		{beatCoord1, 10-1},  //1.5833 min
//		{beatCoord2, 10-1},
//		{wRestCoord, 9-1},	 //38 more beats droning  {31.66 sec}
//		{hRestCoord, 1-1},
//		{beatCoord2, 20-1},  //1.5833 min
//		{beatCoord1, 10-1},  //1.5833 min
//		{wRestCoord, 9-1},	 //38 more beats droning  {31.66 sec}
//		{hRestCoord, 1-1}
//	};
//#else
//	RIFF_T const code beatSong[4] = {
//		{4,0},
//		{beat1, 255},
//		{beat1, 255},
//		{beat1, 255}
//	};
//#endif

//statSong
#ifdef COORD
	//just use silent song
	RIFF_T const code statSong[3] = {
		{3, 0},
		{OnStatCoordInit, 1},
		{wRestCoord, 255}
	};
#elif (MY_L_CHAN == 0)
	RIFF_T const code statSong[2] = {
		{2, 0},
		{OnStat1, 255}	   
	};
#elif (MY_L_CHAN == 2)
	RIFF_T const code statSong[2] = {
		{2, 0},
		{OnStat2, 255}	   
	};
#elif (MY_L_CHAN == 4)
	RIFF_T const code statSong[2] = {
		{2, 0},
		{OnStat3, 255}	   
	};
#elif (MY_L_CHAN == 6)
	RIFF_T const code statSong[2] = {
		{2, 0},
		{OnStat4, 255}	   
	};
#elif (MY_L_CHAN == 8)
	RIFF_T const code statSong[2] = {
		{2, 0},
		{OnStatMel1, 255}	   
	};
#elif (MY_L_CHAN == 10)
	RIFF_T const code statSong[2] = {
		{2, 0},
		{OnStatMel2, 255}	   
	};
#elif (MY_L_CHAN == 12)
	RIFF_T const code statSong[2] = {
		{2, 0},
		{OnStat3, 255}	   
	};
#elif (MY_L_CHAN == 14)
	RIFF_T const code statSong[2] = {
		{2, 0},
		{OnStat4, 255}	   
	};
#endif

//Our body
#ifdef COORD
	//just use silent song
	RIFF_T const code bodySong[3] = {
		{3, 0},
		{bodyInit, 1},
		{wRestCoord, 255}
	};
#else
	RIFF_T const code bodySong[41] = {
		{41, 0},
			{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
					{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3},
				{minorDrone, 3},
		{wholeDrone, 3}
	}; 
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

//busy
#ifdef COORD
	//just use silent song
	RIFF_T const code busySong[28] = {
		{28, 0},
		{busyInit, 1},
		{wRestCoord, 6},
		{busySlower1, 1},
		{wRestCoord, 5},
		{busySlower2, 1},
		{wRestCoord, 4},
		{busySlower3, 1},
		{wRestCoord, 3},
		{busySlower4, 1},
		{wRestCoord, 2},
		{busyInit, 1},
		{wRestCoord, 6},
		{busySlower4, 1},
		{wRestCoord, 2},
		{wRestCoord, 6*3},
		{busySlower1, 1},
		{wRestCoord, 5*3},
		{busySlower2, 1},
		{wRestCoord, 4*3},
		{busySlower3, 1},
		{wRestCoord, 3*3},
		{busySlower4, 1},
		{wRestCoord, 2*3},
		{busyInit, 1},
		{wRestCoord, 6*3},
		{busySlower4, 1},
		{wRestCoord, 2*3}
	};
#elif (MY_L_CHAN == 0)
	RIFF_T const code busySong[2] = {
		{2, 0},
		{busy1, 255}	   
	};
#elif (MY_L_CHAN == 2)
	RIFF_T const code busySong[5] = {
		{5,0},
		{wRest, 11-1},
		{happy2, 3-1},		 //176 beats - 44 bars
		{happy1, 4-1},
		{happy2, 4-1}
	};
#elif (MY_L_CHAN == 4)
	RIFF_T const code busySong[4] = {
		{4,0},
		{happyDrone, 22-1},		 //8*22 = 176 beats	- 44 bars
//		{wRest, 2-1},		   //8 beats
		{happy3, 64-1},	  //160 beats - 5*16 is 80 beats ... ends early
		{happyDroneTx, 255-1}  //
	};
#elif (MY_L_CHAN == 6)
	RIFF_T const code busySong[3] = {
		{3,0},
		{happyDrone, 33-1},		 // 4 * 176
		{happy3, 255-1}
	};
#elif (MY_L_CHAN == 8)
	RIFF_T const code busySong[3] = {
		{3,0},
		{wRest, 33-1},
		{happyDroneTx2, 255-1},
	};
#elif (MY_L_CHAN == 10)
	RIFF_T const code busySong[4] = {
		{4,0},
		{happyDrone, 11-1},		 //88 beats	- 22 bars
		//{wRest, 22-1},		   //88 beats
		{happy3, 32-1},	  //160 beats - 5*16 is 80 beats ... ends early
		{happyDrone, 255-1}  //
	};
#elif (MY_L_CHAN == 12)
	RIFF_T const code busySong[3] = {
		{3, 0},
		{wRest, 56},
		{busy2Stat, 255}	   
	};
#elif (MY_L_CHAN == 14)
	RIFF_T const code busySong[2] = {
		{2, 0},
		{busy2, 255}	   
	};
#endif

//whole tone and minor scale songs
#ifdef COORD
	//just use silent song
	RIFF_T const code wholeToneSong[2] = {
		{2, 0},
		{wRestCoord, 255}
	};
#else
	RIFF_T const code wholeToneSong[2] = {
		{2, 0},
		{wholeDrone, 255}
	};
#endif

#ifdef COORD
	//just use silent song
	RIFF_T const code minorSong[2] = {
		{2, 0},
		{wRestCoord, 255}
	};
#else
	RIFF_T const code minorSong[2] = {
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
	RIFF_T const code dmbSong[13] = { //255 bars @ 70 bpm is more than 14 minutes
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
	RIFF_T const code dmbSong[2] = {
		{2, 0},
//		{qRest, 1-1},
		{dmbVamp0, 255}
	};
#elif (MY_L_CHAN == 2)
	RIFF_T const code dmbSong[3] = {
		{3, 0},
		{qRest, 1-1},
		{dmbVamp1, 255}
	};
#elif (MY_L_CHAN == 4)
	RIFF_T const code dmbSong[2] = {
		{2, 0},
		//{qRest, 1-1},
		{dmbRoot0, 255}
	};
#elif (MY_L_CHAN == 6) /***************MAIN LINE*******************/
	RIFF_T const code dmbSong[3] = {
		{3, 0},
		{dmbVamp0, 1-1},
		{dmbRoot1, 255}
	};
#elif (MY_L_CHAN == 8)
	RIFF_T const code dmbSong[3] = {
		{3, 0},
		{wRest, 255}
//		{qRest, 1-1},
//		{dmbChord15, 255}
	};
#elif (MY_L_CHAN == 10)
	RIFF_T const code dmbSong[3] = {
		{3, 0},
		{qRest, 1-1}, //pickup
//		{wRest, 16-1},
		{dmbBDWh, 255},  //one root
//		{dmbBDHa, 255-1} //five roots deep
//		{qRest, 1-1},

	};
#elif (MY_L_CHAN == 12)
	RIFF_T const code dmbSong[3] = {
		{3, 0},
//		{wRest, 255}
		{qRest, 1-1},
		{dmbBDHa, 255}
	};
#elif (MY_L_CHAN == 14)
	RIFF_T const code dmbSong[2] = {
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

//HAPPY		  ---  works with hands.....
#ifdef COORD
	RIFF_T const code happySong[5] = {
		{5,0},
		{happyCoordInit, 1-1},
		{wRestCoord, 255-1},  //for now...;.
		{wRestCoord, 255-1},
		{wRestCoord, 255-1}
	};
#elif (MY_L_CHAN == 0)
	RIFF_T const code happySong[5] = {
		{5,0},
		{wRest, 11-1},
		{happy1, 3-1},
		{happy2, 4-1},
		{happy1, 4-1}
	};
#elif (MY_L_CHAN == 2)
	RIFF_T const code happySong[5] = {
		{5,0},
		{wRest, 11-1},
		{happy2, 3-1},		 //176 beats - 44 bars
		{happy1, 4-1},
		{happy2, 4-1}
	};
#elif (MY_L_CHAN == 4)
	RIFF_T const code happySong[4] = {
		{4,0},
		{happyDrone, 22-1},		 //8*22 = 176 beats	- 44 bars
//		{wRest, 2-1},		   //8 beats
		{happy3, 64-1},	  //160 beats - 5*16 is 80 beats ... ends early
		{happyDroneTx, 255-1}  //
	};
#elif (MY_L_CHAN == 6)
	RIFF_T const code happySong[3] = {
		{3,0},
		{happyDrone, 33-1},		 // 4 * 176
		{happy3, 255-1}
	};
#elif (MY_L_CHAN == 8)
	RIFF_T const code happySong[3] = {
		{3,0},
		{wRest, 33-1},
		{happyDroneTx2, 255-1},
	};
#elif (MY_L_CHAN == 10)
	RIFF_T const code happySong[4] = {
		{4,0},
		{happyDrone, 11-1},		 //88 beats	- 22 bars
		//{wRest, 22-1},		   //88 beats
		{happy3, 32-1},	  //160 beats - 5*16 is 80 beats ... ends early
		{happyDrone, 255-1}  //
	};
#elif (MY_L_CHAN == 12)
	RIFF_T const code happySong[5] = {
		{5,0},
		{wRest, 11-1},
		{happy1, 3-1},
		{happy2, 4-1},
		{happy1, 4-1}
	};
#elif (MY_L_CHAN == 14)
	RIFF_T const code happySong[5] = {
		{5,0},
		{wRest, 11-1},
		{happy2, 3-1},
		{happy1, 4-1},
		{happy2, 4-1}
	};
#endif

////#define TEST_SS1 6+1
//RIFF_T const code testS1[TEST_SS1] = {
//	{TEST_SS1, 0}, //songLen, songNum!!!!  songNum for building of songBook!!!
//	{upR1, 8-1},
//	{upR2, 8-1},
//	{upR3, 8-1},
//	{upR4, 8-1},
//	{upR5, 8-1},
//	{upR1, 8-1}
//};
//
////#define TEST_SS2 6+1
//RIFF_T const code testS2[TEST_SS2] = {
//	{TEST_SS2, 0}, //songLen, songNum!!!!  songNum for building of songBook!!!
//	{downR1, 8-1},
//	{downR2, 8-1},
//	{downR3, 8-1},
//	{downR4, 8-1},
//	{downR5, 8-1},
//	{downR1, 8-1}
//};
//
//RIFF_T const code testSCo1[7] = {
//	{7, 0},
//	{testCo3, 1-1},
//	{testCo1, 15-1},
//	{testCo3, 1-1},
//	{testCo1, 15-1},
//	{testCo3, 1-1},
//	{testCo1, 15-1}
//};
//
//RIFF_T const code testSCo2[3] = {
//	{3, 0},
//	{testCo4, 3-1},
//	{testCo2, 3-1}
//};