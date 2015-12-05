
#line 1 "Blinky.c" /0

 
 
  
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
 
 
 
#line 4 "Blinky.c" /0
 
  
#line 1 "C:\KEIL\C51\INC\LIMITS.H" /0






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 5 "Blinky.c" /0
 
  
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
 
 
 
#line 6 "Blinky.c" /0
 
  
#line 1 "C:\KEIL\C51\INC\STDIO.H" /0






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 typedef unsigned int size_t;
 
 
 #pragma SAVE
 #pragma REGPARMS
 extern char _getkey (void);
 extern char getchar (void);
 extern char ungetchar (char);
 extern char putchar (char);
 extern int printf   (const char *, ...);
 extern int sprintf  (char *, const char *, ...);
 extern int vprintf  (const char *, char *);
 extern int vsprintf (char *, const char *, char *);
 extern char *gets (char *, int n);
 extern int scanf (const char *, ...);
 extern int sscanf (char *, const char *, ...);
 extern int puts (const char *);
 
 #pragma RESTORE
 
 
 
#line 7 "Blinky.c" /0
 
  
#line 1 "C:\KEIL\C51\INC\CTYPE.H" /0






 
 
 
 
 
 #pragma SAVE
 #pragma REGPARMS
 extern bit isalpha (unsigned char);
 extern bit isalnum (unsigned char);
 extern bit iscntrl (unsigned char);
 extern bit isdigit (unsigned char);
 extern bit isgraph (unsigned char);
 extern bit isprint (unsigned char);
 extern bit ispunct (unsigned char);
 extern bit islower (unsigned char);
 extern bit isupper (unsigned char);
 extern bit isspace (unsigned char);
 extern bit isxdigit (unsigned char);
 extern unsigned char tolower (unsigned char);
 extern unsigned char toupper (unsigned char);
 extern unsigned char toint (unsigned char);
 
 
 
 
 #pragma RESTORE
 
 
#line 8 "Blinky.c" /0
 
  
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
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 9 "Blinky.c" /0
 
  
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
 
#line 10 "Blinky.c" /0
 
  
#line 1 "LUTFreq.h" /0
 
 
 
 
 
 
 
 
 extern const unsigned int code LUTFreq[(99)];
 
 
#line 11 "Blinky.c" /0
 
  
#line 1 "LUTsin.h" /0
 
 
 
 const unsigned char code LUTSIN64[64] = {
 128,
 140,
 152,
 164,
 176,
 187,
 198,
 208,
 217,
 226,
 233,
 240,
 245,
 249,
 252,
 254,
 255,
 254,
 252,
 249,
 245,
 240,
 233,
 226,
 217,
 208,
 198,
 187,
 176,
 164,
 152,
 140,
 127,
 115,
 103,
 91,
 79,
 68,
 57,
 47,
 38,
 29,
 22,
 15,
 10,
 6,
 3,
 1,
 1,
 1,
 3,
 6,
 10,
 15,
 22,
 29,
 38,
 47,
 57,
 68,
 79,
 91,
 103,
 115
 };
 const unsigned char code LUTSIN128[128] = {
 128,
 134,
 140,
 146,
 152,
 158,
 164,
 170,
 176,
 182,
 187,
 193,
 198,
 203,
 208,
 213,
 217,
 222,
 226,
 230,
 233,
 236,
 240,
 242,
 245,
 247,
 249,
 251,
 252,
 253,
 254,
 254,
 255,
 254,
 254,
 253,
 252,
 251,
 249,
 247,
 245,
 242,
 240,
 236,
 233,
 230,
 226,
 222,
 217,
 213,
 208,
 203,
 198,
 193,
 187,
 182,
 176,
 170,
 164,
 158,
 152,
 146,
 140,
 134,
 128,
 121,
 115,
 109,
 103,
 97,
 91,
 85,
 79,
 73,
 68,
 62,
 57,
 52,
 47,
 42,
 38,
 33,
 29,
 25,
 22,
 19,
 15,
 13,
 10,
 8,
 6,
 4,
 3,
 2,
 1,
 1,
 1,
 1,
 1,
 2,
 3,
 4,
 6,
 8,
 10,
 13,
 15,
 19,
 22,
 25,
 29,
 33,
 38,
 42,
 47,
 52,
 57,
 62,
 68,
 73,
 79,
 85,
 91,
 97,
 103,
 109,
 115,
 121
 };
 
#line 12 "Blinky.c" /0
 
  
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
 
 
#line 13 "Blinky.c" /0
 
  
#line 1 "riff.h" /0
 
 
 
 
 extern unsigned char code sthRest[5];
 extern unsigned char code eiRest[5];
 extern unsigned char code qRest[5];
 extern unsigned char code hRest[5];
 extern unsigned char code wRest[5];
 
 
 
 
 extern unsigned char code wholeDrone[5];
 extern unsigned char code minorDrone[5];
 
 
 
 extern unsigned char code sthRestCoord[(2+1)];
 extern unsigned char code eiRestCoord[(2+1)];
 extern unsigned char code qRestCoord[(2+1)];
 extern unsigned char code hRestCoord[(2+1)];
 extern unsigned char code wRestCoord[(2+1)];  
 
 
 extern unsigned char code on0Tx[(4+1)];
 extern unsigned char code on2Tx[(4+1)];
 extern unsigned char code on4Tx[(4+1)];
 extern unsigned char code on6Tx[(4+1)];
 extern unsigned char code on8Tx[(4+1)];
 extern unsigned char code on10Tx[(4+1)];
 extern unsigned char code on12Tx[(4+1)];
 extern unsigned char code on14Tx[(4+1)];
 
 extern unsigned char code off0Tx[(4+1)];
 extern unsigned char code off2Tx[(4+1)];
 extern unsigned char code off4Tx[(4+1)];
 extern unsigned char code off6Tx[(4+1)];
 extern unsigned char code off8Tx[(4+1)];
 extern unsigned char code off10Tx[(4+1)];
 extern unsigned char code off12Tx[(4+1)];
 extern unsigned char code off14Tx[(4+1)];
 
 
 
 




 














 
 
 







 







 
 
 
 
 
 
 
 extern unsigned char code beatCoord1[(69)];
 extern unsigned char code beatCoord2[(69)];
 extern unsigned char code beat1[3];
 
 
 
 
 
 
 
 extern unsigned char code dmbInit[37]; 
 
 
 extern unsigned char code dmbVamp0[(4+1)];  
 extern unsigned char code dmbVamp1[(4+1)];  
 
 
 extern unsigned char code dmbRoot0[((104-72)*4+1)];  
 extern unsigned char code dmbRoot1[((104-72)*4+1)];
 
 
 extern unsigned char code dmbBDHa[7];
 extern unsigned char code dmbBDWh[7];
 
 
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
 









































































































































 
 
#line 14 "Blinky.c" /0
 
  
#line 1 "song.h" /0
 
 
 
 
 
 
 extern RIFF_T code beatSong[];
 
 
 
 
 
 
 
 
 extern RIFF_T code wholeToneSong[];
 
 
 extern RIFF_T code minorSong[];
 
 
 extern RIFF_T code silentSong[];
 
 
 extern RIFF_T code dmbSong[];
 
 
 extern RIFF_T code testS1[6+1];
 
 
 extern RIFF_T code testS2[6+1];
 
 extern RIFF_T code testSCo1[7];
 
 extern RIFF_T code testSCo2[3];
 
 
#line 15 "Blinky.c" /0
 
 
 
 volatile byte xdata sysEx[512];
 volatile byte sysIx = 0;
 
 
 
 void* code songBook[7] = {
 silentSong,
 testS1, 
 testS2, 
 minorSong,
 wholeToneSong,
 beatSong,
 dmbSong
 };
 
 volatile byte songNum = 0; 
 volatile word midiClk = 0;
 
 
 volatile byte bdata midiFlags;
 sbit AUDIO_L_ON = midiFlags^0;	 
 sbit TX_VCC_ON = midiFlags^1; 	 
 sbit STEREO = midiFlags^2;		 
 sbit PLAYING = midiFlags^3;		 
 sbit BUTT_EN = midiFlags^4;		 
 sbit OMNI = midiFlags^5;		 
 sbit SONG_DONE = midiFlags^6;	 
 sbit LOOP_SONGS = midiFlags^7;	 
 
 
 
 
 volatile RIFF_T* curSong;
 volatile word nextRiff = 0;
 volatile byte curRiffCnt = 0;
 volatile word numRiffs = 0;
 volatile byte code* riff;
 
 volatile word deltaPos = 0;
 volatile byte numNotes = 0;
 volatile byte nextNote = 0;
 
 
 
 
 
 
 
 
 
 volatile byte periodH0 = 0; 
 volatile byte periodL0 = 0;   
 volatile byte cnt0 = 0;
 volatile byte temp0 = 0;
 
 
 volatile byte periodH1 = 0; 
 volatile byte periodL1 = 0;
 
 volatile word lDelta = 0;
 volatile word txDelta = 0;
 volatile bit deltaLUp;
 volatile bit deltaTxUp;
 
 
 
 volatile word bdata txState;
 sbit stereoTx = txState^3;
 sbit phaseMode0 = txState^4;
 sbit phaseMode1 = txState^5;
 sbit test0 = txState^6;
 sbit test1 = txState^7;
 
 volatile bit txOffSwitch = 0; 
 
 volatile word station = 879;
 
 
 void main() {	
 
 byte i = 0;
 
 setup();
 txVcc = 0;  
 setFreq(station);
 uart_init();											 
 
 
 curSong = songBook[songNum];
 numRiffs = (curSong[nextRiff]).rAddy;   
 EA = 1;
 BUTT_EN = 1;
 
#line 111 "Blinky.c" /1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 139 "Blinky.c" /0
 delay(65000);
 delay(65000);
 TR1 = 1;
 TR0 = 1;
 
 
 for(;;) {
 
#line 147 "Blinky.c" /1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 239 "Blinky.c" /0
 if (curSong != songBook[songNum]) {
 curSong = songBook[songNum];
 midiClk = 0;
 nextRiff = 0;
 deltaPos = 0;  
 numRiffs = (curSong[nextRiff]).rAddy;   
 } else {
 
 
 
 if (midButt == 0) {
 
 txVcc ^= 1;
 if(txVcc == 1) {
 txOffSwitch = 1;
 LED = 0;
 } else {
 txOffSwitch = 0;
 LED = 1;
 setFreq(station);
 } 
 }	 		
 delay(0xFFFF);
 if (LED) {
 if (hiButt == 0) {
 LED = 0;
 delay(0xFFFF);
 station++;
 setFreq(station);
 LED = 1;
 delay(0xFFFF);
 } 
 else if (loButt == 0) {
 LED = 0;
 delay(0xFFFF);
 --station;
 setFreq(station);
 LED = 1;
 delay(0xFFFF);
 }
 if (station < 700) {
 station = 700;
 LED = 0;
 delay(0xFFFF);
 LED = 1;
 delay(0xFFFF);
 LED = 0;
 delay(0xFFFF);
 LED = 1;
 delay(0xFFFF);
 LED = 0;
 delay(0xFFFF);
 LED = 1;
 delay(0xFFFF);
 LED = 0;
 delay(0xFFFF);
 LED = 1;
 delay(0xFFFF);
 }
 if (station > 1200) {
 station = 1200;
 LED = 0;
 delay(0xFFFF);
 LED = 1;
 delay(0xFFFF);
 LED = 0;
 delay(0xFFFF);
 LED = 1;
 delay(0xFFFF);
 LED = 0;
 delay(0xFFFF);
 LED = 1;
 delay(0xFFFF);
 LED = 0;
 delay(0xFFFF);
 LED = 1;
 delay(0xFFFF);
 }						  
 }
 
 }
 
 }
 }
 
 void setup() {
 
 P0M1 = 0x07;	  
 P0M2 = 0x08;
 P1M1 = 0;		 
 
 P2M1 = 0;		
 P3M1 = 0;
 midButt = 1;  
 hiButt = 1;
 loButt = 1;
 LED = 1;  	 
 txVcc = 1;	 
 CE = 0;		 
 stereoTx = STEREO;
 audioL = 0;
 test0 = 1; 	 
 test1 = 0; 	 
 phaseMode0 = 0;	 
 phaseMode1 = 0;	 
 
 
#line 346 "Blinky.c" /1
 
 
 
 
 
 
 
 
 
 
 
#line 357 "Blinky.c" /0
 
 
 
 TMOD &= 0x00;	  
 
 TAMOD &= 0xEE;	  
 TMOD |= 0x11;	  
 
 
 periodH1 = 0;
 periodL1 = 0;
 
 TH0 = 0;
 TL0 = 0;
 
 TH1 = periodH1;
 TL1 = periodL1;
 
 
 
 
 
 
#line 380 "Blinky.c" /1
 
 
 
 
#line 384 "Blinky.c" /0
 
 
 IP0 &= ~(0x80);
 IP0H &= ~(0x00);
 
 
 ET1 = 1;
 ET0 = 1;
 
 
 
 
 
 
 
 }	
 
 
 void timers_isr1 (void) interrupt 3 using 2
 {
 
#line 405 "Blinky.c" /1
 
 
 
 
 
 
 
 
 
 
 
#line 416 "Blinky.c" /0
 
 TH1 = periodH1;	 
 TL1 = periodL1;
 
 _nop_();  
 _nop_();
 _nop_();
 if(AUDIO_L_ON) {  
 audioL ^= 1; 
 }
 
 }
 
 void timers_isr0 (void) interrupt 1 using 3
 {
 
#line 432 "Blinky.c" /1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 448 "Blinky.c" /0
 
 TH0 = periodH0;
 TL0 = periodL0;
 
 if (!txOffSwitch) {
 if(TX_VCC_ON) {
 txVcc ^= 1;
 } else {
 txVcc = 0;  
 }
 } else {
 txVcc = 1;  
 }
 
 }
 
 void updateNote(void) {
 byte temp, temp2;
 word thisDelta = 0;
 bit thisUp = 0, VnotL = 0;;
 UPDATE_NOTE:
 if (nextNote >= numNotes) {	  
 nextNote = 1;  
 if (curRiffCnt-- == 0) {
 if (++nextRiff == numRiffs) {  
 
 PLAYING = 0;  
 midiClk = 0;
 LED = 0;
 
 AUDIO_L_ON = 0;
 TX_VCC_ON = 0;
 
 nextRiff = numRiffs - 1;
 curRiffCnt = 0;
 nextNote = numNotes;
 SONG_DONE = 1;
 
#line 486 "Blinky.c" /1
 
 
 
 
#line 490 "Blinky.c" /0
 } else {
 riff = (byte*) (curSong[nextRiff]).rAddy; 
 curRiffCnt = (curSong[nextRiff]).repeats; 
 numNotes = riff[0];				 
 }
 }
 }
 deltaPos = riff[nextNote++];				 
 temp = (riff[nextNote++]);				 
 
#line 500 "Blinky.c" /1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 620 "Blinky.c" /0
 if (PLAYING) {  
 if (temp & 0x80) {
 VnotL = 1;
 }
 temp &= 0x7f;
 switch (temp) {
 
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
 
 case NOTE_OFF_MEM:
 if (VnotL == 1) {
 TX_VCC_ON = 0;
 } else {
 AUDIO_L_ON = 0;
 }
 break;
 
 default:
 temp -= 10;
 if (VnotL == 1) {
 TX_VCC_ON = 1;
 periodH0 = (0xff & (LUTFreq[temp] >> 8));
 periodL0 = (0xff & LUTFreq[temp]);
 } else {
 AUDIO_L_ON = 1;
 periodH1 = (0xff & (LUTFreq[temp] >> 8));
 periodL1 = (0xff & LUTFreq[temp]);
 }
 break;
 }
 if (thisDelta) {
 if (VnotL == 1) {	  
 txDelta = thisDelta;
 deltaTxUp = thisUp;
 } else {
 lDelta = thisDelta;
 deltaLUp = thisUp;
 }
 }
 
 if (deltaPos == 0) {
 goto UPDATE_NOTE;
 }
 }
 
 }
 
 
 
 
 void setFreq (word freq) {  
 if (txOffSwitch || freq > 1200 || freq < 700) return;   
 
 else {
 word temp = freq;
 
 temp += (txState & 0xF800);   
 txState = temp;	  
 txProg();
 
 }	
 }
 
 void txProg() {	 
 word i = 0x01;
 bit tempTX = TX_VCC_ON;
 TX_VCC_ON = 0;
 txVcc = 0;	 
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
 
 
 void delay (word cnt) {	 
 while (--cnt);
 }
