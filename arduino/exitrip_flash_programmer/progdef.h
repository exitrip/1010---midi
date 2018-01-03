//***************************************************************************
//* 								progdef.h 
//*	By : Bauke Siderius		
//*	Discription : defenitions for programming commands for the LPC90x 
//* Modified by ed bear 2017
//***************************************************************************

//***************************************************************************
//* What board are we programming with?
//***************************************************************************
#define PRO_MINI
//#define UNO
//#define LITTLEBITS  //TODO test

//***************************************************************************
//* Assign the targets MIDI channels
//* These two channels should not be the same and must be between 1 and 16
//*   targetLChan [left channel] will create synth tones on the left [mono] 
//*     audio channel.  These tones will be output the exitrip's headphone jack
//*     on the TIP conductor.
//*   targetVChan [voltage channel] will create a synth tone sent through the
//*     transmitters power supply.  This channel is 'spookier': It gets quieter
//*     as the pitch rises, while low pitches will modulate a reciever's sound
//*     chaotically.  The V channel transmits around the center broadcast 
//*     station, not exactly on it. (e.g. if the transmitter is tuned to 91.1 FM,
//*     V Channel notes will be strongest around ~90.5 FM and ~91.7 FM)
//*
//*   if OVERWRITE_HEXFILE_CHANNELS is defined, the arduino will overwrite
//*     the channels recorded in the hexfile, if they exist.
//*     Comment OVERWRITE_HEXFILE_CHANNELS to leave the channels as coded in
//*     the hexfile.
//***************************************************************************
#define TARGET_L_CHAN   10
#define TARGET_V_CHAN   8

#define OVERWRITE_HEXFILE_CHANNELS

//channel error checking
#if ((TARGET_L_CHAN > 16) || (TARGET_L_CHAN < 1) || (TARGET_V_CHAN > 16) || (TARGET_V_CHAN < 1))
  #error "MIDI channel is out of the range 1 to 16"
#elif (TARGET_L_CHAN == TARGET_V_CHAN)
  #error "MIDI Left and Voltage channels cannot be the same"
#endif

//***************************************************************************
//* Switch between modes of programming:
//* Headless mode stores exitrip program inside the Arduino for screen-less
//*     operation
//* Serial_Bridge mode requires a computer to feed the Arduino exitrip .hex 
//*     file
//* Just comment the line `#define HEADLESS` to turn on the Serial_Bridge 
//*     mode
//***************************************************************************
#define HEADLESS
#ifndef HEADLESS
    #define SERIAL_BRIDGE
#endif

//***************************************************************************
//* Select the binary to program in Headless operation
//* by including one and only one of the following header files 
//*
//* If EXCLUDE_SONGS is defined, the arduino will skip programming "songs" included in 
//*   the hexfile.  See www.exitrip.org/howto/songs for more information.
//*   You will always be able to include songs later.  This option is most useful
//    if you are writing your own firmware.
//*
//* Only modify CHANNEL_MAGIC_ADDR if you have created custom firmware
//***************************************************************************
#ifdef HEADLESS
  #include "Blinky_hex_basic.h"
  //#include "Blinky_hex_unitXII_0.h"

#define EXCLUDE_SONGS

//must sync with firmware version....
  #define CHANNEL_MAGIC_ADDR    0x1800
  #define CHANNEL_MAGIC_ADDR_HI ((char)(CHANNEL_MAGIC_ADDR >> 8))
  #define CHANNEL_MAGIC_ADDR_LO ((char)(CHANNEL_MAGIC_ADDR & 0xff))
#endif

//***************************************************************************
//* Pin Definitions, ported to Arduino pin numbers on boards
//***************************************************************************
#if  defined(PRO_MINI)
#define PDA     5           // define PDA pin
#define PCL     4           // define PCL pin
#define RESET   6           // define RESET control pin
#define VDD     3           // define VDD control pin

#elif defined(UNO)          
#define PDA     10					// define PDA pin
#define PCL     11 					// define PCL pin
#define RESET   9  				// define RESET control pin
#define VDD     12					// define VDD control pin

#elif defined(LITTLEBITS)   // needs testing TODO
#define PDA     10          // define PDA pin
#define PCL     11          // define PCL pin
#define RESET   9           // needs to be broken out from bottom output
                            // for more mA... should test with ICSP outs
#define VDD     13          // define VDD control pin
#define LED_BUILTIN 1       //use the output 1 pin
#else
#error "Define board used as programmer!!!!"
#endif
//***************************************************************************
//* Programmer Opcodes
//***************************************************************************
#define NOP				0x00		// No operation
#define WR_FMADRL		0x08		// Write address low
#define RD_FMADRL		0x09		// Read address low 
#define WR_FMADRH		0x0A		// Write address high
#define RD_FMADRH		0x0B		// Read address low
#define WR_FMCON		0x0E		// Write a command to FMCON
#define RD_FMCON		0x0F		// Read a command from FMCON
#define WR_FMDATA_PG	0x14		// Write a command to FMDATA and inc addr
#define RD_FMDATA_PG	0x15		// Read a coomand from FMDATA and inc addr
#define WR_FMDATA		0x0C		// Write a data byte to FMDATA
#define RD_FMDATA		0x0D		// Read a data byte from FMDATA
#define WR_FMDATA_I		0x04		// Write a data byte to FMDATA and increment
#define RD_FMDATA_I		0x05		// Read a data byte from FMDATA and increment
#define CLR_CCP_KEY		0x96		// Clear configuration protection key

//***************************************************************************
//* Programmer Commands
//***************************************************************************
#define LOAD			0x00		// Clear then load the page register
#define PROG			0x48		// Program page with page register command
#define ERS_G			0x72		// Erase global command 
#define ERS_S			0x71		// Erase sector command
#define ERS_P			0x70		// Erase page comand
#define CONF			0x6C		// Access user config
#define CRC_G			0x1A		// Global CRC
#define CRC_S			0x19		// Sector CRC
#define CRC_A			0x14		// CRC user config
#define CCP				0x67		// Clear Configuration Protection

//***************************************************************************
//* ISP function codes
//***************************************************************************
#define PROGRAM			0			// program user code
#define READ_VERSION	1			// read IAP/ISP version
#define MISC_WRITE		2			// misc. write functions
#define MISC_READ		3			// misc. read functions
#define ERASE			4			// erase sector/page
#define SECTOR_CRC		5			// read sector CRC
#define GLOBAL_CRC		6			// read global CRC
#define LOAD_BAUD		7			// not implemented
#define CHIP_ERASE		9			// full chip erase 	`

//***************************************************************************
//* versions of ISP and ICP
//***************************************************************************
#define ISP_VERSION		0x05		// ICP version
#define ICP_VERSION		0x05		// ICP version

//***************************************************************************
//* ICP Functions Prototypes
//***************************************************************************
void enter_icp(void);
void init_flash(void);
void load_page(void);
void program(void);
void erase_global(void);
void erase_sector(void);
void erase_page(void);
void crc_global(void);
void crc_sector(void);
void write_config(void);
void read_config(void);
void shift_out(char data_byte);
char shift_in(void);

//***************************************************************************
//* ISP Functions Prototypes
//***************************************************************************
void program_record(void);
unsigned char echo();
unsigned char get2();
unsigned char ascii_to_hex(unsigned char ch);
void msec(int msec);
