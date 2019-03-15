/*  Jaime Rabago Jr
    project1

 */
#include "uart.h"
#include "rtc.h"
#include "led.h"
#include "delay.h"

int main(void)
{

    // initialize
    rtc_init();
    led_init();
    uart_init();

    led_set_blink("--- -.-");
    rtc_set_by_datestr("01/01/2019 00:00:00");

    uart_writestr("SER486 Project 1 - Jaime Rabago \n\r");

    /* get baseline performance */
    signed long c1=0;
    delay_set(1,100); while (!delay_isdone(1)) { c1++; }

    /* measure performance with led_update */
    signed long c2=0;
    delay_set(1,100); while (!delay_isdone(1)) { led_update(); c2++; }

    /* display the results */
    uart_writedec32(c1); uart_writestr(" ");
    uart_writedec32(c2); uart_writestr("\r\n");

    // keeps track of the clock displayed through serial
    delay_set(1,500);
    while(1)
    {
        led_update();
        if(delay_isdone(1))
        {
            //uart_writestr(rtc_num2datestr(rtc_get_date()));
            uart_writestr(rtc_get_date_string());
            uart_writechar('\r');
        }

    };

    return 0;
}
