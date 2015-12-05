
#line 1 "temp.c" /0
 include <reg936.h>
  
#line 1 "iTrip.h" /0


 
 
 
 
 
 typedef unsigned char byte;
 typedef unsigned int word;
 
 
 
 
 
 
 
 
 
 







 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 void setup ();   
 void delay (word cnt);
 void shiftout8 (byte d);
 void shiftout16 (word d);
 void shiftout32 (word dh, word dl);
 void txProg ();
 void txStero ();
 void txMono ();
 void setFreq (word freq);
 void incFreq ();
 void decFreq ();
 void setChan (byte numChan);
 bit getBit ();
 









 
 void deInterleave ();
 void deleaveBits ();
 void testDI();






 
 void interleave ();
 void leaveBits ();
 void testI ();
 void sync();
 void testEncode(byte cnt);
 void encode();
 void encode_ASM ();
 void testDecode(char error);
 void decode ();
 void decode_ASM();








 
 word autotune ();
 
 
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
 
#line 2 "temp.c" /0
 
 
 extern volatile unsigned char inBuf[6], interBuf[6];
 extern volatile unsigned char *outBuf;
 extern volatile unsigned char inRegister, inBit, inByte, interByte;
 
 extern volatile bit barkerFlag, notBarkerFlag, inEmpty;
 
 void leaveBits () {
 if(!inEmpty || interByte != 6 || inByte != 6) {
 return;
 }
 for (interByte = 7; interByte > 3; --interByte) {
 for(inByte = 7; inByte > 3; --inByte) {
 inBuf[inByte] <<= 1;
 if (interBuf[interByte] & 0x80) {
 inBuf[inByte] += 0x10;
 }
 if (interBuf[interByte] & 0x40) {
 ++inBuf[inByte]; 
 }
 interBuf[interByte] <<= 2; 
 }
 }
 for (interByte; interByte; interByte--) {
 while(inByte--) {
 inBuf[inByte] <<= 1;
 if (interBuf[interByte] & 0x80) {
 inBuf[inByte] += 0x10;
 }
 if (interBuf[interByte] & 0x40) {
 ++inBuf[inByte]; 
 }
 interBuf[interByte] <<= 2; 
 }
 }
 }
