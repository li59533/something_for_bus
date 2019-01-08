/**
 **************************************************************************************************
 * @file        mc20_port.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "mc20_port.h"
#include "stm32_bsp_conf.h"
#include "mc20_queue.h"
#include "mc20_task.h"
#include "mc20_queue_process.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    mc20_port_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_port_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_port_Macros_Defines 
 * @brief         
 * @{  
 */
#define GPRS_UART_DATA_LEN_MAX     400
/**
 * @}
 */

/**
 * @defgroup      mc20_port_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_port_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_port_Private_Variables 
 * @brief         
 * @{  
 */
uint8_t g_Gprs_T_buf[GPRS_UART_DATA_LEN_MAX];
uint8_t g_Gprs_R_buf[GPRS_UART_DATA_LEN_MAX];
/**
 * @}
 */

/**
 * @defgroup      mc20_port_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_port_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void mc20_uart_init(uint32_t band,uint8_t uartnum);
static void mc20_power_pin_hal_init(void);
/**
 * @}
 */

/**
 * @defgroup      mc20_port_Functions 
 * @brief         
 * @{  
 */
void MC20_Hal_Init(void)
{
    mc20_uart_init(9600,1);
    mc20_power_pin_hal_init();
}

static void mc20_uart_init(uint32_t band,uint8_t uartnum)
{
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef  NVIC_InitStruct;
    DMA_InitTypeDef DMA_InitStructure;
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);   
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);   

    DMA_DeInit(DMA1_Channel4); 
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)g_Gprs_T_buf;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = GPRS_UART_DATA_LEN_MAX;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);


    //DMA_DeInit(DMA1_Channel5);  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)g_Gprs_R_buf;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = GPRS_UART_DATA_LEN_MAX;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    DMA_Init(DMA1_Channel5, &DMA_InitStructure);

    NVIC_InitStruct.NVIC_IRQChannel=DMA1_Channel4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_Init(&NVIC_InitStruct);  
    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);


    

    //USART_StructInit(&USART_InitStruct);
    USART_InitStruct.USART_BaudRate = band ;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No ;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
    USART_Init( USART1, &USART_InitStruct);   
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_Init(&NVIC_InitStruct); 
    USART_ITConfig( USART1, USART_IT_IDLE, ENABLE);

    USART_DMACmd( USART1,USART_DMAReq_Tx|USART_DMAReq_Rx, ENABLE);
    DMA_Cmd(DMA1_Channel5, DISABLE);         //R
    DMA_Cmd(DMA1_Channel4, DISABLE);         //T
    USART_Cmd( USART1, ENABLE);
	DMA_Cmd(DMA1_Channel5, ENABLE); 
}

static void mc20_power_pin_hal_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);  
    GPIO_SetBits(GPIOB, GPIO_Pin_0);  
}

void MC20_DMA_IRQ(void)
{
   if( DMA_GetITStatus(DMA1_IT_TC4)!=RESET)
   {
        DMA_ClearITPendingBit(DMA1_IT_TC4);
        DMA_Cmd(DMA1_Channel4, DISABLE); 
        
        DMA1_Channel4->CMAR=(uint32_t)g_Gprs_T_buf;
        DMA1_Channel4->CNDTR=GPRS_UART_DATA_LEN_MAX;
   }
}

void MC20_Uart_IDLE_IRQ(void)
{
    if( USART_GetITStatus(USART1, USART_IT_IDLE)!=RESET)
    {
        USART_ReceiveData(USART1);
        DMA_Cmd(DMA1_Channel5, DISABLE); 
        MC20_Rev_Queue_Process(g_Gprs_R_buf,GPRS_UART_DATA_LEN_MAX - DMA_GetCurrDataCounter(DMA1_Channel5));
        DMA_SetCurrDataCounter(DMA1_Channel5, GPRS_UART_DATA_LEN_MAX); 
        DMA_Cmd(DMA1_Channel5, ENABLE); 
    }
}

void MC20_Power_Pin_Set(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_0);      
}

void MC20_Power_Pin_Rest(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
}

void MC20_CMD_Send(const char  * cmd_buf,uint8_t cmd_len)
{
    memcpy(g_Gprs_T_buf,cmd_buf ,cmd_len );
    DMA_SetCurrDataCounter(DMA1_Channel4, cmd_len); 
    DMA_Cmd(DMA1_Channel4, ENABLE); 
}

void MC20_Data_Send(uint8_t * data_buf,uint16_t data_len)
{
    
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

