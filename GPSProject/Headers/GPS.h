#ifndef GPS
#define GPS
#define PI 3.141592653589793238462643383279502884197
#define Earth_Radius 6378000
#define MAX_SENTENCE_SIZE 15
#define SENTENCE_SIZE 100
#include "STD_TYPES.h"
//#include "BIT_MATH.h"

// Define status values
typedef enum {
  GPS_NO_DATA = 0,
  GPS_INVALID_DATA = 1,
  GPS_VALID_DATA = 2
} GPS_Status_t;

//static GPS_status_t GPSStdStatusReadMEASentence(UART_Config_t *CopyPtrUARTConfig, u8 *Copyarru8Buffer);
// GPS reading and formatting
void GPS_READ(void);
void GPS_FORMAT(void);

// Conversion utilities
float ToDegree(float angle);
float ToRad(float angle);

// Distance calculation
float GPS_getDistance(float currentLong, float currentLat, float destLong, float destLat);

#endif	






