#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "bit_utilies.h"

void GPIO_Init_PortE(void) {
    SET_BIT(SYSCTL_RCGCGPIO_R, 4);           // Enable clock for Port E
    while ((GET_BIT(SYSCTL_PRGPIO_R, 4)) == 0); // Wait until ready

    GPIO_PORTE_AMSEL_R &= ~0x02;             // Disable analog on PE1
    GPIO_PORTE_AFSEL_R |= 0x02;              // Enable alternate function on PE1
    GPIO_PORTE_PCTL_R &= ~0x000000F0;        // Clear PCTL for PE1
    GPIO_PORTE_PCTL_R |= 0x00000010;         // Set PE1 as U1RX
    GPIO_PORTE_DEN_R |= 0x02;                // Digital enable PE1
    GPIO_PORTE_DIR_R &= ~0x02;               // Set PE1 as input (U1RX)
}

void GPIO_Init_PortB(void) {
    SET_BIT(SYSCTL_RCGCGPIO_R, 1);          // Enable clock for Port B
    while ((GET_BIT(SYSCTL_PRGPIO_R, 1)) == 0); // Wait until ready

    GPIO_PORTB_AMSEL_R = 0x00;              // Disable analog
    GPIO_PORTB_DIR_R = 0xFF;                // Set all PB pins as output (if using 4-bit LCD)
    GPIO_PORTB_DEN_R = 0xFF;                // Digital enable all PB pins
}

