#include "write_flash.h"

/* Write flash with 4 byte-*/
void Flash_Program(uint32_t Address, uint32_t Data){
  /* wait previous command complate*/
  while ((FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK) == 0 );
  
  /*Check Error from previous command*/
  if((FTFA->FSTAT & FTFA_FSTAT_ACCERR_MASK)==FTFA_FSTAT_ACCERR_MASK 
     || (FTFA->FSTAT & FTFA_FSTAT_FPVIOL_MASK)==FTFA_FSTAT_FPVIOL_MASK)
  {
        FTFA->FSTAT = FTFA_CLEAR_ERROR ;
  }
  /*write command and parameter to FCCOB */
  FTFA->FCCOB0 = CMD_PROGRAM_LONGWORD;
  /*set address*/
  FTFA->FCCOB1 = (uint8_t) (Address >>16);
  FTFA->FCCOB2 = (uint8_t) (Address >>8);
  FTFA->FCCOB3 = (uint8_t) (Address);
  
  /*set data*/
  FTFA->FCCOB4 = (uint8_t) (Data);
  FTFA->FCCOB5 = (uint8_t) (Data >>8);
  FTFA->FCCOB6 = (uint8_t) (Data >>16);
  FTFA->FCCOB7 = (uint8_t) (Data >>24);
  /*clear CCIF Flag to launch command */
  FTFA->FSTAT = START_COMMAND;
}

void Erase_Program(uint32_t Address)
{
   /* wait previous command complate*/
  while ((FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK) == 0 );
  /*write command and parameter to FCCOB0*/
  FTFA->FCCOB0 = CMD_PROGRAM_ERSSCR ;
  /*set address*/
  FTFA->FCCOB1 = (uint8_t) (Address >>16);
  FTFA->FCCOB2 = (uint8_t) (Address >>8);
  FTFA->FCCOB3 = (uint8_t) (Address);
  
  //clear Clear CCIF;
  FTFA->FSTAT = START_COMMAND   ;
  
}

/* Erase n_Sector flash*/
void Flash_Erase_nSector(uint32_t Address, uint8_t count)
{
  uint8_t i = 0;
  uint32_t temp_add = Address;
  for (i = 0; i < count; i++)
  {
    Erase_Program(temp_add);
    temp_add += SAMPLES_OF_SECTOR;
  }
}





