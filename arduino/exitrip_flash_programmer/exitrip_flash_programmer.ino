/*
//*    Based on:
//* 								ISP_to_ICP_bridge.c 
//* v1.5	September 2005
//*	By : Bauke Siderius		
//*	Discription : ISP/ICP gateway code for LPC900 programmer using MCB900 
//*
//* Modified by ed bear 2017
*/

#include "progdef.h"

//***************************************************************************
//* Global variable used for passing parameters
//***************************************************************************
unsigned char reg7;

//***************************************************************************
//* buffers for read record
//***************************************************************************
unsigned char address_low = 0;					// low address
unsigned char address_high = 0;					// high address
unsigned char checksum = 0;						// checksum
unsigned char nbytes = 0;						// number of data bytes
unsigned char record_type = 0;					// record type
unsigned char data_bytes[64];				// data buffer
unsigned char program_byte;						// byte to be programmed

void setup() {
  //initialize output pins
  pinMode(PCL, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(VDD, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  //PDA changes direction based on data direction
  pinMode(PDA, OUTPUT);
  
  //turn target off
  digitalWrite(VDD, LOW);
  digitalWrite(RESET, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(115200);
  
  //wait for things to calm down electrically
  delay(500);
  Serial.println("calling icp...");
  
  //enter in circuit programming mode
  enter_icp();
  digitalWrite(LED_BUILTIN, LOW);
  
#ifdef HEADLESS
  //erase chip    
  Serial.println("global erase...");
  erase_global();
  delay(250);                                 //why rush?
#endif
}

void loop() {
  unsigned char index;
  checksum = 0;								// clear checksum before loading file
  delayMicroseconds(1000);    //why rush?
  //program chip
new_record:
  while(echo() != ':');						// record starts with a ':'
  nbytes = get2();							// get number of bytes in record
  address_high = get2();						// get MSB of load address
  address_low = get2();						// get LSB of load address
  record_type = get2();						// get record type
  
  for(index=0; index < nbytes; index++)		// read record data to buffer
  {
    data_bytes[index] = get2();				// put databytes in an array
  }
  
  reg7 = checksum;							// put calculated checksum in reg7
  if (reg7 != get2())							// read and check checksum on record
  {
#ifdef SERIAL_BRIDGE
    Serial.print("X\n");					// print error message
#else
    Serial.println("crc fail...");
#endif
    goto new_record;						// restart HexLoader
  }
  
  if (nbytes == 0 && address_high == 0 &&     //do we have an EOF???
        address_low == 0 && record_type == 1) 
  {
#ifdef HEADLESS
    Serial.print("fin\n");
    digitalWrite(VDD, LOW);
    digitalWrite(RESET, LOW);
    digitalWrite(PDA, LOW);
    digitalWrite(PCL, LOW);
    delay(1000);
    digitalWrite(VDD, HIGH);
    digitalWrite(RESET, HIGH);    
#else   //what does ISP need at EOF
#endif
    while(1) {                               //then we are done, blink forever
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);    
    }
  }
  
  //grabbed a whole hex record
  switch(record_type)							// switch on record type
  {
    
    case PROGRAM:							// program record type
    {
#ifdef HEADLESS                       
      Serial.print("Writing ");              
      Serial.print(nbytes);
      Serial.print(" bytes to: ");
      Serial.print(address_high, HEX);
      Serial.print(address_low, HEX);
                                    //config bytes are just
      if (address_high == 0xff) {         //records at high address
        Serial.print(" - conf byte skipped\n");
//        Serial.print(" - conf byte\n");
//        for(index=0; index < nbytes; index++) {
//          write_config_byte(address_low & 0x0F, data_bytes[index]);
//        }                               //but they have a special 
        break;                          //write procedure
      }                                   
#endif
      Serial.print(".\n");            // send ok message
      program_record();
      break;
    }

#ifdef SERIAL_BRIDGE
//following codes are from a ISP programmer only
    case MISC_WRITE:						// misc write record type
    { 
      write_config();						// write config byte
      Serial.print(".\n");						// send ok message
      break;
    }

    case MISC_READ:							// misc read record type
    {
      read_config();						// read config byte
      print_hex_to_ascii(data_bytes[0]);	// send config byte in ascii
      Serial.print(".\n");						// send ok message
      break;
    }
    
    case ERASE:								// erase record type
    {
      if(data_bytes[0] == 0)				// check if dbytes[0] indicates page erase
      {
        erase_page();					// try erase a page and get status
        Serial.print(".\n");					// send ok message
      }  
      else if(data_bytes[0] == 1)			// check if dbytes[0] indicates sector erase
      {
        erase_sector();					// try erase a sector and get status
        Serial.print(".\n");					// send ok message
      }
      else
      {
        Serial.print("R\n");					// send error message
      }
      break;
    }
    
    case SECTOR_CRC:						// sector CRC record type
    {
      crc_sector();						// try sector CRC and get status
      Serial.print(data_bytes[3]);	// send first CRC in ascii
      Serial.print(data_bytes[2]);	// send second CRC in ascii
      Serial.print(data_bytes[1]);	// send third CRC in ascii
      Serial.print(data_bytes[0]);	// send fourth CRC in ascii
      Serial.print(".\n");						// send ok message
      break;
    }
    
    case GLOBAL_CRC:
    {  	
      crc_global();
      Serial.print(data_bytes[3]);	// send first CRC in ascii
      Serial.print(data_bytes[2]);	// send second CRC in ascii
      Serial.print(data_bytes[1]);	// send third CRC in ascii
      Serial.print(data_bytes[0]);	// send fourth CRC in ascii
      Serial.print(".\n");						// send ok message
      break;
    }
    
    case CHIP_ERASE:						// chip erase record type	
    {
      erase_global();						// try erase global and get status
      Serial.print(".\n");						// send ok message
      break;
    }
    
    case READ_VERSION:						// read version record type
    {
      Serial.print(ISP_VERSION);	// send ISP version
      Serial.print(ICP_VERSION);	// send ICP version
      Serial.print(".\n");						// send ok message     
      break;
    }
    
    default:									// incorrect record type	
    {
      Serial.print("R\n");							// send error message
      break;
    }
    
#else
    default:                  // incorrect record type  
    {
      Serial.print("Unhandled HEX in memory\n");  // send error message
      break;
    }
#endif
	}
}

//***************************************************************************
//* enter_icp()
//* Input(s) : none.
//* Returns : none.
//* Description : function to pulse reset to enter ICP mode
//***************************************************************************
void enter_icp(void)
{	
    char pulses = 0;
    int delay = 0;
    digitalWrite(VDD, LOW);						// turn off VDD
    digitalWrite(RESET, LOW);					// turn off Reset								
    digitalWrite(VDD, HIGH);						// turn on VDD
     //wait about 250 ms cause EPM900 does
    for(pulses = 0; pulses < 25; pulses++) {
      delayMicroseconds(10000);
    }
    for(pulses = 0; pulses < 7; pulses++)			// pulse reset 7 times
    {
        digitalWrite(RESET, HIGH);					// hold reset high
        delayMicroseconds(20); 
        digitalWrite(RESET, LOW);					// hold reset low
        delayMicroseconds(20);
    }
    digitalWrite(RESET, HIGH);						// hold reset high
    //delayMicroseconds(6500);
    digitalWrite(PCL, HIGH);
    //delayMicroseconds(4500);
}

//***************************************************************************
//* shift_out()
//* Input(s) : data_byte.
//* Returns : none.
//* Description : function to shift out data to the part being programmed
//***************************************************************************
void shift_out(char data_byte)
{
  digitalWrite(7, HIGH);
  char shift_bit;  
  char temp_byte = 0;
  pinMode(PDA, OUTPUT);              // make PDA output
  temp_byte = data_byte;            // put databyte in a temp byte
  for(shift_bit = 0; shift_bit < 8; shift_bit++)// shift out 8 bits
  {
    digitalWrite(PCL, LOW);                  // hold clock line low
    //delayMicroseconds(10);
    if(temp_byte & 0x01)            // check if LSB is set
    {
      digitalWrite(PDA, HIGH);                  // set data-line high
    }
    else
    {
      digitalWrite(PDA, LOW);                  // set data-line low
    }
  temp_byte = (data_byte >>= 1);        // shift databyte right one, put in temp
  digitalWrite(PCL, HIGH);                  // clock  databit
  //delayMicroseconds(10);
  }
  digitalWrite(PDA, HIGH);                    // set dataline high after transfer
  digitalWrite(PCL, HIGH);                    // hold dataline high after transfer
//    pinMode(PDA, OUTPUT);              // make PDA output
//    shiftOut(PDA, PCL, LSBFIRST, data_byte);
//    digitalWrite(PDA, HIGH);						// set dataline high after transfer
//    digitalWrite(PCL, HIGH);						// hold clock high after transfer
    digitalWrite(7, LOW);
}	

//***************************************************************************
//* shift_in()
//* Input(s) : none.
//* Returns : Data shifted back from part that is being programmed.
//* Description : function read data from the part being programmed
//***************************************************************************
char shift_in(void)
{
  digitalWrite(6, HIGH);
  char data_byte = 0;
  char shift_bit = 0;
  digitalWrite(PCL, LOW);
  pinMode(PDA, INPUT);
  for(shift_bit = 0; shift_bit < 8; shift_bit++)// shift in 8 bits
  {
  digitalWrite(PCL, HIGH);                  // clock out databit
  //delayMicroseconds(10);
  if(digitalRead(PDA))                   // check if PDA is set  
  {
    data_byte |= 0x80;            // set bit
    }
    else
  {
      data_byte &= ~0x80;           // or clear bit
    }
    if(shift_bit < 7)             // don't shift last bit MSB
    { 
    data_byte >>= 1;
    }
  digitalWrite(PCL, LOW);                  // hold clock line low
  //delayMicroseconds(10);
  }
  digitalWrite(PCL, LOW);                    // set clockline low after transfer
  digitalWrite(PDA, HIGH);                    // hold dataline high
  pinMode(PDA, OUTPUT);
  digitalWrite(6, LOW);
  return data_byte;               // return clocked in bit

//    char data_byte = 0;
//    //digitalWrite(PCL, LOW);                         //maybe uneeded
//    pinMode(PDA, INPUT);							//make PDA input only
//    delayMicroseconds(50);
//    data_byte = shiftIn(PDA, PCL, LSBFIRST);
//    digitalWrite(PCL, LOW);					        // set clockline low after transfer
//    pinMode(PDA, OUTPUT);							// make PDA output
//    digitalWrite(PDA, HIGH);						// hold dataline high
//    digitalWrite(PCL, HIGH);            // hold clock high after transfer
//    digitalWrite(6, LOW);
//    return data_byte;								// return clocked in byte

}

//***************************************************************************
//* program()
//* Input(s) : none.
//* Returns : none.
//* Description : funtion to program the page register into Flash
//***************************************************************************
void program(void)
{
  unsigned char read_data = 0;
  shift_out(WR_FMADRL);							// write address low command page aligned
  shift_out(address_low);						// write address from the isp command
  shift_out(WR_FMDATA);							// write to FMDATA
  shift_out(program_byte);						// load databyte
  shift_out(WR_FMADRH);							// write address high command
  shift_out(address_high);						// write address from the isp command
  shift_out(WR_FMCON);							// write to FMCON
  shift_out(PROG);								// program commmand
  do
  {
    shift_out(RD_FMCON);						// read FMCON command
	  read_data = shift_in();						// shift in data from FMCON
    if (read_data & 0x0F) {
      Serial.print("err resp:");          // check for done status MSB
      Serial.println(read_data, HEX);
    }
  } while (read_data & 0x80);
}

//***************************************************************************
//* erase_global()
//* Input(s) : none.
//* Returns : none.
//* Description : function to erase all Flash and config
//***************************************************************************
void erase_global(void)
{
  unsigned char read_data = 0;
  char index, dummy;
  shift_out(WR_FMCON);							// write FMCON command
  shift_out(ERS_G);								// write erase global command
//***************************************************************************
//* This code must be added due to a bug in erase global
//* otherwise it will stay busy forever
//***************************************************************************
  for(index = 0; index < 25; index++)			// read for about 5ms
  {
    shift_out(RD_FMDATA_I);						// read data increment address
    dummy = shift_in();							// do dummy reads
  } 
//***************************************************************************
//* End added code for erase global bug
//***************************************************************************
  do										
  {
    shift_out(RD_FMCON);						// read FMCON command
	  read_data = shift_in();						// shift in data from FMCON
    if (read_data & 0x0F) {
      Serial.print("err resp:");          // check for done status MSB
      Serial.println(read_data, HEX);
    }
  } while (read_data & 0x80); 
}

//***************************************************************************
//* erase_sector()
//* Input(s) : none.
//* Returns : none.
//* Description : function to erase a sector in Flash
//***************************************************************************
void erase_sector(void)
{
  unsigned char read_data = 0;
  shift_out(WR_FMADRH);							// write address high command
  shift_out(data_bytes[1]);						// write address stripped from the isp command
  shift_out(WR_FMCON);							// write to FMCON
  shift_out(ERS_S);								// write erase sector command
  do
  {
    shift_out(RD_FMCON);						// read FMCON command
	read_data = shift_in();						// shift in data from FMCON
  }
  while(read_data & 0x80);						// check for done status MSB   
}

//***************************************************************************
//* erase_page()
//* Input(s) : none.
//* Returns : none.
//* Description : function to erase a page in Flash
//***************************************************************************
void erase_page(void)
{
  unsigned char read_data = 0;					// declare local read_data variable
  shift_out(WR_FMADRL);							// write address low command
  shift_out(data_bytes[2]);						// write address stripped from the isp command
  shift_out(WR_FMADRH);							// write address high command
  shift_out(data_bytes[1]);						// write address stripped form the isp command
  shift_out(WR_FMCON);							// write to FMCON
  shift_out(ERS_P);								// write erase page command
  do											// loop till status is done
  {
    shift_out(RD_FMCON);						// read FMCON command
	read_data = shift_in();						// shift in data from FMCON
  }
  while(read_data & 0x80);						// check for done status MSB     
}

//***************************************************************************
//* crc_global()
//* Input(s) : none.
//* Returns : none.
//* Description : function to read the global CRC
//***************************************************************************
void crc_global(void)
{
  unsigned char read_data = 0;					// declare local read_data variable
  unsigned char crc_index = 0;					// declare local crc_index variable
  shift_out(WR_FMCON);							// write to FMCON
  shift_out(CRC_G);								// write global CRC command
  do
  {
    shift_out(RD_FMCON);						// read FMCON command
	  read_data = shift_in();						// shift in data from FMCON
  }	
  while(read_data & 0x80);						// check for done status MSB
  for(crc_index = 0; crc_index < 4; crc_index++)// read 4 CRC bytes
  {
    shift_out(RD_FMDATA_I);						// write read data and increment command    
    data_bytes[crc_index] = shift_in();			// read CRC bytes
  }    
}

//***************************************************************************
//* crc_sector()
//* Input(s) : none.
//* Returns : none.
//* Description : function to read the CRC of a sector
//***************************************************************************
void crc_sector(void)
{
  unsigned char read_data = 0;					// declare local read_data variable
  unsigned char crc_index = 0;					// declare local crc_index variable
  shift_out(WR_FMADRH);							// write address high command
  shift_out(data_bytes[0]);						// write address stripped form the isp command
  shift_out(WR_FMCON);							// write to FMCON
  shift_out(CRC_S);								// write sector CRC command
  do
  {
    shift_out(RD_FMCON);						// read FMCON command
	read_data = shift_in();						// shift in data from FMCON
  }
  while(read_data & 0x80);						// check for done status MSB
  for(crc_index = 0; crc_index < 4; crc_index++)// read 4 CRC bytes
  {
    shift_out(RD_FMDATA_I);						// write read data and increment command    
    data_bytes[crc_index] = shift_in();			// read CRC bytes
  }  
}

//***************************************************************************
//* read_config()
//* Input(s) : none.
//* Returns : none.
//* Description : function to read from the configuration space
//***************************************************************************
void read_config(void)
{
  shift_out(WR_FMCON);							// write to FMCON
  shift_out(CONF);								// write acces config command
  shift_out(WR_FMADRL);							// write address low command
  shift_out(data_bytes[0]);						// write address stripped from the isp command
  shift_out(RD_FMDATA);							// read FMDATA command
  data_bytes[0] = shift_in();					// read config
}

//need a very different implentation for unparsed hex conf bytes
#ifdef HEADLESS
//***************************************************************************
//* write_config()
//* Input(s) : address [de-mapped from fffx, data
//* Returns : none.
//* Description : function to write to the configuration space
//***************************************************************************
void write_config_byte(unsigned char addy, unsigned char data) {
    unsigned char read_data = 0;
    //clear.. conf protection
    shift_out(WR_FMCON);            // write to FMCON
    shift_out(CCP);               // write clear config protection
    shift_out(WR_FMDATA);           // write FMDATA command
    shift_out(CLR_CCP_KEY);           // wirte clear config protection key command
    do                      // loop while status is busy
    {
      shift_out(RD_FMCON);            // read FMCON command
      read_data = shift_in();         // shift in data from FMCON
      if (read_data & 0x0F) {
        Serial.print("err resp:");          // check for done status MSB
        Serial.println(read_data, HEX);
      }
    }
    while(read_data & 0x80);          // check for done status MSB
    //then write....
    shift_out(WR_FMCON);						// write to FMCON
    shift_out(CONF);							// write acces config command
    shift_out(WR_FMADRL);						// write address low command
    shift_out(addy);					// write address stripped from the isp command
    shift_out(WR_FMDATA);						// write FMDATA command
    shift_out(data);					// wirte value stripped from the isp command
    do											// loop while status is busy
    {
      shift_out(RD_FMCON);						// read FMCON command
	    read_data = shift_in();					// shift in data from FMCON
      if (read_data & 0x0F) {
        Serial.print("err resp:");          // check for done status MSB
        Serial.println(read_data, HEX);
      }
    }
    while (read_data & 0x80); 
}
#else
//***************************************************************************
//* write_config()
//* Input(s) : none.
//* Returns : none.
//* Description : function to write to the configuration space
//***************************************************************************
void write_config(void)
{
  unsigned char read_data = 0;
  if(data_bytes[0] == 0x10)
  {
    shift_out(WR_FMCON);						// write to FMCON
    shift_out(CCP);								// write clear config protection
    shift_out(WR_FMDATA);						// write FMDATA command
    shift_out(CLR_CCP_KEY);						// wirte clear config protection key command
    do											// loop while status is busy
    {
      shift_out(RD_FMCON);						// read FMCON command
	  read_data = shift_in();					// shift in data from FMCON
    }
    while(read_data & 0x80);					// check for done status MSB     
  }
  else
  {
    shift_out(WR_FMCON);						// write to FMCON
    shift_out(CONF);							// write acces config command
    shift_out(WR_FMADRL);						// write address low command
    shift_out(data_bytes[0]);					// write address stripped from the isp command
    shift_out(WR_FMDATA);						// write FMDATA command
    shift_out(data_bytes[1]);					// wirte value stripped from the isp command
    do											// loop while status is busy
    {
      shift_out(RD_FMCON);						// read FMCON command
	  read_data = shift_in();					// shift in data from FMCON
    }
    while(read_data & 0x80);					// check for done status MSB 
  }    
}
#endif

//***************************************************************************
//* echo()
//* Input(s) : none.
//* Returns : character read from ISP record.
//* Description : check if in ICP mode
//***************************************************************************
unsigned char echo()
{
#ifdef HEADLESS       //need to check this on non AVR platforms
    if (hexIter < Blinky_hex_len) {
        return pgm_read_byte_near(Blinky_hex + hexIter++);
        //return reg7;
    }
#else
    unsigned char ch;
    while(!RI);									// wait until reception is complete
    RI = 0;		
    ch = SBUF;									// read UART buffer		
    while(!TI);									// wait until previous
    TI=0;										// transmission is complete
    SBUF = ch;									// send character
    if (ch&0x40)	ch&=0xDF;					// if character, then make it upper case
    return ch;
#endif
}

//***************************************************************************
//* get2()
//* Input(s) : none.
//* Returns : byte read from the ISP record.
//* Description : check if in ICP mode
//***************************************************************************
unsigned char get2()
{
  unsigned char record_byte;		
  record_byte = ascii_to_hex(echo())<<4;		// read high nibble
  record_byte += ascii_to_hex(echo());			// read low nibble
  checksum -= record_byte;						// update checksum
  return record_byte;							// return byte
}

//***************************************************************************
//* ascii_to_hex()
//* Input(s) : character in ascii format
//* Returns : character in hex format
//* Description : converts ascii to hex
//***************************************************************************
unsigned char ascii_to_hex(unsigned char ch)
{
  if (ch & 0x40)								// convert ASCII character
  {	
    ch += 0x09;
  }
  ch &= 0x0F;									// into 2 digit Hex
  return ch;
}



//***************************************************************************
//* program_record()
//* Input(s) : none.
//* Returns : none.
//* Description : function to program bytes from hex record
//* 				Warning the hex file records need to be page aligned 
//***************************************************************************
void program_record(void)		 				
{
  char index;
    for(index = 0; index < nbytes; index++)		// program all individual bytes
    {
      program_byte = data_bytes[index];			// get byte to be programmed
      program();									// program the byte
      address_low++;								// update address for programmed byte
      if(address_low == 0x00)						// check if low address rolls over
      {
        address_high += 1;						// then increment high address
      }   
    }    
}
