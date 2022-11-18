#ifndef __QUEUE_H__
#define __QUEUE_H__


#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string_handle.h"

/*** Define Queue Types ***/
typedef struct {
    int8_t Front, Rear, Size;
    uint8_t    Capacity;
    uint32_t * QueueArr;
} Queue_Types;

typedef enum Bool
{
	e_FALSE = 0U,
	e_TRUE = 1U
} Bool;


/*struct got data from file*/
typedef struct {
   uint8_t Count_4bit;
   uint8_t Count_byte;
   uint8_t data_4bit;
   uint8_t data_byte;
   uint32_t data_4Byte;
   uint8_t FLAG;
    
} Data_Receive_Types;

/*******************************************************************************
* API
******************************************************************************/


void Data_Receive();
/* Check Empty Of Queue */
Bool Queue_IsEmpty(Queue_Types *Queue);

/* Check full of Queue */
Bool Queue_IsFull(Queue_Types *Queue);
    
/* Pop Data From Queue */
void Queue_Pop(Queue_Types *Queue);

/* Hadling Push Data In Queue */
void Queue_PushData(Queue_Types *Queue, uint32_t InputData);

/* Super Data Push Function */
Bool Queue_ForcePushData(Queue_Types *Queue, uint32_t InputData);

/* Handling Peek Data In Queue */
uint32_t Queue_PeekData(Queue_Types *Queue);

/* Display Queue Data*/
void Queue_Display(Queue_Types *Queue);

#endif /* __QUEUE_H__ */
