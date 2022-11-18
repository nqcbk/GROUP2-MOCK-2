#ifndef _JUMTOAAP_H_
#define _JUMTOAPP_H_


#include "MKL46Z4.h"
#include "queue.h"
#include "string_handle.h"
#include "write_flash.h"
#include "UART0.h"
#include "button.h"


//0x0003E800UL   0x00003B00UL
#define ADR_BASE_SECTOR_10                       (uint32_t)(0x0003E800UL )
#define ADR_BASE_SECTOR_20                      (uint32_t)(0x00003B000UL)
void Bootloader_Jump_App(uint32_t jump_add);


#endif /*_JUMTOAPP_H_*/