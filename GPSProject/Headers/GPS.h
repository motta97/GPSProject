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
  GPSnoData = 0,
  GPSinvalidData = 1,
  GPSvalidData = 2
} GPS_Status_t;


// GPS reading and formatting
void GPSread(void);
void GPSformat(void);

// Conversion 
float ToDegree(float angle);
float ToRad(float angle);

// Distance calculation
float GPS_getDistance(float currentLong, float currentLat, float destLong, float destLat);

#endif	






