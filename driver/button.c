#include "button.h"

void Setup_EXT_INT_bt1(void)
{
    SIM->SCGC5 |=  SIM_SCGC5_PORTC_MASK;// c3 botton
    /*setup PIN C3 = pullUp */
    PORTC->PCR[3] |= PORT_PCR_MUX(1);// set up button 
    
    PORTC->PCR[3] |= PORT_PCR_PE(1)|PORT_PCR_PS(1);//pullup cho button
    /*setup IRQC -> POrt-PCR-> Falling edge */
    PORTC->PCR[3] &=~PORT_PCR_IRQC_MASK; // clear
    PORTC->PCR[3] |= PORT_PCR_IRQC(10);// Interrupt on falling edge.
    
    /*setup NVIC*/
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);
  
}
void Setup_EXT_INT_bt2(void)
{
    SIM->SCGC5 |=  SIM_SCGC5_PORTC_MASK;// c3 botton
    /*setup PIN C12 = pullUp */
    PORTC->PCR[12] |= PORT_PCR_MUX(1);// set up button 
    
    PORTC->PCR[12] |= PORT_PCR_PE(1)|PORT_PCR_PS(1);//pullup cho button
    /*setup IRQC -> POrt-PCR-> Falling edge */
    PORTC->PCR[12] &=~PORT_PCR_IRQC_MASK; // clear
    PORTC->PCR[12] |= PORT_PCR_IRQC(10);// Interrupt on falling edge.
    
    /*setup NVIC*/
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);
  
}



