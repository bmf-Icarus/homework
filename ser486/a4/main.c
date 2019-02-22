/*
 */

#include "hw4lib.h"
#include "output.h"

#define DDRB (*(volatile char *)0x24)


int main(void)
{
    // set pin1 on portb as output
    DDRB |= 0x02;

    // initialize uart functions in memory
    uart_init();

    writestr("SER486 HW4 - Jaime Rabago\n\r");

    writehex8(0x0a);
    writestr("\n\r");
    writehex16(0xc0de);
    writestr("\n\r");

    while(1)
    {
        blink_led("--- -.-");
        delay(2000);
    }

    return 0;
}
