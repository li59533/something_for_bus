/**
 **************************************************************************************************
 * @file        gprs_port.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "gprs_port.h"
#include "stm32_bsp_conf.h"
#include "gprs_task.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    gprs_port_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_port_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_port_Macros_Defines 
 * @brief         
 * @{  
 */
#define GPRS_UART_DATA_LEN_MAX     200
/**
 * @}
 */

/**
 * @defgroup      gprs_port_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_port_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_port_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_port_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t g_Gprs_T_buf[GPRS_UART_DATA_LEN_MAX];
uint8_t g_Gprs_R_buf[GPRS_UART_DATA_LEN_MAX];


uint8_t test_gprs_dma[200];
/**
 * @}
 */

/**
 * @defgroup      gprs_port_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */
static void gprs_gpio_init(void);
static void gprs_uart_init(uint16_t baud);

/**
 * @defgroup      gprs_port_Functions 
 * @brief         
 * @{  
 */
void Gprs_Hal_Init(void)
{
    gprs_gpio_init();
    gprs_uart_init(9600);
}

static void gprs_uart_init(uint16_t baud)
{
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef  NVIC_InitStruct;
    DMA_InitTypeDef DMA_InitStructure;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);


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


    

    USART_StructInit(&USART_InitStruct);
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

void Gprs_DMA_IRQ(void)
{
   if( DMA_GetITStatus(DMA1_IT_TC4)!=RESET)
   {
        DMA_ClearITPendingBit(DMA1_IT_TC4);
        DMA_Cmd(DMA1_Channel4, DISABLE); 
        
        DMA1_Channel4->CMAR=(uint32_t)g_Gprs_T_buf;
        DMA1_Channel4->CNDTR=GPRS_UART_DATA_LEN_MAX;
   }
}

void Gprs_Uart_IDLE_IRQ(void)
{
    if( USART_GetITStatus(USART1, USART_IT_IDLE)!=RESET)
    {
        USART_ReceiveData( USART1);
        GprsTask_StartTask(GPRS_TASK_TEST2_EVENT);
    }
}

void Gprs_Task_uart_R_test(void)
{
    DMA_Cmd(DMA1_Channel5, DISABLE);
    memcpy(test_gprs_dma,g_Gprs_R_buf,GPRS_UART_DATA_LEN_MAX-DMA_GetCurrDataCounter(DMA1_Channel5));
    
    DMA_SetCurrDataCounter(DMA1_Channel5, GPRS_UART_DATA_LEN_MAX);
    DMA_Cmd(DMA1_Channel5, ENABLE);

}

static void gprs_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    //GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState)
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);   
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);   
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);  
    GPIO_SetBits(GPIOB, GPIO_Pin_0);                                 
}

void Gprs_Power_Pin_Set(void) 
{
    GPIO_SetBits(GPIOB, GPIO_Pin_0);      
}
void Gprs_Power_Pin_Rest(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);      
}


void Gprs_CMD_Send(uint8_t *gprs_cmd_buf, uint8_t gprs_cmd_len)
{
    memcpy(g_Gprs_T_buf,gprs_cmd_buf ,gprs_cmd_len );
    DMA_SetCurrDataCounter(DMA1_Channel4, gprs_cmd_len); 
    DMA_Cmd(DMA1_Channel4, ENABLE); 
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

