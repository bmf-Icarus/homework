/********************************************************
 * output.c
 *
 * SER486 Assignment 4
 * Spring 2018
 * Written By:  Doug Sandy (instructor)
 * Modified By: JJ Rabago
 *
 * this file implements functions associated with SER486
 * homework assignment 4.  The procedures implemented
 * provide led and console output support for debugging
 * of future SER 486 assignments.
 *
 * functions are:
 *    writestr(char *)  - a function to write an ascii
 *                        null-terminated string to the
 *                        avr atmega 328P uart port.
 *                        (instructor provided)
 *
 *    writehex8(unsigned char) - a function to write the
 *                        hexadecimal representation of
 *                        an 8-bit unsigned integer to
 *                        avr atmega 328P uart port.
 *
 *    writehex16(unsigned int) - a function to write the
 *                        hexadecimal representation of
 *                        a 16-bit unsigned integer to
 *                        avr atmega 328P uart port.
 *
 *    blink_led(char *) - a function to send a specific
 *                        blink pattern to the development
 *                        board's user-programmable LED.
 *
 *    delay(unsigned int) - delay code execution for
 *                        the specified amount of milliseconds.
 *                        (instructor provided)
 */

 #include "hw4lib.h"

 /* macro definitions used by delay() */
 #define MSEC_PER_SEC     1000
 #define CLOCKS_PER_LOOP  16
 #define LOOPS_PER_MSEC   ((F_CPU/MSEC_PER_SEC)/CLOCKS_PER_LOOP)

/**********************************
 * delay(unsigned int msec)
 *
 * This code delays execution for for
 * the specified amount of milliseconds.
 *
 * arguments:
 *   msec - the amount of milliseconds to delay
 *
 * returns:
 *   nothing
 *
 * changes:
 *   nothing
 *
 * NOTE: this is not ideal coding practice since the
 * amount of time spent in this delay may change with
 * future hardware changes.  Ideally a timer should be
 * used instead of a set of for loops.  Timers will be
 * taught later in the semester.
 */
void delay(unsigned int msec)
{
    volatile unsigned i,j ;  /* volatile prevents loops from being optimized away */

    /* outer loop, loops for specified number of milliseconds */
    for (i=0; i<msec; i++) {
        /* inner loop, loops for 1 millisecond delay */
        for (j=0;j<LOOPS_PER_MSEC;j++) {}
    }
}


/**********************************
 * writestr(char * str)
 *
 * This code writes a null-terminated string
 * to the UART.
 *
 * arguments:
 *   str - a pointer to the beginning of the
 *         string to be printed.
 *
 * returns:
 *   nothing
 *
 * changes:
 *   the state of the uart transmit buffer will
 *   be changed by this function.
 *
 * NOTE: uart_init() should be called this function
 *   is invoked for the first time or unpredictable
 *   UART behavior may result.
 */
void writestr(char * str)
{
    unsigned int i;

    /* loop for each character in the string */
    for (i=0; str[i]!=0;i++) {
        /* output the character to the UART */
        uart_writechar(str[i]);
    }
}

/************************************************************
* STUDENT CODE BELOW THIS POINT
*************************************************************/

#define PORTB (*(volatile char *)0x25)

/* fx breaks 1 byte into 4bit array,
    converts int value to ascii code in helper fx*/
void writehex8(unsigned char num)
{
    // separate the byte into four bits each
    unsigned char char4Arr[2];
    char4Arr[1]= num & 0x0F;
    char4Arr[0]= num >> 4;

    for(char i = 0; i < 2; i++)
    {
        ;
        if( (char4Arr[i] >= 0) && (char4Arr[i] < 10))
        {   // num is 9 or less which map to hex
            // ascii code for 0 evaluates to 48
            uart_writechar(char4Arr[i]+'0');
        }else if( char4Arr[i] >= 10 && char4Arr[i] < 16)
        {   // num-10 because we start at 0xA which is 10(decimal)
            // thus 0 = A(65) and 5 = F(70)
            uart_writechar((char4Arr[i]-10)+'A');
        }
    }

}

/* fx similar to writehex8 but 2x bigger */
void writehex16(unsigned int num)
{
    unsigned char char4Arr[2];

    char4Arr[1]= num & 0x00FF;
    char4Arr[0]= num >> 8;

    for(char i = 0; i < 2; i++)
    {
        writehex8(char4Arr[i]);
    }

}

/* Student-provided function comments go here */
void blink_led(char *msg)
{
    unsigned char i = 0;

    while(msg[i] != '\0')
    {
        /* student-provided implementation code goes here */
        if( msg[i] == '-')
        {   // turn on portb
            PORTB |= 0x02;
            delay(750);
            //turn off portb
            PORTB &= 0xFD;
            delay(100);
        }else if( msg[i] == '.')
        {   // turn on portb
            PORTB |= 0x02;
            delay(250);
            // turn off portb
            PORTB &= 0xFD;
            delay(100);
        }else if( msg[i] == ' ')
        {
            delay(1000);
        }
        i++;

    }
}
