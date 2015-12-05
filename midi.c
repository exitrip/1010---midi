///*
//
//  thanks Peter Everett
//
//*/
//
//#include "midi.h"
//#include "midi_spec.h"
//
//#include "uart.h"
//
//
////#define PROGRAM_UPDATES_BANKS // bank messages take effect on the next program change
//
////extern chan_t myMIDIChan;        // main channel data structure
//
////extern const chan_t code def_chan;
//
//
//// m_in.count data counter values when accumulating 14bit values
//
//#define LSB 2
//							  
//#define MSB 1
//
//
//static m_in_t m_in;                 // current midi in message structure
//
//
//// default midi channel parameters (single channel)
//
//const chan_t code def_chan = 
//
//{
//
//// controllers
//
//    0x3f,   // volume (max)
//
//    0x20,   // pan position (mid)
//
//       0,   // switches
//
//};
//
//
//
//
///*
//
// * reset_controllers
//
// * -----------------
//
// * Sets the controllers of a single channel to their default values.
//
// */
//
//static void reset_controllers(chan_t *c)
//
//{
//
//  const chan_t *def = &def_chan;
//
//  c->volume      = def->volume;
//
//  c->pan_posn    = def->pan_posn;
//
//  c->switches    = def->switches;
//
//}
//
//
//
//
///*
//
// * load_14bit_value
//
// * ----------------
//
// * Midi data is only 7 bits per byte. This accumulates 2 bytes into a 14 bit value.
//
// * Data is sent lsb first, msb second, as determined by the data count.  It doesn't
//
// * actually matter which order the data comes, and sometimes only the MSB is sent.
// * We only listen to the MSB
//
// */
//
//static void load_14bit_value(unsigned short *parm, int dataByte, int byteCnt)
//
//{
//
//  //if(byte == LSB)
//
//    //*parm = (*parm & ~0x7f) | dataByte;
//
//  if (byteCnt == MSB) // msb 
//    *parm = (*parm & ~(0x7f)) | (dataByte);
//
//}
//
//
//
//
///*
//
// * synth_midi_in
//
// * -------------
//
// * This is the main synth remote control input, it interprets data from midi input ports.
//
// * Most changes to synth parameters will be picked up automatically by the regular synth
//
// * task and audio output interrupt.
//
// */
//
//static void midi_in(int dataByte)
//
//{
//
//  int real_time, on;
//
//  chan_t *c = &myMIDIChan;
//
//
//  if (dataByte & 0x80)
//
//  {
//
//    // status byte 
//
//  
//
//    real_time = 0;
//
//  
//
//    if (dataByte < 0xf0)
//
//    {
//
//      // voice messages
//
//      m_in.type    = dataByte & 0xf0;
//
//      m_in.channel = dataByte & 0x0f; 
//
//  
//
//      // set message lengths
//
//      switch (m_in.type)
//
//      {
//
//        case NOTE_OFF:
//
//        case NOTE_ON:
//
//        case KEY_PRESSURE:
//
//        case CONTROL:
//
//        case PITCH_WHEEL:
//
//          m_in.count = 2;
//
//          break;
//
//  
//
//        case PROGRAM:
//
//        case CHAN_PRESSURE:
//
//          m_in.count = 1;
//
//          break;
//
//      }
//
//    }
//
//    else
//
//    {
//
//      // system messages
//
//      switch (dataByte)
//
//      {
//
//        // system common commands
//
//  
//
//        case SYSTEM_EXCLUSIVE: // variable length until terminated by an EOX or any status byte
//
////          m_in.type = dataByte;
////
////          sys.ix = 0;
//
//          break;
//
//          
//
//        case SONG_POSITION:
//
////          m_in.type = dataByte;
////
////          m_in.count = 2;
//
//          break;
//
//          
//
//        case SONG_SELECT:
//
//          m_in.type = dataByte;
//
//          m_in.count = 1;
//
//          break;
//
//          
//
//        case TUNE_REQUEST:
//
//          // no associated dataByte
//
//          break;
//
//          
//
//        case EOX: // system exclusive terminator 
//
//          // no need to do anything here, it will be picked up after the switch
//
//          break;
//
//          
//
//        // real time (no associated dataByte)
//
//  
//
//        case TIMING_CLOCK:
//
////          real_time = 1;
//
//          break;
//
//          
//
//        case START:
//
////          real_time = 1;
//
//          break;
//
//          
//
//        case STOP:
//
////          real_time = 1;
//
//          break;
//
//  
//
//        case CONTINUE:
//
////          real_time = 1;
//
//          break;
//
//          
//
//        case ACTIVE_SENSING:
//
////          real_time = 1;
//
//          break;
//
//          
//
//        case SYSTEM_RESET:
//
////          real_time = 1;
//
//          break;
//
//      }
//
//    }
//
//  
//
//    // check for an unterminated system exclusive message
//
////    if(!real_time && (sys.ix > 0))
////
////    {
////
////      sys.ex[sys.ix] = EOX;
////
////      interpret_sys_ex(sys.ex);
////
////      sys.ix = 0;
////
////    }
//
//  }
//
//  else
//
//  {
//
//    // data byte 
//
//    //c = &chan[m_in.channel]; // point to the current channel (not always needed)
//
//    on = dataByte >> 6; // for on/off controls (not always needed)
//
//  
//
//    switch (m_in.type)
//
//    {
//
//      case SYSTEM_EXCLUSIVE:
////
////        if(sys.ix < SYS_LEN) // discard data if the buffer is full
////
////          sys.ex[sys.ix++] = dataByte;
////
//        break;
//
//  
//
//      case SONG_SELECT:
//
//        m_in.song = dataByte;
//
//        break;
//
//  
//
//      case SONG_POSITION:
////
////        load_14bit_value(&m_in.position, dataByte, m_in.count);
////
//        break;
//
//  
//
//      case NOTE_OFF:
//
//        if(m_in.count == 2) // pitch 
//
//          m_in.pitch = dataByte;
//
//        else // velocity 
//
//        {
//
//          m_in.velocity = dataByte;
//
////          poly_action_key(m_in.pitch, FALSE, m_in.channel, REMOTE_KEY, m_in.velocity);
//
//        }
//
//        break;
//
//      
//
//      case NOTE_ON:
//
//        if(m_in.count == 2) // pitch 
//
//          m_in.pitch = dataByte;
//
//        else // velocity 
//
//        {
//
//          m_in.velocity = dataByte;
//
////          poly_action_key(m_in.pitch, (dataByte != 0), m_in.channel, REMOTE_KEY, m_in.velocity); // note off if data == 0
//
//        }
//
//        break;
//
//      
//
//      case KEY_PRESSURE:
//
////        if(m_in.count == 2) // pitch 
////
////          m_in.pitch = dataByte;
////
////        else // pressure 
////
////          m_in.pressure = dataByte;
//
//        break;
//
//      
//
//      case CONTROL:
//
//        if(m_in.count == 2)
//
//          m_in.controller = dataByte; // controller number
//
//        else // setting 
//
//          switch (m_in.controller)
//
//          {
//
//#ifdef PROGRAM_UPDATES_BANKS
//            case BANK_hi: bank_hi = dataByte; break;
//
//            case BANK_lo: bank_lo = dataByte; break;
//
//#else
//
//            case BANK_hi: c->bank_hi = dataByte; break;
//
//            case BANK_lo: c->bank_lo = dataByte; break;
//
//#endif
//	        case MOD_WHEEL_hi: load_14bit_value(&c->mod_wheel, dataByte, MSB); break;
//
//            case MOD_WHEEL_lo: load_14bit_value(&c->mod_wheel, dataByte, LSB); break;
//
//  
//
//            case VOLUME_hi: load_14bit_value(&c->volume, dataByte, MSB); break;
//
//            case VOLUME_lo: load_14bit_value(&c->volume, dataByte, LSB); break;
//
//  
//
//            case BALANCE_hi: load_14bit_value(&c->balance, dataByte, MSB); break;
//
//            case BALANCE_lo: load_14bit_value(&c->balance, dataByte, LSB); break;
//
//  
//
//            case PAN_POSN_hi: load_14bit_value(&c->pan_posn, dataByte, MSB); break;
//
//            case PAN_POSN_lo: load_14bit_value(&c->pan_posn, dataByte, LSB); break;
//
//  
//
//            case EXPRESSION_hi: break;
//
//            case EXPRESSION_lo: break;
//
//  
//
//            case DATA_ENTRY_hi: load_14bit_value(c->param_ptr, dataByte, MSB); break;
//
//            case DATA_ENTRY_lo: load_14bit_value(c->param_ptr, dataByte, LSB); break;
//
//            case DATA_BUTTON_INC: break;
//
//            case DATA_BUTTON_DEC: break;
//
//  
//
//            case REG_PARM_hi: load_14bit_value(&c->reg_param, dataByte, MSB); break;
//
//            case REG_PARM_lo: load_14bit_value(&c->reg_param, dataByte, LSB); break;
//
//  
//
//            case HOLD_PEDAL_on:
//
//              break;
//
//  
//
//            case ALL_SOUND_OFF:
//
//              break;
//
//  
//
//            case ALL_CONTROLLERS_OFF:
//
//              break;
//
//  
//
//            case LOCAL_KEYBOARD_on:
//
//              break;
//
//  
//
//            case ALL_NOTES_OFF:
//
//              break;
//
//              
//
//            case OMNI_MODE_OFF:
//
////              syn.switches |= (1<<OMNI_MODE);
//
//              break;
//
//              
//
//            case OMNI_MODE_ON:
//
////              syn.switches &= ~(1<<OMNI_MODE);
//
//              break;
//
//              
//
//            case MONO_OPERATION:
//
//              // data = number of monophonic voices 
//
////              syn.switches = (syn.switches & ~(MONO_MASK<<MONO_VOICES)) | (1<<POLY_MODE) | (dataByte<<MONO_VOICES);
//
//              break;
//
//  
//
//            case POLY_OPERATION:
//
////              syn.switches &= ~(1<<POLY_MODE);
//
//              break;
//
//          }
//
//        break;
//
//      
//
//      case PROGRAM:
//
//        c->program = dataByte;      
//
//    }
//
//  
//
//    m_in.count ^= 3; // toggle between 1 and 2 (MSB and LSB for 14 bit values)
//
//  }
//
//}
//
//void send_midi_msg(int len, int status, int data1, int data2)
//
//{
//
//
//}
//
