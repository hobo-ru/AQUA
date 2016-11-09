
#include <ax8052f143.h>
#include <libmftypes.h>
#include <libmfwtimer.h>
#include <libmfflash.h>
#include <stdlib.h>
#include "../COMMON/misc.h"
#include "unb.h"
#include "application.h"
#include "water5.h"

W5_TAGS_TO_SAVE W5_Tags;


uint8_t __xdata SendBuf[8];
uint8_t __xdata LaterSendBuf[8];
uint8_t   LaterTimer = 0;

uint8_t __xdata SendFlag;

uint8_t __xdata Seconds = 0;
uint8_t __xdata Minutes = 0;
uint8_t __xdata Hours = 0;
uint8_t __xdata Days = 0;
uint8_t __xdata Days4month = 0;

uint8_t __xdata NewMinute = 0;

uint16_t __xdata HourMas0[24], HourMas1[24];
uint16_t __xdata DayMas0[7], DayMas1[7];

uint8_t __xdata sendweekflag = 0;
uint8_t __xdata sendmonthflag = 0;

uint32_t  __xdata PC_PrevHour0, PC_PrevHour1;
uint32_t  __xdata PC_PrevDay0, PC_PrevDay1;
uint32_t  __xdata PC_PrevMinute0, PC_PrevMinute1;

uint8_t   __xdata MaxFlow0 = 0;
uint8_t   __xdata MaxFlow1 = 0;

uint8_t  __xdata Calibrate;

uint16_t  __xdata Switch_i;

int8_t  __xdata PowLev = 0;

uint32_t __xdata DaysAfterDepas = 59;

uint8_t waitsomeminutes = 0;

uint16_t testptr = 0;
uint8_t measure = 0;


void mem_set(uint8_t* ptr, uint8_t data, uint16_t len) {while(len--) *ptr++ = data;}



void ReadAllParams()
{


    uint16_t* ptr = (uint16_t*)&W5_Tags;

    for(int i = 0; i < sizeof(W5_TAGS_TO_SAVE); i+=2)
    {
        *ptr++ = flash_read(EDATAPTR + i);
    }

}

void WriteAllParams()
{

    uint16_t* ptr = (uint16_t*)&W5_Tags;

    flash_unlock();
    flash_pageerase(EDATAPTR);

    for(int i = 0; i < sizeof(W5_TAGS_TO_SAVE); i += 2)
    {
        flash_write(EDATAPTR + i,*ptr++);
    }

    flash_lock();

}

void ClearAllParams()
{
  mem_set((void*)&W5_Tags, 0, sizeof(W5_TAGS_TO_SAVE));
  W5_Tags.ADCLOW = DEFAULT_ADCLOW;
  W5_Tags.ADCHIGH = DEFAULT_ADCHIGH;
  W5_Tags.ADCVDD = DEFAULT_ADCVDD;
  WriteAllParams();
}


void Water5Init(uint8_t clear)
{

    ReadAllParams();

    if(clear||(W5_Tags.Protocol == 0xff))  ClearAllParams();

    testptr = 0;

    for(int i = 0; i < 24; i++) HourMas0[i] = HourMas1[i] = 0;
    for(int i = 0; i < 7; i++) DayMas0[i] = DayMas1[i] = 0;

    PC_PrevMinute0 = PC_PrevHour0 = PC_PrevDay0 = W5_Tags.PulseCounter0;
    PC_PrevMinute1 = PC_PrevHour1 = PC_PrevDay1 = W5_Tags.PulseCounter1;

    *((uint32_t __xdata*)(&SendBuf[1])) = W5_Tags.PulseCounter0;
    *((uint32_t __xdata*)(&LaterSendBuf[1])) = W5_Tags.PulseCounter1;

    SendBuf[0] = 0x41;
    LaterSendBuf[0] = 0x49;

    SendBuf[5] = LaterSendBuf[5] = HARDWARE_REV;
    SendBuf[6] = LaterSendBuf[6] = SOFTWARE_REV;
    //SendBuf[5] = LaterSendBuf[5] = LPOSCFREQ1;
    //SendBuf[6] = LaterSendBuf[6] = LPOSCFREQ0;
    SendBuf[7] = LaterSendBuf[7] = CompVersion();

    SendFlag = 3;


}


void PCSendDayData(uint8_t chan, uint8_t later)
{

    uint8_t i;
    uint32_t Hours2BitsLo, Hours2BitsHi;
    uint16_t maxHour;

    uint16_t __xdata* HourMas;
    uint8_t __xdata*  buf;


    Hours2BitsLo = 0;
    Hours2BitsHi = 0;

    maxHour = 1;

    EA = 0;
    WriteAllParams();
    EA = 1;

    HourMas = chan?HourMas1:HourMas0;
    buf =  later?LaterSendBuf:SendBuf;

    for(i=0;i!=24;i++) if(HourMas[i] > maxHour) maxHour = HourMas[i];

    for(i=0;i!=24;i++)
    {
        if(HourMas[i])
        {
            if(i<16) Hours2BitsLo+=(((uint32_t)(HourMas[i])*3*99/maxHour/100)+1)<<(i*2);
            else Hours2BitsHi+=(((uint32_t)(HourMas[i])*3*99/maxHour/100)+1)<<((i-16)*2);
        }

    }
    *((uint16_t __xdata*)(&buf[0])) = ((((chan?W5_Tags.PulseCounter1:W5_Tags.PulseCounter0)/DIV)&0xFFFF)<<1)&0xfffe;
    *((uint32_t __xdata*)(&buf[2])) = Hours2BitsLo;
    *((uint16_t __xdata*)(&buf[6])) = Hours2BitsHi&0xFFFF;

    if(later)
    {
       LaterTimer = later&0x7F;
       if(later&0x80) SendFlag |= 2;
    }
    else SendFlag |= 1;

}


void PCSendWeekData(uint8_t chan, uint8_t later)
{

    uint8_t i;

    uint16_t   maxDay;
    uint32_t   DayBits;
    uint16_t __xdata * DayMas;
    uint8_t __xdata*  buf;

    DayMas = chan?DayMas1:DayMas0;
    buf =  later?LaterSendBuf:SendBuf;

    *((uint32_t __xdata*)(&buf[1])) = chan?W5_Tags.PulseCounter1:W5_Tags.PulseCounter0;

    buf[7] = Voltage;

    DayBits = 0;
    maxDay=1;
    for(i=0;i!=7;i++) if(DayMas[i] > maxDay) maxDay = DayMas[i];
    for(i=0;i!=7;i++) DayBits+=(((uint32_t)(DayMas[i])*8*99/maxDay/100))<<(i*3);

    DayBits<<=3;
    DayBits|=buf[4]&0x7;
    *((uint16_t __xdata*)(&buf[4])) = DayBits&0xFFFF;
    buf[6] = DayBits>>16;
    buf[0] = chan?0x7B:0x73;

    if(later)
    {
       LaterTimer = later&0x7F;
       if(later&0x80) SendFlag |= 2;
    }
    else SendFlag |= 1;
}

void PCSendExtInfo(uint8_t chan, uint8_t later)
{

     uint8_t __xdata*  buf;

     buf =  later?LaterSendBuf:SendBuf;

     buf[0] = chan?0x89:0x81;;
     buf[1] = HARDWARE_REV;
     buf[2] = SOFTWARE_REV;
     buf[3] = CompVersion();
     buf[4] = GetVoltageOrTemp(0);
     buf[5] = Voltage;
     buf[6] = pwr;
     buf[7] = chan?MaxFlow1:MaxFlow0;

     if(later)
     {
       LaterTimer = later&0x7F;
       if(later&0x80) SendFlag |= 2;
     }
     else SendFlag |= 1;
}

void PCSendInfoData(uint8_t chan, uint8_t later)
{
     static uint8_t sendextinfo_timer = 5;

     uint8_t __xdata*  buf;
     if(!chan) sendextinfo_timer++;
     if(!(sendextinfo_timer%6))
     {
        PCSendExtInfo(chan, later);
        return;
     }

     buf =  later?LaterSendBuf:SendBuf;

     *((uint32_t __xdata*)(&buf[1])) = chan?W5_Tags.PulseCounter1:W5_Tags.PulseCounter0;
     *((uint16_t __xdata*)(&buf[5])) = W5_Tags.MesNum;
     //SendBuf[5] = LaterSendBuf[5] = LPOSCFREQ1;
     //SendBuf[6] = LaterSendBuf[6] = LPOSCFREQ0;

     buf[0] = chan?0x69:0x61;
     buf[7] = PowLev;
     buf[7] <<= 6;
     buf[7] += (chan?MaxFlow1:MaxFlow0)&0x3F;
     if(later)
     {
       LaterTimer = later&0x7F;
       if(later&0x80) SendFlag |= 2;
     }
     else SendFlag |= 1;
}


void PCSendComm(uint8_t comm, uint8_t chan, uint8_t later)
{
     uint8_t __xdata*  buf;

     buf =  later?LaterSendBuf:SendBuf;

     *((uint32_t __xdata*)(&buf[1])) =  chan?W5_Tags.PulseCounter1:W5_Tags.PulseCounter0;
     buf[5] = comm;
     buf[6] = GetVoltageOrTemp(0);
     buf[7] = Voltage;
     buf[0] = chan?0x59:0x51;
     if(later)
     {
       LaterTimer = later&0x7F;
       if(later&0x80) SendFlag |= 2;
     }
     else SendFlag |= 1;
}


uint8_t __xdata tmp_buf[8];
bool Water5Loop()
{

    if(SendFlag&1)
    {
        SendFlag &= 0xfe;
        for(uint8_t i = 0; i != 8; i++) tmp_buf[i] = SendBuf[i];
        if(W5_Tags.Protocol) UNB_Send(tmp_buf, serial, 8);
        else UNB_ProtocolC_Send(tmp_buf, serial);
        W5_Tags.MesNum++;
        return 1;

    }
    else if(SendFlag&2)
    {
        SendFlag &= 0xfd;
        #ifdef TWOCHANNELS
        if(W5_Tags.Protocol) UNB_Send(LaterSendBuf,serial,8);
        else UNB_ProtocolC_Send(LaterSendBuf, serial);
        W5_Tags.MesNum++;
        return 1;
        #endif

    }

    return 0;
}

void  Water5OneSec()    //run it every 1 sec
{


#ifdef AQUA
    if(W5_Tags.initcal > 1)
    {
        if((W5_Tags.PulseCounter0  >= 2)&&(GoodCal))
        {
            if(W5_Tags.initcal>2) {rotate_speed = 1;speed_counter = 0; speed=0; LED = 0; W5_Tags.initcal = 2;}
            if(rotate_speed == 0 )
            {
                    W5_Tags.initcal = 1;
                    EA = 0;
                    WriteAllParams();
                    EA = 1;
                    Switch_i = 66;
            }

        }
        else
        {
            if(--W5_Tags.initcal == 1) {W5_Tags.initcal = 0; LED = 0;}
            if((measure == 0)&&(GoodCal == 0)) measure = 1;
        }
    }
#endif // AQUA


    if(!BUTT&&(Switch_i!=60)&&!waitsomeminutes)
    {
        Calibrate = 0;
        LED = Switch_i%2;
        Switch_i++;
    }
    else
    {
        if(!(DaysAfterDepas%60)&&(Voltage < 0x80)) LED = 1;
        if(Voltage < 60) LED = 1;
        if(Switch_i)
        {
            if(W5_Tags.initcal != 1)
            {

#ifdef AQUA
                W5_Tags.initcal = 240;
                Switch_i = 0;
                LED = 1;
                measure = 1;
                return;

#else
                W5_Tags.initcal = 1;
                WriteAllParams();
                Switch_i = 66;
#endif
             }
            switch(Switch_i/2)
            {
            case 5: //cal
            case 33: //init cal
                if(Switch_i/2 == 5) Calibrate = 10;
                PC_PrevMinute0 = PC_PrevHour0 = PC_PrevDay0 = W5_Tags.PulseCounter0;
                PC_PrevMinute1 = PC_PrevHour1 = PC_PrevDay1 = W5_Tags.PulseCounter1;
                Seconds = random() % 60;;
                Minutes = random() % 60;;
                Hours = 12 + random() % 11;
                MaxFlow0 = MaxFlow1 = 0;
                for(int i = 0; i < 24; i++) HourMas0[i] = HourMas1[i] = 0;
                for(int i = 0; i < 7; i++) DayMas0[i] = DayMas1[i] = 0;
                EA = 0;
                WriteAllParams();
                EA = 1;
                PCSendComm(Switch_i/2,0,0);
                PCSendComm(Switch_i/2,1,0x80);
                break;
            case 7://15:
                measure = 2;
                break;
            case 21:
                if(W5_Tags.Protocol) W5_Tags.Protocol = 0;
                else W5_Tags.Protocol = 1;
                EA = 0;
                WriteAllParams();
                EA = 1;
                break;
           case 30:
                EA = 0;
                WriteAllParams();
                EA = 1;
                PCSendComm(30,0,0);
                waitsomeminutes = 120;
                break;
            case 0:
                break;

            default:
                Calibrate = 10;
                EA = 0;
                WriteAllParams();
                EA = 1;
                PCSendComm(Switch_i/2,0,0);
                PCSendComm(Switch_i/2,1,0x80);
                break;
            }
            Switch_i = LED = 0;
        }
    }

    if(++Seconds == 60)
    {

        Seconds = 0;

        if((W5_Tags.PulseCounter0 - PC_PrevMinute0) > MaxFlow0) MaxFlow0 = W5_Tags.PulseCounter0 - PC_PrevMinute0;
        if((W5_Tags.PulseCounter1 - PC_PrevMinute1) > MaxFlow1) MaxFlow1 = W5_Tags.PulseCounter1 - PC_PrevMinute1;

        PC_PrevMinute0 = W5_Tags.PulseCounter0;
        PC_PrevMinute1 = W5_Tags.PulseCounter1;

        if(LaterTimer)
        {
            if(--LaterTimer == 0) SendFlag |= 2;
        }

        if(Calibrate&&!SendFlag)
        {
            Calibrate--;
            PCSendInfoData(0,0);
            PCSendInfoData(1,0x80);
        }

        if(sendweekflag)
        {
            sendweekflag = 0;
            PCSendWeekData(0,0);
            PCSendWeekData(1,0x80);
        }
        else if(sendmonthflag)
        {
            sendmonthflag = 0;
            PCSendInfoData(0,0);
            PCSendInfoData(1,0x80);
        }

        if(waitsomeminutes) waitsomeminutes--;
        NewMinute++;
        if(++Minutes == 60)
        {
            Minutes = 0;
            LED = 0;
            HourMas0[Hours] = W5_Tags.PulseCounter0 - PC_PrevHour0;
            PC_PrevHour0 = W5_Tags.PulseCounter0;

            HourMas1[Hours] = W5_Tags.PulseCounter1 - PC_PrevHour1;
            PC_PrevHour1 = W5_Tags.PulseCounter1;

            if((!(W5_Tags.poehali&0x1))&&(HourMas0[Hours]>2))
            {
                W5_Tags.poehali |= 1;
                PCSendInfoData(0,0);
            }
            if((!(W5_Tags.poehali&0x2))&&(HourMas1[Hours]>2))
            {
                W5_Tags.poehali |= 2;
                PCSendInfoData(1,0x80);
            }

            if(++Hours == 24)
            {
                Hours = 0;
                DaysAfterDepas++;
                DayMas0[Days] = W5_Tags.PulseCounter0 - PC_PrevDay0;
                DayMas1[Days] = W5_Tags.PulseCounter1 - PC_PrevDay1;
                PC_PrevDay0 = W5_Tags.PulseCounter0;
                PC_PrevDay1 = W5_Tags.PulseCounter1;
#ifdef TWOCHANNELS
                if(W5_Tags.Protocol)
                {
                    PCSendDayData(0,0);
                    PCSendDayData(1,30);
                }
                else
                {
                    PCSendDayData(0,0x80*((UNB_GetCiter()%2) != 0));
                    PCSendDayData(1,0x80*((UNB_GetCiter()%2) == 0));
                }
#else
                PCSendDayData(0,0);
#endif
                if(++Days == 7) {Days = 0; sendweekflag = 2;}
                if(++Days4month == 30) {Days4month = 0; sendmonthflag = 1;}

            }
        }
    }
}

