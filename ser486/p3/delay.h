/********************************************************
 * delay.h
 *
 * this file provides function declarations for SER486
 * timer-based delay library functions.
 *
 * Author:   Doug Sandy
 * Date:     3/1/2018
 * Revision: 1.0
 *
 * Copyright(C) 2018, Arizona State University
 * All rights reserved
 *
 */
#ifndef DELAY_H_INCLUDED
#define DELAY_H_INCLUDED

#ifdef __cplusplus
    extern "C" {
#endif

#define DELAY_MS(x) {unsigned long start = millis(); while (millis()!=start+x+1);}
#define DELAY_US(x) {volatile unsigned char i;for (i=0;i<8*x;i++);}

/* get the number of milliseconds since the program was started */
unsigned long millis(void);

/* get the current tick counter value for the specified instance */
unsigned delay_get(unsigned num);

/* set the counter limit and reset the count for the specified instance */
void     delay_set(unsigned int num, unsigned int msec);

/* return 1 if the specified instance of the counter has reached its
* limit, otherwise, return 0 */
unsigned delay_isdone(unsigned int num);

#ifdef __cplusplus
    }
#endif

#endif // DELAY_H_INCLUDED
