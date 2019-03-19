/*  Jaime Rabago Jr
    project1


    main.c

    control loop for program displays non blocking error codes and time keeping
 */
#include "uart.h"
#include "rtc.h"
#include "led.h"
#include "delay.h"
#include "timer1.h"

int main(void)
{

    // initialize
    led_init();
    uart_init();
    // the program does not work without this init
    // i know rtc is supposed to call timer1_init();
    //  but it doesnt.
    timer1_init();
    rtc_init();

    // send the string to be played forever 
    led_set_blink("--- -.-");
    // reset the rtc to a base time.
    rtc_set_by_datestr("01/01/2019 00:00:00");

    uart_writestr("SER486 Project 1 - Jaime Rabago \n\r");

    /* get baseline performance */
    signed long c1=0;
    delay_set(1,10000); while (!delay_isdone(1)) { c1++; }

    /* measure performance with led_update */
    signed long c2=0;
    delay_set(1,10000); while (!delay_isdone(1)) { led_update(); c2++; }

    /* display the results */
    uart_writedec32(c1); uart_writestr(" ");
    uart_writedec32(c2); uart_writestr("\r\n");

    // update the clock on the cli for a 2hz refresh rate
    delay_set(1,500);
    while(1)
    {

        led_update();

	// display the clock when half a sec has passed
        if(delay_isdone(1))
        {
		// write out time
            uart_writestr(rtc_get_date_string());
	    // reset cursor
            uart_writechar('\r');
        }

    };

    return 0;
}
