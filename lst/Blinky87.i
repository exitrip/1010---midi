
#line 1 "Blinky87.c" /0

 
 
  
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
 
 
 
#line 4 "Blinky87.c" /0
 
  
#line 1 "C:\KEIL\C51\INC\LIMITS.H" /0






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 5 "Blinky87.c" /0
 
  
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
 
 
 
#line 6 "Blinky87.c" /0
 
  
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
 
 
 
#line 7 "Blinky87.c" /0
 
  
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
 
 
#line 8 "Blinky87.c" /0
 
  
#line 1 "ITRIP.H" /0


 
 
 
 
 
 typedef unsigned char byte;
 typedef unsigned int word;
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 







 
 
 
 
 void setup ();   
 void delay (word cnt);
 void shiftout8 (byte d);
 
 
 void txProg ();
 void setFreq (word freq);
 void tone ();
 void delayT (word t);
 
 
 
 
 
 
 
 
 
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
 sbit ccTimer = P2^0;
 
#line 9 "Blinky87.c" /0
 
 
 
 
 
 volatile word bdata txState;
 sbit stereo = txState^3;
 sbit phaseMode0 = txState^4;
 sbit phaseMode1 = txState^5;
 sbit test0 = txState^6;
 sbit test1 = txState^7;	
 
 
 
 void main() {	
 
 
 
 word station = 870;
 
 
 setup();											 
 setFreq(station);
 
 for(;;) {
 delay(0xFFFF);
 if (midButt == 0) {
 LED ^= 1;
 txVcc ^= 1; 
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
 if (station > 1080) {
 station = 1080;
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
 
 void setup() {
 
 P0M1 = 0x17;	  
 P1M1 = 0;		 
 P2M1 = 0;
 P3M1 = 0;
 midButt = 1;  
 hiButt = 1;
 loButt = 1;
 LED = 1;  	 
 txVcc = 0;	 
 CE = 0;		 
 stereo = 0;
 audioL = 0;
 test0 = 1; 	 
 test1 = 0; 	 
 phaseMode0 = 0;	 
 phaseMode1 = 0;	 
 }	
 
 
 
 
 void setFreq (word freq) {  
 if (freq > 1080 || freq < 700) return;   
 else {
 word temp = freq;
 EA = 0;		 
 temp += (txState & 0xF800);   
 txState = temp;	  
 txProg();
 EA = 1;		 
 }	
 }
 
 
 void txProg() {	 
 word i = 0x01;
 EA = 0;
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
 EA = 1;   
 }
 
 
 void delay (word cnt) {	 
 while (--cnt);
 }
