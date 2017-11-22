/*
    gps.h

    Copyright (c) IMS Electronics Co., Ltd 2014-2016. All Rights Reserved.
    This software is distributed under commercial and open source licenses.
    You may use the Embedthis Open Source license or you may acquire a 
    commercial license from Embedthis Software. You agree to be fully bound
    by the terms of either license. Consult the LICENSE.md distributed with
    this software for full details and other copyrights.
    
    Author : siseong@gmail.com
 */
 
#ifndef _GPS_H_
#define _GPS_H_

struct location {
    double latitude;
    double longitude;
    double speed;
    double altitude;
    double course;
    char buffer[256];
};
typedef struct location loc_t;

// Initialize device
extern void gps_init(void);
// Activate device
extern void gps_on(void);
// Get the actual location
extern void gps_location(loc_t *);


// Turn off device (low-power consumption)
extern void gps_off(void);

// -------------------------------------------------------------------------
// Internal functions
// -------------------------------------------------------------------------

// convert deg to decimal deg latitude, (N/S), longitude, (W/E)
void gps_convert_deg_to_dec(double *, char, double *, char);
double gps_deg_dec(double);

#endif
