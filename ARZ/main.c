/** \file MASTER\main.c
*
* \brief Code skeleton for MASTER module, illustrating periodic or on-demand transmission of packets.
* \brief The packet format is determined by AX-RadioLAB_output\config.c, produced by the AX-RadioLab GUI
*
*/

// Copyright (c) 2007,2008,2009,2010,2011,2012,2013, 2014 AXSEM AG
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     1.Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     2.Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     3.Neither the name of AXSEM AG, Duebendorf nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//     4.All advertising materials mentioning features or use of this software
//       must display the following acknowledgement:
//       This product includes software developed by AXSEM AG and its contributors.
//     5.The usage of this source code is only granted for operation with AX5043
//       and AX8052F143. Porting to other radio or communication devices is
//       strictly prohibited.
//
// THIS SOFTWARE IS PROVIDED BY AXSEM AG AND CONTRIBUTORS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL AXSEM AG AND CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//#define USE_DBGLINK
#include "../AX_Radio_Lab_output/configmaster.h"

#include <ax8052f143.h>
#include <libmftypes.h>
#include <libmfradio.h>
#include <libmfflash.h>
#include <libmfwtimer.h>

#ifdef USE_COM0
#include <libmfuart1.h>
#endif // USE_COM0

#define TX_ON_DEMAND

#if defined(USE_LCD) || defined(USE_COM0)
#define USE_DISPLAY
#endif // defined(USE_LCD) || defined(USE_COM0)

#include "../COMMON/display_com0.h"

#include "../COMMON/libminidvkled.h"
#define BUTTON_INTCHG INTCHGC
#define BUTTON_PIN    PINC
#define BUTTON_MASK   0x04

#include <string.h>

#include "../COMMON/misc.h"
#include "../COMMON/configcommon.h"

#include "application.h"
#include "unb.h"
#include "water5.h"

uint8_t __data coldstart = 1; // caution: initialization with 1 is necessary! Variables are initialized upon _sdcc_external_startup returning 0 -> the coldstart value returned from _sdcc_external startup does not survive in the coldstart case



//#define arzamas

static void pwrmgmt_irq(void) __interrupt(INT_POWERMGMT)
{
    uint8_t pc = PCON;
    if (!(pc & 0x80))
        return;
    GPIOENABLE = 0;
    IE = EIE = E2IE = 0;
    //PCON |= 0x10;
    for (;;)
    {
        PCON |= 0x01;
    }
}


void axradio_statuschange(struct axradio_status __xdata *st)
{
    switch (st->status)
    {
    case AXRADIO_STAT_TRANSMITSTART:

        PORTB_1 = 1;//TCXO
        #ifndef arzamas
//        PORTC_1 = 1; //LED
        //UNB_SetModeAndPower(pwr, TX, ant);
        UNB_SetPower(pwr);
        axradio_set_channel(channel);
        #endif // arzamas
        if (st->error == AXRADIO_ERR_RETRANSMISSION)
        {
        }
        if( st->error == AXRADIO_ERR_TIMEOUT )  deglitch_busy = 0;
        break;

    case AXRADIO_STAT_TRANSMITEND:
        //PORTB_1 = 0;//TCXO
        #ifndef arzamas
  //      PORTC_1 = 0; //LED
        //UNB_SetModeAndPower(pwr, IDLE, ANT2);
        UNB_SetPower(pwr);
        #endif // arzamas

        if (st->error == AXRADIO_ERR_NOERROR)
        {
        }
        else if (st->error == AXRADIO_ERR_TIMEOUT)
        {
        }
        deglitch_busy = 0;
        if (st->error == AXRADIO_ERR_BUSY)
        {
        }
        else
        {
        }
        break;

#if RADIO_MODE == AXRADIO_MODE_SYNC_MASTER || RADIO_MODE == AXRADIO_MODE_SYNC_ACK_MASTER
    case AXRADIO_STAT_TRANSMITDATA:
        // in SYNC_MASTER mode, transmit data may be prepared between the call to TRANSMITEND until the call to TRANSMITSTART
        // TRANSMITDATA is called when the crystal oscillator is enabled, approximately 1ms before transmission
        transmit_packet();
        break;
#endif

    case AXRADIO_STAT_CHANNELSTATE:
        if (st->u.cs.busy)
        {
        }
        else
        {
        }
        break;

    default:
        break;
    }
}

#if defined(__ICC8051__)
//
// If the code model is banked, low_level_init must be declared
// __near_func elsa a ?BRET is performed
//
#if (__CODE_MODEL__ == 2)
__near_func __root char
#else
__root char
#endif
__low_level_init(void) @ "CSTART"
#else
uint8_t _sdcc_external_startup(void)
#endif
{
    LPXOSCGM = 0x8A;
    wtimer0_setclksrc(WTIMER0_CLKSRC, WTIMER0_PRESCALER);
    wtimer1_setclksrc(CLKSRC_FRCOSC, 7);

    LPOSCCONFIG = 0x09; // Slow, PRESC /1, no cal. Does NOT enable LPOSC. LPOSC is enabled upon configuring WTCFGA (MODE_TX_PERIODIC and receive_ack() )

    coldstart = !(PCON & 0x40);

    ANALOGA = 0x18; // PA[3,4] LPXOSC, other PA are used as digital pins
/*
#ifdef arzamas
    PORTA = 0x00; //
    PORTB = 0x00; //
    PORTC = 0x00; //
    PORTR = 0x0B; //

    DIRA = 0xFF; //
    DIRB = 0xFF; // pb1-tcxo
    DIRC = 0xFF; //  PC2 = button
    DIRR = 0x15; //
#else // rm4
    PORTA = 0x00; //
    PORTB = 0x03; //
    PORTC = 0x04; //
    PORTR = 0x0B; //

    DIRA = 0x00; //
    //DIRB = 0x03; //
    DIRB = 0x05; //
    DIRC = 0x13; //  PC2 = button
    DIRR = 0x15; //
#endif
*/
    axradio_setup_pincfg1();
    DPS = 0;
    IE = 0x40;
    EIE = 0x00;
    E2IE = 0x00;
    GPIOENABLE = 1; // unfreeze GPIO
    return coldstart;
}

/*
void UNB_Init_B100()
{
    uint8_t i;
    TCXO_EN = 1;
    delay_ms(10);
    i = axradio_init();
    if (i != AXRADIO_ERR_NOERROR)
    {
        if (i == AXRADIO_ERR_NOCHIP)
        {
            // No AX5043 RF chip found
            while(1);
        }
        while(1);
    }
    axradio_set_local_address(&localaddr);
    axradio_set_default_remote_address(&remoteaddr);

    i = axradio_set_mode(RADIO_MODE);
    if (i != AXRADIO_ERR_NOERROR)
        while(1);
}
*/
void main(void)
{

    EA = 1;

    if(!coldstart)
    {
        uint8_t lp0 = LPOSCFREQ0;
        uint8_t lp1 = LPOSCFREQ1;
        flash_apply_calibration();
        LPOSCFREQ1 = lp1;
        LPOSCFREQ0 = lp0;
    }
    else  flash_apply_calibration();

    CLKCON = 0x00;
    wtimer_init();

    if (coldstart)
    {
        Setup();
        UNB_Init(UNB_PROTOCOL_B100);
        //UNB_SetModeAndPower(26, IDLE, ANT2);
    }
    else
    {
        // warmstart
        ax5043_commsleepexit();
        IE_4 = 1; // enable radio interrupt
        EIE_5 = 1;//enable uart interrupt
    }
    axradio_setup_pincfg2();
 //   delay_ms(1);
    TCXO_EN = 0;
    DIRB |= 0x03;
    for(;;)
    {
        wtimer_runcallbacks();
        Loop();
        EA = 0;
        uint8_t flg = WTFLAG_CANSTANDBY;
        if (axradio_cansleep() )   flg |= WTFLAG_CANSLEEP;
        wtimer_idle(flg);
        IE_3 = 0; // no ISR!
        EA = 1;
    }
}
