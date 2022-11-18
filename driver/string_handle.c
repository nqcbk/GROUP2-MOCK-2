#include "string_handle.h"

/*
 * Implementation of Char2Dec() - Convert character to Decimal
 * Intput = '0' to '9' and 'A' to 'F'
 * If Invalid input, program will be corrupted
 */
uint8_t Char2Dec(uint8_t chardata)
{
	uint8_t retVal;
	
	if ( (47 <chardata) && (chardata < 58) )
	{
		retVal = chardata - 48;
	}
	else if ( (64 < chardata) && (chardata < 71) )
	{
		retVal = chardata - 55;
	}
	else if(chardata==13 || chardata==10){
                retVal = 16;// xuong dong
        }else if(chardata==77)
        {
                retVal = 17; /*check char to app 1: char == MMMMM*/
        }else if(chardata==79)
        {
                retVal = 18; /*check char to app 2: char == OOOOO*/
        }else if(chardata==71){
                retVal = 19;    /* Erase  SECTOR_4): char = G*/
        }else if(chardata==72){
                retVal = 20;/* Erase  SECTOR_2: char = H*/
        }else
	{
		while(1);
	}
	
	return retVal;
}
