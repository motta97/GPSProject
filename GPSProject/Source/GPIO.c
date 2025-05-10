#include "tm4c123gh6pm.h"
#include "Bit_Utilies.h"
//Port B is already intialized in UART1.c
//This code is for LCD only, if also intialized in LCD.c, please remove it, and let this be
void LCD_GPIO_Init(void) {
    // Enable clocks for Ports A, B, D, and E
    SYSCTL_RCGCGPIO_R |= (1<<0) | (1<<1) | (1<<3) | (1<<4); // A, B, D, E
    while ((SYSCTL_PRGPIO_R & ((1<<0)|(1<<1)|(1<<3)|(1<<4))) != ((1<<0)|(1<<1)|(1<<3)|(1<<4))); // Wait for ready

    // === PORT A === (PA5, PA6, PA7 → DB2–DB0)
    GPIO_PORTA_DIR_R |= (1<<5)|(1<<6)|(1<<7);
    GPIO_PORTA_DEN_R |= (1<<5)|(1<<6)|(1<<7);
    GPIO_PORTA_AFSEL_R &= ~((1<<5)|(1<<6)|(1<<7));
    GPIO_PORTA_AMSEL_R &= ~((1<<5)|(1<<6)|(1<<7));

    // === PORT B === (PB4 → DB3)
    GPIO_PORTB_DIR_R |= (1<<4);
    GPIO_PORTB_DEN_R |= (1<<4);
    GPIO_PORTB_AFSEL_R &= ~(1<<4);
    GPIO_PORTB_AMSEL_R &= ~(1<<4);

    // === PORT D === (PD0, PD1, PD2 → RS, RW, E | PD3 → DB7)
    GPIO_PORTD_DIR_R |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
    GPIO_PORTD_DEN_R |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
    GPIO_PORTD_AFSEL_R &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3));
    GPIO_PORTD_AMSEL_R &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3));

    // === PORT E === (PE1, PE4, PE5 → DB6, DB5, DB4)
    GPIO_PORTE_DIR_R |= (1<<1)|(1<<4)|(1<<5);
    GPIO_PORTE_DEN_R |= (1<<1)|(1<<4)|(1<<5);
    GPIO_PORTE_AFSEL_R &= ~((1<<1)|(1<<4)|(1<<5));
    GPIO_PORTE_AMSEL_R &= ~((1<<1)|(1<<4)|(1<<5));
}
