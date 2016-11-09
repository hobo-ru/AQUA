#ifndef XTEA_H
#define XTEA_H

#include <libmftypes.h>

void Encode(unsigned long __xdata* data, unsigned char dataLength, const uint32_t __code* key);
void Decode(unsigned long __xdata* data, unsigned char dataLength, const uint32_t __code* key);
void XTEA_Encode(uint8_t __xdata *buf, const uint32_t __code* key);
void XTEA_Decode(uint8_t __xdata *buf, const uint32_t __code* key);

#define NUM_ITERATIONS 64
#endif
