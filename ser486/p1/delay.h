/********************************************************
 * delay.h
 *
 * this file provides function declarations for SER486
 * delay library functions.
 *
 * Author:   Doug Sandy
 * Date:     2/16/2018
 * Revision: 1.0
 *
 * Copyright(C) 2018, Arizona State University
 * All rights reserved
 *
 */
#ifndef DELAY_H_INCLUDED
#define DELAY_H_INCLUDED

void delay(unsigned int msec);  /* delay for the specified amount of milliseconds */
unsigned int delay_get(unsigned int num);
void delay_set(unsigned int num, unsigned int time);
unsigned int delay_isdone(unsigned int num);


#endif // DELAY_H_INCLUDED
