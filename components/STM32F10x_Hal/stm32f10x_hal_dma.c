/**
 **************************************************************************************************
 * @file        stm32f10x_hal_dma.c
 * @author
 * @version
 * @date        5/29/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stm32f10x.h"
#include "stm32f10x_hal_dma.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    stm32f10x_hal_dma_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_dma_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_dma_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_dma_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_dma_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_dma_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_dma_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_dma_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_dma_Functions 
 * @brief         
 * @{  
 */
DMA_InitTypeDef HAL_DMA_USART_StructInit(uint32_t periph_addr,uint32_t mem_addr,uint32_t buf_size,uint32_t dir,uint32_t mode)
{
    DMA_InitTypeDef DMA_InitStructure;
 
    DMA_InitStructure.DMA_PeripheralBaseAddr = periph_addr;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryBaseAddr = mem_addr;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_DIR = dir;
    DMA_InitStructure.DMA_BufferSize = buf_size;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_Mode = mode;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    return DMA_InitStructure;
}

DMA_InitTypeDef HAL_DMA_ADC_StructInit(uint32_t periph_addr,uint32_t mem_addr,uint32_t buf_size,uint32_t dir,uint32_t mode)
{
    DMA_InitTypeDef DMA_InitStructure;
 
    DMA_InitStructure.DMA_PeripheralBaseAddr = periph_addr;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryBaseAddr = mem_addr;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_DIR = dir;
    DMA_InitStructure.DMA_BufferSize = buf_size;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_Mode = mode;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    return DMA_InitStructure;
}

void HAL_DMA_USART_Init(DMA_Channel_TypeDef* DMAy_Channelx,DMA_InitTypeDef* DMA_InitStruct)
{
    if ((uint32_t)DMAy_Channelx <= (uint32_t)DMA1_Channel7)
    {
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 
    }
    else
    {
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);
    }
    DMA_Init(DMAy_Channelx,DMA_InitStruct);
}

void HAL_DMA_USART_Send(DMA_Channel_TypeDef* DMAy_Channelx,uint32_t DMAy_IT,uint32_t memAddr,uint32_t size)
{
    DMA_ClearITPendingBit(DMAy_IT);
    DMA_Cmd(DMAy_Channelx,DISABLE);
    DMAy_Channelx->CMAR = memAddr;
    DMAy_Channelx->CNDTR = size;
    DMA_Cmd(DMAy_Channelx,ENABLE);
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

