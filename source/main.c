#include "JumToApp.h"
#include "queue.h"

#define RAM_ADDRESS         		(0x20004000)
#define BOOT_ADDRESS_BASE   		(0x00000000)
#define QUEUE_SIZE             		(10)

/*------------------------------------------------------------*/
uint32_t QueueArr[QUEUE_SIZE]={0};
volatile uint8_t data=0;
volatile uint32_t dataQueue;
volatile uint32_t adrres_Sector10 = ADR_BASE_SECTOR_10;
volatile uint32_t adrres_Sector20 =ADR_BASE_SECTOR_20;

 /*----------------------------------------------------*/ 
/* =================GLOBAL=============================*/
Data_Receive_Types Data_Receive_GL ={
  0,0,0,0,0,0
};

Queue_Types Queue_Data={
  0,-1,QUEUE_SIZE,
  0,
  &QueueArr[0]
};

uint8_t Status_Flag_bt1;
uint8_t Status_Flag_bt2;
/*----------------------------------------------------*/
/* Function Prototypes */ 
void UART0_OutString(uint8_t *s, uint8_t len);
void CopyFlashFuncToRam(void);
void UART0_SetupReceiveINT();


/*==========================================================================================================*/
/*==========================================================================================================*/
/*=============================================   MAIN   ===================================================*/

void main()
{
    CopyFlashFuncToRam();   
    UART0_Init();
    UART0_SetupReceiveINT();    /*setup INT for UART receive*/ 
    Setup_EXT_INT_bt1();        /*setup INT for button sw1*/
    Setup_EXT_INT_bt2();        /*setup INT for button sw2*/
    __enable_irq();
    uint8_t t[] = "Bootloader-KL46";
    UART0_OutString(t, sizeof(t));
    while(1)
    {
      if(Status_Flag_bt1 == 1){
          Status_Flag_bt1 =0;
          Bootloader_Jump_App(ADR_BASE_SECTOR_10);
      }else if(Status_Flag_bt2 ==1){
          Bootloader_Jump_App(ADR_BASE_SECTOR_20);
      }
          if(!Queue_IsEmpty(&Queue_Data) && Data_Receive_GL.FLAG ==1){
              dataQueue = Queue_PeekData(&Queue_Data); 
              Queue_Pop(&Queue_Data);
              Flash_Program(adrres_Sector10,dataQueue);
              adrres_Sector10 +=0x04U;
        
              // check dieu kien queue va co FLAG de ghi den sector co dia chi 3e800
           }else if(!Queue_IsEmpty(&Queue_Data) && Data_Receive_GL.FLAG ==2){
              dataQueue = Queue_PeekData(&Queue_Data); 
              Queue_Pop(&Queue_Data);
              Flash_Program(adrres_Sector20,dataQueue);
              adrres_Sector20 +=0x04U;
            } 
      }
  }

/*==========================================================================================================*/
/*==========================================================================================================*/
/*==========================================================================================================*/


void CopyFlashFuncToRam(void)
{
   uint32_t size = 0x100, cntr;
   uint32_t *pDst = (uint32_t*)RAM_ADDRESS ;
   uint32_t *pSrc = (uint32_t*)BOOT_ADDRESS_BASE;
   for(cntr = 0; cntr < size; cntr++)
   {
      *pDst++ = *pSrc++; 
   }   
   SCB->VTOR = RAM_ADDRESS; 
}


void UART0_DriverIRQHandler()
{
    /* Application Code */
    if ( (UART0->S1 & (UART0_S1_RDRF_MASK)) == UART0_S1_RDRF_MASK)
    {
      /*get data , string to hex*/
        data =Char2Dec(UART0->D);
        if(data==19){
			Flash_Erase_nSector(ADR_BASE_SECTOR_10, 5);
        }else if(data==20)
        {
			Flash_Erase_nSector(ADR_BASE_SECTOR_20, 5);
        }else   
        {
          Data_Receive_GL.data_4bit=data;
           /*get data to UART add QUEUE*/
          Data_Receive(&Data_Receive_GL,&Queue_Data);
        }
    }
    
    /* Clear Pending Interrupt */
    NVIC_ClearPendingIRQ(UART0_IRQn);
}

void PORTC_PORTD_IRQHandler()
{
	PORTC->ISFR &=~ PORT_ISFR_ISF(3);
	NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);
	if((GPIOC->PDIR&(BUTTON_SW1_PIN))==0)
      {
        /* App binkLed */
        Status_Flag_bt1=1;
        Status_Flag_bt2=0;
  
      }else if((GPIOC->PDIR&(BUTTON_SW2_PIN))==0){
        /* App ADC */
        Status_Flag_bt1=0;
        Status_Flag_bt2=1;
      }
}



