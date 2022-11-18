#ifndef _UART0_H_
#define _UART0_H_

#include "MKL46Z4.h"

#define UART0_RX_PIN    1
#define UART0_TX_PIN    2
#define BAUD_RATE       9600U

void UART0_Clock48Mhz();
void UART0_SetBaudrate();
void UART0_PortInit();

void UART0_SetFrame();
void UART0_Init();
void UART0_Transmit(uint8_t u8Data);
void UART0_OutString(uint8_t *s, uint8_t len);
void UART0_SetupReceiveINT();
void UART0_SetupReceiveINT();    /*setup INT for UART receive*/ 

#endif /*UART0_H*/


