/* Warning: This file is automatically generated by AX-RadioLAB.
Manual changes are overwritten! */

#include "../COMMON/axradio.h"


#define MINI_KIT
//#define USE_LCD
//#define USE_DBGLINK
//#define USE_COM0
//#define DEBUGMSG
#define MCU_SLEEP

/*
//*****LPXOSC*******
#define WTIMER0_CLKSRC	CLKSRC_LPXOSC
#define WTIMER0_PRESCALER 0x07      //512 Hz
*/

//************LPOSC************
#define WTIMER0_CLKSRC	CLKSRC_LPOSC
#define WTIMER0_PRESCALER 0x05  //40Hz



//#define WTIMER0_PERIOD    0x1900
#define RADIO_MODE        AXRADIO_MODE_ASYNC_TRANSMIT
extern const struct axradio_address __code remoteaddr;
extern const struct axradio_address_mask __code localaddr;
extern const uint8_t __code demo_packet[136];
extern const uint8_t __code framing_insert_counter;
extern const uint8_t __code framing_counter_pos;

extern const uint16_t __code lpxosc_settlingtime;
