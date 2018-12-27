/**
 **************************************************************************************************
 * @file        stm32f10x_hal_dma.h
 * @author
 * @version
 * @date        5/29/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F10X_HAL_DMA_H_
#define _STM32F10X_HAL_DMA_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f10x_hal_dma_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_dma_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_dma_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_dma_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_dma_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_dma_Exported_Functions 
 * @{  
 */
DMA_InitTypeDef HAL_DMA_USART_StructInit(uint32_t periph_addr,uint32_t mem_addr,uint32_t buf_size,uint32_t dir,uint32_t mode);
DMA_InitTypeDef HAL_DMA_ADC_StructInit(uint32_t periph_addr,uint32_t mem_addr,uint32_t buf_size,uint32_t dir,uint32_t mode);
void HAL_DMA_USART_Init(DMA_Channel_TypeDef* DMAy_Channelx,DMA_InitTypeDef* DMA_InitStruct);
void HAL_DMA_USART_Send(DMA_Channel_TypeDef* DMAy_Channelx,uint32_t DMAy_IT,uint32_t memAddr,uint32_t size);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif
