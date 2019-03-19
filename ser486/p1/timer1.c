/*	Jaime Rabago
 *	project1	SER486
 *	timer1.c
 *
 *  the delay class utilizes the timer1 hardware to track 1s intervals
 *  to measure time during code execution
 */


#define TCCR1A (*(volatile char *)0x80)
#define TCCR1B (*(volatile char *)0x81)
#define TIMSK1 (*(volatile char *)0x6F)
#define OCR1AL (*(volatile char *)0x88)
#define OCR1AH (*(volatile char *)0x89)
#define SREG (*(volatile char *)0x5F)

unsigned long volatile count = 0;
unsigned char timer1_temp_byte = 0;

// initializes the 16 bit clock for 1 second interrputs for future error logging
void timer1_init()
{

    // the clock is running at 15625hz
	// store 15625 or 0x3D09 in OCR1A for 1 second interrupts
	OCR1AL |= 0x09;
	OCR1AH |= 0x3D;
    // set wgm12 for ctc and cs12 cs10 to high for 1024 pre scalar
    TCCR1B |= 0x0D;
    // enable timer interrupt bit1
    TIMSK1 |= 0x02;

	// enable global interrupts
	SREG |= 0x80;


}

// gets current count of timer1 count progression atomic operation
unsigned long timer1_get(void)
{
    unsigned long temp_long = 0;
    // save status register
    timer1_temp_byte = SREG;
    // disable interrupts
    SREG &= 0x7F;
    // store the current value of count
    temp_long = count;
    // restore global interrupt and status
    SREG |= timer1_temp_byte;
    return temp_long;

}
// atomically clear count
void timer1_clear()
{
    // save status register
    timer1_temp_byte = SREG;
    // disable interrupts
    SREG &= 0x7F;
    // clear current state
    count = 0;
    // restore sreg state also enables interrupts again
    SREG |= timer1_temp_byte;
}
// ISR for 1s counter
void __vector_11(void) __attribute__ ((signal, used, externally_visible));
void __vector_11(void)
{
    count++;
}
