#include "riff.h"
#include "midi_spec.h"
#include "itrip.h"

////////utility riffs

unsigned char code sthRest[5] = {
	5,
		0, 255,	//notes off
	6, 127
};

unsigned char code eiRest[5] = {
	5,
		0, 255,	//notes off
	12, 127
};

unsigned char code qRest[5] = {
	5,
		0, 255,	//notes off
	24, 127
};

unsigned char code hRest[5] = {
	5,
		0, 255,	//notes off
	24*2, 127
};

unsigned char code wRest[5] = {
	5,
		0, 255,	//notes off
	24*4, 127
};

//single pitches with switches
unsigned char code minorDrone[5] = {
	5,
#if (MY_L_CHAN == 0)
	0, MINORDRONE_ROOT, 24*4, MINORDRONE_ROOT+0x80
#elif (MY_L_CHAN == 2)
	0, MINORDRONE_ROOT+2, 24*4, MINORDRONE_ROOT+2+0x80
#elif (MY_L_CHAN == 4)
	0, MINORDRONE_ROOT+3, 24*4, MINORDRONE_ROOT+3+0x80
#elif (MY_L_CHAN == 6)
	0, MINORDRONE_ROOT+5, 24*4, MINORDRONE_ROOT+5+0x80
#elif (MY_L_CHAN == 8)
	0, MINORDRONE_ROOT+7, 24*4, MINORDRONE_ROOT+7+0x80
#elif (MY_L_CHAN == 10)
	0, MINORDRONE_ROOT+8, 24*4, MINORDRONE_ROOT+8+0x80
#elif (MY_L_CHAN == 12)
	0, MINORDRONE_ROOT+10, 24*4, MINORDRONE_ROOT+10+0x80
#elif (MY_L_CHAN == 14)
	0, MINORDRONE_ROOT+11, 24*4, MINORDRONE_ROOT+11+0x80
#endif
};

unsigned char code wholeDrone[5] = {
	5,
	0, WHOLEDRONE_ROOT+MY_L_CHAN, 24*4, WHOLEDRONE_ROOT+0x80+MY_L_CHAN
};

//COORD UTILL
unsigned char code sthRestCoord[RECO_S] = {	 //one empty bar
	RECO_S,
	6, NOTE_ON
};

unsigned char code eiRestCoord[RECO_S] = {	 //one empty bar
	RECO_S,
	12, NOTE_ON
};

unsigned char code qRestCoord[RECO_S] = {	 //one empty bar
	RECO_S,
	24, NOTE_ON
};

unsigned char code hRestCoord[RECO_S] = {	 //one empty bar
	RECO_S,
	24*2, NOTE_ON
};

unsigned char code wRestCoord[RECO_S] = {	 //one empty bar
	RECO_S,
	24*4, NOTE_ON
};

unsigned char code wDblRestCoord[RECO_S] = {	 //one empty bar
	RECO_S,
	24*8, NOTE_ON
};

unsigned char code on0Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+0, GENERAL_BUTTON_1_on, 127
};

unsigned char code on2Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+2, GENERAL_BUTTON_1_on, 127
};

unsigned char code on4Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+4, GENERAL_BUTTON_1_on, 127
};

unsigned char code on6Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+6, GENERAL_BUTTON_1_on, 127
};

unsigned char code on8Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+8, GENERAL_BUTTON_1_on, 127
};

unsigned char code on10Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+10, GENERAL_BUTTON_1_on, 127
};

unsigned char code on12Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+12, GENERAL_BUTTON_1_on, 127
};

unsigned char code on14Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+14, GENERAL_BUTTON_1_on, 127
};

unsigned char code off0Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+0, GENERAL_BUTTON_1_on, 0
};

unsigned char code off2Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+2, GENERAL_BUTTON_1_on, 0
};

unsigned char code off4Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+4, GENERAL_BUTTON_1_on, 0
};

unsigned char code off6Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+6, GENERAL_BUTTON_1_on, 0
};

unsigned char code off8Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+8, GENERAL_BUTTON_1_on, 0
};

unsigned char code off10Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+10, GENERAL_BUTTON_1_on, 0
};

unsigned char code off12Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+12, GENERAL_BUTTON_1_on, 0
};

unsigned char code off14Tx[CRTLTX_S] = {
	CRTLTX_S,
	0, CONTROL+14, GENERAL_BUTTON_1_on, 0
};

//shepard station
unsigned char code shepStatCoordInit[5] = {
	5,
	0, TEMPO_SET+((byte)(SHEP_TEMPO>>16)), ((byte)(SHEP_TEMPO>>8)), ((byte)(SHEP_TEMPO))
};

unsigned char code shepStatCoordFasterInit[5] = {
	5,
	0, TEMPO_SET+((byte)(SHEP_FASTER_TEMPO>>16)), ((byte)(SHEP_FASTER_TEMPO>>8)), ((byte)(SHEP_FASTER_TEMPO))
};

unsigned char code shepStatCoordFastInit[5] = {
	5,
	0, TEMPO_SET+((byte)(SHEP_FAST_TEMPO>>16)), ((byte)(SHEP_FAST_TEMPO>>8)), ((byte)(SHEP_FAST_TEMPO))
};

unsigned char code shepStatCoord[33] = {
	33,
	24, CONTROL+0, GENERAL_SLIDER_1_hi, 55,  //92 MHz
	24, CONTROL+2, GENERAL_SLIDER_1_hi, 55,
	24, CONTROL+4, GENERAL_SLIDER_1_hi, 55,  
	24, CONTROL+6, GENERAL_SLIDER_1_hi, 55,
	24, CONTROL+8, GENERAL_SLIDER_1_hi, 55,  
	24, CONTROL+10, GENERAL_SLIDER_1_hi, 55,
	24, CONTROL+12, GENERAL_SLIDER_1_hi, 55,  
	24, CONTROL+14, GENERAL_SLIDER_1_hi, 55
};

unsigned char code shepStat[9] = {
	3,
	24, STATION_DOWN6,
	24, STATION_DOWN6,
	24, STATION_DOWN6,
	24, STATION_DOWN6
};

unsigned char code shepStatVoiced[17] = {
	3,
	12+MY_L_CHAN, STATION_DOWN6,
	12, C5,
	18-MY_L_CHAN, STATION_DOWN6,
	6, A4,
	16, STATION_DOWN6,
	8, E4,
	8, STATION_DOWN6,
	16, A3
};

//peace
unsigned char code peaceCoord[5] = {
	5,
	0, TEMPO_SET+((byte)(PEACE_TEMPO>>16)), ((byte)(PEACE_TEMPO>>8)), ((byte)(PEACE_TEMPO))
};

unsigned char code peaceOne[PEACEONE_S] = {
	PEACEONE_S,
		24, C4,
	24, B4,
	24, B4
};

unsigned char code peaceTwo[PEACEONE_S] = {
	PEACEONE_S,
		24, As4,
	24, G4,
	24, As4
};

unsigned char code peaceThree[PEACEONE_S] = {
	PEACEONE_S,
		24, Gs4,
	24, G4,
	24, Gs4		 
};

unsigned char code peaceAs4[PEACEONE_S] = {
	PEACEONE_S,
		24, As4,
	24, As4,
	24, As4
};

unsigned char code peaceGs4[PEACEONE_S] = {
	PEACEONE_S,
		24, Gs4,
	24, Gs4,
	24, Gs4
};
//4onStat
unsigned char code OnStatCoordInit[5] = {
	5,
	0, TEMPO_SET+((byte)(ONSTAT_TEMPO>>16)), ((byte)(ONSTAT_TEMPO>>8)), ((byte)(ONSTAT_TEMPO))
};

unsigned char code OnStat1[ONSTAT1_S] = {
	ONSTAT1_S,
	60,	STATION_UP4,
		60, STATION_DOWN4,
	60,	STATION_UP4,
		60, STATION_DOWN4,
	60,	STATION_UP4,
		60, STATION_DOWN4,
	45,	STATION_UP4,
		45, STATION_DOWN4,
	45,	STATION_UP4,
		45, STATION_DOWN4,
	45,	STATION_UP4,
		45, STATION_DOWN4,
	45,	STATION_UP4,
		45, STATION_DOWN4
};

unsigned char code OnStat2[ONSTAT2_S] = {
	ONSTAT2_S,
	60,	STATION_UP6,
		60, STATION_DOWN6,
	60,	STATION_UP6,
		60, STATION_DOWN6,
	60,	STATION_UP6,
		60, STATION_DOWN6,
	40,	STATION_UP6,
		40, STATION_DOWN6,
	40,	STATION_UP6,
		40, STATION_DOWN6,
	40,	STATION_UP6,
		40, STATION_DOWN6,
	40,	STATION_UP6,
		40, STATION_DOWN6,
	40, STATION_UP6,
	60,	STATION_DOWN6,
		60, STATION_UP6,
	60,	STATION_DOWN6,
		60, STATION_UP6,
	60,	STATION_DOWN6,
		60, STATION_UP6,
	40,	STATION_DOWN6,
		40, STATION_UP6,
	40,	STATION_DOWN6,
		40, STATION_UP6,
	40,	STATION_DOWN6,
		40, STATION_UP6,
	40,	STATION_DOWN6,
		40, STATION_UP6,
	40, STATION_DOWN6
};

unsigned char code OnStat3[ONSTAT3_S] = {
	ONSTAT3_S,
	5, STATION_DOWN5,
		5, STATION_UP5,
	10, STATION_DOWN5,
		10, STATION_UP5,
		10, STATION_DOWN5,
	15, STATION_UP5,
	20, STATION_DOWN5,
	25, STATION_UP5,
	30, STATION_DOWN5,
	35, STATION_UP5,
	40, STATION_DOWN5,
	45, STATION_UP5,
	50, STATION_DOWN5,
	60, STATION_UP5
};

unsigned char code OnStat4[ONSTAT4_S] = {
	ONSTAT4_S,
	5, STATION_DOWN5,
		5, STATION_UP5,
	10, STATION_DOWN5,
		10, STATION_UP5,
		10, STATION_DOWN5,
	15, STATION_UP5,
	20, STATION_DOWN5,
	25, STATION_UP5,
	30, STATION_DOWN5,
	35, STATION_UP5,
	40, STATION_DOWN5,
	45, STATION_UP5,
	50, STATION_DOWN5,
	60, STATION_UP5
};

unsigned char code OnStatMel1[ONSTATMEL1_S] = {
	ONSTATMEL1_S,
	72-18, Ds2,
	18, UP5,
	0, UPDOWN_OFF,
	0, STATION_UP2,
	72, As2,
	0, STATION_UP2,
	72, Cs2,
	0, STATION_UP2,
	72, As2,
	0, STATION_DOWN2,
	72, Cs2,
	0, STATION_DOWN4
};

unsigned char code OnStatMel2[ONSTATMEL2_S] = {
	ONSTATMEL2_S,
	0, Ds2+0x80,
	72, Ds3,
	0, Cs2+0x80,
	72, Cs3,
	0, C4+0x80,
	72, C4,
	0, As3+0x80,
	72, As3
};

//happy //omes
unsigned char code happyCoordInit[5] = {
	5,
	0, TEMPO_SET+((byte)(HAPPY_TEMPO>>16)), ((byte)(HAPPY_TEMPO>>8)), ((byte)(HAPPY_TEMPO))
};

unsigned char code happy1[HAPPY1_S] = {
	HAPPY1_S,
	9, A3,				//1
		3, NOTE_OFF_MEM,
		9, A3,
		3, NOTE_OFF_MEM,
	9, A3,
		3, NOTE_OFF_MEM,
		9, A3,
		3, NOTE_OFF_MEM,
	9, G3,				//2
		3, NOTE_OFF_MEM,
		9, G3,
		3, NOTE_OFF_MEM,
	9, G3,
		3, NOTE_OFF_MEM,
		9, G3,
		3, NOTE_OFF_MEM,
	9, Fs3,			   //3
		3, NOTE_OFF_MEM,
		9, Fs3,
		3, NOTE_OFF_MEM,
	9, Fs3,
		3, NOTE_OFF_MEM,
		9, Fs3,
		3, NOTE_OFF_MEM,
	9, A3,				 //4
		3, NOTE_OFF_MEM,
		9, A3,
		3, NOTE_OFF_MEM,
	9, A3,
		3, NOTE_OFF_MEM,
		9, A3,
		3, NOTE_OFF_MEM,
	9, G3,				 //5
		3, NOTE_OFF_MEM,
		9, G3,
		3, NOTE_OFF_MEM,
	9, G3,
		3, NOTE_OFF_MEM,
		9, G3,
		3, NOTE_OFF_MEM,
	9, F3,				//6
		3, NOTE_OFF_MEM,
		9, F3,
		3, NOTE_OFF_MEM,
	9, F3,
		3, NOTE_OFF_MEM,
		9, F3,
		3, NOTE_OFF_MEM,
	9, G3,				//7
		3, NOTE_OFF_MEM,
		9, G3,
		3, NOTE_OFF_MEM,
	9, G3,
		3, NOTE_OFF_MEM,
		9, G3,
		3, NOTE_OFF_MEM,
	9, E3,				//8
		3, NOTE_OFF_MEM,
		9, E3,
		3, NOTE_OFF_MEM,
	9, E3,
		3, NOTE_OFF_MEM,
		9, E3,
		3, NOTE_OFF_MEM,
	9, E3,				//9
		3, NOTE_OFF_MEM,
		9, E3,
		3, NOTE_OFF_MEM,
	9, E3,
		3, NOTE_OFF_MEM,
		9, E3,
		3, NOTE_OFF_MEM,
	9, G3,				//10
		3, NOTE_OFF_MEM,
		9, G3,
		3, NOTE_OFF_MEM,
	9, G3,
		3, NOTE_OFF_MEM,
		9, G3,
		3, NOTE_OFF_MEM,
	9, G3,				//11
		3, NOTE_OFF_MEM,
		9, G3,
		3, NOTE_OFF_MEM,
	9, G3,
		3, NOTE_OFF_MEM,
		9, G3,
		3, NOTE_OFF_MEM
};

unsigned char code happy2[HAPPY1_S] = {
	HAPPY1_S,
	9, D3,				//1
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,				//2
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,			   //3
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,				 //4
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,				 //5
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,				//6
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,				//7
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, D3,
		3, NOTE_OFF_MEM,
		9, D3,
		3, NOTE_OFF_MEM,
	9, C3,				//8
		3, NOTE_OFF_MEM,
		9, C3,
		3, NOTE_OFF_MEM,
	9, C3,
		3, NOTE_OFF_MEM,
		9, C3,
		3, NOTE_OFF_MEM,
	9, A2,				//9
		3, NOTE_OFF_MEM,
		9, A2,
		3, NOTE_OFF_MEM,
	9, A2,
		3, NOTE_OFF_MEM,
		9, A2,
		3, NOTE_OFF_MEM,
	9, A2,				//10
		3, NOTE_OFF_MEM,
		9, A2,
		3, NOTE_OFF_MEM,
	9, A2,
		3, NOTE_OFF_MEM,
		9, A2,
		3, NOTE_OFF_MEM,
	9, C3,				//11
		3, NOTE_OFF_MEM,
		9, C3,
		3, NOTE_OFF_MEM,
	9, C3,
		3, NOTE_OFF_MEM,
		9, C3,
		3, NOTE_OFF_MEM
};

//unsigned char code happy12[HAPPY1_S];

unsigned char code happy3[HAPPY3_S] = {	   //5 beats
	HAPPY3_S,
	0, UP3,
	0, 33,
	24, TX_ON,
	0, UP3+0x80,
	24*2, 33+0x80,
	24, UPDOWN_OFF,
	24, UPDOWN_OFF+0x80
};

unsigned char code happyDrone[3] = {
	3,
	24*8, E6
};

unsigned char code happyDroneTx[3] = {
	3,
	24*8, E2 
};

unsigned char code happyDroneTx2[3] = {
	3,
	24*8, E5 
};

////heavy Beats!!!   ???
//#define CLKMULT	8
//unsigned char code beatCoord1[BEATCOORD1_S] = {
//	BEATCOORD1_S,
//	0, TEMPO_SET+((byte)(BEAT1_TEMPO>>16)), ((byte)(BEAT1_TEMPO>>8)), ((byte)(BEAT1_TEMPO)),
//		6*CLKMULT, CONTROL+14, GENERAL_BUTTON_1_on, 0,
//	7*CLKMULT, CONTROL+8, GENERAL_BUTTON_1_on, 0,
//	8*CLKMULT, CONTROL+12, GENERAL_BUTTON_1_on, 0,
//	9*CLKMULT, CONTROL+6, GENERAL_BUTTON_1_on, 0,
//	10*CLKMULT, CONTROL+10,  GENERAL_BUTTON_1_on, 0,
//	11*CLKMULT, CONTROL+4, GENERAL_BUTTON_1_on, 0,
//	12*CLKMULT, CONTROL+2, GENERAL_BUTTON_1_on, 0,
//	13*CLKMULT, CONTROL+0,  GENERAL_BUTTON_1_on, 0,
//		13*CLKMULT, CONTROL, GENERAL_BUTTON_1_on, 127,
//	12*CLKMULT, CONTROL+6, GENERAL_BUTTON_1_on, 127,
//	11*CLKMULT, CONTROL+2, GENERAL_BUTTON_1_on, 127,
//	10*CLKMULT, CONTROL+8, GENERAL_BUTTON_1_on, 127,
//	9*CLKMULT, CONTROL+4,  GENERAL_BUTTON_1_on, 127,
//	8*CLKMULT, CONTROL+10, GENERAL_BUTTON_1_on, 127,
//	7*CLKMULT, CONTROL+12, GENERAL_BUTTON_1_on, 127,
//	6*CLKMULT, CONTROL+14,  GENERAL_BUTTON_1_on, 127
////		6, CONTROL, GENERAL_BUTTON_1_on, 127,
////	7, CONTROL+2, GENERAL_BUTTON_1_on, 127,
////	8, CONTROL+4, GENERAL_BUTTON_1_on, 127,
////	9, CONTROL+6, GENERAL_BUTTON_1_on, 127,
////	10, CONTROL+8,  GENERAL_BUTTON_1_on, 127,
////	11, CONTROL+10, GENERAL_BUTTON_1_on, 127,
////	12, CONTROL+12, GENERAL_BUTTON_1_on, 127,
////	13, CONTROL+14,  GENERAL_BUTTON_1_on, 127,
////		13, CONTROL, GENERAL_BUTTON_1_on, 0,
////	12, CONTROL+2, GENERAL_BUTTON_1_on, 0,
////	11, CONTROL+4, GENERAL_BUTTON_1_on, 0,
////	10, CONTROL+6, GENERAL_BUTTON_1_on, 0,
////	9, CONTROL+8,  GENERAL_BUTTON_1_on, 0,
////	8, CONTROL+10, GENERAL_BUTTON_1_on, 0,
////	7, CONTROL+12, GENERAL_BUTTON_1_on, 0,
////	6, CONTROL+14,  GENERAL_BUTTON_1_on, 0,
//};
//
//unsigned char code beatCoord2[BEATCOORD1_S] = {
//	BEATCOORD1_S,
//	0, TEMPO_SET+((byte)(BEAT2_TEMPO>>16)), ((byte)(BEAT2_TEMPO>>8)), ((byte)(BEAT2_TEMPO)),
//		6*CLKMULT, CONTROL+14, GENERAL_BUTTON_1_on, 127,
//	7*CLKMULT, CONTROL+14, GENERAL_BUTTON_1_on, 0,
//	8*CLKMULT, CONTROL+12, GENERAL_BUTTON_1_on, 127,
//	9*CLKMULT, CONTROL+12, GENERAL_BUTTON_1_on, 0,
//	10*CLKMULT, CONTROL+10,  GENERAL_BUTTON_1_on, 127,
//	11*CLKMULT, CONTROL+10, GENERAL_BUTTON_1_on, 0,
//	12*CLKMULT, CONTROL+8, GENERAL_BUTTON_1_on, 127,
//	13*CLKMULT, CONTROL+8,  GENERAL_BUTTON_1_on, 0,
//		13*CLKMULT, CONTROL+6, GENERAL_BUTTON_1_on, 127,
//	12*CLKMULT, CONTROL+6, GENERAL_BUTTON_1_on, 0,
//	11*CLKMULT, CONTROL+4, GENERAL_BUTTON_1_on, 127,
//	10*CLKMULT, CONTROL+4, GENERAL_BUTTON_1_on, 0,
//	9*CLKMULT, CONTROL+2,  GENERAL_BUTTON_1_on, 127,
//	8*CLKMULT, CONTROL+2, GENERAL_BUTTON_1_on, 0,
//	7*CLKMULT, CONTROL, GENERAL_BUTTON_1_on, 127,
//	6*CLKMULT, CONTROL,  GENERAL_BUTTON_1_on, 0
//};
//
//unsigned char code beat1[BEAT1_S] = {
//	BEAT1_S,
//	24*4, BEAT_ROOT//+((MY_L_CHAN*2))
//};

//Our body
unsigned char code bodyInit[5] = {
	5,
	0, TEMPO_SET+((byte)(BODY_TEMPO>>16)), ((byte)(BODY_TEMPO>>8)), ((byte)(BODY_TEMPO))
};

//driving me backwards!!!!! Vamp on Vcc....
unsigned char code dmbInit[DMBINIT_S] = {	 //tempo... does beat pickup!!! all but 6 off
	DMBINIT_S,
	0, TEMPO_SET+((byte)(DMB_TEMPO>>16)), ((byte)(DMB_TEMPO>>8)), ((byte)(DMB_TEMPO)),
	3, CONTROL, GENERAL_BUTTON_1_on, 0,
	3, CONTROL+2, GENERAL_BUTTON_1_on, 0,
	3, CONTROL+4, GENERAL_BUTTON_1_on, 0,
	3, CONTROL+6, GENERAL_BUTTON_1_on, 127, //only 7 on at first...
	3, CONTROL+8,  GENERAL_BUTTON_1_on, 0,
	3, CONTROL+10, GENERAL_BUTTON_1_on, 0,
	3, CONTROL+12, GENERAL_BUTTON_1_on, 0,
	3, CONTROL+14,  GENERAL_BUTTON_1_on, 0  
};

unsigned char code dmbVamp0[DMBVAMP_S] = {
	DMBVAMP_S,
	12, 255,	 //silent on down beat
	12, DMB_PEDAL+0x80
};

unsigned char code dmbVamp1[DMBVAMP_S] = {
	DMBVAMP_S,
	12,	DMB_ROOT+0x80,
	12, DMB_PEDAL+0x80
};

unsigned char code dmbRoot0[DMBROOT_S] = {
	DMBROOT_S,
		0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, 255, 12, 127,
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, 255, 12, 127,
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, 255, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, 255, 12, 127, 
		0, DMB_ROOT+12, 12, DMB_ROOT+7+0x80,
	0, 255, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+7+0x80,
	0, 255, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+7+0x80,
	0, 255, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+7+0x80,
	0, 255, 12, 127, 
		0, DMB_ROOT+12, 12, DMB_ROOT+9+0x80,
	0, 255, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+9+0x80,
	0, 255, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+9+0x80,
	0, 255, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+9+0x80,
	0, 255, 12, 127, 
		0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, 255, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, 255, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, 255, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, 255, 12, 127 
};

unsigned char code dmbRoot1[DMBROOT_S] = {
	DMBROOT_S,
		0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, DMB_PEDAL+0x80, 12, 127,
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, DMB_PEDAL+0x80, 12, 127,
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
		0, DMB_ROOT+12, 12, DMB_ROOT+7+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+7+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+7+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+7+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
		0, DMB_ROOT+12, 12, DMB_ROOT+9+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+9+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+9+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+9+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
		0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, DMB_PEDAL+0x80, 12, 127, 
	0, DMB_ROOT+12, 12, DMB_ROOT+8+0x80,
	0, DMB_PEDAL+0x80, 12, 127 
};

unsigned char code dmbBDHa[DMBBD_S] = {  //hit plus halfRest
	DMBBD_S,
	1, DMB_ROOT+7,
	1, DMB_ROOT-12,
	46, 127
};

unsigned char code dmbBDWh[DMBBD_S] = {  //hit plus wholeRest
	DMBBD_S,
	1, DMB_ROOT+7,
	1, DMB_ROOT-12,
	94, 127
};

///BUSY
unsigned char code busyInit[5] = {
	5,
	0, TEMPO_SET+((byte)(BUSY_TEMPO>>16)), ((byte)(BUSY_TEMPO>>8)), ((byte)(BUSY_TEMPO))
};

unsigned char code busySlower1[5] = {
	5,
	0, TEMPO_SET+((byte)(BUSY_TEMPO1>>16)), ((byte)(BUSY_TEMPO1>>8)), ((byte)(BUSY_TEMPO1))
};

unsigned char code busySlower2[5] = {
	5,
	0, TEMPO_SET+((byte)(BUSY_TEMPO2>>16)), ((byte)(BUSY_TEMPO2>>8)), ((byte)(BUSY_TEMPO2))
};

unsigned char code busySlower3[5] = {
	5,
	0, TEMPO_SET+((byte)(BUSY_TEMPO3>>16)), ((byte)(BUSY_TEMPO3>>8)), ((byte)(BUSY_TEMPO3))
};

unsigned char code busySlower4[5] = {
	5,
	0, TEMPO_SET+((byte)(BUSY_TEMPO4>>16)), ((byte)(BUSY_TEMPO4>>8)), ((byte)(BUSY_TEMPO4))
};

unsigned char code busy1[BUSY1_SIZE] = {
	BUSY1_SIZE,
		0, DOWN2+0x80,
	16*3, 36,
	18*3, 43+0x80,
	20*3, 49,
	24*3, 50+0x80,
	22, NOTE_OFF_MEM+0x80  		//256
};

unsigned char code busy1a[BUSY1_SIZE] = {
	BUSY1_SIZE,
		0, DOWN2+0x80,
	16*3, 36,
	18*3, 43+0x80,
	20*3, 49,
	24*3, 50+0x80,
	22, NOTE_OFF_MEM+0x80  		//256
};

unsigned char code busy1Stat[BUSY1_SIZE] = {
	BUSY1_SIZE,
		0, DOWN2+0x80,
	16*3, 36,
	18*3, 43+0x80,
	20*3, 49,
	24*3, 50+0x80,
	22, NOTE_OFF_MEM+0x80  		//256
};

unsigned char code busy2[BUSY1_SIZE-2] = {
	BUSY1_SIZE-2,
	16*3, 36,
	18*3, 43+0x80,
	20*3, 49,
	24*3, 50+0x80,
	22, NOTE_OFF_MEM+0x80  		//256
};

unsigned char code busy2a[BUSY1_SIZE-2] = {
	BUSY1_SIZE-2,
	16*3, 36,
	18*3, 43+0x80,
	20*3, 49,
	24*3, 50+0x80,
	22, NOTE_OFF_MEM+0x80  		//256
};

unsigned char code busy2Stat[BUSY2STAT_SIZE] = {
	BUSY2STAT_SIZE,
	8, 36,
	16, STATION_UP2,
	16, STATION_UP2,
	8, STATION_DOWN4,
	9, STATION_DOWN2,
	18, STATION_DOWN2,
	18, STATION_DOWN2,
	9, STATION_UP6,
	30, 24,
	30, STATION_UP2,
	24, 24+0x80,
	24, STATION_DOWN2,
	24, NOTE_OFF_MEM,
	22, NOTE_OFF_MEM+0x80  		//256
};
//vexations 12 beats to a quarter
unsigned char code vex1[VEX_S] = {
	VEX_S,
		12, 60 + VEX_SHIFT,
	6,  57 + VEX_SHIFT,
	6,  61 + VEX_SHIFT,
	12,	58 + VEX_SHIFT,
	12,	63 + VEX_SHIFT,
	6,	55 + VEX_SHIFT,
	6,	62 + VEX_SHIFT,
	6,	60 + VEX_SHIFT,
	6,	63 + VEX_SHIFT,
	12,	54 + VEX_SHIFT,
	12,	61 + VEX_SHIFT,
	6,	53 + VEX_SHIFT,
	6,	58 + VEX_SHIFT,
	6,	54 + VEX_SHIFT,
	6,	63 + VEX_SHIFT,
	12,	59 + VEX_SHIFT,
	6,	64 + VEX_SHIFT,
	12,	64 + VEX_SHIFT,
	6, NOTE_OFF_MEM
};
unsigned char code vex2[VEX_S] = {
	VEX_S,
		12, 69 + VEX_SHIFT,
	6,	73 + VEX_SHIFT,
	6,	70 + VEX_SHIFT,
	12,	73 + VEX_SHIFT,
	12,	72 + VEX_SHIFT,
	6,	70 + VEX_SHIFT,
	6,	71 + VEX_SHIFT,
	6,	75 + VEX_SHIFT,
	6,	72 + VEX_SHIFT,
	12,	69 + VEX_SHIFT,
	12,	70 + VEX_SHIFT,
	6,	69 + VEX_SHIFT,
	6,	68 + VEX_SHIFT,
	6,	69 + VEX_SHIFT,
	6,	72 + VEX_SHIFT,
	12,	74 + VEX_SHIFT,
	6,	73 + VEX_SHIFT,
	12,	73 + VEX_SHIFT,
	6, NOTE_OFF_MEM
};
unsigned char code vex3[VEX_S] = {
	VEX_S,
		12, 63 + 12 + VEX_SHIFT,
	6,  65 + 12 + VEX_SHIFT,
	6,  64 + 12 + VEX_SHIFT,
	12,	67 + 12 + VEX_SHIFT,
	12,	66 + 12 + VEX_SHIFT,
	6,	64 + 12 + VEX_SHIFT,
	6,	65 + 12 + VEX_SHIFT,
	6,	70 + 12 + VEX_SHIFT,
	6,	66 + 12 + VEX_SHIFT,
	12,	63 + 12 + VEX_SHIFT,
	12,	64 + 12 + VEX_SHIFT,
	6,	63 + 12 + VEX_SHIFT,
	6,	62 + 12 + VEX_SHIFT,
	6,	63 + 12 + VEX_SHIFT,
	6,	66 + 12 + VEX_SHIFT,
	12,	68 + 12 + VEX_SHIFT,
	6,	67 + 12 + VEX_SHIFT,
	12,	67 + 12 + VEX_SHIFT,
	6, NOTE_OFF_MEM
};
unsigned char code vex3vb[VEX_S] = {
	VEX_S,
		12, 63 + VEX_SHIFT,
	6,  65 + VEX_SHIFT,
	6,  64 + VEX_SHIFT,
	12,	67 + VEX_SHIFT,
	12,	66 + VEX_SHIFT,
	6,	64 + VEX_SHIFT,
	6,	65 + VEX_SHIFT,
	6,	70 + VEX_SHIFT,
	6,	66 + VEX_SHIFT,
	12,	63 + VEX_SHIFT,
	12,	64 + VEX_SHIFT,
	6,	63 + VEX_SHIFT,
	6,	62 + VEX_SHIFT,
	6,	63 + VEX_SHIFT,
	6,	66 + VEX_SHIFT,
	12,	68 + VEX_SHIFT,
	6,	67 + VEX_SHIFT,
	12,	67 + VEX_SHIFT,
	6, NOTE_OFF_MEM
};
//unsigned char code stereoTest1[9] = {
//	9,
//	24, 36,
//	24, STEREO_TOG_MEM,
//	24, NOTE_OFF_MEM,
//	24, STEREO_TOG_MEM
//};
//unsigned char code busy1[BUSY1_SIZE] = {
//	BUSY1_SIZE,
//		0, DOWN3+0x80,
//	24*10, 46+0x80,
//	24, UPDOWN_OFF+0x80,
//		24*10, NOTE_OFF_MEM+0x80,
//	24, NOTE_OFF_MEM+0x80 
//};

//unsigned char code busy2[BUSY1_SIZE] = {
//	BUSY1_SIZE,
//		0, DOWN3+0x80,
//	24*6, 46+0x80,
//	24, UPDOWN_OFF+0x80,
//		0, DOWN4+0x80,
//	24*10, 53+0x80,
//	24, UPDOWN_OFF+0x80,
//		0, DOWN4+0x80,
//	24*10, 59+0x80,
//	24, UPDOWN_OFF+0x80,
//		0, DOWN4+0x80,
//	24*10, 60+0x80,
//	24, UPDOWN_OFF+0x80,
//		24*10, NOTE_OFF_MEM+0x80,
//	24, NOTE_OFF_MEM+0x80 
//};
//
//unsigned char code busy3[BUSY1_SIZE] = {
//	BUSY1_SIZE,
//		0, DOWN3+0x80,
//	24*6, 46+0x80,
//	24, UPDOWN_OFF+0x80,
//		0, DOWN4+0x80,
//	24*10, 53+0x80,
//	24, UPDOWN_OFF+0x80,
//		0, DOWN4+0x80,
//	24*10, 59+0x80,
//	24, UPDOWN_OFF+0x80,
//		0, DOWN4+0x80,
//	24*10, 60+0x80,
//	24, UPDOWN_OFF+0x80,
//		24*10, NOTE_OFF_MEM+0x80,
//	24, NOTE_OFF_MEM+0x80 
//};
////////////////// TEST_Riffs
//byte code testCo1[3] = {
//	3,
//	24*5, NOTE_ON	
//};
//
//byte code testCo1b[7] = {
//	5,
//	24*5, NOTE_ON,
////	0, SONG_POSITION, 0x70, 0x01, //LSB first
//	24*5, START	
//};
//
//byte code testCo2[9] = {
//	9,
//	24*5, TEMPO_SET, 0x96, 0xb4, //240bpm??
//	24*5, TEMPO_SET+0x0F, 0xFF, 0xFF //slow as possible	
//};
//
//byte code testCo3[69] = {
//	69,
//	0, TEMPO_SET + 1, 0x2d, 0x68, //120bpm = 0x12D68
//	0, CONTROL, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+2, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+2, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+4, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+4, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+6, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+6, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+8, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+8, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+10, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+10, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+12, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+12, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+14, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+14, GENERAL_SLIDER_1_lo, STATION_TO_LO(879)
//};		   
//
//byte code testCo3b[69] = {
//	69,
//	0, TEMPO_SET, 0x4b, 0x5a, //480bpm = 0x4b5a?
//	0, CONTROL, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+2, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+2, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+4, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+4, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+6, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+6, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+8, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+8, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+10, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+10, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+12, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+12, GENERAL_SLIDER_1_lo, STATION_TO_LO(879),
//	0, CONTROL+14, GENERAL_SLIDER_1_hi, STATION_TO_HI(879),
//	0, CONTROL+14, GENERAL_SLIDER_1_lo, STATION_TO_LO(879)
//};
//
//byte code testCo3c[69] = {
//	69,
//	0, TEMPO_SET, 0x96, 0xb4, //240bpm
//	0, CONTROL, GENERAL_SLIDER_1_hi, STATION_TO_HI(1001),
//	0, CONTROL, GENERAL_SLIDER_1_lo, STATION_TO_LO(1001),
//	0, CONTROL+2, GENERAL_SLIDER_1_hi, STATION_TO_HI(1001),
//	0, CONTROL+2, GENERAL_SLIDER_1_lo, STATION_TO_LO(1001),
//	0, CONTROL+4, GENERAL_SLIDER_1_hi, STATION_TO_HI(1001),
//	0, CONTROL+4, GENERAL_SLIDER_1_lo, STATION_TO_LO(1001),
//	0, CONTROL+6, GENERAL_SLIDER_1_hi, STATION_TO_HI(1001),
//	0, CONTROL+6, GENERAL_SLIDER_1_lo, STATION_TO_LO(1001),
//	0, CONTROL+8, GENERAL_SLIDER_1_hi, STATION_TO_HI(1001),
//	0, CONTROL+8, GENERAL_SLIDER_1_lo, STATION_TO_LO(1001),
//	0, CONTROL+10, GENERAL_SLIDER_1_hi, STATION_TO_HI(1001),
//	0, CONTROL+10, GENERAL_SLIDER_1_lo, STATION_TO_LO(1001),
//	0, CONTROL+12, GENERAL_SLIDER_1_hi, STATION_TO_HI(1001),
//	0, CONTROL+12, GENERAL_SLIDER_1_lo, STATION_TO_LO(1001),
//	0, CONTROL+14, GENERAL_SLIDER_1_hi, STATION_TO_HI(1001),
//	0, CONTROL+14, GENERAL_SLIDER_1_lo, STATION_TO_LO(1001)
//};		   
//byte code testCo4[69] = {
//	69,
//	0, TEMPO_SET, 0x96, 0xb4, //240bpm??
//	0, CONTROL, GENERAL_BUTTON_1_on, 0,
//	0, CONTROL+2, GENERAL_BUTTON_1_on, 0,
//	0, CONTROL+4, GENERAL_BUTTON_1_on, 0,
//	0, CONTROL+6, GENERAL_BUTTON_1_on, 0,
//	0, CONTROL+8,  GENERAL_BUTTON_1_on, 0,
//	0, CONTROL+10, GENERAL_BUTTON_1_on, 0,
//	0, CONTROL+12, GENERAL_BUTTON_1_on, 0,
//	24*5, CONTROL+14,  GENERAL_BUTTON_1_on, 0,
//	0, CONTROL, GENERAL_BUTTON_1_on, 127,
//	0, CONTROL+2, GENERAL_BUTTON_1_on, 127,
//	0, CONTROL+4, GENERAL_BUTTON_1_on, 127,
//	0, CONTROL+6, GENERAL_BUTTON_1_on, 127,
//	0, CONTROL+8,  GENERAL_BUTTON_1_on, 127,
//	0, CONTROL+10, GENERAL_BUTTON_1_on, 127,
//	0, CONTROL+12, GENERAL_BUTTON_1_on, 127,
//	24*5, CONTROL+14,  GENERAL_BUTTON_1_on, 127
//};
//
//byte code downR1[14+1] = {
//	14,
//	0, DOWN1,
//	0, 33,
//	0, UP1+0x80,
//	0, 33+0x80,
//	24*2, TX_ON,
//	24*2, UPDOWN_OFF+0x80,
//	24, UPDOWN_OFF
//};
//
//byte code downR2[TEST_LEN+1] = {
//	TEST_LEN,
//	0, DOWN2,
//	0, 33,
//	24*2, TX_ON,
//	24*2, TX_OFF,
//	24, UPDOWN_OFF
//};
//
//byte code downR3[TEST_LEN+1] = {
//	TEST_LEN,
//	0, DOWN3,
//	0, 33,
//	24*2, TX_ON,
//	24*2, TX_OFF,
//	24, UPDOWN_OFF
//};
//
//byte code downR4[TEST_LEN+1] = {
//	TEST_LEN,
//	0, DOWN4+0x80,
//	0, 36+0x80,
//	24*2, TX_ON,
//	24*2, NOTE_OFF_MEM+0x80,
//	24, UPDOWN_OFF+0x80
//};
//
//byte code downR5[TEST_LEN+1] = {
//	TEST_LEN,
//	0, DOWN5,
//	0, 33+0x80,
//	24*2, TX_ON,
//	24*2, NOTE_OFF_MEM+0x80,
//	24, UPDOWN_OFF
//};
//
//byte code upR1[TEST_LEN+1] = {
//	TEST_LEN,
//	0, UP1+0x80,
//	0, 55+0x80,
//	24*2, TX_ON,
//	24*2, TX_OFF,
//	24, UPDOWN_OFF+0x80
//};
//
//byte code upR2[TEST_LEN+1] = {
//	TEST_LEN,
//	0, UP2,
//	0, 33,
//	0, 33+0x80,
//	24*4, TX_ON,
//	24, UPDOWN_OFF
//};
//
//byte code upR3[14+1] = {
//	14,
//	0, UP3,
//	0, 33,
//	24, TX_ON,
//	0, UP3+0x80,
//	24*2, 33+0x80,
//	24, UPDOWN_OFF,
//	24, UPDOWN_OFF+0x80
//};
//
//byte code upR4[16+1] = {
//	16,
//	0, UP4,
//	0, 90,
//	0, UP4+0x80,
//	0, 90+0x80,
//	24*2, TX_ON,
//	24*2, TX_OFF,
//	0, UPDOWN_OFF+0x80,
//	24, UPDOWN_OFF
//};
//
//byte code upR5[16+1] = {
//	16,
//	0, UP5,
//	0, 33,
//	0, UP3+0x80,
//	0, 33+0x80,
//	24*2, TX_ON,
//	24*2, TX_OFF,
//	0, UPDOWN_OFF+0x80,
//	24, UPDOWN_OFF
//};