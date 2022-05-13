#ifndef _UARTH_
#define _UARTH_

#define RX_BUF_SIZE	8

// midi in definition

typedef struct m_in_s {
  unsigned char
    typeChan,          // type              )
//    channel,       // channel           )  current message 
    count,         // data counter      )
    controller,    // controller number )
    pitch;         // key pitch         )
//	song;          // song number
// Always acted on, never persistent
//    velocity,      //key velocity      ) last note message or pressure message data
//    pressure,      // key pressure      )
  unsigned short
    position;      // song position
	short bend;      // pitch bend
} m_in_t;


void uart_transmit (unsigned char value);
unsigned char uart_get (void);
void uart_init (void);
unsigned char ascii_to_hex(unsigned char ch);
void print_hex_to_ascii(unsigned char ch);
#endif // _UARTH_