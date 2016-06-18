/*

  thanks Peter Everett!!!!

*/

#ifndef midi_spec_h
#define midi_spec_h

//COORD extra codes from midi Files... 
//really only ever gonna be TEMPO
#define TEMPO_SET	0x70//0x51 in file

//Staion macros for general sliders..
#define STATION_TO_HI(x)	((unsigned char)(((((unsigned int)x) - 700) >> 2) & 0x7f))
#define STATION_TO_LO(x)	((unsigned char)(((((unsigned int)x) - 700) << 5) & 0x7f))

#define NUM_MIDI_CHANS      16    // Number of logical channels

#define PERCUSSION_CHAN     10    // Channel used for percussuion

#define MIDI_DATA_RANGE    128    // 7 bit data range


// Note numbers,

// lowest note  C0  (0)   =     8.1757989156437073336828122976033Hz

// middle C is  C5  (60)  =   261.6255653005986346778499935233Hz

// reference    A6  (69)  =   440Hz

// highest note G10 (127) = 12543.853951415977410742384974714Hz

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

  C10,Cs10,D10,Ds10,E10,F10,Fs10,G10,NUM_NOTES

};




// Voice messages. (bits 0..3 are the channel number)

#define NOTE_OFF            0x80  // + 2 bytes, pitch (note), velocity

#define NOTE_ON             0x90  // + 2 bytes, pitch (note), velocity

#define KEY_PRESSURE        0xa0  // + 2 bytes, pitch (note), pressure

#define CONTROL             0xb0  // + 2 bytes, controller, setting

#define PROGRAM             0xc0  // + 1 byte, program (patch)

#define CHAN_PRESSURE       0xd0  // + 1 byte, pressure

#define PITCH_WHEEL         0xe0  // + 2 bytes, 14bit value, 7 lsb's first


// System messages

#define SYSTEM_EXCLUSIVE    0xf0

#define SONG_POSITION       0xf2

#define SONG_SELECT         0xf3

#define TUNE_REQUEST        0xf6

#define EOX                 0xf7 // system exclusive terminator


// Real Time messages

#define TIMING_CLOCK        0xf8

#define START               0xfa

#define CONTINUE            0xfb

#define STOP                0xfc

#define ACTIVE_SENSING      0xfe

#define SYSTEM_RESET        0xff




// Controllers


// msb of 14 bit values

#define BANK_hi             0x00

#define MOD_WHEEL_hi        0x01

#define BREATH_CTRL_hi      0x02

#define FOOT_PEDAL_hi       0x04

#define PORTAMENTO_TIME_hi  0x05

#define DATA_ENTRY_hi       0x06

#define VOLUME_hi           0x07

#define BALANCE_hi          0x08

#define PAN_POSN_hi         0x0a  // mono < 64 , else stereo

#define EXPRESSION_hi       0x0b

#define EFFECT_CTRL_1_hi    0x0c

#define EFFECT_CTRL_2_hi    0x0d

#define GENERAL_SLIDER_1_hi 0x10

#define GENERAL_SLIDER_2_hi 0x11

#define GENERAL_SLIDER_3_hi 0x12

#define GENERAL_SLIDER_4_hi 0x13


// lsb of 14 bit values

#define BANK_lo             0x20

#define MOD_WHEEL_lo        0x21

#define BREATH_CTRL_lo      0x22

#define FOOT_PEDAL_lo       0x24

#define PORTAMENTO_TIME_lo  0x25

#define DATA_ENTRY_lo       0x26

#define VOLUME_lo           0x27

#define BALANCE_lo          0x28

#define PAN_POSN_lo         0x2a

#define EXPRESSION_lo       0x2b

#define EFFECT_CTRL_1_lo    0x2c

#define EFFECT_CTRL_2_lo    0x2d

#define GENERAL_SLIDER_1_lo 0x30

#define GENERAL_SLIDER_2_lo 0x31

#define GENERAL_SLIDER_3_lo 0x32

#define GENERAL_SLIDER_4_lo 0x33


// switches, >=64 = on, <64 = off

#define HOLD_PEDAL_on       0x40

#define PORTAMENTO_on       0x41

#define SUSTENUTO_PEDAL_on  0x42

#define SOFT_PEDAL_on       0x43

#define LEGATO_PEDAL_on     0x44

#define HOLD_2_PEDAL_on     0x45


// 7 bit values

#define SOUND_VARIATION     0x46

#define SOUND_TIMBRE        0x47

#define SOUND_RELEASE_TIME  0x48

#define SOUND_ATTACK_TIME   0x49

#define SOUND_BRIGHTNESS    0x4a

#define SOUND_CTRL_6        0x4b

#define SOUND_CTRL_7        0x4c

#define SOUND_CTRL_8        0x4d

#define SOUND_CTRL_9        0x4e

#define SOUND_CTRL_10       0x4f


// switches, >=64 = on, <64 = off

#define GENERAL_BUTTON_1_on 0x50

#define GENERAL_BUTTON_2_on 0x51

#define GENERAL_BUTTON_3_on 0x52

#define GENERAL_BUTTON_4_on 0x53


// 7 bit values

#define EFFECTS_LEVEL       0x5b

#define TREMULO_LEVEL       0x5c

#define CHORUS_LEVEL        0x5d

#define CELESTE_LEVEL       0x5e

#define PHASER_LEVEL        0x5f


#define DATA_BUTTON_INC     0x60

#define DATA_BUTTON_DEC     0x61


// 14 bit values

#define NON_REG_PARM_lo     0x62

#define NON_REG_PARM_hi     0x63

#define REG_PARM_lo         0x64

#define REG_PARM_hi         0x65


// mode controls

#define ALL_SOUND_OFF       0x78

#define ALL_CONTROLLERS_OFF 0x79

#define LOCAL_KEYBOARD_on   0x7a

#define ALL_NOTES_OFF       0x7b

#define OMNI_MODE_OFF       0x7c

#define OMNI_MODE_ON        0x7d

#define MONO_OPERATION      0x7e

#define POLY_OPERATION      0x7f




// System Exclusive ID's

#define SEQUENTIAL_CIRCUITS 0x01

#define BIG_BRIAR           0x02

#define OCTAVE_PLATEAU      0x03

#define MOOG                0x04

#define PASSPORT_DESIGNS    0x05

#define LEXICON             0x06

#define KURZWEIL            0x07

#define FENDER              0x08

#define GULBRANSEN          0x09

#define DELTA_LABS          0x0a

#define SOUND_COMP          0x0b

#define GENERAL_ELECTRO     0x0c

#define TECHMAR             0x0d

#define MATTHEWS_RESEARCH   0x0e

#define OBERHEIM            0x10

#define PAIA                0x11

#define SIMMONS             0x12

#define DIGIDESIGN          0x13

#define FAIRLIGHT           0x14

#define JL_COOPER           0x15

#define LOWERY              0x16

#define LIN                 0x17

#define EMU                 0x18

#define PEAVEY              0x1b


#define BON_TEMPI           0x20

#define SEIL                0x21

#define SYNTHEAXE           0x23

#define HOHNER              0x24

#define CRUMAR              0x25

#define SOLTON              0x26

#define JELLINGHAUS_MS      0x27

#define CTS_                0x28

#define PPG                 0x29

#define ELKA                0x2f

#define CHEETAH             0x36

#define WALDORF             0x3e


#define KAWAI               0x40

#define ROLAND              0x41

#define KORG                0x42

#define YAMAHA              0x43

#define CASIO               0x44

#define KAMIYA_STUDIO       0x46

#define AKAI                0x47

#define VICTOR              0x48

#define FUJITSU             0x4b

#define SONY                0x4c

#define TEAC                0x4e

#define MATSUSHITA          0x50

#define FOSTEX              0x51

#define ZOOM                0x52

#define MATSUSHITA2         0x54

#define SUZUKI              0x55

#define FUJI_SOUND          0x56

#define ACOUSTIC_TECH_LIB   0x57


#define EDUCATIONAL_USE_ID  0x7d // for educational or development use only

#define NON_REAL_TIME_ID    0x7e

#define REAL_TIME_ID        0x7f


#endif