#include <ax8052f143.h>
#include <libmftypes.h>
#include <libmfradio.h>
#include <libmfflash.h>
#include <libmfwtimer.h>
#include <libmfcrc.h>
#include "../AX_Radio_Lab_output/configmaster.h"
#include "../COMMON/misc.h"
#include "../COMMON/configcommon.h"

#include "unb.h"
#include "application.h"
#include "water5.h"



int8_t pwr = 6;
//uint8_t ant = ANT1;
uint8_t channel = 0;
//uint32_t serial;
//uint8_t in = 0x3;
//uint8_t in_old = 3;
uint8_t transmit_pending;

uint8_t it=0;

uint8_t  ina, inb;
uint8_t  oldina, oldinb;

uint8_t rotate_speed = 0;
uint8_t speed = 0;
uint8_t speed_counter = 0;

uint32_t serial;

uint8_t __xdata Voltage = 0xA0;

uint8_t BUTT = 1;

uint8_t GoodCal;
//uint8_t __xdata unb_pckt[]= {0,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21}; //test unb packet


uint8_t CompVersion()
{
    const char CompTime[] = __TIME__;
    const char* ptr;
    uint8_t ver = 0;
    ptr = &CompTime[0];
    while(*ptr) ver += *ptr++;
    return ver;
}

struct wtimer_desc __xdata everysecond_desc, every250ms_desc, every31ms_desc;

void EverySecond(struct wtimer_desc __xdata *desc);
void Every250ms(struct wtimer_desc __xdata *desc);
void Every31ms(struct wtimer_desc __xdata *desc);

void GPIO_Init()
{
    DIRA |= 0x20; //all unused pins = outputs
    DIRB |= 0xF1; //all unused pins = outputs
    DIRC |= 0x1D; //all unused pins = outputs
    PORTA &= 0x07;  //all unused pins = 0;
    PORTB &= 0x0E;  //all unused pins = 0;
    PORTC &= 0x02;  //all unused pins = 0;
    PORTR = 0x0B; //
    DIRR = 0x15; //

 ////
    DIRA |= 0x06;     //0b110  - IRLEN_EN, SENSE_EN = outs
    DIRA &= 0xFE;    //SENSE = input
    DIRC |= 0x02;    //LED = output
    DIRB |= 0x04;    //IMP - unused = output
    PORTB &= 0xFB;   //IMP = 0
    DIRB &= ~(1<<3); // PORTB3 - input(switch)
    PORTB_3 = 1; //pullup for switch
    DIRB |= 0x02;   //TCXO_EN = output
}

/*void GPIO_Deinit()
{
    PORTA = 0x00; //
    PORTB = 0x00; //
    PORTC = 0x00; //
    //PORTR = 0x0B; //

    DIRA = 0xE7; //  PA3,4 - osc
    DIRB = 0xFF; //  PB0 - ANT, PB1 - TCXO, PB2 - IN_SUP
    DIRC = 0xFF; //  PC0 - TX/RX, PC1 - LED, PC2 - button, PC3 - 5V
    //DIRR = 0x15; //
}*/


uint8_t GetVoltageOrTemp(uint8_t val)
{
    uint8_t i = 0;
    uint32_t   VDDIOAVER = 0;
    uint16_t   VDDIO;
    uint32_t   TEMPERAVER = 0;
    uint8_t res;
    EA = 0;
    ADCCLKSRC = 0x30;
    ADCCH1CONFIG = 0xD9;    //VddIO
    ADCCH2CONFIG = 0xD8;    //Temperature
    do
    {
        ADCCONV = 0x01;
        while(ADCCLKSRC&0x80);
        VDDIOAVER += ADCCH1VAL0;
        VDDIOAVER += (((uint16_t)ADCCH1VAL1)<<8);
        TEMPERAVER += ADCCH2VAL0;
        TEMPERAVER += (((uint16_t)ADCCH2VAL1)<<8);

    }
    while(++i);
    EA = 1;
    if(val)
    {
        VDDIO = (((VDDIOAVER>>8)*1000)>>16) - 450;
        res = (VDDIO>300)?0x80:0;
        res += VDDIO%100;
        Voltage = res;

    }
    else res = TEMPERAVER>>16;

    return res;

}

void Setup()
{

    WDTCFG |= 0x1D;

    serial = *((const uint32_t __code*)SERIALPTR);
    random_seed = serial;

    GPIO_Init();

    do
    {
        uint16_t i = 0;
        LED = 1;
        delay_ms(500);
        GetVoltageOrTemp(1);
        delay_ms(500);
        LED = 0;
        if(++i > 60) break;   //wait no more than 1 min
    }
    while(Voltage < 0x94);
  /*  LED = 1;
    delay_ms(500);
    GetVoltageOrTemp(1);
    delay_ms(500);
    LED = 0;
*/
    Water5Init(0);

    everysecond_desc.handler = EverySecond;
    //everysecond_desc.time = 512; // 1 second
    everysecond_desc.time = 40; // 1 second

    wtimer0_addrelative(&everysecond_desc);



    every250ms_desc.handler = Every250ms;
    //every250ms_desc.time = 128; // 1/4 second

    every250ms_desc.time = 10; // 1/4 second

    wtimer0_addrelative(&every250ms_desc);


}

void Loop()
{
    WDTRESET = 0xAE;
    if(Water5Loop())
    {
        if(Voltage > 90) ////if Ubat>3V then PowerLevel Up
        {
            if(++PowLev > 3) PowLev = 3;
        }
        else if(Voltage < 25) { PowLev = 0;}
        else if(Voltage < 70)
        {
            if(--PowLev < 0) PowLev = 0;     //if Ubat<2.8V then PowerLevel down
        }
        pwr = MAXPOWER-9+3*PowLev;
    }
    else
    {
        if(NewMinute >= OSC_CAL_PERIOD)
        {
            NewMinute = 0;
            UNB_Init(UNB_PROTOCOL_C50);
            UNB_Deinit();
            //measure = 1;
        }
    }
}

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)


//uint8_t __xdata testmas[256];


static uint16_t myabs(int16_t a)
{
    if(a > 0) return a;
    else return -a;
}

void Every250ms(struct wtimer_desc __xdata *desc)
{

    static uint16_t ADCRes;

    static uint8_t IMPPrevState = 1;
    static uint8_t runfaster_timer = 255;
    static uint8_t led_was_on = 0;

    static uint8_t magnetic_read = 0;
    static uint8_t magn_period = 1;

    static uint32_t   VDDIOAVER = 0;
    static uint32_t   vdd_tmp;

    static uint16_t VDDIO;
    static uint8_t vddcntr = 0;

    static uint8_t adc_low, adc_high;

   // BUTT =  MAGN;
   // HALL = 1;

    if(magnetic_read == 0) HALL = 1;
    if(magnetic_read == 1)
    {
        BUTT =  MAGN;
        if(!BUTT) {magn_period = 1; runfaster_timer = 255;}
        if(magn_period > 1) HALL = 0;
        //HALL = 0;
    }
    if(magnetic_read++ >= magn_period) magnetic_read = 0;


    if(!W5_Tags.initcal)
    {
        //every250ms_desc.time += 256; // 1/2 сек
        every250ms_desc.time += 10; // 1/2 сек
        wtimer0_addabsolute(&every250ms_desc);
        adc_low = W5_Tags.ADCLOW;
        adc_high = W5_Tags.ADCHIGH;
        return;
    }

    if(led_was_on) {LED = 0; led_was_on=0;}

    ADCCLKSRC = 0x18;
    //ADCCLKSRC = 0x30;
    ADCCH0CONFIG = 0xD9;
    ADCCH1CONFIG = 0xC8;
    ADCCH2CONFIG = 0xC8;
    ADCCH3CONFIG = 0xC8;

    ADCTUNE0 = 0x01;
    ADCTUNE1 = 0x06;
    ADCTUNE2 = 0x00;

    ANALOGA |= 0x01;

    SENSE_EN=1;

    delay(20);

    uint16_t t1, t2, t3;
    int16_t mx, mn;

    IRLED_EN=1;
    delay(10);
    ADCCONV = 0x01;


    delay(25);
    IRLED_EN=0;

    //delay(125);
    //while(ADCCLKSRC&0x80);

    VDDIOAVER += ADCCH0VAL0;
    VDDIOAVER += (((uint16_t)ADCCH0VAL1)<<8);

    t1 = ADCCH1VAL1;
    t1 <<= 8;
    t1 |= ADCCH1VAL0;

    t2 = ADCCH2VAL1;
    t2 <<= 8;
    t2 |= ADCCH2VAL0;

    t3 = ADCCH3VAL1;
    t3 <<= 8;
    t3 |= ADCCH3VAL0;

    SENSE_EN=0;

    mx = max(max(t1,t2),t3);
    mn = min(min(t1,t2),t3);

    ADCRes = (t1^t2^t3^mx^mn);
    ADCRes >>= 8;


    if(ADCRes>adc_high)  //22000
    {
        if(!IMPPrevState)
        {
            W5_Tags.PulseCounter0++;
            IMPPrevState = 1;
            speed++;
            runfaster_timer = 255;
            if(Calibrate)
            {
                LED = 1;
                led_was_on = 1;
            }

        }
    }
    else if(ADCRes<adc_low)
    {
        if(IMPPrevState)
        {
            IMPPrevState = 0;
            speed++;
            runfaster_timer = 255;

        }

    } //18000

    if(++vddcntr == 4)
    {
        VDDIO = (((VDDIOAVER>>2)*1000)>>16) - 450;
        VDDIOAVER = 0;
        adc_low = (((uint32_t)W5_Tags.ADCLOW)*(VDDIO-140)/(W5_Tags.ADCVDD-140));
        adc_high = (((uint32_t)W5_Tags.ADCHIGH)*(VDDIO-140)/(W5_Tags.ADCVDD-140));
        vddcntr = 0;
    }

    if(measure != 0)
    {
        static uint8_t MinMesure = 0xff, MaxMesure;
        static uint16_t AverMesure;
        runfaster_timer = 10;
        //testmas[testptr] = ADCRes;
        if(ADCRes < MinMesure) MinMesure = ADCRes;
        if(ADCRes > MaxMesure) MaxMesure = ADCRes;
        AverMesure +=ADCRes;
        if(++testptr == 256)
        {
            EA = 0;
            testptr = 0;
           /* for (uint16_t j = 0; j < 256-1; j++)
            {
                WDTRESET = 0xAE;
                for (uint16_t i = 0; i < 256 - j - 1; i++)
                {
                    if (testmas[i] > testmas[i+1])
                    {
                        uint8_t b = testmas[i]; //change for elements
                        testmas[i] = testmas[i+1];
                        testmas[i+1] = b;
                    }
                }

            }*/
            AverMesure >>= 8;
            SendBuf[0] = 0xE1;
            uint8_t tmp = (MaxMesure - MinMesure)/8;
            SendBuf[1] = MinMesure + tmp;//testmas[56];
            SendBuf[2] = MaxMesure - tmp;
            SendBuf[3] = MinMesure;
            SendBuf[4] = MaxMesure;
            SendBuf[5] = AverMesure;
            SendBuf[6] = (VDDIO>300)?0x80:0;
            SendBuf[6] += VDDIO%100;
            SendBuf[7] = GoodCal = 0;

            if( ((((uint16_t)MaxMesure)*10/MinMesure) > 20)&&(MinMesure > 40))
            {
                    if(measure == 2)
                    {
                        W5_Tags.ADCLOW = SendBuf[1];
                        W5_Tags.ADCHIGH =  SendBuf[2];
                        W5_Tags.ADCVDD = VDDIO;
                        WriteAllParams();
                    }
                    SendBuf[7] = GoodCal = measure;
                    SendFlag |= 1;

            }
            if(measure == 2)   SendFlag |= 1;
            measure = 0;
            MinMesure = 0xff;
            MaxMesure = 0;
            AverMesure = 0;
            EA = 1;
        }
        else
        {
            runfaster_timer--;
            every250ms_desc.time += 2;  //1/20 sec
            wtimer0_addabsolute(&every250ms_desc);
            return;

        }

    }


    if(++speed_counter == 40)
    {
        speed_counter = 0;
        rotate_speed = speed;
        speed = 0;
    }


    if(runfaster_timer)
    {
        runfaster_timer--;
        //every250ms_desc.time += 128;  1/4 sec
        every250ms_desc.time += 10;  //1/4 sec

    }
    else
    {
        //every250ms_desc.time += 192;    //3/8 sec
        every250ms_desc.time += 15;    //3/8 sec
        magn_period = 10;
     }

    wtimer0_addabsolute(&every250ms_desc);

}




void EverySecond(struct wtimer_desc __xdata *desc)
{
    //everysecond_desc.time += 512;
    everysecond_desc.time += 40;
    wtimer0_addabsolute(&everysecond_desc);
    Water5OneSec();
}

