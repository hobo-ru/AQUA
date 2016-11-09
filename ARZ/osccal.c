#include <ax8052f143.h>
#include <libmftypes.h>
#include <libmfflash.h>
#include <libmfwtimer.h>
#include <libmfradio.h>
#include <libmfosc.h>
#include <libaxlcd2.h>
#include <libdvk2leds.h>
#include <stdlib.h>



#define XTALFREQ   26000000UL
#define XTALDIV    (((XTALFREQ) > 40000000UL) ? 2 : ((XTALFREQ) > 20000000UL) ? 1 : 0)
#define XTALFRQDIV ((XTALFREQ) >> (XTALDIV))
uint16_t __xdata frcmaxerr;
uint16_t __xdata lpmaxerr;
uint16_t __xdata frcperiod;
uint16_t __xdata lpperiod;
uint8_t __xdata frccalcnt;
uint8_t __xdata lpcalcnt;
uint8_t __xdata clkconsave;

void calibrate_oscillators(void)
{

    frcperiod = 0;
    lpperiod = 0;
    frccalcnt = 0;
    lpcalcnt = 0;
    clkconsave = 0xff;
    ax5043_rclk_enable(XTALDIV);

	uint8_t lposccfg;
	uint8_t frcosccfg;

    frcosccfg = 0x70 | ((CLKSRC_RSYSCLK) & 0x07);
    FRCOSCREF0 = (10000000UL << 8) / ((XTALFRQDIV) >> 6);
    FRCOSCREF1 = ((10000000UL << 8) / ((XTALFRQDIV) >> 6)) >> 8;
    lposccfg = 0x00 | ((CLKSRC_RSYSCLK) & 0x07);
    LPOSCREF0 = (XTALFRQDIV) / 320UL;
    LPOSCREF1 = ((XTALFRQDIV) / 320UL) >> 8;
	FRCOSCKFILT0 = 0x0;
	FRCOSCKFILT1 = 0x40;
	LPOSCKFILT0 = 0x40;
	LPOSCKFILT1 = 0x0;
	FRCOSCCONFIG = frcosccfg;
	LPOSCCONFIG = lposccfg;

    frcmaxerr = FRCOSCREF1;
    frcmaxerr <<= 8;
    frcmaxerr |= FRCOSCREF0;
    frcmaxerr /= 500;

    lpmaxerr = LPOSCREF1;
    lpmaxerr <<= 8;
    lpmaxerr |= LPOSCREF0;
    lpmaxerr /= 500;

    OSCCALIB |= 0x03;

    for (;;) {
        uint8_t osccal = OSCCALIB;
        if (osccal & 0x40) {

            frcperiod = FRCOSCPER1;
            frcperiod <<= 8;
            frcperiod |= FRCOSCPER0;

            uint16_t tmp = FRCOSCREF1;
            tmp <<= 8;
            tmp |= FRCOSCREF0;

            if (abs(frcperiod - tmp) > frcmaxerr)
                frccalcnt = 0;
            else if (frccalcnt != 0xff)
                ++frccalcnt;
        }
        if (osccal & 0x80) {
            lpperiod = LPOSCPER1;
            lpperiod <<= 8;
            lpperiod |= LPOSCPER0;

            uint16_t tmp = LPOSCREF1;
            tmp <<= 8;
            tmp |= LPOSCREF0;

            if (abs(lpperiod - tmp) > lpmaxerr)
                lpcalcnt = 0;
            else if (lpcalcnt != 0xff)
                ++lpcalcnt;
        }
        if (frccalcnt > 4 && lpcalcnt > 4)
            break;
        wtimer_runcallbacks();
    }
    OSCCALIB &= (uint8_t)~0x03;
    if (clkconsave != 0xff) {
        // undo
        CLKCON = 0x08 | CLKSRC_FRCOSC;
        while ((CLKCON & 0x3F) != (0x08 | CLKSRC_FRCOSC));
        CLKCON = clkconsave;
    }
    ax5043_rclk_disable();
}
