/********************************************************
 * util.h
 *
 * this file provides function declarations for various
 * utility functions for SER486.
 *
 * Author:   Doug Sandy
 * Date:     3/24/2018
 * Revision: 1.0
 *
 * Copyright(C) 2018, Arizona State University
 * All rights reserved
 *
 */

#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

/* update the configuration tcrit_hi limit with the specified value
* This function is called by the packet command parser.
*/
int update_tcrit_hi(int value);

/* Update the configuration twarn_hi limit with the specified value
* This function is called by the packet command parser.
*/
int update_twarn_hi(int value);

/* Update the configuration tcrit_lo limit with the specified value
* This function is called by the packet command parser.
*/
int update_tcrit_lo(int value);

/* Update the configuration twarn_lo limit with the specified value
* This function is called by the packet command parser.
*/
int update_twarn_lo(int value);


/* update the checksum (last byte) of the specifed data so
* that the sum of all the bytes will be zero
*/
void update_checksum(unsigned char *data, unsigned int dsize);

/* returns 1 if the sum of all the bytes in the data structure is 0.
* Otherwise, returns 0.
*/
int is_checksum_valid(unsigned char *data, unsigned int dsize);

/* dump the contents of the eeprom (instructor provided code) */
void dump_eeprom(unsigned int start_address, unsigned int numbytes);

/* parse the current packet and take actions based on the type of request */
void parse_and_send_response();

#endif // UTIL_H_INCLUDED
