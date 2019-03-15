/********************************************************
 * led.h
 *
 * this file provides function declarations for SER486
 * led library functions.
 *
 * Author:   Doug Sandy
 * Date:     2/16/2018
 * Revision: 1.0
 *
 * Copyright(C) 2018, Arizona State University
 * All rights reserved
 *
 */
#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

void led_init();        /* initialize the LED device */
void led_on();          /* turn on the LED */
void led_off();         /* turn off the LED */
int  led_ison();        /* returns 1 if the LED is on, otherwise, 0 */
void led_blink(char *); /* output a Morse code message to the LED */

void led_set_blink(char* msg);  // sets the FSM message to display in Morse code for humans
void led_update(void);          // updates the led FSM

#endif // LED_H_INCLUDED
