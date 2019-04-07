/********************************************************
 * vpd.h
 *
 * this file provides declarations for SER486
 * vpd class library functions.
 *
 * Author:   Doug Sandy
 * Date:     4/5/2018
 * Revision: 1.0
 *
 * Copyright(C) 2018, Arizona State University
 * All rights reserved
 *
 */
 #ifndef VPD_H_INCLUDED
#define VPD_H_INCLUDED
    typedef struct {
        char token[4];
        char model[12];
        char manufacturer[12];
        char serial_number[12];
        unsigned long manufacture_date;
        unsigned char mac_address[6];
        char country_of_origin[4];
        unsigned char checksum;
    } vpd_struct;

    /* "public member functions and data" */
    vpd_struct vpd;
    void vpd_init();

    /* debug code */
    void vpd_dump();

    /* private member functions and data
    int vpd_is_data_valid()
    void vpd_update_checksum(char*data)
    */

#endif // VPD_H_INCLUDED
