#include "tm4c123gh6pm.h" // Register definitions for the microcontroller
#include <stdint.h>
#include <string.h>
#include "UART.h"
#include "Bit_Utilies.h"  // Macros like SET_BIT(), CLR_BIT(), GET_BIT()

#define CB 0x2A								// ASCII of '*' character, used as a command termination marker

void UART1_Init (void){// Should be called only once , Initializes UART1 for communication on PB0 (RX) and PB1 (TX)
	SET_BIT(SYSCTL_RCGCUART_R , 1); // Activate UART1(enable clock on UART1)
	SET_BIT(SYSCTL_RCGCGPIO_R,1); // Activate Port B (Enable clock on Port B)
	
	while(GET_BIT(SYSCTL_PRGPIO_R , 1)==0); //wait until ready 
	CLR_BIT(UART1_CTL_R , 0); // Disable UART1 before configuration 
	UART1_IBRD_R = 0x68; // IBRD=int (160000000/ (16*9600) ) = 104
	UART1_FBRD_R = 0xB; // FBRD = int (0.166 * 69 + 0.5)=11
	UART1_LCRH_R = 0x0070; // 8-bit word length,no parity,1 stop bit , enable FIFO 001110000
	UART1_CTL_R = 0x0301; // Enable RX, TX and UART 001100000001
	GPIO_PORTB_AFSEL_R |= 0x03; // Enable alternate  function PBO , PB1  
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF00) +0x00000011; // Configure UART on PB0 , PB1 
	GPIO_PORTB_DEN_R |= 0x03; // Enable digital I/0 on PBO , PB1 
	GPIO_PORTB_AMSEL_R &= ~0x03; // Disable analog function on PBO , PB1
}

void UART1_OutChar(char data){
		while((UART1_FR_R & 0x20)!=0);  //check if transmitter is full or not (Wait until TX FIFO is not full)
	UART1_DR_R=data; //send data
}
char UART1_getChar() {
	while((UART1_FR_R & 0x10) !=0);    // Wait until RX FIFO is not empty
return (char) UART1_DR_R;  // Return the received character
}

//This function reads a command string of up to len characters from UART1.
//It stops early if it sees the character * (used as an end-of-message marker).
void GetCommand_UART1(char *Command,int len ){ 
		
		char character_UART1;
		int p;		
		for(p=0 ; p< len; p++){
			character_UART1 = UART1_getChar(); // Receive a character
			if(character_UART1!=CB)   // If not '*'
			{
				Command[p]=character_UART1; // If '*', stop
			}
			else if(character_UART1==CB)
				break;		
		}
}

//Sends a null-terminated string over UART1
void UART1_OutString(char *pt){
	while(*pt){
		UART1_OutChar(*pt);
		pt++;
	}
}
void UART0_init(void) {
    SYSCTL_RCGCUART_R |= 0x0001;  // Activate UART0
    SYSCTL_RCGCGPIO_R |= 0x0001;  // Activate PortA
    while(GET_BIT(SYSCTL_PRGPIO_R, 0) == 0);  // Wait for GPIOA to be ready

    UART0_CTL_R &= ~(0x0001);  // Disable UART0
    UART0_IBRD_R = 0x68;  // Set baud rate (9600)
    UART0_FBRD_R = 0xB;   // Fine tuning for baud rate
    UART0_LCRH_R = 0x0070;  // 8-bit data, enable FIFO
    UART0_CTL_R = 0x0301;  // Enable RXE, TXE and UART

    GPIO_PORTA_AFSEL_R |= 0x03;  // Enable alt function PA0, PA1
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;  // Configure UART for PA0, PA1
    GPIO_PORTA_DEN_R |= 0x03;  // Enable digital I/O on PA0, PA1
    GPIO_PORTA_AMSEL_R &= ~0x03;  // Disable analog function on PA0, PA1
}

char UART0_getChar() {
    while((UART0_FR_R & 0x10) != 0);  // Wait until UART0 is ready to read
    return (char) UART0_DR_R;  // Return the character received
}

void UART0_OutChar(char data) {
    while((UART0_FR_R & 0x20) != 0);  // Wait until UART0 is ready to send data
    UART0_DR_R = data;  // Send the character
}

void UART0_OutString(char *pt) {
    while(*pt) {  // While there are characters in the string
        UART0_OutChar(*pt);  // Send each character one by one
        pt++;  // Move to the next character
    }
}
