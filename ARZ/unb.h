#ifndef UNB_H
#define UNB_H

#define FEM_MAX_DBM 26
#define FEM_GAIN 14
#define AX5043_MAX_DBM 15
#define TX_RX_SEL PORTC_0
#define PA_EN PORTC_4
#define ANT_SEL PORTB_0
#define TCXO_EN PORTB_1


enum rxtxmode
{
    RX = 0,
    TX = 1,
    IDLE = 2
};

enum antsel
{
    ANT1 = 1,
    ANT2 = 0
};

typedef enum {UNB_PROTOCOL_B100, UNB_PROTOCOL_C50, UNB_PROTOCOL_DL_RX, UNB_PROTOCOL_DL_TX,} unb_protocol_t;

extern const uint16_t AX5043_power[26];
extern volatile unb_protocol_t unb_protocol;
extern bool deglitch_busy;

void        HopChannel();
//void        UNB_SetModeAndPower(uint8_t dBm, uint8_t mode, uint8_t ant);
void        UNB_SetPower(int8_t dBm);
void        UNB_Send(uint8_t __xdata* buf, uint32_t serial, uint8_t len);
void        UNB_ProtocolC_Send(uint8_t __xdata* buf, uint32_t serial);
uint8_t     UNB_Init(unb_protocol_t protocol);
uint8_t     UNB_Deinit();
uint8_t     UNB_GetCiter();
void        calibrate_oscillators(void);

__reentrantb void ax5043_set_constants(void) __reentrant;

#endif
