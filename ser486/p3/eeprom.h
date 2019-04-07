/********************************************************
 * eeprom.h
 *
 * this file provides declarations for SER486
 * eeprom class library functions.
 *
 * Author:   Doug Sandy
 * Date:     4/5/2018
 * Revision: 1.0
 *
 * Copyright(C) 2018, Arizona State University
 * All rights reserved
 *
 */
#ifndef EEPROM_H_INCLUDED
#define EEPROM_H_INCLUDED

void eeprom_writechar(unsigned int addr, unsigned char data);
void eeprom_writebuf(unsigned int addr, unsigned char *buf, unsigned char size);
void eeprom_writebuf_noisr(unsigned int addr, unsigned char *buf, unsigned char size);
unsigned char eeprom_readchar(unsigned int addr);
void eeprom_readbuf(unsigned int addr, unsigned char *buf, unsigned char size);
int eeprom_isbusy();
#endif // EEPROM_H_INCLUDED
