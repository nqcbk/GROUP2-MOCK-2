#include "UART0.h"

void UART0_Init()
{
    UART0_Clock48Mhz();
    UART0_PortInit();
    UART0_SetBaudrate();
    UART0_SetFrame();
    
    /* Enable Transmitter & Receiver */
    UART0->C2 |= UART0_C2_TE_MASK;
    UART0->C2 |= UART0_C2_RE_MASK;
}

void UART0_Clock48Mhz()
{
    /*Set UART0_Clock = MCGFLLCLK = 32768*640 = 20971520Hz*/
   /*set the slow internal reference clock: 32768kHz*/
    MCG->C1 |= MCG_C1_IREFS_MASK;

   /*set FLL*/
    MCG->C6 &= (~MCG_C6_PLLS_MASK);

   /*set FLL Factor = 640*/
    MCG->C4 &= (~MCG_C4_DMX32_MASK);
    MCG->C4 &= (~MCG_C4_DRST_DRS_MASK);

   /*set UART0_Clock = MCGFLLCLK*/
    SIM->SOPT2 &= (~SIM_SOPT2_PLLFLLSEL_MASK);
    SIM->SOPT2 = (SIM->SOPT2 & ~SIM_SOPT2_UART0SRC_MASK) | SIM_SOPT2_UART0SRC(1);  
    /* Enable clock for PORTA & UART0 */
    SIM->SCGC5 |= SIM_SCGC5_PORTA(1);
    SIM->SCGC4 |= SIM_SCGC4_UART0(1);
}

void UART0_SetBaudrate()
{
    /*set Baudrate = 20971520 / (26*7) = 115228*/
    /*set OSR + 1 = 7*/
    UART0->C4 = (UART0->C4 & (~UART0_C4_OSR_MASK)) | UART0_C4_OSR(6);

   /*set BR = 26*/
    UART0->BDH &= (~UART0_BDH_SBR_MASK);
    UART0->BDL = (UART0->BDL & (~UART0_BDL_SBR_MASK)) | UART0_BDL_SBR(26);
}

void UART0_PortInit()
{
  /* Clear PCR_MUX Register */
  PORTA->PCR[UART0_RX_PIN] &= ~PORT_PCR_MUX_MASK;
  PORTA->PCR[UART0_TX_PIN] &= ~PORT_PCR_MUX_MASK;
  
  /* Set Pin PA1 & PA2 = ALT2 Mode */
  PORTA->PCR[UART0_RX_PIN] |= PORT_PCR_MUX(2);     
  PORTA->PCR[UART0_TX_PIN] |= PORT_PCR_MUX(2);
  
  /* Set up Pull-up for UART Pin */
  PORTA->PCR[UART0_RX_PIN] |= PORT_PCR_PE(1) | PORT_PCR_PS(1);
  PORTA->PCR[UART0_TX_PIN] |= PORT_PCR_PE(1) | PORT_PCR_PS(1);
}

void UART0_SetFrame()
{
    /* Select number of Data Bits - 8 bits */
    UART0->C4 &= (~UART0_C4_M10_MASK);
    UART0->C1 &= (~UART0_C1_M_MASK);  
	
    /* Select Parity Bit - None */
    UART0->C1 &= (~UART0_C1_PE_MASK);  
	
    /*set mode LSB*/
    UART0->S2 &= (~UART0_S2_MSBF_MASK);
	
   /*set receive data not inverted*/
    UART0->S2 &= (~UART0_S2_RXINV_MASK);
	
   /*set transmit data not inverted*/
    UART0->C3 &= (~UART0_C3_TXINV_MASK);
}

void UART0_Transmit(uint8_t u8Data)
{
  /* Wait Data Register is Empty */
  while( (UART0->S1 & UART0_S1_TDRE_MASK) == 0 );
  
  /* Write to Data Register */
  UART0->D = u8Data;

 /*wait transmission activity complete*/
  while ((UART0->S1 & UART0_S1_TC_MASK) == 0);
}

void UART0_OutString(uint8_t *s, uint8_t len)
{
  uint8_t i = 0;
  for (i = 0; i < len; i++)
  {
    UART0_Transmit(s[i]);
  }
}

void UART0_SetupReceiveINT()
{
  /* Setup UART Interrupt */
  UART0->C2 |= UART0_C2_RIE(1);
  
  /* Enable UART Interrupt by NVIC */
  NVIC_EnableIRQ(UART0_IRQn);
}

