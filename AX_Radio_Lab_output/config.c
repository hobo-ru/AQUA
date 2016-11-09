/* Warning: This file is automatically generated by AX-RadioLAB.
   Manual changes are overwritten! */

#include "../COMMON/easyax5043.h"
#include <libmftypes.h>
#include <libmfcrc.h>
#include "../ARZ/unb.h"
// TX: fcarrier=868.775MHz dev=  0.000kHz br=  0.400kBit/s pwr= 15.0dBm
// RX: fcarrier=868.775MHz bw=  0.400kHz br=  0.400kBit/s

__reentrantb void ax5043_set_registers(void) __reentrant
{
	if(!Protocol)       //if(Protocol) - 100B,   if(!Protocol)  -  50C
    {
    AX5043_MODULATION              = 0x04;
	AX5043_ENCODING                = 0x03;
	AX5043_FRAMING                 = 0x06;
	AX5043_PINFUNCSYSCLK           = 0x01;
	AX5043_PINFUNCDCLK             = 0x01;
	AX5043_PINFUNCDATA             = 0x01;
	AX5043_PINFUNCANTSEL           = 0x82;
	AX5043_PINFUNCPWRAMP           = 0x82;
	AX5043_WAKEUPXOEARLY           = 0x01;
	AX5043_IFFREQ1                 = 0x01;
	AX5043_IFFREQ0                 = 0xFC;
	AX5043_DECIMATION              = 0x7F;
	AX5043_RXDATARATE2             = 0x00;
	AX5043_RXDATARATE1             = 0x3F;
	AX5043_RXDATARATE0             = 0xF9;
	AX5043_MAXDROFFSET2            = 0x00;
	AX5043_MAXDROFFSET1            = 0x00;
	AX5043_MAXDROFFSET0            = 0x00;
	AX5043_MAXRFOFFSET2            = 0x80;
	AX5043_MAXRFOFFSET1            = 0x00;
	AX5043_MAXRFOFFSET0            = 0x00;
	AX5043_AMPLFILTER              = 0x00;
	AX5043_RXPARAMSETS             = 0xF4;
	AX5043_AGCGAIN0                = 0xE8;
	AX5043_AGCTARGET0              = 0x84;
	AX5043_TIMEGAIN0               = 0xF8;
	AX5043_DRGAIN0                 = 0x83;
	AX5043_PHASEGAIN0              = 0x43;
	AX5043_FREQUENCYGAINA0         = 0x46;
	AX5043_FREQUENCYGAINB0         = 0x0A;
	AX5043_FREQUENCYGAINC0         = 0x1F;
	AX5043_FREQUENCYGAIND0         = 0x1F;
	AX5043_AMPLITUDEGAIN0          = 0x06;
	AX5043_FREQDEV10               = 0x00;
	AX5043_FREQDEV00               = 0x00;
	AX5043_BBOFFSRES0              = 0x00;
	AX5043_AGCGAIN1                = 0xE8;
	AX5043_AGCTARGET1              = 0x84;
	AX5043_AGCAHYST1               = 0x00;
	AX5043_AGCMINMAX1              = 0x00;
	AX5043_TIMEGAIN1               = 0xF6;
	AX5043_DRGAIN1                 = 0x82;
	AX5043_PHASEGAIN1              = 0x43;
	AX5043_FREQUENCYGAINA1         = 0x46;
	AX5043_FREQUENCYGAINB1         = 0x0A;
	AX5043_FREQUENCYGAINC1         = 0x1F;
	AX5043_FREQUENCYGAIND1         = 0x1F;
	AX5043_AMPLITUDEGAIN1          = 0x06;
	AX5043_FREQDEV11               = 0x00;
	AX5043_FREQDEV01               = 0x00;
	AX5043_FOURFSK1                = 0x16;
	AX5043_BBOFFSRES1              = 0x00;
	AX5043_AGCGAIN3                = 0xFF;
	AX5043_AGCTARGET3              = 0x84;
	AX5043_AGCAHYST3               = 0x00;
	AX5043_AGCMINMAX3              = 0x00;
	AX5043_TIMEGAIN3               = 0xF5;
	AX5043_DRGAIN3                 = 0x81;
	AX5043_PHASEGAIN3              = 0x43;
	AX5043_FREQUENCYGAINA3         = 0x46;
	AX5043_FREQUENCYGAINB3         = 0x0A;
	AX5043_FREQUENCYGAINC3         = 0x1F;
	AX5043_FREQUENCYGAIND3         = 0x1F;
	AX5043_AMPLITUDEGAIN3          = 0x06;
	AX5043_FREQDEV13               = 0x00;
	AX5043_FREQDEV03               = 0x00;
	AX5043_FOURFSK3                = 0x16;
	AX5043_BBOFFSRES3              = 0x00;
	AX5043_FSKDEV2                 = 0x00;
	AX5043_FSKDEV1                 = 0x00;
	AX5043_FSKDEV0                 = 0x00;
	AX5043_MODCFGA                 = 0x05;
	AX5043_TXRATE2                 = 0x00;
	AX5043_TXRATE1                 = 0x01;
	AX5043_TXRATE0                 = 0x02;
	AX5043_TXPWRCOEFFB1            = 0x0F;
	AX5043_TXPWRCOEFFB0            = 0xFF;
	AX5043_PLLVCOI                 = 0x99;
	AX5043_PLLRNGCLK               = 0x04;
	AX5043_BBTUNE                  = 0x0F;
	AX5043_BBOFFSCAP               = 0x77;
	AX5043_PKTADDRCFG              = 0x80;
	AX5043_PKTLENCFG               = 0x00;
	AX5043_PKTLENOFFSET            = 0x88;
	AX5043_PKTMAXLEN               = 0xC8;
	AX5043_MATCH0PAT3              = 0xFF;
	AX5043_MATCH0PAT2              = 0x00;
	AX5043_MATCH0PAT1              = 0x00;
	AX5043_MATCH0PAT0              = 0x00;
	AX5043_MATCH0LEN               = 0x07;
	AX5043_MATCH0MAX               = 0x07;
	AX5043_MATCH1PAT1              = 0xFF;
	AX5043_MATCH1PAT0              = 0xFF;
	AX5043_MATCH1LEN               = 0x0A;
	AX5043_MATCH1MAX               = 0x0A;
	AX5043_TMGTXBOOST              = 0x3E;
	AX5043_TMGTXSETTLE             = 0x31;
	AX5043_TMGRXBOOST              = 0x3E;
	AX5043_TMGRXSETTLE             = 0x31;
	AX5043_TMGRXOFFSACQ            = 0x00;
	AX5043_TMGRXCOARSEAGC          = 0x7F;
	AX5043_TMGRXRSSI               = 0x03;
	AX5043_TMGRXPREAMBLE2          = 0x12;
	AX5043_RSSIABSTHR              = 0xCB;
	AX5043_BGNDRSSITHR             = 0x00;
	AX5043_PKTCHUNKSIZE            = 0x0D;
	AX5043_PKTACCEPTFLAGS          = 0x20;
	AX5043_DACVALUE1               = 0x00;
	AX5043_DACVALUE0               = 0x00;
	AX5043_DACCONFIG               = 0x00;
	AX5043_REF                     = 0x03;
	AX5043_XTALOSC                 = 0x04;
	AX5043_XTALAMPL                = 0x00;
	AX5043_0xF1C                   = 0x07;
	AX5043_0xF21                   = 0x68;
	AX5043_0xF22                   = 0xFF;
	AX5043_0xF23                   = 0x84;
	AX5043_0xF26                   = 0x98;
	AX5043_0xF34                   = 0x08;
	AX5043_0xF35                   = 0x12;
	AX5043_0xF44                   = 0x25;
	AX5043_MODCFGP                 = 0xE1;
    }
    else
    {
        // TX: fcarrier=868.775MHz dev=  0.000kHz br=  0.200kBit/s pwr= 15.0dBm
        // RX: fcarrier=868.775MHz bw=  0.200kHz br=  0.200kBit/s
	AX5043_MODULATION              = 0x04;
	AX5043_ENCODING                = 0x03;
	AX5043_FRAMING                 = 0x06;
	AX5043_PINFUNCSYSCLK           = 0x01;
	AX5043_PINFUNCDCLK             = 0x01;
	AX5043_PINFUNCDATA             = 0x01;
	AX5043_PINFUNCANTSEL           = 0x82;
	AX5043_PINFUNCPWRAMP           = 0x82;
	AX5043_WAKEUPXOEARLY           = 0x01;
	AX5043_IFFREQ1                 = 0x01;
	AX5043_IFFREQ0                 = 0xFC;
	AX5043_DECIMATION              = 0x7F;
	AX5043_RXDATARATE2             = 0x00;
	AX5043_RXDATARATE1             = 0x7F;
	AX5043_RXDATARATE0             = 0xF3;
	AX5043_MAXDROFFSET2            = 0x00;
	AX5043_MAXDROFFSET1            = 0x00;
	AX5043_MAXDROFFSET0            = 0x00;
	AX5043_MAXRFOFFSET2            = 0x80;
	AX5043_MAXRFOFFSET1            = 0x00;
	AX5043_MAXRFOFFSET0            = 0x00;
	AX5043_AMPLFILTER              = 0x00;
	AX5043_RXPARAMSETS             = 0xF4;
	AX5043_AGCGAIN0                = 0xE9;
	AX5043_AGCTARGET0              = 0x84;
	AX5043_TIMEGAIN0               = 0xF9;
	AX5043_DRGAIN0                 = 0x84;
	AX5043_PHASEGAIN0              = 0x03;
	AX5043_FREQUENCYGAINA0         = 0x46;
	AX5043_FREQUENCYGAINB0         = 0x0A;
	AX5043_FREQUENCYGAINC0         = 0x1F;
	AX5043_FREQUENCYGAIND0         = 0x1F;
	AX5043_AMPLITUDEGAIN0          = 0x06;
	AX5043_FREQDEV10               = 0x00;
	AX5043_FREQDEV00               = 0x00;
	AX5043_BBOFFSRES0              = 0x00;
	AX5043_AGCGAIN1                = 0xE9;
	AX5043_AGCTARGET1              = 0x84;
	AX5043_AGCAHYST1               = 0x00;
	AX5043_AGCMINMAX1              = 0x00;
	AX5043_TIMEGAIN1               = 0xF7;
	AX5043_DRGAIN1                 = 0x83;
	AX5043_PHASEGAIN1              = 0x03;
	AX5043_FREQUENCYGAINA1         = 0x46;
	AX5043_FREQUENCYGAINB1         = 0x0A;
	AX5043_FREQUENCYGAINC1         = 0x1F;
	AX5043_FREQUENCYGAIND1         = 0x1F;
	AX5043_AMPLITUDEGAIN1          = 0x06;
	AX5043_FREQDEV11               = 0x00;
	AX5043_FREQDEV01               = 0x00;
	AX5043_FOURFSK1                = 0x16;
	AX5043_BBOFFSRES1              = 0x00;
	AX5043_AGCGAIN3                = 0xFF;
	AX5043_AGCTARGET3              = 0x84;
	AX5043_AGCAHYST3               = 0x00;
	AX5043_AGCMINMAX3              = 0x00;
	AX5043_TIMEGAIN3               = 0xF6;
	AX5043_DRGAIN3                 = 0x82;
	AX5043_PHASEGAIN3              = 0x03;
	AX5043_FREQUENCYGAINA3         = 0x46;
	AX5043_FREQUENCYGAINB3         = 0x0A;
	AX5043_FREQUENCYGAINC3         = 0x1F;
	AX5043_FREQUENCYGAIND3         = 0x1F;
	AX5043_AMPLITUDEGAIN3          = 0x06;
	AX5043_FREQDEV13               = 0x00;
	AX5043_FREQDEV03               = 0x00;
	AX5043_FOURFSK3                = 0x16;
	AX5043_BBOFFSRES3              = 0x00;
	AX5043_FSKDEV2                 = 0x00;
	AX5043_FSKDEV1                 = 0x00;
	AX5043_FSKDEV0                 = 0x00;
	AX5043_MODCFGA                 = 0x05;
	AX5043_TXRATE2                 = 0x00;
	AX5043_TXRATE1                 = 0x00;
	AX5043_TXRATE0                 = 0x81;
	AX5043_TXPWRCOEFFB1            = 0x0F;
	AX5043_TXPWRCOEFFB0            = 0xFF;
	AX5043_PLLVCOI                 = 0x99;
	AX5043_PLLRNGCLK               = 0x04;
	AX5043_BBTUNE                  = 0x0F;
	AX5043_BBOFFSCAP               = 0x77;
	AX5043_PKTADDRCFG              = 0x80;
	AX5043_PKTLENCFG               = 0x00;
	AX5043_PKTLENOFFSET            = 0x88;
	AX5043_PKTMAXLEN               = 0xC8;
	AX5043_MATCH0PAT3              = 0xFF;
	AX5043_MATCH0PAT2              = 0x00;
	AX5043_MATCH0PAT1              = 0x00;
	AX5043_MATCH0PAT0              = 0x00;
	AX5043_MATCH0LEN               = 0x07;
	AX5043_MATCH0MAX               = 0x07;
	AX5043_MATCH1PAT1              = 0xFF;
	AX5043_MATCH1PAT0              = 0xFF;
	AX5043_MATCH1LEN               = 0x0A;
	AX5043_MATCH1MAX               = 0x0A;
	AX5043_TMGTXBOOST              = 0x3E;
	AX5043_TMGTXSETTLE             = 0x31;
	AX5043_TMGRXBOOST              = 0x3E;
	AX5043_TMGRXSETTLE             = 0x31;
	AX5043_TMGRXOFFSACQ            = 0x00;
	AX5043_TMGRXCOARSEAGC          = 0x7F;
	AX5043_TMGRXRSSI               = 0x03;
	AX5043_TMGRXPREAMBLE2          = 0x12;
	AX5043_RSSIABSTHR              = 0xCB;
	AX5043_BGNDRSSITHR             = 0x00;
	AX5043_PKTCHUNKSIZE            = 0x0D;
	AX5043_PKTACCEPTFLAGS          = 0x20;
	AX5043_DACVALUE1               = 0x00;
	AX5043_DACVALUE0               = 0x00;
	AX5043_DACCONFIG               = 0x00;
	AX5043_REF                     = 0x03;
	AX5043_XTALOSC                 = 0x04;
	AX5043_XTALAMPL                = 0x00;
	AX5043_0xF1C                   = 0x07;
	AX5043_0xF21                   = 0x68;
	AX5043_0xF22                   = 0xFF;
	AX5043_0xF23                   = 0x84;
	AX5043_0xF26                   = 0x98;
	AX5043_0xF34                   = 0x08;
	AX5043_0xF35                   = 0x12;
	AX5043_0xF44                   = 0x25;
	AX5043_MODCFGP                 = 0xE1;
    }
}


__reentrantb void ax5043_set_registers_tx(void) __reentrant
{
	AX5043_PLLLOOP                 = 0x07;
	AX5043_PLLCPI                  = 0x12;
	AX5043_PLLVCODIV               = 0x20;
	AX5043_XTALCAP                 = 0x00;
	AX5043_0xF00                   = 0x0F;
	AX5043_0xF18                   = 0x06;
}


__reentrantb void ax5043_set_registers_rx(void) __reentrant
{
	AX5043_PLLLOOP                 = 0x07;
	AX5043_PLLCPI                  = 0x08;
	AX5043_PLLVCODIV               = 0x20;
	AX5043_XTALCAP                 = 0x00;
	AX5043_0xF00                   = 0x0F;
	AX5043_0xF18                   = 0x06;
}


__reentrantb void ax5043_set_registers_rxwor(void) __reentrant
{
	AX5043_TMGRXAGC                = 0x90;
	AX5043_TMGRXPREAMBLE1          = 0x19;
	AX5043_PKTMISCFLAGS            = 0x03;
}


__reentrantb void ax5043_set_registers_rxcont(void) __reentrant
{
	AX5043_TMGRXAGC                = 0x00;
	AX5043_TMGRXPREAMBLE1          = 0x00;
	AX5043_PKTMISCFLAGS            = 0x00;
}


__reentrantb void ax5043_set_registers_rxcont_singleparamset(void) __reentrant
{
	AX5043_RXPARAMSETS             = 0xFF;
	AX5043_FREQDEV13               = 0x00;
	AX5043_FREQDEV03               = 0x00;
	AX5043_AGCGAIN3                = 0xE8;
}



__reentrantb void axradio_setup_pincfg1(void) __reentrant
{
	PALTRADIO = 0x00; //pass through
}

__reentrantb void axradio_setup_pincfg2(void) __reentrant
{
	PORTR = (PORTR & 0x3F) | 0x00; //AX8052F143 --> no pull-ups on PR6, PR7
}



#if defined SDCC

#define CONST #

#define CONSTMULFIX24(x)			\
	__asm					\
	mov	r0,dpl				\
	mov	r1,dph				\
	mov	r2,b				\
	mov	r3,a				\
	push	acc				\
	jnb	acc.7,00000$			\
	clr	c				\
	clr	a				\
	subb	a,r0				\
	mov	r0,a				\
	clr	a				\
	subb	a,r1				\
	mov	r1,a				\
	clr	a				\
	subb	a,r2				\
	mov	r2,a				\
	clr	a				\
	subb	a,r3				\
	mov	r3,a				\
00000$:	clr	a				\
	mov	r4,a				\
	mov	r5,a				\
	mov	r6,a				\
	mov	r7,a				\
	;; stage -1				\
	.if	(((x)>>16)&0xff)		\
	mov	a,CONST (((x)>>16)&0xff)	\
	mov	b,r0				\
	mul	ab				\
	mov	r7,a				\
	mov	r4,b				\
	.endif					\
	.if	(((x)>>8)&0xff)			\
	mov	a,CONST (((x)>>8)&0xff)		\
	mov	b,r1				\
	mul	ab				\
	.if	(((x)>>16)&0xff)		\
	add	a,r7				\
	mov	r7,a				\
	mov	a,b				\
	addc	a,r4				\
	mov	r4,a				\
	clr	a				\
	addc	a,r5				\
	mov	r5,a				\
	.else					\
	mov	r7,a				\
	mov	r4,b				\
	.endif					\
	.endif					\
	.if	((x)&0xff)			\
	mov	a,CONST ((x)&0xff)		\
	mov	b,r2				\
	mul	ab				\
	.if	(((x)>>8)&0xffff)		\
	add	a,r7				\
	mov	r7,a				\
	mov	a,b				\
	addc	a,r4				\
	mov	r4,a				\
	clr	a				\
	addc	a,r5				\
	mov	r5,a				\
	.else					\
	mov	r7,a				\
	mov	r4,b				\
	.endif					\
	.endif					\
	;; clear precision extension		\
	clr	a				\
	mov	r7,a				\
	;; stage 0				\
	.if	(((x)>>24)&0xff)		\
	mov	a,CONST (((x)>>24)&0xff)	\
	mov	b,r0				\
	mul	ab				\
	add	a,r4				\
	mov	r4,a				\
	mov	a,b				\
	addc	a,r5				\
	mov	r5,a				\
	clr	a				\
	addc	a,r6				\
	mov	r6,a				\
	.endif					\
	.if	(((x)>>16)&0xff)		\
	mov	a,CONST (((x)>>16)&0xff)	\
	mov	b,r1				\
	mul	ab				\
	add	a,r4				\
	mov	r4,a				\
	mov	a,b				\
	addc	a,r5				\
	mov	r5,a				\
	clr	a				\
	addc	a,r6				\
	mov	r6,a				\
	.endif					\
	.if	(((x)>>8)&0xff)			\
	mov	a,CONST (((x)>>8)&0xff)		\
	mov	b,r2				\
	mul	ab				\
	add	a,r4				\
	mov	r4,a				\
	mov	a,b				\
	addc	a,r5				\
	mov	r5,a				\
	clr	a				\
	addc	a,r6				\
	mov	r6,a				\
	.endif					\
	.if	((x)&0xff)			\
	mov	a,CONST ((x)&0xff)		\
	mov	b,r3				\
	mul	ab				\
	add	a,r4				\
	mov	r4,a				\
	mov	a,b				\
	addc	a,r5				\
	mov	r5,a				\
	clr	a				\
	addc	a,r6				\
	mov	r6,a				\
	.endif					\
	;; stage 1				\
	.if	(((x)>>24)&0xff)		\
	mov	a,CONST (((x)>>24)&0xff)	\
	mov	b,r1				\
	mul	ab				\
	add	a,r5				\
	mov	r5,a				\
	mov	a,b				\
	addc	a,r6				\
	mov	r6,a				\
	clr	a				\
	addc	a,r7				\
	mov	r7,a				\
	.endif					\
	.if	(((x)>>16)&0xff)		\
	mov	a,CONST (((x)>>16)&0xff)	\
	mov	b,r2				\
	mul	ab				\
	add	a,r5				\
	mov	r5,a				\
	mov	a,b				\
	addc	a,r6				\
	mov	r6,a				\
	clr	a				\
	addc	a,r7				\
	mov	r7,a				\
	.endif					\
	.if	(((x)>>8)&0xff)			\
	mov	a,CONST (((x)>>8)&0xff)		\
	mov	b,r3				\
	mul	ab				\
	add	a,r5				\
	mov	r5,a				\
	mov	a,b				\
	addc	a,r6				\
	mov	r6,a				\
	clr	a				\
	addc	a,r7				\
	mov	r7,a				\
	.endif					\
	;; stage 2				\
	.if	(((x)>>24)&0xff)		\
	mov	a,CONST (((x)>>24)&0xff)	\
	mov	b,r2				\
	mul	ab				\
	add	a,r6				\
	mov	r6,a				\
	mov	a,b				\
	addc	a,r7				\
	mov	r7,a				\
	.endif					\
	.if	(((x)>>16)&0xff)		\
	mov	a,CONST (((x)>>16)&0xff)	\
	mov	b,r3				\
	mul	ab				\
	add	a,r6				\
	mov	r6,a				\
	mov	a,b				\
	addc	a,r7				\
	mov	r7,a				\
	.endif					\
	;; stage 3				\
	.if	(((x)>>24)&0xff)		\
	mov	a,CONST (((x)>>24)&0xff)	\
	mov	b,r3				\
	mul	ab				\
	add	a,r7				\
	mov	r7,a				\
	.endif					\
	pop	acc				\
	jnb	acc.7,00001$			\
	clr	c				\
	clr	a				\
	subb	a,r4				\
	mov	dpl,a				\
	clr	a				\
	subb	a,r5				\
	mov	dph,a				\
	clr	a				\
	subb	a,r6				\
	mov	b,a				\
	clr	a				\
	subb	a,r7				\
	sjmp	00002$				\
00001$:	mov	dpl,r4				\
	mov	dph,r5				\
	mov	b,r6				\
	mov	a,r7				\
00002$:						\
	__endasm

#define CONSTMULFIX16(x)			\
	__asm					\
	mov	r0,dpl				\
	mov	a,dph				\
	mov	r1,a				\
	push	acc				\
	jnb	acc.7,00000$			\
	clr	c				\
	clr	a				\
	subb	a,r0				\
	mov	r0,a				\
	clr	a				\
	subb	a,r1				\
	mov	r1,a				\
00000$:	clr	a				\
	mov	r4,a				\
	mov	r5,a				\
	mov	r6,a				\
	mov	r7,a				\
	;; stage -1				\
	.if	(((x)>>16)&0xff)		\
	mov	a,CONST (((x)>>16)&0xff)	\
	mov	b,r0				\
	mul	ab				\
	mov	r7,a				\
	mov	r4,b				\
	.endif					\
	.if	(((x)>>8)&0xff)			\
	mov	a,CONST (((x)>>8)&0xff)		\
	mov	b,r1				\
	mul	ab				\
	.if	(((x)>>16)&0xff)		\
	add	a,r7				\
	mov	r7,a				\
	mov	a,b				\
	addc	a,r4				\
	mov	r4,a				\
	clr	a				\
	addc	a,r5				\
	mov	r5,a				\
	.else					\
	mov	r7,a				\
	mov	r4,b				\
	.endif					\
	.endif					\
	;; clear precision extension		\
	clr	a				\
	mov	r7,a				\
	;; stage 0				\
	.if	(((x)>>24)&0xff)		\
	mov	a,CONST (((x)>>24)&0xff)	\
	mov	b,r0				\
	mul	ab				\
	add	a,r4				\
	mov	r4,a				\
	mov	a,b				\
	addc	a,r5				\
	mov	r5,a				\
	clr	a				\
	addc	a,r6				\
	mov	r6,a				\
	.endif					\
	.if	(((x)>>16)&0xff)		\
	mov	a,CONST (((x)>>16)&0xff)	\
	mov	b,r1				\
	mul	ab				\
	add	a,r4				\
	mov	r4,a				\
	mov	a,b				\
	addc	a,r5				\
	mov	r5,a				\
	clr	a				\
	addc	a,r6				\
	mov	r6,a				\
	.endif					\
	;; stage 1				\
	.if	(((x)>>24)&0xff)		\
	mov	a,CONST (((x)>>24)&0xff)	\
	mov	b,r1				\
	mul	ab				\
	add	a,r5				\
	mov	r5,a				\
	mov	a,b				\
	addc	a,r6				\
	mov	r6,a				\
	clr	a				\
	addc	a,r7				\
	mov	r7,a				\
	.endif					\
	pop	acc				\
	jnb	acc.7,00001$			\
	clr	c				\
	clr	a				\
	subb	a,r4				\
	mov	dpl,a				\
	clr	a				\
	subb	a,r5				\
	mov	dph,a				\
	clr	a				\
	subb	a,r6				\
	mov	b,a				\
	clr	a				\
	subb	a,r7				\
	sjmp	00002$				\
00001$:	mov	dpl,r4				\
	mov	dph,r5				\
	mov	b,r6				\
	mov	a,r7				\
00002$:						\
	__endasm

#else // SDCC

#define MUL8_16(x,y) ((uint8_t)((x)&0xff)*(uint16_t)(uint8_t)((y)&0xff))

#define CONSTMULFIX24(x)					\
	if (f >= 0) {						\
		uint32_t r = MUL8_16((x)>>16,f);		\
		r += MUL8_16((x)>>8,f>>8);			\
		r += MUL8_16((x),f>>16);			\
		r >>= 8;					\
		r += MUL8_16((x)>>24,f);			\
		r += MUL8_16((x)>>16,f>>8);			\
		r += MUL8_16((x)>>8,f>>16);			\
		r += MUL8_16((x),f>>24);			\
		r += ((uint32_t)MUL8_16((x)>>24,f>>8))<<8;	\
		r += ((uint32_t)MUL8_16((x)>>16,f>>16))<<8;	\
		r += ((uint32_t)MUL8_16((x)>>8,f>>24))<<8;	\
		r += ((uint32_t)MUL8_16((x)>>24,f>>16))<<16;	\
		r += ((uint32_t)MUL8_16((x)>>16,f>>24))<<16;	\
		r += ((uint32_t)MUL8_16((x)>>24,f>>24))<<24;	\
		return r;					\
	}							\
	{							\
		int32_t r;					\
		f = -f;						\
		r = -(uint32_t)MUL8_16((x)>>16,f);		\
		r -= (uint32_t)MUL8_16((x)>>8,f>>8);		\
		r -= (uint32_t)MUL8_16((x),f>>16);		\
		r >>= 8;					\
		r -= (uint32_t)MUL8_16((x)>>24,f);		\
		r -= (uint32_t)MUL8_16((x)>>16,f>>8);		\
		r -= (uint32_t)MUL8_16((x)>>8,f>>16);		\
		r -= (uint32_t)MUL8_16((x),f>>24);		\
		r -= ((uint32_t)MUL8_16((x)>>24,f>>8))<<8;	\
		r -= ((uint32_t)MUL8_16((x)>>16,f>>16))<<8;	\
		r -= ((uint32_t)MUL8_16((x)>>8,f>>24))<<8;	\
		r -= ((uint32_t)MUL8_16((x)>>24,f>>16))<<16;	\
		r -= ((uint32_t)MUL8_16((x)>>16,f>>24))<<16;	\
		r -= ((uint32_t)MUL8_16((x)>>24,f>>24))<<24;	\
		return r;					\
	}

#define CONSTMULFIX16(x)					\
	if (f >= 0) {						\
		uint32_t r = MUL8_16((x)>>16,f);		\
		r += MUL8_16((x)>>8,f>>8);			\
		r >>= 8;					\
		r += MUL8_16((x)>>24,f);			\
		r += MUL8_16((x)>>16,f>>8);			\
		r += ((uint32_t)MUL8_16((x)>>24,f>>8))<<8;	\
		return r;					\
	}							\
	{							\
		int32_t r;					\
		f = -f;						\
		r = -(uint32_t)MUL8_16((x)>>16,f);		\
		r -= (uint32_t)MUL8_16((x)>>8,f>>8);		\
		r >>= 8;					\
		r -= (uint32_t)MUL8_16((x)>>24,f);		\
		r -= (uint32_t)MUL8_16((x)>>16,f>>8);		\
		r -= ((uint32_t)MUL8_16((x)>>24,f>>8))<<8;	\
		return r;					\
	}

#endif // SDCC

#if defined SDCC
// do not mark as reentrant, otherwise the register allocator will generate suboptimal code
#pragma nooverlay
int32_t axradio_conv_freq_fromhz(int32_t f)
#else
__reentrantb int32_t axradio_conv_freq_fromhz(int32_t f) __reentrant
#endif
{
	/* scale by 0.645278 (true 0.645278) */
	CONSTMULFIX24(0xa530e8);
}

#if defined SDCC
// do not mark as reentrant, otherwise the register allocator will generate suboptimal code
#pragma nooverlay
int32_t axradio_conv_freq_tohz(int32_t f)
#else
__reentrantb int32_t axradio_conv_freq_tohz(int32_t f) __reentrant
#endif
{
	/* scale by 1.549721 (true 1.549721) */
	CONSTMULFIX24(0x18cba80);
}

const uint8_t __code axradio_phy_innerfreqloop = 1;

#if defined SDCC
// do not mark as reentrant, otherwise the register allocator will generate suboptimal code
#pragma nooverlay
int32_t axradio_conv_freq_fromreg(int32_t f)
#else
__reentrantb int32_t axradio_conv_freq_fromreg(int32_t f) __reentrant
#endif
{
	/* scale by 0.003938 (true 0.003938) */
	CONSTMULFIX16(0x1021c);
}

#if defined SDCC
// do not mark as reentrant, otherwise the register allocator will generate suboptimal code
#pragma nooverlay
int32_t axradio_conv_timeinterval_totimer0(int32_t dt)
#else
__reentrantb int32_t axradio_conv_timeinterval_totimer0(int32_t dt) __reentrant
#endif
{
	/* scale by 0.020142 (true 0.020165) */
	int32_t r;
	dt >>= 6;
	r = dt;
	dt >>= 2;
	r += dt;
	dt >>= 3;
	r += dt;
	dt >>= 2;
	r += dt;
	return r;
}

__reentrantb uint8_t axradio_byteconv(uint8_t b) __reentrant
{
	return rev8(b);
}


__reentrantb void axradio_byteconv_buffer(uint8_t __xdata *buf, uint16_t buflen) __reentrant
{
	while (buflen) {
		*buf = rev8(*buf);
		++buf;
		--buflen;
	}
}

__reentrantb uint16_t axradio_framing_check_crc(uint8_t __xdata *pkt, uint16_t cnt) __reentrant
{
	return cnt;
}

__reentrantb uint16_t axradio_framing_append_crc(uint8_t __xdata *pkt, uint16_t cnt) __reentrant
{
	return cnt;
}





// physical layer
const uint8_t __code axradio_phy_pn9 = 0;
const uint8_t __code axradio_phy_nrchannels = 251;
const uint32_t __code axradio_phy_chanfreq[251] = { 0x216a17a1, 0x216a1823, 0x216a18a5, 0x216a1925, 0x216a19a7, 0x216a1a27, 0x216a1aa9, 0x216a1b29, 0x216a1bab, 0x216a1c2b, 0x216a1cad, 0x216a1d2d, 0x216a1daf, 0x216a1e2f, 0x216a1eb1, 0x216a1f31, 0x216a1fb3, 0x216a2033, 0x216a20b5, 0x216a2137, 0x216a21b7, 0x216a2239, 0x216a22b9, 0x216a233b, 0x216a23bb, 0x216a243d, 0x216a24bd, 0x216a253f, 0x216a25bf, 0x216a2641, 0x216a26c1, 0x216a2743, 0x216a27c3, 0x216a2845, 0x216a28c5, 0x216a2947, 0x216a29c7, 0x216a2a49, 0x216a2acb, 0x216a2b4b, 0x216a2bcd, 0x216a2c4d, 0x216a2ccf, 0x216a2d4f, 0x216a2dd1, 0x216a2e51, 0x216a2ed3, 0x216a2f53, 0x216a2fd5, 0x216a3055, 0x216a30d7, 0x216a3157, 0x216a31d9, 0x216a3259, 0x216a32db, 0x216a335d, 0x216a33dd, 0x216a345f, 0x216a34df, 0x216a3561, 0x216a35e1, 0x216a3663, 0x216a36e3, 0x216a3765, 0x216a37e5, 0x216a3867, 0x216a38e7, 0x216a3969, 0x216a39e9, 0x216a3a6b, 0x216a3aeb, 0x216a3b6d, 0x216a3bed, 0x216a3c6f, 0x216a3cf1, 0x216a3d71, 0x216a3df3, 0x216a3e73, 0x216a3ef5, 0x216a3f75, 0x216a3ff7, 0x216a4077, 0x216a40f9, 0x216a4179, 0x216a41fb, 0x216a427b, 0x216a42fd, 0x216a437d, 0x216a43ff, 0x216a447f, 0x216a4501, 0x216a4583, 0x216a4603, 0x216a4685, 0x216a4705, 0x216a4787, 0x216a4807, 0x216a4889, 0x216a4909, 0x216a498b, 0x216a4a0b, 0x216a4a8d, 0x216a4b0d, 0x216a4b8f, 0x216a4c0f, 0x216a4c91, 0x216a4d11, 0x216a4d93, 0x216a4e13, 0x216a4e95, 0x216a4f17, 0x216a4f97, 0x216a5019, 0x216a5099, 0x216a511b, 0x216a519b, 0x216a521d, 0x216a529d, 0x216a531f, 0x216a539f, 0x216a5421, 0x216a54a1, 0x216a5523, 0x216a55a3, 0x216a5625, 0x216a56a5, 0x216a5727, 0x216a57a9, 0x216a5829, 0x216a58ab, 0x216a592b, 0x216a59ad, 0x216a5a2d, 0x216a5aaf, 0x216a5b2f, 0x216a5bb1, 0x216a5c31, 0x216a5cb3, 0x216a5d33, 0x216a5db5, 0x216a5e35, 0x216a5eb7, 0x216a5f37, 0x216a5fb9, 0x216a6039, 0x216a60bb, 0x216a613d, 0x216a61bd, 0x216a623f, 0x216a62bf, 0x216a6341, 0x216a63c1, 0x216a6443, 0x216a64c3, 0x216a6545, 0x216a65c5, 0x216a6647, 0x216a66c7, 0x216a6749, 0x216a67c9, 0x216a684b, 0x216a68cb, 0x216a694d, 0x216a69cf, 0x216a6a4f, 0x216a6ad1, 0x216a6b51, 0x216a6bd3, 0x216a6c53, 0x216a6cd5, 0x216a6d55, 0x216a6dd7, 0x216a6e57, 0x216a6ed9, 0x216a6f59, 0x216a6fdb, 0x216a705b, 0x216a70dd, 0x216a715d, 0x216a71df, 0x216a725f, 0x216a72e1, 0x216a7363, 0x216a73e3, 0x216a7465, 0x216a74e5, 0x216a7567, 0x216a75e7, 0x216a7669, 0x216a76e9, 0x216a776b, 0x216a77eb, 0x216a786d, 0x216a78ed, 0x216a796f, 0x216a79ef, 0x216a7a71, 0x216a7af1, 0x216a7b73, 0x216a7bf5, 0x216a7c75, 0x216a7cf7, 0x216a7d77, 0x216a7df9, 0x216a7e79, 0x216a7efb, 0x216a7f7b, 0x216a7ffd, 0x216a807d, 0x216a80ff, 0x216a817f, 0x216a8201, 0x216a8281, 0x216a8303, 0x216a8383, 0x216a8405, 0x216a8485, 0x216a8507, 0x216a8589, 0x216a8609, 0x216a868b, 0x216a870b, 0x216a878d, 0x216a880d, 0x216a888f, 0x216a890f, 0x216a8991, 0x216a8a11, 0x216a8a93, 0x216a8b13, 0x216a8b95, 0x216a8c15, 0x216a8c97, 0x216a8d17, 0x216a8d99, 0x216a8e1b, 0x216a8e9b, 0x216a8f1d, 0x216a8f9d, 0x216a901f, 0x216a909f, 0x216a9121, 0x216a91a1, 0x216a9223, 0x216a92a3, 0x216a9325, 0x216a93a5, 0x216a9427, 0x216a94a7, 0x216a9529, 0x216a95a9 };
const uint8_t __code axradio_phy_chanpllrnginit[251] = { 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a };
const uint8_t __code axradio_phy_chanvcoiinit[251] = { 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99 };
uint8_t __xdata axradio_phy_chanpllrng[251];
uint8_t __xdata axradio_phy_chanvcoi[1];
const uint8_t __code axradio_phy_vcocalib = 0;
const int32_t __code axradio_phy_maxfreqoffset = 65;
const int8_t __code axradio_phy_rssioffset = 64;
// axradio_phy_rssioffset is added to AX5043_RSSIREFERENCE and subtracted from chip RSSI value to prevent overflows (8bit RSSI only goes down to -128)
// axradio_phy_rssioffset is also added to AX5043_RSSIABSTHR
const int8_t __code axradio_phy_rssireference = 0xFA + 64;
const int8_t __code axradio_phy_channelbusy = -117 + 64;
const uint16_t __code axradio_phy_cs_period = 7; // timer0 units, 10ms
const uint8_t __code axradio_phy_cs_enabled = 0;
const uint8_t __code axradio_phy_lbt_retries = 0;
const uint8_t __code axradio_phy_lbt_forcetx = 0;
const uint16_t __code axradio_phy_preamble_wor_longlen = 0; // wor_longlen + wor_len totals to 240.0ms plus 0bits
const uint16_t __code axradio_phy_preamble_wor_len = 96;
const uint16_t __code axradio_phy_preamble_longlen = 0;
const uint16_t __code axradio_phy_preamble_len = 0;
const uint8_t __code axradio_phy_preamble_byte = 0xff;
const uint8_t __code axradio_phy_preamble_flags = 0x18;
const uint8_t __code axradio_phy_preamble_appendbits = 0;
const uint8_t __code axradio_phy_preamble_appendpattern = 0x00;

//framing
const uint8_t __code axradio_framing_maclen = 0;
const uint8_t __code axradio_framing_addrlen = 0;
const uint8_t __code axradio_framing_destaddrpos = 0;
const uint8_t __code axradio_framing_sourceaddrpos = 0xff;
const uint8_t __code axradio_framing_lenpos = 0;
const uint8_t __code axradio_framing_lenoffs = 136;
const uint8_t __code axradio_framing_lenmask = 0x00;
const uint8_t __code axradio_framing_swcrclen = 0;

const uint8_t __code axradio_framing_synclen = 8;
const uint8_t __code axradio_framing_syncword[] = { 0xff, 0xff, 0x99, 0x20};
const uint8_t __code axradio_framing_syncflags = 0x18;
const uint8_t __code axradio_framing_enable_sfdcallback = 0;

const uint32_t __code axradio_framing_ack_timeout = 85; // 130.0ms in wtimer0 units (640Hz)
const uint32_t __code axradio_framing_ack_delay = 313; // 1.0ms in wtimer1 units (20MHz/64)
const uint8_t __code axradio_framing_ack_retransmissions = 2;
const uint8_t __code axradio_framing_ack_seqnrpos = 0xff;

const uint8_t __code axradio_framing_minpayloadlen = 0; // must be set to 1 if the payload directly follows the destination address, and a CRC is configured
//WOR
const uint16_t __code axradio_wor_period = 128;

// synchronous mode
const uint32_t __code axradio_sync_period = 64454656; // ACTUALLY FREQ, NOT PERIOD!
const uint32_t __code axradio_sync_xoscstartup = 49;
const uint32_t __code axradio_sync_slave_syncwindow = 193363968; // 5901.000s
const uint32_t __code axradio_sync_slave_initialsyncwindow = 5898240; //180.000s
const uint32_t __code axradio_sync_slave_syncpause = 19660800; // 600.000s
const int16_t __code axradio_sync_slave_maxperiod = 826620; // in (2^SYNC_K1) * wtimer0 units
const uint8_t __code axradio_sync_slave_resyncloss = 11;  // resyncloss is one more than the number of missed packets to cause a resync
// window 0 is the first window after synchronisation
// window 1 is the window normally used when there are no lost packets
// window 2 is used after one packet is lost, etc
const uint8_t __code axradio_sync_slave_nrrx = 3;
const uint32_t __code axradio_sync_slave_rxadvance[] = { 34745, 5195, 13976 };// 1060.325ms, 158.530ms, 426.505ms
const uint32_t __code axradio_sync_slave_rxwindow[] = { 67173, 8073, 25635 }; // 2049.949ms, 246.360ms, 782.310ms
const uint32_t __code axradio_sync_slave_rxtimeout = 89949; // 2745.0ms, maximum duration of a packet