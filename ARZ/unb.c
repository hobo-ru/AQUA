#include <ax8052f143.h>
#include <libmftypes.h>
#include <libmfradio.h>
#include <libmfwtimer.h>
#include <libmfcrc.h>
#include "../AX_Radio_Lab_output/configmaster.h"
#include "../COMMON/misc.h"
#include "../COMMON/configcommon.h"
#include "../COMMON/easyax5043.h"
#include "unb.h"
#include "application.h"
#include "xtea.h"




bool deglitch_busy = 0;

uint8_t iter=0;


const uint32_t __code*  UNB_KEY = (const uint32_t __code*)KEYPTR;


const uint16_t AX5043_power[26] = {0x00aa, 0x00bf, 0x00d1, 0x00ec, 0x010f, 0x0132, 0x0156, 0x017f, 0x01af, 0x1e0, 0x207, 0x244, 0x290, 0x2eb, 0x35e, 0x3d6, 0x406, 0x4a9, 0x57c, 0x600, 0x700, 0x800, 0x9d4, 0xc00, 0xf00, 0xfff};

//const uint16_t AX5043_power[16] = {0x207, 0x244, 0x290, 0x2eb, 0x35e, 0x3d6, 0x406, 0x4a9, 0x57c, 0x600, 0x700, 0x800, 0x9d4, 0xc00, 0xf00, 0xfff};

// Zigzag code permutation table
const uint8_t  n[4][128] =
{
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127},
    {104,52,43,96,31,7,71,78,58,37,93,25,125,85,42,111,6,95,72,117,27,51,63,84,91,35,120,26,97,45,110,70,1,28,86,114,53,67,12,127,40,101,73,94,115,61,20,126,3,46,92,116,9,56,87,77,109,44,65,54,100,118,2,34,21,41,76,14,69,124,90,18,103,48,113,36,0,81,13,62,24,38,105,68,15,75,88,50,122,29,83,102,8,16,108,23,32,49,99,112,19,55,89,11,107,82,47,98,22,30,60,80,66,121,10,57,17,39,79,4,64,123,33,59,106,74,5,119},
    {26,10,105,48,38,84,76,57,23,125,115,3,106,33,77,99,71,113,22,1,44,87,8,31,111,96,2,42,70,81,13,93,122,37,114,88,63,107,50,40,82,116,68,6,127,16,51,73,61,83,46,0,126,104,78,67,41,119,28,11,56,47,4,21,52,66,15,98,24,7,30,91,112,35,55,124,64,5,95,32,49,9,85,65,43,18,92,36,12,86,118,60,25,72,53,80,123,45,58,102,110,120,89,34,17,75,94,27,100,62,20,39,108,90,69,117,97,59,79,109,101,19,121,54,29,14,74,103},
    {0,93,104,36,87,125,23,97,44,107,11,3,70,35,60,77,29,84,6,91,126,15,76,56,4,89,115,99,43,22,122,16,105,55,2,113,78,51,63,14,120,102,8,19,68,111,86,47,64,32,121,72,59,108,96,80,25,67,118,12,58,127,20,90,9,37,103,53,62,69,85,10,110,34,100,119,39,73,1,83,48,112,30,54,65,45,5,123,101,26,88,18,46,95,40,109,7,27,57,66,116,38,75,92,21,52,61,28,106,114,94,33,17,79,42,71,124,50,82,13,31,41,117,74,98,81,24,49}
};

void HopChannel()
{
    channel = (channel+37) % 251;
}

uint8_t UNB_GetCiter() {return iter;}


/*void UNB_SetPower(int8_t dBm)
{
    AX5043_TXPWRCOEFFB1 = AX5043_power[dBm+10] >> 8;
    AX5043_TXPWRCOEFFB0 = AX5043_power[dBm+10] &0xFF;
}
*/

void UNB_SetPower(int8_t dBm)
{
    AX5043_TXPWRCOEFFB1 = AX5043_power[dBm+10] >> 8;
    AX5043_TXPWRCOEFFB0 = AX5043_power[dBm+10] &0xFF;
}

/*void UNB_SetModeAndPower(uint8_t dBm, uint8_t mode, uint8_t ant)
{
    if(dBm > FEM_MAX_DBM) dBm = FEM_MAX_DBM;

    DIRB |= 0x01; //ANT_SEL = output
    DIRC |= 0x11; //TXRX_EN, PA_EN = output

    ANT_SEL = ant;

    if(mode == TX)
    {
        if(dBm <= AX5043_MAX_DBM)
        {
            // set power
            AX5043_TXPWRCOEFFB1 = AX5043_power[dBm + 10] >> 8;
            AX5043_TXPWRCOEFFB0 = AX5043_power[dBm + 10] &0xFF;

            // select differential PA
            AX5043_MODCFGA = 0x5;

            // FEM PA bypass
            TX_RX_SEL = RX;
            PA_EN = 0;
        }
        else
        {
            // set power, considering FEM gain
            AX5043_TXPWRCOEFFB1 = AX5043_power[dBm + 10 - FEM_GAIN] >> 8;
            AX5043_TXPWRCOEFFB0 = AX5043_power[dBm + 10 - FEM_GAIN] &0xFF;

            // select single-ended PA
            AX5043_MODCFGA = 0x6;

            // enable FEM PA
            TX_RX_SEL = TX;
            PA_EN = 1;
        }
    }
    else // mode == RX or IDLE
    {
        // select differential PA
        AX5043_MODCFGA = 0x5;
        // enable FEM PA bypass
        TX_RX_SEL = RX;
        PA_EN = 0;
        ANT_SEL = 0;
    }
}
*/

void UNB_Send(uint8_t __xdata* buf, uint32_t serial, uint8_t len)
{
    static uint8_t __xdata tx_packet_encoded[256];
    static uint8_t __xdata tx_packet[32];
    uint8_t preambula[] = {0xAA, 0xF0, 0x99};
    uint8_t ptr = 0, ptr_enc = 0, i, j;
    uint32_t crc = 0xFFFFFFFF;
    uint8_t length_header[21] = {0,0,0,1,2,3,4,5,6,7,8,9,10,11,11,12,12,13,13,14,14};

    if(length_header[len+1] == (length_header[len])) len++;

    // form UNB protocol B packet
    // [3B preambula] [1/2B length] [4B serial ID] [2..20B payload] [4B CRC]
    tx_packet[ptr++] = length_header[len];
    tx_packet[ptr++] = (uint8_t)(serial >> 24);
    tx_packet[ptr++] = (uint8_t)(serial >> 16);
    tx_packet[ptr++] = (uint8_t)(serial >> 8);
    tx_packet[ptr++] = (uint8_t)(serial);
    for(i = 0; i < len; i++)
    {
        tx_packet[ptr++] = buf[i];
    }

    for(i = 0; i < 8; i++)  if(UNB_KEY[i]) break;
    if(i != 8) XTEA_Encode(&tx_packet[ptr-8], UNB_KEY);

    crc = crc_crc32_msb(tx_packet, len+5, crc) ^ 0xFFFFFFFF;
    tx_packet[ptr++] = (uint8_t)(crc >> 24);
    tx_packet[ptr++] = (uint8_t)(crc >> 16);
    tx_packet[ptr++] = (uint8_t)(crc >> 8);
    tx_packet[ptr++] = (uint8_t)(crc);

    //encoding is basically padding each bit with 3 ones
    for(i = 0; i < sizeof(preambula); i++)  // preambula
    {
        for(j = 0; j < 4; j++)
        {
            tx_packet_encoded[ptr_enc] = 0x77;
            tx_packet_encoded[ptr_enc] |= (preambula[i]<<(2*j)) &0x80;
            tx_packet_encoded[ptr_enc] |= ((preambula[i]<<(2*j+1)) >> 4) &0x08;
            ptr_enc++;
        }
    }

    for(j = 2; j < 4; j++)
    {
        tx_packet_encoded[ptr_enc] = 0x77;
        tx_packet_encoded[ptr_enc] |= (tx_packet[0]<<(2*j)) &0x80;
        tx_packet_encoded[ptr_enc] |= ((tx_packet[0]<<(2*j+1)) >> 4) &0x08;
        ptr_enc++;
    }

    for(i = 1; i < ptr; i++)  // payload
    {
        for(j = 0; j < 4; j++)
        {
            tx_packet_encoded[ptr_enc] = 0x77;
            tx_packet_encoded[ptr_enc] |= (tx_packet[i]<<(2*j)) &0x80;
            tx_packet_encoded[ptr_enc] |= ((tx_packet[i]<<(2*j+1)) >> 4) &0x08;
            ptr_enc++;
        }
    }

    for(i = 0; i < 2; i++)  // padding zeroes TODO do we still need them?
    {
        for(j = 0; j < 4; j++)
        {
            tx_packet_encoded[ptr_enc] = 0x77;
            tx_packet_encoded[ptr_enc] |= (0xFF<<(2*j)) &0x80;
            tx_packet_encoded[ptr_enc] |= ((0xFF<<(2*j+1)) >> 4) &0x08;
            ptr_enc++;
        }
    }

    TCXO_EN = 1;
    UNB_Init(UNB_PROTOCOL_B100);
    for(int i=0; i<3; i++)
    {
        HopChannel();
        deglitch_busy = 1;
        delay_ms(1);
        axradio_transmit(0, tx_packet_encoded, ptr_enc);
        delay_ms(300);
        GetVoltageOrTemp(1);
        while(deglitch_busy)
        {
            wtimer_runcallbacks();
        }

    }

    UNB_Deinit();
    TCXO_EN = 0;
}

static void CalculateZigzag(uint8_t __xdata* src_buf, uint8_t __xdata* dst_buf, bool parity)
{
    uint8_t b0;     // source bit 0
    uint8_t b1;     // source bit 0
    uint8_t bprev;  // previous result bit
    uint8_t res;    // result bit

    // code[N] is zigzag code for Nth permutation
    uint8_t code[4][8]={{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};

    // calculate zigzag code for each permutation
    for(int j=0; j<4; j++)
    {
        for(uint8_t i=0; i<64; i++) //payload 16bytes, each zigzag code 8bytes
        {
            b0      = (src_buf[ n[j][ i ]  /8] << ( n[j][ i ]  %8)) & 0x80;
            b1      = (src_buf[ n[j][64+i] /8] << ( n[j][64+i] %8)) & 0x80;
            bprev   = (code[j][   (i-1)    /8] << (   (i-1)    %8)) & 0x80;
            res     =  b0 ^ b1 ^ bprev;
            code[j][i/8] |= res >> (i%8);
        }
    }

    // append result to dst_buf
    for(int i=0; i<8;i++)
    {
        // depending on parity, use either odd or even parts of zigzag code
        dst_buf[i]      = (code[0][i] & (parity ? 0xAA : 0x55)) | (code[1][i] & (parity ? 0x55 : 0xAA));
        dst_buf[i+8]    = (code[2][i] & (parity ? 0xAA : 0x55)) | (code[3][i] & (parity ? 0x55 : 0xAA));
    }
}

static void UNB_ProtocolC_SendOneMsg(uint8_t __xdata* buf, uint32_t serial, uint8_t parity)
{
    static uint8_t __xdata tx_packet_encoded[255];
    static uint8_t  __xdata tx_packet[64];
    uint8_t preambula[] = {0x97, 0x15, 0x7A};
    uint8_t ptr = 0, ptr_enc = 0, i, j;
    uint32_t crc = 0xFFFFFFFF;

    deglitch_busy = 1;

    // clear tx_packet buffer
    for(i=0;i<sizeof(tx_packet);i++)    tx_packet[i]=0;

    // form UNB protocol B packet
    tx_packet[ptr++] = 0x6F;//header
    tx_packet[ptr++] = (uint8_t)(serial >> 8);
    tx_packet[ptr++] = (uint8_t)(serial);
    tx_packet[ptr++] = (iter)&0xF;
    for(i = 0; i < 8; i++)
    {
        tx_packet[ptr++] = buf[i];
    }

    for(i = 0; i < 8; i++)  if(UNB_KEY[i]) break;
    if(i != 8) XTEA_Encode(&tx_packet[ptr-8], UNB_KEY);

    crc = crc_crc32_msb(tx_packet, 8+4, crc) ^ 0xFFFFFFFF;
    tx_packet[ptr++] = (uint8_t)(crc >> 24);
    tx_packet[ptr++] = (uint8_t)(crc >> 16);
    tx_packet[ptr++] = (uint8_t)(crc >> 8);
    tx_packet[ptr++] = (uint8_t)(crc);

    CalculateZigzag(tx_packet, tx_packet + ptr, parity);
    ptr += 16;

    //encoding is basically padding each bit with 3 ones
    for(i = 0; i < sizeof(preambula); i++)  // preambula
    {
        for(j = 0; j < 4; j++)
        {
            tx_packet_encoded[ptr_enc] = 0x77;
            tx_packet_encoded[ptr_enc] |= (preambula[i]<<(2*j)) &0x80;
            tx_packet_encoded[ptr_enc] |= ((preambula[i]<<(2*j+1)) >> 4) &0x08;
            ptr_enc++;
        }
    }

    for(i = 0; i < ptr; i++) // payload
    {
        for(j = 0; j < 4; j++)
        {
            tx_packet_encoded[ptr_enc] = 0x77;
            tx_packet_encoded[ptr_enc] |= (tx_packet[i]<<(2*j))&0x80;
            tx_packet_encoded[ptr_enc] |= ((tx_packet[i]<<(2*j+1)) >> 4)&0x08;
            ptr_enc++;
        }
    }
    axradio_transmit(0, tx_packet_encoded, ptr_enc);

    delay_ms(300);
    GetVoltageOrTemp(1);
    // Wait for tx complete
    while(deglitch_busy)
    {
        wtimer_runcallbacks();
    }
}

void UNB_ProtocolC_Send(uint8_t __xdata* buf, uint32_t serial)
{
    static uint8_t ch = 0;
    TCXO_EN = 1;
    UNB_Init(UNB_PROTOCOL_C50);
    // Send first part
    channel = ch; //first part in lower freq band
    UNB_ProtocolC_SendOneMsg(buf, serial, 0);

    // Send second part
    channel = 150 + ch; //second part in higher freq band
    UNB_ProtocolC_SendOneMsg(buf, serial, 1);
    UNB_Deinit();
    TCXO_EN = 0;
    iter++;
    ch = (ch+17)%101;
}

uint8_t UNB_Init(unb_protocol_t protocol)
{
    uint8_t er;

    switch(protocol)
    {
    case UNB_PROTOCOL_B100:
    case UNB_PROTOCOL_C50:
        TCXO_EN = 1;    // Enable TCXO,
        delay_ms(10);   // Let it settle
        ax5043_set_constants();
        unb_protocol = protocol;
        er = axradio_init();    // Init radio registers
        if (er != AXRADIO_ERR_NOERROR) return 0;
        //axradio_set_local_address(&localaddr);
        //axradio_set_default_remote_address(&remoteaddr);
        er = axradio_set_mode(AXRADIO_MODE_ASYNC_TRANSMIT);
        if (er != AXRADIO_ERR_NOERROR) return 0;
        calibrate_oscillators();
        return 1;

    case UNB_PROTOCOL_DL_RX:
        break;
    case UNB_PROTOCOL_DL_TX:
        break;
    default:
        return 0;
    }
    return 0;
}

uint8_t UNB_Deinit()
{
    uint8_t er;
    er = axradio_set_mode(AXRADIO_MODE_OFF);
    if (er != AXRADIO_ERR_NOERROR) return 0;
    TCXO_EN = 0;
    return 1;
}


#define XTALFREQ   26000000UL
#define XTALDIV    (((XTALFREQ) > 40000000UL) ? 2 : ((XTALFREQ) > 20000000UL) ? 1 : 0)
#define XTALFRQDIV ((XTALFREQ) >> (XTALDIV))
//uint16_t __xdata frcmaxerr;
uint16_t __xdata lpmaxerr;
//uint16_t __xdata frcperiod;
uint16_t __xdata lpperiod;
//uint8_t __xdata frccalcnt;
uint8_t __xdata lpcalcnt;
//uint8_t __xdata clkconsave;

static inline uint16_t myabs(int16_t a)
{
    if(a > 0) return a;
    else return -a;
}

void calibrate_oscillators(void)
{

   // frcperiod = 0;
    lpperiod = 0;
   // frccalcnt = 0;
    lpcalcnt = 0;
   // clkconsave = 0xff;
    ax5043_rclk_enable(XTALDIV);

	uint8_t lposccfg;
	//uint8_t frcosccfg;

    //frcosccfg = 0x70 | ((CLKSRC_RSYSCLK) & 0x07);
    //FRCOSCREF0 = (10000000UL << 8) / ((XTALFRQDIV) >> 6);
    //FRCOSCREF1 = ((10000000UL << 8) / ((XTALFRQDIV) >> 6)) >> 8;
    lposccfg = 0x00 | ((CLKSRC_RSYSCLK) & 0x07);
    LPOSCREF0 = (XTALFRQDIV) / 320UL;
    LPOSCREF1 = ((XTALFRQDIV) / 320UL) >> 8;
	//FRCOSCKFILT0 = 0x0;
	//FRCOSCKFILT1 = 0x40;
	LPOSCKFILT0 = 0x40;
	LPOSCKFILT1 = 0x0;
	//FRCOSCCONFIG = frcosccfg;
	LPOSCCONFIG = lposccfg;

    //frcmaxerr = FRCOSCREF1;
    //frcmaxerr <<= 8;
    //frcmaxerr |= FRCOSCREF0;
    //frcmaxerr /= 500;

    lpmaxerr = LPOSCREF1;
    lpmaxerr <<= 8;
    lpmaxerr |= LPOSCREF0;
    lpmaxerr /= 500;

    //OSCCALIB |= 0x03;
    OSCCALIB |= 0x02;

    for (;;) {
        uint8_t osccal = OSCCALIB;
   /*     if (osccal & 0x40) {

            frcperiod = FRCOSCPER1;
            frcperiod <<= 8;
            frcperiod |= FRCOSCPER0;

            uint16_t tmp = FRCOSCREF1;
            tmp <<= 8;
            tmp |= FRCOSCREF0;

            if (myabs(frcperiod - tmp) > frcmaxerr)
                frccalcnt = 0;
            else if (frccalcnt != 0xff)
                ++frccalcnt;
        }*/
        if (osccal & 0x80) {
            lpperiod = LPOSCPER1;
            lpperiod <<= 8;
            lpperiod |= LPOSCPER0;

            uint16_t tmp = LPOSCREF1;
            tmp <<= 8;
            tmp |= LPOSCREF0;

            if (myabs(lpperiod - tmp) > lpmaxerr)
                lpcalcnt = 0;
            else if (lpcalcnt != 0xff)
                ++lpcalcnt;
        }
        if (/*frccalcnt > 4 && */lpcalcnt > 4)
            break;
        wtimer_runcallbacks();
    }
    OSCCALIB &= (uint8_t)~0x03;
    /*if (clkconsave != 0xff) {
        // undo
        CLKCON = 0x08 | CLKSRC_FRCOSC;
        while ((CLKCON & 0x3F) != (0x08 | CLKSRC_FRCOSC));
        CLKCON = clkconsave;
    */
    ax5043_rclk_disable();
}

