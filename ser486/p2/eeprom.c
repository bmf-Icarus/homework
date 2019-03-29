/*	Jaime Rabago Jr
 *	project2	ser486
 *	eeprom.c
 *
 *	hardware device design pattern meant to encapsulate reading from
 *	and writing to the electronically erasable programmable read only
 *	memory. reads are directly from the hardware while the writes are
 *	buffered for efficiency.
 */

#define EEAR (*(volatile char *)0x41)
#define EEDR (*(volatile char *)0x40)
#define EECR (*(volatile char *)0x3F)

#define SPMCSR (*(volatile char *)0x57)

#define BUFSIZE 64

unsigned char writebuf[BUFSIZE];
unsigned char bufidx;
unsigned char writesize;
unsigned int writeaddr;
volatile unsigned char write_busy;

void eeprom_writebuf(unsigned int addr, unsigned char * buf, unsigned char size)
{
    // _isbusy tells us if there is something being written
    while( eeprom_isbusy() )
    {
        ;// wait for write to complete
    }
    // this process has control of the eeprom write
    // save parameters and message
    writeaddr = addr;
    writesize = size;
    write_busy = 1;
    bufidx = 0;
    for (char n = 0; n < size; n++)
    {
        writebuf[n] = buf[n];
    }

    // first char write for simulator fix

    EEAR = writeaddr + bufidx;
    EEDR = writebuf[bufidx];
    EECR |= 0x04;
    EECR |= 0x02;
    bufidx++;
    // end simulator fix

    // enable eeprom ready interrupt
    EECR |= 0x8;
}

void eeprom_readbuf(unsigned int addr, unsigned char * buf, unsigned char size)
{
    // _isbusy tells us if there is something being written
    while( eeprom_isbusy() )
    {
        ;// wait for write to complete
    }

        for (char n = 0; n < size; n++)
        {

            EEAR = addr + n;
            EECR |= 0x01;
            buf[n] = EEDR;
        }
}

int eeprom_isbusy()
{
    //make sure there is no write in progress(EEPE bit)
    //do nothing while SPMEN bit is high(program writing)
    if(!write_busy | (EECR & 0x02) | (SPMCSR & 0x01))
    {
        return 1; //eeprom currently writing
    }

    return 0;
}

void __vector_22(void) __attribute__ ((signal, used, externally_visible));
void __vector_22(void)
{
    if(bufidx < writesize)
    {
        // write to the eeprom depending on the position of bufidx
        EEAR = writeaddr + bufidx;
        EEDR = writebuf[bufidx];
        EECR |= 0x04;
        EECR |= 0x02;
        bufidx++;

    }else if( bufidx >= writesize)
    {
        // enable eeprom ready interrupt
        EECR &= 0xF3;
        write_busy = 0;
    }
}
