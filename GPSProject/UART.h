#ifndef UART
#define UART

void UART0_init(void);

char UART0_getChar();
void GetCommand(char *Command,int len );
void UART0_OutChar(char data);					//for testing
void UART0_OutString(char *pt);					//for testing

void UART1_Init (void);

void GetCommand_UART1(char *Command,int len );
char UART1_getChar();

#endif
