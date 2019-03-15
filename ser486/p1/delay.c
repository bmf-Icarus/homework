/*	Jaime Rabago
 *	project1	SER486
 *	delay.c
 *
 *  the delay class utilizes the timer0 hardware to track 1ms intervals
 *  to measure time during code execution. This project calls for two instances
 *  to track timings
 */

#define TCCR0A (*(volatile char *)0x44)
#define TCCR0B (*(volatile char *)0x45)
#define TIMSK0 (*(volatile char *)0x6E)
#define OCR0A (*(volatile char *)0x47)
#define SREG (*(volatile char *)0x5F)

// count keeps track of time passed
unsigned int volatile count[] = {0,0};
// limit is what the count goes up to
unsigned int limit[] = {0,0};
// initialized will act as a flag as to not reset current settings.
unsigned char initialized = 0;
// used to save sreg state
unsigned char timer0_temp_byte = 0;

// initializes the timer functionality with necessary registers
void delay_init(void)
{
	// clear out output modes & set WGM00 to low
	TCCR0A &= 0x00;
	// set timer to clear on compare match - set WGM01 to high
	TCCR0A |= 0x02;
	// set WGM02 to low
	TCCR0B &= 0xC0;
	// set CS0[2] as high for 64 pre-scaler on clock
	TCCR0B |= 0x03;
	// enable timer interrupt bit0 TOIE
	TIMSK0 |= 0x01;

	// enable global interrupts
    SREG |= 0x80;

	// timer0 is now set on a pre-scaler of 64
	// the clock will run at 250kHz which works out well
	// every 250 cycles about 1ms would pass.
	// this will produce an approx 1ms interrupt
	OCR0A = 0xF9;
	// at this point initialization is complete
	initialized = 1;
}

// get the delay and do it atomically
unsigned int delay_get(unsigned int num)
{
    unsigned int d_value;
    // save the current state of SREG before disabling the interrupts
    // for an atomic operation
    timer0_temp_byte = SREG;
    SREG &= 0x7F;
    d_value = count[num];
    SREG = timer0_temp_byte;

	// return the count for given instance
	return d_value;
}

// set delay for given instance and do it atomically
void delay_set(unsigned int num, unsigned int time)
{
	// only two instances are valid
	if(!(num >= 0 && num < 2))
	{
		// exit function if instance DNE
		return;
	}
	// makes sure timer is initialized
	if(!initialized) { delay_init(); }

	timer0_temp_byte = SREG;
    SREG &= 0x7F;
	// set the limit for given instance
	limit[num] = time;
	// clear count for given instance
	count[num] = 0;

	SREG = timer0_temp_byte;
}

// function to ensure count equals limit
unsigned int delay_isdone(unsigned int num)
{
	if( count[num] == limit[num] )
	{
	    // once this has been read reset the counter
	    count[num]=0;
		return 1;
	}else
	{
		return 0;
	}
}

// first line for compiler to set up the vector function correctly
// ISR gets called when timer completes on match
void __vector_14(void) __attribute__ ((signal, used, externally_visible));
void __vector_14(void)
{
    for(unsigned char i = 0 ; i < 2; i++)
    {
        //only increment if the values are not equal
        // with this count should never be higher than the limit
        if(count[i] != limit[i])
            count[i]++;
    }

}
