#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "MKL46Z4.h"

#define GREEN_LED_PIN       (1 << 5)
#define RED_LED_PIN       (1 << 29)
#define BUTTON_SW1_PIN               (1<<3)
#define BUTTON_SW2_PIN               (1<<12)
/* buutton-PTC3-external interrup*/
/*Click button*/

 void   Setup_EXT_INT_bt1();        /*setup INT for button sw1*/
 void   Setup_EXT_INT_bt2();        /*setup INT for button sw2*/

#endif /*UART0_H*/


