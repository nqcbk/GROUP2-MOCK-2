#include "queue.h"



#define QUEUE_EMPTY                 (0U)
#define QUEUE_EMPTY_PEEK_VALUE        (0U)
/* Check Empty Of Queue */
Bool Queue_IsEmpty(Queue_Types *Queue)
{
    Bool isEmpty;
    if (Queue->Capacity == 0)
    {
        isEmpty = e_TRUE;
    }
    else
    {
        isEmpty = e_FALSE;
    }

    return isEmpty;
}

/* Check Full Of Queue */
Bool Queue_IsFull(Queue_Types *Queue)
{
    Bool isFull;
    if ((Queue->Size) == (Queue->Capacity))
    {
        isFull = e_TRUE;
    } 
    else
    {
        isFull = e_FALSE;
    }
    return isFull;                                                                                                                                                                                                                                                                                                                                      
}

/* Hadling push data in queue */
/////////////////////////////////////////////////////////////////////////////////////////
void Queue_PushData(Queue_Types *Queue, uint32_t InputData)
{
	if(!Queue_IsFull(Queue)){
		Queue->QueueArr[Queue->Rear+1]=InputData;
		Queue->Rear++;
		Queue->Capacity++;
		
	}
 }

/* Handling peek data in queue */
uint32_t Queue_PeekData(Queue_Types *Queue){
	uint32_t PeekData = QUEUE_EMPTY_PEEK_VALUE;
	if(!Queue_IsEmpty(Queue)){
		PeekData = Queue->QueueArr[Queue->Front];
		Queue->Front++;
		Queue->Capacity--;
	}
	return PeekData;
	
}
/* Pop data from queue */
void Queue_Pop(Queue_Types *Queue){
	uint8_t count;
	if((Queue->Front)<=(Queue->Rear)){
		// 
		for(count =Queue->Front;count<=Queue->Rear; count++){
			Queue->QueueArr[count-Queue->Front] = Queue->QueueArr[count];
		}
		///
		Queue->Front = 0;
		Queue->Rear = Queue->Capacity-1;
		
		////
		for(count = Queue->Capacity;count<=Queue->Size; count++){
			Queue->QueueArr[count]=0;
		}
	}else if((Queue->Front)>(Queue->Rear)){
                Queue->Front = 0;
		Queue->Rear = Queue->Capacity-1;
        }
}
////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
void Data_Receive(Data_Receive_Types* Data_Receive,Queue_Types *Queue){
  /*check data recevive to UART*/ 
  if((Data_Receive->data_4bit)==16){                     /*data Exception*/
    __asm("nop");                                         /*skip*/  
  }else if((Data_Receive->data_4bit)==17){
      Data_Receive->FLAG=1; // App1--- check ki tu M da sua lai ham char2dex, dung co len thoi
  }else if((Data_Receive->data_4bit)==18){
      Data_Receive->FLAG=2; //App2---check ki tu O da sua lai ham char2dex, dung co len
  }else{
      if(Data_Receive->Count_4bit==0){
          Data_Receive->data_byte =(Data_Receive->data_4bit << 4);
          Data_Receive->Count_4bit++;
      }else if(Data_Receive->Count_4bit==1){
          Data_Receive->data_byte |= Data_Receive->data_4bit;
          Data_Receive->Count_4bit=0;
          
          if(Data_Receive->Count_byte==0){
              Data_Receive->data_4Byte |= Data_Receive->data_byte << 24;                /* qua trinh gop 8 ki tu*/
              Data_Receive->Count_byte++;
          }else if(Data_Receive->Count_byte==1){
              Data_Receive->data_4Byte |= Data_Receive->data_byte << 16;
              Data_Receive->Count_byte++;
          }else if(Data_Receive->Count_byte==2){
              Data_Receive->data_4Byte |= Data_Receive->data_byte << 8;
              Data_Receive->Count_byte++;
          }else {
              Data_Receive->data_4Byte |= Data_Receive->data_byte << 0;
              Queue_PushData(Queue, Data_Receive->data_4Byte);
              Data_Receive->data_4Byte=0;
              Data_Receive->Count_byte=0;   
          }
       }
    
  }
}
////////////////////////////////////////////////////////////////////////////////////



