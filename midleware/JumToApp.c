#include "JumToApp.h"

void Bootloader_Jump_App(uint32_t jump_add)
{
  uint32_t temp_address = jump_add;
  /* disable interrup, FLag interrup,clear pending Interrup and disible sysTick*/
  __disable_irq();
  SysTick->CTRL = 0;
  SysTick->LOAD = 0;
  SysTick->VAL = 0;
  /*disable Hard Fault.*/
  SCB->SHCSR &= ~(SCB_SHCSR_SVCALLPENDED_Msk);
  
  uint32_t Application_Main_Stack_porter = 0;
  /* ----*/
  /* Initialize the user application Stack Pointe*/
  Application_Main_Stack_porter = *(volatile uint32_t *)(temp_address);
  __set_MSP(Application_Main_Stack_porter);

  __DMB();
  //
  SCB->VTOR = temp_address;
  __DSB();
  
  
  /*jump to app*/
  void (*resethandler)(void) = (void (*)(void))(*(volatile uint32_t *)(temp_address + 0x04U));
  resethandler();
}

/*=============================================================*/
