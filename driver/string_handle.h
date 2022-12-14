#ifndef __STRING_HANDLE_H__
#define __STRING_HANDLE_H__

#include <stdint.h>

/* Implementation of itoa() */
uint8_t* itoa(uint32_t num, uint8_t* str, uint32_t base);
uint8_t Char2Dec(uint8_t chardata);

#endif	/* __STRING_HANDLE_H__ */
