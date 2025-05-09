#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <string.h>
#include "UART.h"
#include "Bit_Utilies.h"

#define CB 0x2A								//HexaDecimal for (*)
void UART1_Init (void){// Should be called only once
	SET_BIT(SYSCTL_RCGCUART_R , 1); // Activate UART1
	SET_BIT(SYSCTL_RCGCGPIO_R,1); // Activate Port B 
	while(GET_BIT(SYSCTL_PRGPIO_R , 1)==0); //Check on the clock
	CLR_BIT(UART1_CTL_R , 0); // Disable UART1
	UART1_IBRD_R = 0x68; // IBRD=int (160000000/ (16*9600) ) = 104
	UART1_FBRD_R = 0xB; // FBRD = int (0.166 * 69 + 0.5)=11
	UART1_LCRH_R = 0x0070; // 8-bit word length, enable FIFO 001110000
	UART1_CTL_R = 0x0301; // Enable RE, IXE and UART 001100000001
	GPIO_PORTB_AFSEL_R |= 0x03; // Enable alt function PBO , PB1  
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF00) +0x00000011; // Configure UART on PB0 , PB1
	GPIO_PORTB_DEN_R |= 0x03; // Enable digital I/0 on PBO , PB1 
	GPIO_PORTB_AMSEL_R &= ~0x03; // Disable analog function on PBO , PB1
}

void UART1_OutChar(char data){
		while((UART1_FR_R & 0x20)!=0);  //check if transmitter is full or not
	UART1_DR_R=data;
}
char UART1_getChar() {
	while((UART1_FR_R & 0x10) !=0);   
return (char) UART1_DR_R;
}

void GetCommand_UART1(char *Command,int len ){ 
		
		char character_UART1;
		int p;		
		for(p=0 ; p< len; p++){
			character_UART1 = UART1_getChar();
			if(character_UART1!=CB)
			{
				Command[p]=character_UART1;
			}
			else if(character_UART1==CB)
				break;		
		}
}
void UART1_OutString(char *pt){
	while(*pt){
		UART1_OutChar(*pt);
		pt++;
	}
}
