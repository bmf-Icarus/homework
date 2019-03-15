/*	Jaime Rabago
 *	project1	SER486
 *	timer1.c
 *
 *  the delay class utilizes the timer1 hardware to track 1s intervals
 *  to measure time during code execution
 */


#define TCCR1A (*(volatile char *)0x80)
#define TCCR1B (*(volatile char *)0x81)
#define TCCR1C (*(volatile char *)0x82)
#define TIMSK1 (*(volatile char *)0x6F)
#define OCR1AL (*(volatile char *)0x88)
#define OCR1AH (*(volatile char *)0x89)
#define SREG (*(volatile char *)0x5F)

unsigned long volatile count_1s = 0;

unsigned char timer1_temp_byte = 0;

void timer1_init(void)
{
    // normal port operation no channels needed
    // tccr1a bit0 and bit1 are WGM 10 & 11 they must be low
    // for CTC on register OCR1A
    TCCR1A &= 0x00;
    // and mask to set wgm13 and cs11 as low ignore everything else
    TCCR1B &= 0xCD;
    // set wgm12 cs12 cs10 to high for 1024 pre scalar
    TCCR1B |= 0x0D;
    // forced output disabled
    TCCR1C &= 0x3F;
    // enable timer interrupt bit0 TOIE
    TIMSK1 |= 0x01;

	// enable global interrupts
	SREG |= 0x80;
	// __builtin_avr_sei();
	// the clock is running at 15625hz
	// store 15625 or 0x3D09 in OCR1A for 1 second interrupts
	OCR1AL = 0x09;
	OCR1AH = 0x3D;
}

unsigned long timer1_get(void)
{
    unsigned long temp_long = 0;
    // save status register
    timer1_temp_byte = SREG;
    // disable interrupts
    SREG &= 0x7F;
    // store the current value of count
    temp_long = count_1s;
    // restore global interrupt and status
    SREG = timer1_temp_byte;
    return temp_long;

}

void timer1_clear()
{
    // save status register
    timer1_temp_byte = SREG;
    // disable interrupts
    SREG &= 0x7F;
    // clear current state
    count_1s = 0;
    // restore sreg state also enables interrupts again
    SREG = timer1_temp_byte;
}

void __vector_11(void) __attribute__ ((signal, used, externally_visible));
void __vector_11(void)
{
    count_1s++;
}
