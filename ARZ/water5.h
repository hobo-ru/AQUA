#ifndef WATER5_H_INCLUDED
#define WATER5_H_INCLUDED


void Water5OneSec();
void Water5Init(uint8_t);
bool Water5Loop();

void ClearAllParams();
void WriteAllParams();

typedef struct _W5_TAGS_TO_SAVE
{
  uint32_t PulseCounter0;
  uint32_t PulseCounter1;
  uint16_t MesNum;
  uint8_t Protocol;
  uint8_t poehali;
  uint8_t initcal;
  uint8_t ADCLOW;
  uint8_t ADCHIGH;
  uint16_t ADCVDD;
  uint8_t reservedMas[13];
} W5_TAGS_TO_SAVE;


extern W5_TAGS_TO_SAVE W5_Tags;

extern int8_t  __xdata PowLev;
extern uint8_t  __xdata Calibrate;
extern uint16_t  testptr;
extern uint8_t   measure;
extern uint8_t __xdata NewMinute;
extern uint8_t __xdata SendBuf[8];
extern uint8_t __xdata SendFlag;

#endif // WATER5_H_INCLUDED
