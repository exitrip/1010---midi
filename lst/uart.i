
#line 1 "uart.c" /0
  
#line 1 "C:\KEIL\C51\INC\PHILIPS\REG936.H" /0







 
 
 
 
 
 
 sfr P0   = 0x80;
 sfr P1   = 0x90;
 sfr P2   = 0xA0;
 sfr P3   = 0xB0;
 sfr PSW  = 0xD0;
 sfr ACC  = 0xE0;
 sfr B    = 0xF0;
 sfr SP   = 0x81;
 sfr DPL  = 0x82;
 sfr DPH  = 0x83;
 sfr PCON = 0x87;
 sfr TCON = 0x88;
 sfr TMOD = 0x89;
 sfr TL0  = 0x8A;
 sfr TL1  = 0x8B;
 sfr TH0  = 0x8C;
 sfr TH1  = 0x8D;
 sfr IEN0 = 0xA8;
 sfr IP0  = 0xB8;
 sfr SCON = 0x98;
 sfr SBUF = 0x99;
 
 sfr ADCON0 = 0x8E;
 sfr ADCON1 = 0x97;
 sfr ADMODA = 0xC0;
 sfr ADMODB = 0xA1;
 sfr ADINS  = 0xA3;
 sfr AD0DAT0= 0xC5;
 sfr AD0DAT1= 0xC6;
 sfr AD0DAT2= 0xC7;
 sfr AD0DAT3= 0xF4;
 sfr AD1DAT0= 0xD5;
 sfr AD1DAT1= 0xD6;
 sfr AD1DAT2= 0xD7;
 sfr AD1DAT3= 0xF5;
 sfr AD0BH  = 0xBB;
 sfr AD0BL  = 0xA6;
 sfr AD1BH  = 0xC4;
 sfr AD1BL  = 0xBC;
 sfr AUXR1  = 0xA2;
 sfr SADDR  = 0xA9;
 sfr SADEN  = 0xB9;
 sfr TL2    = 0xCC;
 sfr TH2    = 0xCD;
 sfr BRGR0  = 0xBE;
 sfr BRGR1  = 0xBF;
 sfr BRGCON = 0xBD;
 sfr CCCRA  = 0xEA;
 sfr CCCRB  = 0xEB;
 sfr CCCRC  = 0xEC;
 sfr CCCRD  = 0xED;
 sfr CMP1   = 0xAC;
 sfr CMP2   = 0xAD;
 sfr DEECON = 0xF1;
 sfr DEEDAT = 0xF2;
 sfr DEEADR = 0xF3;
 sfr DIVM   = 0x95;
 sfr I2ADR  = 0xDB;
 sfr I2CON  = 0xD8;
 sfr I2DAT  = 0xDA;
 sfr I2SCLH = 0xDD;
 sfr I2SCLL = 0xDC;
 sfr I2STAT = 0xD9;
 sfr ICRAH  = 0xAB;
 sfr ICRAL  = 0xAA;
 sfr ICRBH  = 0xAF;
 sfr ICRBL  = 0xAE;
 sfr IEN1   = 0xE8;
 sfr IP1    = 0xF8;
 sfr IP1H   = 0xF7;
 sfr KBCON  = 0x94;
 sfr KBMASK = 0x86;
 sfr KBPATN = 0x93;
 sfr OCRAH  = 0xEF;
 sfr OCRAL  = 0xEE;
 sfr OCRBH  = 0xFB;
 sfr OCRBL  = 0xFA;
 sfr OCRCH  = 0xFD;
 sfr OCRCL  = 0xFC;
 sfr OCRDH  = 0xFF;
 sfr OCRDL  = 0xFE;
 sfr P0M1   = 0x84;
 sfr P0M2   = 0x85;
 sfr P1M1   = 0x91;
 sfr P1M2   = 0x92;
 sfr P2M1   = 0xA4;
 sfr P2M2   = 0xA5;
 sfr P3M1   = 0xB1;
 sfr P3M2   = 0xB2;
 sfr PCONA  = 0xB5;
 sfr PT0AD  = 0xF6;
 sfr RSTSRC = 0xDF;
 sfr RTCCON = 0xD1;
 sfr RTCH   = 0xD2;
 sfr RTCL   = 0xD3;
 sfr SSTAT  = 0xBA;
 sfr SPCTL  = 0xE2;
 sfr SPSTAT = 0xE1;
 sfr SPDAT  = 0xE3;
 sfr TAMOD  = 0x8F;
 sfr TCR20  = 0xC8;
 sfr TCR21  = 0xF9;
 sfr TICR2  = 0xC9;
 sfr TIFR2  = 0xE9;
 sfr TISE2  = 0xDE;
 sfr TOR2H  = 0xCF;
 sfr TOR2L  = 0xCE;
 sfr TPCR2H = 0xCB;
 sfr TPCR2L = 0xCA;
 sfr TRIM   = 0x96;
 sfr WDCON  = 0xA7;
 sfr WDL    = 0xC1;
 sfr WFEED1 = 0xC2;
 sfr WFEED2 = 0xC3;
 sfr IP0H   = 0xB7;
 
 
 
 
 
 
 
 
 
 
 
 
 
 sbit CY   = PSW^7;
 sbit AC   = PSW^6;
 sbit F0   = PSW^5;
 sbit RS1  = PSW^4;
 sbit RS0  = PSW^3;
 sbit OV   = PSW^2;		   
 sbit F1   = PSW^1;
 sbit P    = PSW^0;
 
 
 sbit TF1  = TCON^7;
 sbit TR1  = TCON^6;
 sbit TF0  = TCON^5;
 sbit TR0  = TCON^4;
 sbit IE1  = TCON^3;
 sbit IT1  = TCON^2;
 sbit IE0  = TCON^1;
 sbit IT0  = TCON^0;
 
 
 sbit EA   = IEN0^7;
 sbit EWDRT = IEN0^6;
 sbit EBO   = IEN0^5;
 sbit ES   = IEN0^4;  
 sbit ESR  = IEN0^4;
 sbit ET1  = IEN0^3;
 sbit EX1  = IEN0^2;
 sbit ET0  = IEN0^1;
 sbit EX0  = IEN0^0;
 
 
 sbit EAD  = IEN1^7;  
 sbit EIEE = IEN1^7;
 sbit EST  = IEN1^6;
 sbit ECCU = IEN1^4;
 sbit ESPI = IEN1^3;
 sbit EC   = IEN1^2;
 sbit EKBI = IEN1^1;
 sbit EI2C = IEN1^0;
 
 
 sbit PWDRT = IP0^6;
 sbit PB0   = IP0^5;
 sbit PS    = IP0^4;  
 sbit PSR   = IP0^4;
 sbit PT1   = IP0^3;
 sbit PX1   = IP0^2;
 sbit PT0   = IP0^1;
 sbit PX0   = IP0^0;
 
 
 sbit PAD  = IP1^7;  
 sbit PIEE = IP1^7;
 sbit PST  = IP1^6;
 sbit PCCU = IP1^4;
 sbit PSPI = IP1^3;
 sbit PC_  = IP1^2;
 sbit PKBI = IP1^1;
 sbit PI2C = IP1^0;
 
 
 sbit SM0  = SCON^7;  
 sbit FE   = SCON^7;
 sbit SM1  = SCON^6;
 sbit SM2  = SCON^5;
 sbit REN  = SCON^4;
 sbit TB8  = SCON^3;
 sbit RB8  = SCON^2;
 sbit TI   = SCON^1;
 sbit RI   = SCON^0;
 
 
 sbit I2EN  = I2CON^6;
 sbit STA   = I2CON^5;
 sbit STO   = I2CON^4;
 sbit SI    = I2CON^3;
 sbit AA    = I2CON^2;
 sbit CRSEL = I2CON^0;
 
 
 sbit KB7 = P0^7;  
 sbit T1 = P0^7;
 sbit KB6 = P0^6;  
 
 sbit KB5 = P0^5;
 sbit KB4 = P0^4;
 sbit KB3 = P0^3;
 sbit KB2 = P0^2;
 sbit KB1 = P0^1;
 sbit KB0 = P0^0;  
 
 
 
 sbit OCC     = P1^7;
 sbit OCB     = P1^6;
 sbit RST     = P1^5;
 sbit INT1    = P1^4;
 sbit INT0    = P1^3;  
 sbit SDA     = P1^3;
 sbit T0      = P1^2;  
 sbit SCL     = P1^2;
 sbit RxD     = P1^1;
 sbit TxD     = P1^0;
 
 
 sbit ICA     = P2^7;
 sbit OCA     = P2^6;
 sbit SPICLK  = P2^5;
 sbit SS      = P2^4;
 sbit MISO    = P2^3;
 sbit MOSI    = P2^2;
 sbit OCD     = P2^1;
 sbit ICB     = P2^0;
 
 
 sbit XTAL1= P3^1;
 sbit XTAL2= P3^0;
 
 
 sbit PLLEN = TCR20^7;
 sbit HLTRN = TCR20^6;
 sbit HLTEN = TCR20^5;
 sbit ALTCD = TCR20^4;
 sbit ALTAB = TCR20^3;
 sbit TDIR2 = TCR20^2;
 sbit TMOD21= TCR20^1;
 sbit TMOD20= TCR20^0;
 
 
 sbit BNDI1  = ADMODA^7;
 sbit BURST1 = ADMODA^6;
 sbit SCC1   = ADMODA^5;
 sbit SCAN1  = ADMODA^4;
 sbit BNDI0  = ADMODA^3;
 sbit BURST0 = ADMODA^2;
 sbit SCC0   = ADMODA^1;
 sbit SCAN0  = ADMODA^0;
 
 
 
#line 1 "uart.c" /0
 
  
#line 1 "C:\KEIL\C51\INC\LIMITS.H" /0






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 2 "uart.c" /0
 
  
#line 1 "C:\KEIL\C51\INC\MATH.H" /0






 
 
 
 
 
 #pragma SAVE
 #pragma REGPARMS
 extern char  cabs  (char  val);
 extern int    abs  (int   val);
 extern long  labs  (long  val);
 extern float fabs  (float val);
 extern float sqrt  (float val);
 extern float exp   (float val);
 extern float log   (float val);
 extern float log10 (float val);
 extern float sin   (float val);
 extern float cos   (float val);
 extern float tan   (float val);
 extern float asin  (float val);
 extern float acos  (float val);
 extern float atan  (float val);
 extern float sinh  (float val);
 extern float cosh  (float val);
 extern float tanh  (float val);
 extern float atan2 (float y, float x);
 
 extern float ceil  (float val);
 extern float floor (float val);
 extern float modf  (float val, float *n);
 extern float fmod  (float x, float y);
 extern float pow   (float x, float y);
 
 #pragma RESTORE
 
 
#line 3 "uart.c" /0
 
  
#line 1 "itrip.h" /0


 
 
 
 
 
  
#line 1 "C:\KEIL\C51\INC\PHILIPS\REG936.H" /0







 
 
 
#line 11 "C:\KEIL\C51\INC\PHILIPS\REG936.H" /1
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 281 "C:\KEIL\C51\INC\PHILIPS\REG936.H" /0
 
#line 8 "itrip.h" /0
 
 
 
 typedef unsigned char byte;
 typedef unsigned int word;  
 
 
 
 typedef struct Riff_s {
 word rAddy;  
 byte repeats;
 } RIFF_T;
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 enum {
 TX_OFF = 0,	 
 TX_ON = 1,   
 UPDOWN_OFF = 2,
 STATION_UP = 3,
 STATION_DOWN = 4,
 DOWN1 = 5,   
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
 STATION_UP2 = 115,			 
 STATION_DOWN2 = 116,			  
 STATION_UP3 = 117,
 STATION_DOWN3 = 118,					   
 STATION_UP4 = 119,							   
 STATION_DOWN4 = 120,							   
 STATION_UP5 = 121,	 
 STATION_DOWN5 = 122,	  
 STATION_UP6 = 123,			  
 STATION_DOWN6 = 124,				   
 HOLD1 = 125,
 HOLD2 = 126,
 NOTE_OFF_MEM = 127
 };
 
 
 
 extern volatile byte songNum;  
 extern volatile word midiClk;
 extern volatile byte xdata sysEx[512];
 extern volatile byte sysIx;
 
 extern volatile RIFF_T* curSong;
 extern volatile word nextRiff;
 extern volatile byte curRiffCnt;
 extern volatile word numRiffs;
 extern volatile byte code* riff;
 extern volatile word deltaPos;
 extern volatile byte numNotes;
 extern volatile byte nextNote;
 
 extern volatile byte bdata midiFlags;
 
 extern bit AUDIO_L_ON;	
 extern bit TX_VCC_ON; 	
 extern bit STEREO;		
 extern bit PLAYING;		
 extern bit BUTT_EN;		
 extern bit OMNI;		
 extern bit SONG_DONE;	
 
 
 extern volatile byte periodH0;
 extern volatile byte periodL0;
 extern volatile byte periodH1;
 extern volatile byte periodL1;
 extern volatile word lDelta;    
 extern volatile word txDelta;
 extern volatile bit deltaLUp;
 extern volatile bit deltaTxUp;
 
 
 
 extern volatile bit txOffSwitch;
 extern word station;
 
 
 void setup ();   
 void delay (word cnt);
 void shiftout8 (byte d);
 
 
 void txProg ();
 void setFreq (word freq);
 void delayT (word t);
 void updateNote(void);
 
 
 
 
 sbit txVcc = P2^7;
 sbit txData = P2^2;
 sbit txClk = P2^3;
 sbit LED = P2^5;
 sbit CE = P2^4;
 sbit midButt = P0^0;
 sbit hiButt = P0^1;
 sbit loButt = P0^2;
 sbit audioL = P0^3;
 sbit audioN = P0^4; 	 
 
 
#line 4 "uart.c" /0
 
  
#line 1 "uart.h" /0
 
 
 
 
 
 
 
 typedef struct m_in_s {
 unsigned char
 typeChan,           
 
 count,          
 controller,     
 pitch;          
 
 
 
 
 unsigned short
 position;       
 } m_in_t;
 
 
 void uart_transmit (unsigned char value);
 unsigned char uart_get (void);
 void uart_init (void);
 unsigned char ascii_to_hex(unsigned char ch);
 void print_hex_to_ascii(unsigned char ch);
 
#line 5 "uart.c" /0
 
  
#line 1 "midi_spec.h" /0




 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 enum
 
 {
 
 C0, Cs0, D0, Ds0, E0, Fm0, Fs0, G0, Gs0, A0, As0, B0,
 
 C1, Cs1, D1, Ds1, E1, Fm1, Fs1, G1, Gs1, A1, As1, B1,
 
 C2, Cs2, D2, Ds2, E2, F2, Fs2, G2, Gs2, A2, As2, B2,
 
 C3, Cs3, D3, Ds3, E3, F3, Fs3, G3, Gs3, A3, As3, B3,
 
 C4, Cs4, D4, Ds4, E4, F4, Fs4, G4, Gs4, A4, As4, B4,
 
 C5, Cs5, D5, Ds5, E5, F5, Fs5, G5, Gs5, A5, As5, B5,
 
 C6, Cs6, D6, Ds6, E6, F6, Fs6, G6, Gs6, A6, As6, B6,
 
 C7, Cs7, D7, Ds7, E7, F7, Fs7, G7, Gs7, A7, As7, B7,
 
 C8, Cs8, D8, Ds8, E8, F8, Fs8, G8, Gs8, A8, As8, B8,
 
 C9, Cs9, D9, Ds9, E9, F9, Fs9, G9, Gs9, A9, As9, B9,
 
 C10,Cs10,D10,Ds10,E10,F10,Fs10,NOTE_OFF, NUM_NOTES
 
 };
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 6 "uart.c" /0
 
  
#line 1 "LUTFreq.h" /0
 
 
 
 
 
 
 
 
 extern const unsigned int code LUTFreq[(99)];
 
 
#line 7 "uart.c" /0
 
  
#line 1 "C:\KEIL\C51\INC\INTRINS.H" /0






 
 
 
 
 
 extern void          _nop_     (void);
 extern bit           _testbit_ (bit);
 extern unsigned char _cror_    (unsigned char, unsigned char);
 extern unsigned int  _iror_    (unsigned int,  unsigned char);
 extern unsigned long _lror_    (unsigned long, unsigned char);
 extern unsigned char _crol_    (unsigned char, unsigned char);
 extern unsigned int  _irol_    (unsigned int,  unsigned char);
 extern unsigned long _lrol_    (unsigned long, unsigned char);
 extern unsigned char _chkfloat_(float);
 extern void          _push_    (unsigned char _sfr);
 extern void          _pop_     (unsigned char _sfr);
 
 
 
#line 8 "uart.c" /0
 
 
 
 static bit mtxbusy;
 static volatile bit LnotV;  
 static volatile m_in_t midiMsg; 
 
 volatile word LPeriod;
 volatile word VPeriod;
 
 void uart_init (void) {
 
 
 PCON &= ~0x40;
 SCON = 0x50;
 
 PCON &= 0x7f;
 PCON |= (0 << 8);
 SSTAT = 0xA0;
 
 
 BRGCON = 0x00;
 BRGR0 = 0x30;
 BRGR1 = 0x00;
 BRGCON = 0x03;
 
 
 P1M1 &= ~0x01;
 P1M2 |= 0x01;
 P1M1 |= 0x02;
 P1M2 &= ~0x02;
 
 
 mtxbusy = 0;
 
 
 IP0 &= ~(0x10);
 IP0H &= ~(0x10);
 
 ESR = 1;
 
 
#line 50 "uart.c" /1
 
 
 
 
#line 54 "uart.c" /0
 
 IP1 &= 0xBF;
 IP1H &= 0xBF;
 
 
 EST = 1;
 }  
 
 void uart_rx_isr (void) interrupt 4 using 0 {
 
 word riffClks = 0;
 bit riffCntGotReset = 0;
 
#line 67 "uart.c" /1
 
 
#line 69 "uart.c" /0
 if (_testbit_(RI)) {
 
#line 71 "uart.c" /1
 
 
#line 73 "uart.c" /0
 byte dataByte = SBUF;
 
 if (dataByte & 0x80) {    
 if (dataByte < 0xf0) {	 
 if (OMNI == 1) {
 midiMsg.typeChan = (byte)(dataByte & 0xf0) + (0+1);  
 } else if ((byte)(dataByte & 0x0f) == 0 || (byte)(dataByte & 0x0f) == (0+1)) {
 midiMsg.typeChan = dataByte; 
 } else {
 midiMsg.typeChan = 0;  
 goto IGNORE_MIDI;
 }
 switch (midiMsg.typeChan & 0xf0) {
 case 0x80:
 case 0x90:
 case 0xb0:
 midiMsg.count = 2;
 break;
 case 0xc0:
 midiMsg.count = 1;
 break;
 case 0xe0:  
 case 0xd0:
 case 0xa0:																	
 default:
 goto IGNORE_MIDI;
 break;
 }
 } else {
 
 switch (dataByte) {
 case 0xf0:  
 sysIx = 0;
 break;
 
 case 0xf2:
 midiMsg.typeChan = dataByte;
 midiMsg.count = 2;
 break;
 
 case 0xf3:
 midiMsg.typeChan = dataByte;
 midiMsg.count = 1;
 break;
 
 case 0xf6:
 break;
 
 case 0xf7:  
 
 break;
 
 case 0xf8:
 
 
#line 128 "uart.c" /1
 
 
 
 
 
#line 133 "uart.c" /0
 midiClk++;
 if (PLAYING) {
 if (deltaPos == 0) {
 updateNote();
 LED^=1;	 
 } else {
 --deltaPos;
 }
 }
 
 
 if (lDelta != 0) {
 word tempDelta = (0xFFFF - LPeriod) >> lDelta;
 if (tempDelta < 11 - lDelta) {  
 tempDelta = 11 - lDelta;
 }
 if (deltaLUp) {
 if ((LPeriod + tempDelta) <= 0xFFFF) {
 LPeriod += tempDelta;
 }
 } else {
 if (LPeriod > tempDelta) {
 LPeriod -= tempDelta;
 }
 }
 periodH1 = ((byte)(LPeriod >> 8));
 periodL1 = (0xff & LPeriod);
 }
 if (txDelta != 0) {
 word tempDelta = (0xFFFF - VPeriod) >> txDelta;
 if (tempDelta < 11 - txDelta) {  
 tempDelta = 11 - txDelta;
 }
 if (deltaTxUp) {
 if ((VPeriod + tempDelta) <= 0xFFFF) {
 VPeriod += tempDelta;
 }
 } else {
 if (VPeriod > tempDelta) {
 VPeriod -= tempDelta;
 }
 }
 periodH0 = ((byte)(VPeriod >> 8));
 periodL0 = (0xff & VPeriod);							
 }
 
 
 break;
 
 case 0xfa:	  
 midiClk = 0;
 deltaPos = 0;
 nextRiff = 0;
 numRiffs = (curSong[nextRiff]).rAddy;
 curRiffCnt = 0;
 numNotes = 0;
 nextNote = 0;
 PLAYING = 1;
 txDelta = 0;
 deltaTxUp = 0;
 lDelta = 0;
 deltaLUp = 0;
 updateNote();
 break;
 
 case 0xfc:
 PLAYING = 0;
 break;
 
 case 0xfb:
 PLAYING = 1;
 break;
 
 case 0xfe:
 break;
 
 case 0xff:
 
 AUXR1 |= 0x08;  
 
 
 
 
 
 
 
 
 
 break;
 
 default:
 break;
 }
 } 
 } else {  
 switch (midiMsg.typeChan) {
 
 case 0xf0:
 if(sysIx < 512) { 
 sysEx[sysIx++] = dataByte;
 } else {  
 }
 break;
 
 
 case 0xf3:
 
 songNum = dataByte;
 midiClk = 0;   
 break;
 
 
 case 0xf2: 
 if(midiMsg.count == 2) {  
 midiMsg.position = dataByte;
 } else {
 bit tempBit = PLAYING;
 PLAYING = 0;
 if (dataByte) {
 midiMsg.position += (word) (dataByte << 7);
 }
 
 
 
 if (midiClk > midiMsg.position || midiMsg.position == 0) {
 midiClk = 0;
 deltaPos = 0;
 nextRiff = 0;
 numRiffs = (curSong[nextRiff]).rAddy;
 curRiffCnt = 0;
 numNotes = 0;
 nextNote = 0;
 }
 
 if (midiClk == 0) {															
 updateNote();  
 riffClks += deltaPos;
 riffCntGotReset = 1;  
 }
 while (!SONG_DONE && midiClk != midiMsg.position) {
 ++midiClk;
 if (--deltaPos == 0) {  
 updateNote();
 while (!SONG_DONE && midiClk + deltaPos < midiMsg.position) {  
 riffClks += deltaPos;  
 midiClk += deltaPos;   
 updateNote();
 if (nextNote == 3) {  
 if (riffCntGotReset == 0) {	 
 riffCntGotReset = 1;
 } else {   
 while (midiClk + riffClks < midiMsg.position && curRiffCnt != 0) {
 midiClk += riffClks;  
 --curRiffCnt;
 }
 
 numNotes = 0;
 nextNote = 0;
 updateNote();
 }
 riffClks = 0;  
 }
 } 
 }		
 }   
 
 if (!SONG_DONE) {
 PLAYING = tempBit;
 }
 }
 break;
 
 
 case (0x80 + 0):
 LnotV = 1;
 case (0x80 + (0+1)):
 
#line 310 "uart.c" /1
 
#line 311 "uart.c" /0
 if(midiMsg.count == 2) { 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 } else { 
 LED = 0;
 if (OMNI == 1) {
 
 TX_VCC_ON = 0;
 AUDIO_L_ON = 0;
 } else {
 if (LnotV == 0) {
 
 TX_VCC_ON = 0;
 } else {
 
 AUDIO_L_ON = 0;
 }
 }
 }
 
 break;
 
 
 case (0x90 + 0):
 LnotV = 1;
 case (0x90 + (0+1)):
 
#line 352 "uart.c" /1
 
#line 353 "uart.c" /0
 if(midiMsg.count == 2) { 
 word thisDelta = 0;
 bit thisUp = 0;
 midiMsg.pitch = dataByte;
 switch (dataByte) {
 
 case TX_OFF:
 LED = 0;
 txOffSwitch = 1;	 
 break;
 
 case TX_ON:
 LED = 1;
 txOffSwitch = 0;	 
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
 
 case HOLD0:
 case HOLD1:
 case HOLD2:
 break;
 
 default:
 dataByte -= 10;
 if (OMNI == 1) {
 VPeriod = LUTFreq[dataByte];
 LPeriod = VPeriod;
 } else {
 if (LnotV == 0) {	    
 VPeriod = LUTFreq[dataByte];
 
 
 } else {
 LPeriod = LUTFreq[dataByte];
 
 
 }
 }
 break;
 }
 if (thisDelta) {
 if (LnotV == 0) {	  
 txDelta = thisDelta;
 deltaTxUp = thisUp;
 } else {
 lDelta = thisDelta;
 deltaLUp = thisUp;
 }
 }
 } else if (midiMsg.pitch >= 10 && midiMsg.pitch < ((99) + 10)) {    
 if(dataByte != 0) {
 LED = 1;
 if (OMNI) {	
 AUDIO_L_ON = 1;
 TX_VCC_ON = 1;
 
 
 
 periodH0 = (0xff & (VPeriod >> 8));
 periodL0 = (0xff & VPeriod);
 periodH1 = periodH0;
 periodL1 = periodL0;
 } else {
 if (LnotV == 0) {
 TX_VCC_ON = 1;
 periodH0 = (0xff & (VPeriod >> 8));
 periodL0 = (0xff & VPeriod);
 } else {
 AUDIO_L_ON = 1;
 periodH1 = (0xff & (LPeriod >> 8));
 periodL1 = (0xff & LPeriod);
 }
 }
 } else {    
 if (LnotV == 0) {
 TX_VCC_ON = 0;
 } else {	
 AUDIO_L_ON = 0;
 }
 }
 }
 
 break;
 
 
 case 0xa0:
 break;
 
 case 0xb0 + 0:
 LnotV = 1;
 case 0xb0 + (0+1):
 if(midiMsg.count == 2) {
 midiMsg.controller = dataByte;  
 } else { 
 switch (midiMsg.controller) {
 
 case 0x10:
 if (((station - 700) >> 2) != dataByte) {
 station &= ~(0xFFFC);
 station += (word) (dataByte << 2) + 700;
 setFreq(station);
 }
 break;
 
 case 0x30:
 if ((station & 0x03) != (dataByte >> 5)) {
 station &= ~(0x0003);
 station += (dataByte >> 5);
 setFreq(station);
 }
 break;
 
 
 
 
 case 0x50:
 if (dataByte >= 64) {
 LED = 1;
 txOffSwitch = 0;
 } else {
 LED = 0;
 txOffSwitch = 1;  
 }
 break;
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 case 0x78:
 AUDIO_L_ON = 0;
 TX_VCC_ON = 0;
 break;
 
 
 case 0x79:
 break;
 
 
 case 0x7a:  
 if (dataByte & 0x7f) {
 BUTT_EN = 1;
 } else {
 BUTT_EN = 0;
 }
 break;
 
 
 case 0x7b:
 
 TX_VCC_ON = 0;
 AUDIO_L_ON = 0;
 break;
 
 
 case 0x7c:
 
 OMNI = 0;
 break;
 
 
 case 0x7d:
 
 OMNI = 1;
 break;
 
 case 0x7e:
 PLAYING = 0;
 
#line 619 "uart.c" /1
 
#line 620 "uart.c" /0
 
 if(dataByte >= 0) {
 TR1 = 1;
 periodH1 = 0x10;
 if(dataByte >= (0+1)) {
 TR0 = 1;
 periodH0 = 0x10;
 } else {
 TR0 = 0;  
 }	
 } else {
 TR1 = 0;   
 }
 
 break;
 
 case 0x7f:
 
 
 break;
 default:
 break;
 }
 }
 break;
 
 case 0xc0:
 
 
#line 649 "uart.c" /1
 
#line 650 "uart.c" /0
 
 break;
 
 default:
 break;
 }
 midiMsg.count ^= 3;  
 }
 IGNORE_MIDI:
 
 
 LnotV = 0;		
 }  
 }
 void uart_tx_isr (void) interrupt 13 using 1 {
 if (_testbit_(TI)) {
 
 
 
 mtxbusy = 0;
 }  
 }  
 
 void uart_transmit (unsigned char value) {
 while(mtxbusy);
 mtxbusy = 1;
 SBUF = value;
 }  
 
 unsigned char uart_get (void) {
 return SBUF;
 }  
 
 unsigned char ascii_to_hex(unsigned char ch) {
 if (ch & 0x40)								 
 {	
 ch += 0x09;
 }
 ch &= 0x0F;									 
 return ch;
 }
 
 void print_hex_to_ascii(unsigned char ch) {
 char temp_character;
 temp_character = ch;
 temp_character >>= 4;							 
 temp_character &= 0x0F;						 
 if (temp_character >= 10)						 
 {
 temp_character += 7;						 
 }
 temp_character += 0x30;						 
 uart_transmit(temp_character);					 
 temp_character = ch;
 temp_character &= 0x0F;						 
 if (temp_character >= 10)						 
 {
 temp_character += 7;						 
 }
 temp_character += 0x30;						 
 uart_transmit(temp_character);					 
 }
