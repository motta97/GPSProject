#include <stdint.h>
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <math.h>
#include "GPS.h"
#include "UART.h"
#include "GPIO.h"
#include "LCD.h"
float locations_lat[5] = {
	30.0634605, 30.0653043, 30.0635504, 30.0640122, 30.0652914
};
float locations_long[5] = {
	31.2784228, 31.2783271, 31.2802217, 31.2800418, 31.2799843
};
char* names[5] = {
        "Credit", "FOUNTAIN", "HALL C ", "HALL A ", "Library"
    };



// ????????? ????????? ?? ????? ????
extern char GPS_FORMATARR[15][20];
extern char GPS1[80];
extern char GPS_logname[];

extern float currentLat, currentLong;

// ???? GPS
void GPS_READ(void);
void GPS_FORMAT(void);
float ToDegree(float angle);
float GPS_getDistance(float currentLong, float currentLat, float destLong, float destLat);
//////////
void UpdateLEDsBySpeedAndDistance(float speed, float distance) {
    // Clear all LEDs first
    GPIO_PORTF_DATA_R &= ~0x0E;  // Clear PF1 (Red), PF2 (Blue), PF3 (Green)
// replace inside while(1) block

GPIO_PORTF_DATA_R &= ~0x0E;  // Clear all LEDs

/*if (distance < 25) {
    GPIO_PORTF_DATA_R |= 0x08;  // Green (PF3)
} else if (distance < 50) {
    GPIO_PORTF_DATA_R |= 0x0A;  // Yellow = Red + Green (PF1 + PF3)
}  else {
    GPIO_PORTF_DATA_R |= 0x02;  // Red (PF1)
} */

if (distance < 25) {
    GPIO_SetLedValue(GPIO_GREEN_LED, GPIO_LED_ON);  // Green (PF3)
} else if (distance < 50) {
   GPIO_SetLedValue(GPIO_GREEN_LED, GPIO_LED_ON);  // Yellow = Red + Green (PF1 + PF3)
	 GPIO_SetLedValue(GPIO_RED_LED,GPIO_LED_ON) ;
}  else {
    GPIO_SetLedValue(GPIO_RED_LED,GPIO_LED_ON) ;  // Red (PF1)
}

}

// ???? ?????? float ??? UART
/*void UART_TX_Float(float number) { // 
    char buffer[20];
    sprintf(buffer, "%.6f", number);  // 6 ????? ?????
    UART1_OutString(buffer);
} */

void delayMs(int n) {
    volatile int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3180; j++) {}  // ~1 ms delay at 16 MHz
}

void UART0_OutFloat(float num) {
    char buffer[20];
    sprintf(buffer, "%.6f", num); // 6 decimal places
    UART0_OutString(buffer);
}
int main(void) {
    float min_distance = 10000000000000000;
    int i;
    float calculatedDistance;
    int min_index;
    
    UART0_init();     // UART0 for Tera Term
    UART1_Init();     // UART1 for GPS
    UART0_OutString("Starting GPS location test...\n");

    LCD_Init();  // Initialize the LCD to display the closest location

    while (1) {
        GPS_READ();         // Get a GPRMC sentence
        GPS_FORMAT();       // Parse the sentence
        
        // Calculate the closest location
        min_distance = 10000000000000000;
        for (i = 0; i < 5; i++) {
            float distance = GPS_getDistance(currentLong, currentLat, locations_long[i], locations_lat[i]);
            if (distance < min_distance) {
                min_distance = distance;
                min_index = i;
            }
        }

        // Send the closest location name to UART
        UART0_OutString("Closest is : ");
        UART0_OutString(names[min_index]);
        UART0_OutString("             ");

        // Now print the closest location on the LCD
        LCD_Cmd(0x01);                     // Clear screen
        SysTick_Wait10ms(2);               // Delay for clear

        LCD_Cmd(0x80);                     // Set cursor to line 1
        LCD_String_modified("Closest:");

        LCD_Cmd(0xC0);                     // Set cursor to line 2
        LCD_String_modified(names[min_index]);  // Display location name

        SysTick_Wait10ms(200);             // 2 second delay
    }
};
