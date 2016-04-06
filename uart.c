#include <REG936.H>
#include <LIMITS.H>
#include <MATH.H>
#include "itrip.h"
#include "uart.h"
#include "midi_spec.h"
#include "LUTFreq.h"
#include "intrins.h"

// flag that indicates if the UART is busy transmitting or not
static bit mtxbusy;
static volatile bit LnotV; //local flag of which channel to touch
static volatile m_in_t midiMsg; 

extern volatile word LPeriod;
extern volatile word VPeriod;
extern volatile bit deltaLUp;
extern volatile bit deltaTxUp;

void uart_init (void) {
  // configure UART
  // clear SMOD0
  PCON &= ~0x40;
  SCON = 0x50;
  // set or clear SMOD1
  PCON &= 0x7f;
  PCON |= (0 << 8);
  SSTAT = 0xA0;

  // configure baud rate generator
  BRGCON = 0x00;
  BRGR0 = 0x30;
  BRGR1 = 0x00;
  BRGCON = 0x03;

  // TxD = push-pull, RxD = input
  P1M1 &= ~0x01;
  P1M2 |= 0x01;
  P1M1 |= 0x02;
  P1M2 &= ~0x02;

  // initially not busy
  mtxbusy = 0;
  
  // set receive isr priority to 0
  IP0 &= ~(0x10);
  IP0H &= ~(0x10);
  // enable uart receive interrupt
  ESR = 1;
 
#ifdef COORD
  // set transmit isr priority to 3
  IP1 |= 0x40;
  IP1H |= 0x40;
#else
  // set transmit isr priority to 0 
  IP1 &= 0xBF;
  IP1H &= 0xBF;
#endif
  // enable uart transmit interrupt
  EST = 1;
} // uart_init

void uart_rx_isr (void) interrupt 4 using 0 {
	//variables for scanning !!!
	word idata riffClks = 0;
	bit riffCntGotReset = 0;
#ifdef DEBUG_SIM
	volatile byte temp = SBUF;
#endif
  if (_testbit_(RI)) {
#ifdef DEBUG_SIM
  	volatile byte dataByte = temp; //volatile for debug!!!
#else
	byte dataByte = SBUF;
#endif
	if (dataByte & 0x80) {   //status byte
		if (dataByte < 0xf0) {	//voice mesg
			if (OMNI == 1) {
				midiMsg.typeChan = (byte)(dataByte & 0xf0) + MY_V_CHAN; //trigger note commands in OMNI mode 
			} else if ((byte)(dataByte & 0x0f) == MY_L_CHAN || (byte)(dataByte & 0x0f) == MY_V_CHAN) {
				midiMsg.typeChan = dataByte; 
			} else {
				midiMsg.typeChan = 0; //clear midiMsg
				goto IGNORE_MIDI;
			}
			switch (midiMsg.typeChan & 0xf0) {
		        case NOTE_OFF:
		        case NOTE_ON:
		        case CONTROL:
		          midiMsg.count = 2;
		          break;
		        case PROGRAM:
		          midiMsg.count = 1;
		          break;
				case PITCH_WHEEL: //todo
				case CHAN_PRESSURE:
				case KEY_PRESSURE:																	
				default:
				  goto IGNORE_MIDI;
			      break;
			}
		} else {
		      // system messages
	    	switch (dataByte) {
				case SYSTEM_EXCLUSIVE: // variable length until terminated by an EOX or any status byte
					midiMsg.typeChan = dataByte;
			  		sysIx = 0;
					//stop what youre doing and listen
					PLAYING = 0;
					TR0 = 0;
					TR1 = 0;
					BUTT_EN = 0;
				break;
	
	        	case SONG_POSITION:
			  		midiMsg.typeChan = dataByte;
			  		midiMsg.count = 2;
			  	break;
	
	        	case SONG_SELECT:
			  		midiMsg.typeChan = dataByte;
			  		midiMsg.count = 1;
				break;
	
	        	case TUNE_REQUEST:
	          	break;
	
	        	case EOX: // system exclusive terminator 
					//do stuff - everbody who heard the SYS_EX stopped playing and their timers 
					//parse teh sysIx for data... playback rupts should be halted and sysEx full to sysIx
					//check manuId [010e0d], ignore myDevId, Universal sysEx header for file transfers
					if (sysEx[0] == 0x01 && sysEx[1] == 0x0e && sysEx[2] == 0x0d && 
						sysEx[5] == NON_REAL_TIME_ID && sysEx[6] == 0x07 && sysEx[7] == 0x02) {
						//we should only be here on purpose...
						//my devID?
						if (sysEx[3] == MY_ID_H && sysEx[4] == MY_ID_L) {
							//we are going to use this as a reboot into bootloader CMD
							LED = 1;
							delay(50000);
							no_touch();
						} else {
							//somebody is getting programmed, so ... just freak out... ihex is all ascii
							//the further progBaud is away the safer this is
						}
					} else { //sysEx flying around by not a programming instruction						
					}
					//erase sysEx buffer
					while(sysIx > 0) {
						sysEx[sysIx--] = 0;
					}
	          	break;
	
	        	case TIMING_CLOCK:
			  		//if (PLAYING) {
					#ifdef COORD
//						midiClk++;
//						if (deltaPos > 0) {
//							deltaPos--; 										  
//						}
					#else
						midiClk++;
						if (PLAYING) {
							if (deltaPos == 0) {
								updateNote();
								LED^=1;	 
							} else {
								--deltaPos;
							}
						}
						//pitch up/down...
						
						if (lDelta != 0) {
							word tempDelta = (UINT_MAX - LPeriod) >> lDelta;
							if (tempDelta < 11 - lDelta) { //Delta is currently 6-10
								tempDelta = 11 - lDelta;
							}
							if (deltaLUp) {
								if ((word)(LPeriod + tempDelta) > LPeriod) {
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
							word tempDelta = (UINT_MAX - VPeriod) >> txDelta;
							if (tempDelta < 11 - txDelta) { //Delta is currently 6-10
								tempDelta = 11 - txDelta;
							}
							if (deltaTxUp) {
								if ((word)(VPeriod + tempDelta) > VPeriod) {
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
					#endif
					//}
	          	break;
	
	        	case START:	 //from the beginning
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
	
	        	case STOP:
			  		PLAYING = 0;
	          	break;
	
	        	case CONTINUE:
			  		PLAYING = 1;
			  	break;
	
	        	case ACTIVE_SENSING:
	          	break;
	 
	        	case SYSTEM_RESET:
					//Goodbye, See you!
					AUXR1 |= 0x08; //soft reset
//			  		midiFlags = 0;
//					midiClk = 0;
//					deltaPos = 0;
//					numRiffs = (curSong[nextRiff]).rAddy;
//					curRiffCnt = 0;
//					numNotes = 0;
//					nextNote = 0;
//			  		PLAYING = 0;
//					BUTT_EN = 1;
	          	break;
			
				default:
			  	break;
			}
		} 
	} else { //databyte
    	switch (midiMsg.typeChan) {

      		case SYSTEM_EXCLUSIVE:
        		if(sysIx < SYS_LEN) {// discard data if the buffer is full
          			sysEx[sysIx++] = dataByte;
				} else { //buffer full!!!
					//reset??  something is real bad...
				}
        	break;

	      	
			case SONG_SELECT:
	      		//midiMsg.song = dataByte;
				songNum = dataByte;
				midiClk = 0;  //myabe not, would be very usefully weird, sysex or switch
	        break;

      		
			case SONG_POSITION: 
				if(midiMsg.count == 2) { //LSB
					midiMsg.position = dataByte;
				} else {
					bit tempBit = PLAYING;
					PLAYING = 0;
					if (dataByte) {
						midiMsg.position += (word) (dataByte << 7);
					}
					//This algorithm's worst case is ~20ms per 140 beats, with completely
					//non repetitive storage...  1.5ms per 5040 beats with uniformly repetitive test song 
					//todo good enough to just scan forward for every search!
					if (midiClk > midiMsg.position || midiMsg.position == 0) {
				  		midiClk = 0;
						deltaPos = 0;
						nextRiff = 0;
						numRiffs = (curSong[nextRiff]).rAddy;
						curRiffCnt = 0;
						numNotes = 0;
						nextNote = 0;
					}
					//midiClk is gauranteed to be less than position
					if (midiClk == 0) {															
						updateNote(); //grab first note if we are uninit'd
						riffClks += deltaPos;
						riffCntGotReset = 1; //we know we are at the beginning of a riff
					}
					while (!SONG_DONE && midiClk != midiMsg.position) {
						++midiClk;
						if (--deltaPos == 0) { //scan up to edge of note
							updateNote();
							while (!SONG_DONE && midiClk + deltaPos < midiMsg.position) { //loop through notes until we get close
								riffClks += deltaPos; //accumulate!
								midiClk += deltaPos;  //skip forward past this note
								updateNote();
								if (nextNote == 3) { //are we at the start of a riff?
									if (riffCntGotReset == 0) {	//for the very first time?
										riffCntGotReset = 1;
									} else {  //then i know how many clks are in this whole riff!!!
										while (midiClk + riffClks < midiMsg.position && curRiffCnt != 0) {
											midiClk += riffClks; //and how many times it repeats!!!
											--curRiffCnt;
										}
										//skip to next riff
										numNotes = 0;
										nextNote = 0;
										updateNote();
									}
									riffClks = 0; //we are out of that riffLoop
								}
							} 
						}		
					}  // todo Q: maybe i should just maintain riffClks through normal opssss......
					//A: only when scanning in reverse is important does it even matter much....
					if (!SONG_DONE) {
						PLAYING = tempBit;
					}
				}
        	break;


      		case (NOTE_OFF + MY_L_CHAN):
				LnotV = 1;
			case (NOTE_OFF + MY_V_CHAN):
				#ifdef COORD
				#else
	        		if(midiMsg.count == 2) {// pitch
					//commentint this out to keep noteOff from fiddling with up/down!!!
//						if (dataByte >= LUT_NUM_NOTES || dataByte <	LUT_MIDI_NOTE_SHIFT) {  //treat as a special CMD
//							//do nothing for now.... 
//						} else {
//							dataByte -= LUT_MIDI_NOTE_SHIFT;
//							if (OMNI == 1) {
//								VPeriod = LUTFreq[dataByte];
//								LPeriod = VPeriod; //LUTFreq[dataByte];
//							} else {
//							  	if (LnotV == 0) {	   //why not???  
//							  		VPeriod = LUTFreq[dataByte];
//							  	} else {
//							  		LPeriod = LUTFreq[dataByte];
//						  		}
//							}
//						}
			        } else {// velocity 
						LED = 0;
						if (OMNI == 1) {
						  //midiFlags &= ~(TX_VCC_ON + AUDIO_L_ON);
						  	TX_VCC_ON = 0;
						  	AUDIO_L_ON = 0;
						} else {
						  	if (LnotV == 0) {
						  	  	//turn off txVCC
								TX_VCC_ON = 0;
						  	} else {
						  		//turn off Left channel
								AUDIO_L_ON = 0;
						  	}
						}
					}
				#endif
	  		break;

      
		  	case (NOTE_ON + MY_L_CHAN):
				LnotV = 1;
		  	case (NOTE_ON + MY_V_CHAN):
				#ifdef COORD
				#else
		        	if(midiMsg.count == 2) {// pitch		 //todo test
						word thisDelta = 0;
						bit thisUp = 0;
						midiMsg.pitch = dataByte;
						switch (dataByte) {

							case TX_OFF:
								LED = 0;
								txOffSwitch = 1;	//	TX off
							break;
							
							case TX_ON:
								LED = 1;
								txOffSwitch = 0;	//	TX on
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
								if (LnotV == 0) {
									txDelta = 0;
								} else {
									lDelta = 0;
								}
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
								dataByte -= LUT_MIDI_NOTE_SHIFT;
								if (OMNI == 1) {
									VPeriod = LUTFreq[dataByte];
									LPeriod = VPeriod;
								} else {
								  	if (LnotV == 0) {	   //why not???  
								  		VPeriod = LUTFreq[dataByte];
//										thisDelta = txDelta;
//										thisUp = deltaTxUp;
								  	} else {
								  		LPeriod = LUTFreq[dataByte];
//										thisDelta = lDelta;
//										thisUp = deltaLUp;
									}
								}
							break;
						}
						if (thisDelta) {
							if (LnotV == 0) {	 //not OMNIfied!!!! todo
								txDelta = thisDelta;
								deltaTxUp = thisUp;
							} else {
								lDelta = thisDelta;
								deltaLUp = thisUp;
							}
						}
					} else if (midiMsg.pitch >= LUT_MIDI_NOTE_SHIFT && midiMsg.pitch < LUT_NOTE_LIMIT) {   //glitchy!!!!
						if(dataByte != 0) {
							LED = 1;
							if (OMNI) {	
								AUDIO_L_ON = 1;
								TX_VCC_ON = 1;
								//why this didnt work??? i dont remember why i didnt do this?
//								periodH0 = ((byte)(VPeriod >> 8));   todo
//								periodL0 = ((byte) VPeriod);
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
						} else {   //turn off cause Velocity = 0
						  	if (LnotV == 0) {
						  		TX_VCC_ON = 0;
						  	} else {	
						  		AUDIO_L_ON = 0;
					  		}
						}
					}
				#endif
	        break;


      		case KEY_PRESSURE:
        	break;

      		case CONTROL + MY_L_CHAN:
				LnotV = 1;
			case CONTROL + MY_V_CHAN:
		        if(midiMsg.count == 2) {
		          midiMsg.controller = dataByte; // controller number
		        } else {// setting 
		        	switch (midiMsg.controller) {
 //todo maybe COORD listens to station!!!
 						case GENERAL_SLIDER_1_hi:
							if (((station - MIN_FREQ) >> 2) != dataByte) {
								station &= ~(0xFFFC);
								station += (word) (dataByte << 2) + MIN_FREQ;
								setFreq(station);
							}
						break;

						case GENERAL_SLIDER_1_lo:
							if ((station & 0x03) != (dataByte >> 5)) {
								station &= ~(0x0003);
								station += (dataByte >> 5);
								setFreq(station);
							}
						break;

//						case SOUND_RELEASE_TIME: //todo a sustain structure!
//						break;

						case GENERAL_BUTTON_1_on:
							if (dataByte >= 64) {
								LED = 1;
								txOffSwitch = 0;
							} else {
								LED = 0;
								txOffSwitch = 1; //tx off
							}
						break;

//            case BANK_hi: break;

//            case BANK_lo: bank_lo = dataByte; break;

//	          case MOD_WHEEL_hi: load_14bit_value(&c->mod_wheel, dataByte, MSB); break;

//            case MOD_WHEEL_lo: load_14bit_value(&c->mod_wheel, dataByte, LSB); break;

//            case VOLUME_hi: load_14bit_value(&c->volume, dataByte, MSB); break;

//            case VOLUME_lo: load_14bit_value(&c->volume, dataByte, LSB); break;

//            case BALANCE_hi: load_14bit_value(&c->balance, dataByte, MSB); break;

//            case BALANCE_lo: load_14bit_value(&c->balance, dataByte, LSB); break;

//            case PAN_POSN_hi: load_14bit_value(&c->pan_posn, dataByte, MSB); break;

//            case PAN_POSN_lo: load_14bit_value(&c->pan_posn, dataByte, LSB); break;

//            case EXPRESSION_hi: break;

//            case EXPRESSION_lo: break;

//            case DATA_ENTRY_hi: load_14bit_value(c->param_ptr, dataByte, MSB); break;

//            case DATA_ENTRY_lo: load_14bit_value(c->param_ptr, dataByte, LSB); break;

//            case DATA_BUTTON_INC: break;

//            case DATA_BUTTON_DEC: break;

//            case REG_PARM_hi: load_14bit_value(&c->reg_param, dataByte, MSB); break;

//            case REG_PARM_lo: load_14bit_value(&c->reg_param, dataByte, LSB); break;

//            case HOLD_PEDAL_on:

//              break;

			            case ALL_SOUND_OFF:
						  	AUDIO_L_ON = 0;
							TX_VCC_ON = 0;
			            break;

			            
						case ALL_CONTROLLERS_OFF:
			            break;


			            case LOCAL_KEYBOARD_on: //most useful with a saved state...  maybe just a choas source.. todo
							if (dataByte & 0x7f) {
						  		BUTT_EN = 1;
						  	} else {
						    	BUTT_EN = 0;
						  	}
			            break;
//COORD does not care about voicing/channel states, but never touches the pins...

			            case ALL_NOTES_OFF:
//				            midiFlags &= (BUTT_EN + PLAYING + STEREO);
							TX_VCC_ON = 0;
							AUDIO_L_ON = 0;
						break;

			            
						case OMNI_MODE_OFF:
							//midiFlags &= (BUTT_EN + PLAYING + STEREO);
							OMNI = 0;
			            break;

			            
						case OMNI_MODE_ON:
//							midiFlags &= (BUTT_EN + PLAYING + STEREO);
							OMNI = 1;
			            break;
						
						case MONO_OPERATION:
							PLAYING = 0;
							#ifdef COORD
							#else
	//							midiFlags &= (BUTT_EN + PLAYING + STEREO);
								if(dataByte >= MY_L_CHAN) {
									TR1 = 1;
									periodH1 = 0x10;
									if(dataByte >= MY_V_CHAN) {
										TR0 = 1;
										periodH0 = 0x10;
									} else {
										TR0 = 0; //turn off this channel
									}	
								} else {
									TR1 = 0;  //turn off this channel too.
								}
							#endif
			            break;
			            
						case POLY_OPERATION:
//							midiFlags &= (BUTT_EN + PLAYING + STEREO);
							//do nothing always mono!!!
			            break;
						default:
						break;
          			}
				}
        	break;

      		case PROGRAM:
				//c->program = dataByte;  //todo
				#ifdef COORD
				#else
				#endif 
	  		break;

			default:
			break;
    	}
    midiMsg.count ^= 3; // toggle between 1 and 2 (MSB and LSB for 14 bit values)
	}
IGNORE_MIDI:
  // clear interrupt flag
  //RI = 0;
  LnotV = 0;		
  } // uart_rx_isr
}
void uart_tx_isr (void) interrupt 13 using 1 {
  if (_testbit_(TI)) {
    // clear interrupt flag
//    TI = 0;
    // no longer busy
    mtxbusy = 0;
  } // if
} // uart_tx_isr

void uart_transmit (unsigned char value) {
  while(mtxbusy);
  mtxbusy = 1;
  SBUF = value;
} // uart_transmit

unsigned char uart_get (void) {
  return SBUF;
} // uart_get

unsigned char ascii_to_hex(unsigned char ch) {
  if (ch & 0x40)								// convert ASCII character
  {	
    ch += 0x09;
  }
  ch &= 0x0F;									// into 2 digit Hex
  return ch;
}

void print_hex_to_ascii(unsigned char ch) {
  char temp_character;
  temp_character = ch;
  temp_character >>= 4;							// get highest nible
  temp_character &= 0x0F;						// save lower nibble
  if (temp_character >= 10)						// check if A-F
  {
    temp_character += 7;						// offset for A-F
  }
  temp_character += 0x30;						// add '0' to get ascii
  uart_transmit(temp_character);					// print upper nible
  temp_character = ch;
  temp_character &= 0x0F;						// save lower nibble
  if (temp_character >= 10)						// check if A-F
  {
    temp_character += 7;						// offset for A-F
  }
  temp_character += 0x30;						// add '0' to get ascii
  uart_transmit(temp_character);					// print lower nible
}
/******************   Couldn't get IAP-Lite to work! ****************************/
///the hail mary, happy Easter
//#define LOAD 0x00 // clear page register, enable loading
//#define EP 0x68 // erase & program page


//returns 0 on success, -1 on failure, and 1 on EOF packet
//char progMemSysEx() {
//  TODO DONT WORK FIXME NEVER?
//	//get length and check checksum
//	byte length = (ascii_to_hex(sysEx[9]) << 4) + ascii_to_hex(sysEx[10]);			
//	byte hiAddy;
//	byte loAddy;		
//	word addy;
//	byte pageOffset;
//	byte overflow = 0;
//	byte checksum = 0;
//	byte index = 9;
//	byte fmStat;
//	byte temp;
//	word wTemp;
//	//scan uart buffer till the end of the data section
//	for (index = 9; index < sysIx-2; index) {
//		temp = ascii_to_hex(sysEx[index++]) << 4;
//		temp += ascii_to_hex(sysEx[index++]);
//		checksum += temp;	
//	}
//	checksum = ~checksum;
//	checksum++;
//	//compare calc checksum to reported
//	if (checksum != ((ascii_to_hex(sysEx[sysIx-2]) << 4) + ascii_to_hex(sysEx[sysIx-1]))) {
//		return -1;	//failed checksum
//		//uart_transmit('X');
//	}
////	if (length == 0) {
////		if (ascii_to_hex(15) == 1 && )
////	}
//	//grab metadata	
//	hiAddy = (ascii_to_hex(sysEx[11]) << 4) + ascii_to_hex(sysEx[12]);
//	loAddy = (ascii_to_hex(sysEx[13]) << 4) + ascii_to_hex(sysEx[14]);		
//	addy = (hiAddy << 8) + loAddy;
//	pageOffset = loAddy & 0x3F;
//	//does the record actually want us to write anything???
//	//00 means data to write
//	if (sysEx[15] == '0' && sysEx[16] == '0') {
//		//does the data cross a page boundary????  ...  jerks...
//		if (pageOffset + length > 0x3F) {	//hic sunt leones
//			overflow = length - (pageOffset + length - 0x40); //e.g. 0x31+16-0x40 = 1
//			length -= overflow;  //adjust amount to write to this page 
//		}
//		//word pageAddy = (hiAddy << 8 + (loAddy & 0xC0)); //pages are 64 byte aligned
//		FMCON = LOAD; //load command, clears page reg
//		FMADRH = hiAddy; //
//		FMADRL = loAddy; //write my page address to addr regs
//		index = 17;
//		while (length-- != 0) {
//			temp = ascii_to_hex(sysEx[index++]) << 4;
//			temp += ascii_to_hex(sysEx[index++]);
//			FMDATA = temp;	
//		}
//		FMCON = EP; //erase & prog page command
//		//delay???
//		wTemp = 4000;
//		while (--wTemp);
//		fmStat = FMCON; //read the result status
//		if ((fmStat & 0x0F)!= 0) {
//			return -1;
//		}
//		if (overflow != 0) {
//			FMADRH = ++hiAddy; //
//			FMADRL = 0; //write my page address to addr regs
//			while (overflow-- != 0) {
//				temp = ascii_to_hex(sysEx[index++]) << 8;
//				temp += ascii_to_hex(sysEx[index++]);
//				FMDATA = temp;
//				length--;	
//			}
//			FMCON = EP; //erase & prog page command
//			//delay???
//			wTemp = 4000;
//			while (--wTemp);
//			fmStat = FMCON; //read the result status
//			if ((fmStat & 0x0F)!=0) {
//				return -1;
//			}
//		}
//		//success???
//		return 0;
//	}
//	return 0;
//}
