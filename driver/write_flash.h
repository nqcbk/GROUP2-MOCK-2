#ifndef _WRITE_FLASH_H_
#define _WRITE_FLASH_H_

#include "MKL46Z4.h"

/* Flash Program */
#define FTFA_CLEAR_ERROR                	(0x30UL)
#define CMD_PROGRAM_LONGWORD            	(0x06U)
#define START_COMMAND                    	(0x80)
#define CMD_PROGRAM_ERSSCR              	(0x09U)
#define SAMPLES_OF_SECTOR					(0x400)

/* Write Flash*/
void Flash_Program(uint32_t Address, uint32_t Data);

/* Erase Flash*/
void Erase_Program(uint32_t Address);

/* Erase n_Sector flash*/
void Flash_Erase_nSector(uint32_t Address, uint8_t count)

#endif /*_WRITE_FLASH_H_*/
