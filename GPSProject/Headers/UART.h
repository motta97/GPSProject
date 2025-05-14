#ifndef UART
#define UART

void UART0_init(void); // initialize UART0 , used with PC

char UART0_getChar(); // reads one character from input 

void GetCommand(char *Command,int len ); //read full string length from UART0

void UART0_OutChar(char data);					//Sends a single character via UART0.
//Useful for debugging or displaying text to a PC.

void UART0_OutString(char *pt);					//for testing,Sends a null-terminated string over UART0

void UART1_Init (void); //intialize UART1 , used with GPS

void GetCommand_UART1(char *Command,int len ); //recieve string from UART1

char UART1_getChar(); //read single character from UART1

#endif
