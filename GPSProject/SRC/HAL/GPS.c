#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include "GPS.h"
#include "UART.h"
#include "GPIO.h"

#ifndef NULL
#define NULL ((void*)0)
#endif


double LatSaved;
double LongSaved;


float currentLong, currentLat, speed;
const float long_final = 0.0;  // replace with actual destination longitude
const float lat_final = 0.0;   // replace with actual destination latitude

char A;
char N_S;
char E_W;
char GPS1[80];
char GPS_logname[]="$GPRMC,";
char GPS_FORMATARR[15][20];
char *token;


float custom_atof(char *str) {
    float result = 0.0;         // will accumulate the final value
    float decimalPlace = 0.1;   // weight of the next digit after the decimal point
    char  decimalFound = 0;     // flag: have we seen the ‘.’ yet?

    // Walk each character until we hit the terminating NUL
    while (*str) {
        if (*str == '.') {
            // Once we hit the decimal point, flip the flag
            decimalFound = 1;
        }
        else if (*str >= '0' && *str <= '9') {
            // It’s a digit (ASCII ’0’ through ’9’)
            if (!decimalFound) {
                // — before the decimal point —
                // shift the old value left one decimal place, then add the new digit
                result = (result * 10.0) + (*str - '0');
            } else {
                // — after the decimal point —
                // add digit × current decimalPlace (first 0.1, then 0.01, 0.001, …)
                result += (*str - '0') * decimalPlace;
                decimalPlace *= 0.1;  // next digit is one more place to the right
            }
        }
        // skip any other character (commas, NMEA prefixes, etc.)
        str++;
    }

    return result;
}

void GPS_READ() {
    char recieved;
    char counter = 0;
    int i;
    char match = 0;

    while (1) {
        if (UART1_getChar() == '$') {
            match = 1;
            for (i = 1; i < 7; i++) {
                recieved = UART1_getChar();
                if (recieved != GPS_logname[i]) {
                    match = 0;
                    break;
                }
            }
            if (match) break;
        }
    }

    GPS1[0] = '$'; 
    strcpy(&GPS1[1], GPS_logname + 1); 
    counter = 7;

    do {
        recieved = UART1_getChar();
        GPS1[counter++] = recieved;
    } while (recieved != '*');

    GPS1[counter] = '\0';
}

void GPS_FORMAT() {
    char token_counter = 0;
    token = strtok(GPS1, ",");
    while (token != NULL) {
        strcpy(GPS_FORMATARR[token_counter], token);
        token = strtok(NULL, ",");
        token_counter++;
    }

    if (strcmp(GPS_FORMATARR[2], "A") == 0) {  
	    
        currentLat = custom_atof(GPS_FORMATARR[3]);
        if (GPS_FORMATARR[4][0] == 'S') {
            currentLat = -currentLat;
        }
	    
        currentLong = custom_atof(GPS_FORMATARR[5]);
        if (GPS_FORMATARR[6][0] == 'W') {
            currentLong = -currentLong;
        }
    }
}

float ToDegree(float angle) {
    int degree = (int)(angle / 100);
    float minutes = angle - (float)degree * 100;
    return (degree + (minutes / 60));
}
float ToRad(float angle) {
    return angle * PI / 180;
}

float GPS_getDistance(float currentLong, float currentLat, float destLong, float destLat) {
    float currentLongRad = ToRad(ToDegree(currentLong));
    float currentLatRad = ToRad(ToDegree(currentLat));
    float destLongRad = ToRad(destLong);
    float destLatRad = ToRad(destLat);

    float longDiff = destLongRad - currentLongRad;
    float latDiff = destLatRad - currentLatRad;

    float a = pow(sin(latDiff / 2), 2) +
              cos(currentLatRad) * cos(destLatRad) *
              pow(sin(longDiff / 2), 2);

    float c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return Earth_Radius * c;
}
