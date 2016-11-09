#include "display_com0.h"

#include <ax8052f143.h>
#include <libmf.h>
#include <libmfuart.h>
//#include <libmfuart0.h>
#include <libmfuart1.h>

static const __code char lcd_border[]=
"\x1b[0;8;44;30m\x1b[1;1f"
"******************\x1b[2;1f"
"*                *\x1b[3;1f"
"*                *\x1b[4;1f"
"******************\x1b[5;1f\x1b[37m\x1b[?25l";

uint8_t __xdata row;
uint8_t __xdata column;

#if 0
__reentrantb void com0_inituart0(void) __reentrant
{
    // need this if libmfuart0.h is included. Including but not initializing the uart prevents sleeping (wtimer_cansleep will evaluate uart0_txidle() which does not work without clock)
    uart_timer0_baud(CLKSRC_SYSCLK, 115200, 20000000UL);
    uart0_init(0, 8, 1);
}
#endif

__reentrantb void com0_portinit(void) __reentrant
{
//    PALTB |= 0x11;
//    DIRB |= (1<<0) | (1<<4);
//    DIRB &= (uint8_t)~(1<<5);
//    PINSEL &= (uint8_t)~((1<<0) | (1<<1));
//
//    uart_timer0_baud(CLKSRC_SYSCLK, 115200, 20000000UL);
//    uart0_init(0, 8, 1);

    PALTA |= 0x20;
    DIRA |= 0x20;
    DIRA &= (uint8_t)~(0x04);
    PORTA &= (uint8_t)~(0x24);
    PINSEL |= 0x02;

    uart_timer0_baud(CLKSRC_FRCOSC, 115200, 17083000UL);
    uart1_init(0,8,1);
}

__reentrantb void com0_init(void) __reentrant
{
//    uart_timer0_baud(CLKSRC_SYSCLK, 115200, 20000000UL);
//    uart0_init(0, 8, 1);

    uart_timer0_baud(CLKSRC_FRCOSC, 115200, 17083000UL);
    uart1_init(0,8,1);

    com0_writestr(lcd_border);
    com0_setpos(0);
}

__reentrantb void com0_writestr2(const char* msg)  __reentrant
{
    uart1_writestr(msg);
}

static __reentrantb void com0_setrowcol(void) __reentrant
{
    uart1_tx(0x1b);
    uart1_tx('[');
    uart1_tx(row + '0');
    uart1_tx(';');
    uart1_tx(column / 10 + '0');
    uart1_tx(column % 10 + '0');
    uart1_tx('f');
}

__reentrantb void com0_newline(void) __reentrant
{
    if (row < 3)
        ++row;
    column = 2;
    com0_setrowcol();
}

__reentrantb void com0_setpos(uint8_t v) __reentrant
{
    //http://www.termsys.demon.co.uk/vtansi.htm
    //Force Cursor Position	<ESC>[{ROW};{COLUMN}f
    row = (v >> 6) + 2;
    column = (v & 0x3F) + 2;
    com0_setrowcol();
}

__reentrantb void com0_writestr(const char __generic *msg) __reentrant
{
    for (;;) {
        char ch = *msg;
        if (!ch)
            break;
        com0_tx(ch);
        msg++;
    }
    //com0_allow_swreset();
}

__reentrantb void com0_tx(uint8_t val)  __reentrant
{
    if (val == '\n')
        com0_newline();
    else
        uart1_tx(val);
}

__reentrantb void com0_clear(uint8_t pos, uint8_t len) __reentrant
{
    com0_setpos(pos);
    if (!len)
        return;
    do {
        com0_tx(' ');
    } while (--len);
}

