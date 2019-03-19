/*	Jaime Rabago
 *	project1	SER486
 *	led.c
 *
 *  the delay class utilizes the led light to display error codes and
 *  preform non blocking operation of led Morse code messages
 */


#include "led.h"
#include "delay.h"

#define PORTB (*(volatile char *)0x25)
#define DDRB (*(volatile char *)0x24)

char* blink_msg;
unsigned int blink_pos;
unsigned char blink_state;


// takes in message pointer to iterate over with the FSM
void led_set_blink(char* msg)
{
        // save the address of the message
        blink_msg = msg;
        // reset position and blink state
        blink_pos = 0;
	// default state going in with delay done
        delay_set(0,0);
	// entry state
        blink_state = 1;
        led_off();
        // blink has been reset with new message
}

// FSM realized, depending on the current state and the values of the next char
// determines the FSM action. this is a non blocking led morse code 
// error algorithm
void led_update(void)
{
	// only change states when delays are finished
    if(delay_isdone(0))
    {
	    // blink state describes phase, phase 1 is the start for each char
        switch(blink_state)
        {
            case 1:
                switch(blink_msg[blink_pos])
                {
                    case ' ':
                        // set proper delay and next phase
                        // in this case we stay in phase 1
                        delay_set(0,1000);
                        led_off();
                        // if the next char is not null advance blink position
                        // but if it is null then reset the blink position
                        blink_pos = (blink_msg[blink_pos+1]) ? blink_pos+1 : 0 ;
                        break;
                    case '-':
                        delay_set(0,750);
                        led_on();
                        // once the delay is done must go to phase 2
                        blink_state = 2;
                        break;
                    case '.':
                        delay_set(0,250);
                        led_on();
                        // once the delay is done must go to phase 2
                        blink_state = 2;
                        break;
                    default:
                        // while the char is not in Morse code ignore
                        delay_set(0,0);
                        led_off();
                        // if the next char is not null advance blink position
                        // but if it is null then reset the blink position
                        blink_pos = (blink_msg[blink_pos+1]) ? blink_pos+1 : 0 ;
                        break;
                }
                break;
            case 2:
                // set delay to give small break between Morse code char
                delay_set(0,100);
                led_off();
                blink_state = 1;
                // fancy statement if the next char is anything but null
                // advance the message and if it is null then reset the message
                blink_pos = (blink_msg[blink_pos+1]) ? blink_pos+1 : 0 ;
                break;

        }
    }
}
