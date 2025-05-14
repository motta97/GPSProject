#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>  // ??? ?????? atof()
#include "tm4c123gh6pm.h"
#include "GPS.h"
#include "UART.h"
#include "GPIO.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

//#define SENTENCE_SIZE 100
//char LatGPS[15];
//char LongGPS[15];
double LatSaved;
double LongSaved;
//char speed[15];

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
//f64 stringToFloat(u8 *str);

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
    //int UART_GPS = 1;
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

    GPS1[0] = '$'; // ??? ???
    strcpy(&GPS1[1], GPS_logname + 1); // ??????
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

    if (strcmp(GPS_FORMATARR[2], "A") == 0) {  // Status = A
        // Latitude
        currentLat = custom_atof(GPS_FORMATARR[3]);
        if (GPS_FORMATARR[4][0] == 'S') {
            currentLat = -currentLat;
        }

        // Longitude
        currentLong = custom_atof(GPS_FORMATARR[5]);
        if (GPS_FORMATARR[6][0] == 'W') {
            currentLong = -currentLong;
        }
    }
}




//to calc the distance==> must be decimalDegree  


/***** SERVICES *****/
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

/*
static GPS_Status_t GPS_stdStatusReadNMEA_Sentence(uint8_t *Copy_arrU8Buffer) {
  uint8_t byte;
  uint8_t idx = 0;
  uint8_t start_found = 0;

  while (idx < (SENTENCE_SIZE - 1)) {
    if (UART_RX(&byte) != 0) return GPS_NO_DATA;

    if (byte == '$') {
      start_found = 1;
      idx = 0;
    }

    if (start_found) {
      Copy_arrU8Buffer[idx++] = byte;
      if (byte == '\n' || byte == '\r') {
        Copy_arrU8Buffer[idx] = '\0';
        return GPS_VALID_DATA;
      }
    }
  }





GPS_Status_t GPS_stdStatusWaitForValidData(f64 *lat, f64 *lon, uint16_t timeout) {
  uint16_t i;
  for (i = 0; i < timeout ; i++) {
    if (GPS_stdStatusGetLocation(lat, lon) == GPS_VALID_DATA) return GPS_VALID_DATA;
  }
  return GPS_NO_DATA;
}

uint8_t GPS_u8IsWithinRadius(f64 currentLat, f64 currentLong, f64 targetLat, f64 targetLong, f64 radiusMeters) {
  f64 distance = GPS_f64GetDistance_ArginDegrees(currentLat, currentLong, targetLat, targetLong);
  return (distance <= radiusMeters) ? 1 : 0;
}

f64 stringToFloat(u8 *str) {
	f64 result = 0.0;
	f64 decimalPlace = 0.1;
	u8 decimalFound = 0;
	while(*str) {
		if (*str == '.') {
			decimalFound = 1;
		}else if (*str >= '0' && *str <= '9') {
			if (!decimalFound) {
				result = (result * 10) + (*str - 0);
			} else {
				result += (*str - '0') * decimalPlace;
				decimalPlace *= 0.1;
			}
		}
		str++;
	}
	return result;
}*/










/*static GPS_Status_t GPS_stdStatusReadNMEA_Sentence(uint8_t *Copy_arrU8Buffer) {
  uint8_t byte;
  uint8_t idx = 0;
  uint8_t start_found = 0;

  while (idx < (SENTENCE_SIZE - 1)) {
    if (UART_stdErrorReceiveByte(&byte) != 0) return GPS_NO_DATA;

    if (byte == '$') {
      start_found = 1;
      idx = 0;
    }

    if (start_found) {
      Copy_arrU8Buffer[idx++] = byte;
      if (byte == '\n' || byte == '\r') {
        Copy_arrU8Buffer[idx] = '\0';
        return GPS_VALID_DATA;
      }
    }
  }*/