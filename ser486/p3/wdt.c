/*	Jaime Rabago Jr
 *	wdt.c	SER486
 *
 *	hardware device pattern to encapsulate a special timer to
 *	keep track of running processes and ensure no process runs
 *	for too long. Once triggered WDT will set off an ISR to
 *	possibly save logs or other vital data.
 */

#define MCUSR (*(volatile char *)0x54)
#define WDTCSR (*(volatile char *)0x60)
#define SREG (*(volatile char *)0x5F)

void wdt_init()
{
    // store sreg state and disable interrupts
    char temp = SREG;
    SREG &= 0x7F;
    // for changing wd registers bit 3 must be set first
    WDTCSR = 0x14;
    // bit 6 WDIE, WDE, and WDP(pre-scaler ~2s)
    WDTCSR = 0x4F;
    // ensure that SREG state is restored
    SREG = temp;
}

void wdt_reset()
{
    //assembly language reset watchdog timer
    asm("WDR");

}

void wdt_force_restart()
{
    // set forge restart
    __vector_6();
}

void __vector_6(void) __attribute__ ((signal, used, externally_visible));
void __vector_6(void)
{
    //send out messages to log for info logging


    while(true){} // busy waiting loop
}
