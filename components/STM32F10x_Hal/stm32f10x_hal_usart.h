/**
 **************************************************************************************************
 * @file        stm32f10x_hal_usart.h
 * @author
 * @version
 * @date        5/29/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F10X_HAL_USART_H_
#define _STM32F10X_HAL_USART_H_

#include "stdint.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f10x_hal_usart_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_usart_Exported_Macros 
 * @{  
 */
#define HAL_USART_COUNT 5
#define HAL_USART1      0
#define HAL_USART2      1
#define HAL_USART3      2
#define HAL_USART4      3
#define HAL_USART5      4
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_usart_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_usart_Exported_Types 
 * @{  
 */
typedef enum
{
    USART_TransmissionMode_Query = 0,
    USART_TransmissionMode_IRQ = 1,
    USART_TransmissionMode_DMA = 2,
}USART_TransmissionMode;

typedef struct
{
    uint8_t *pBuf;
    uint16_t Size;
    uint16_t WritePtr;
    uint16_t ReadPtr;
}USART_Buf_t;

typedef struct
{
    USART_TypeDef          *Instance;
    uint8_t                 IRQn;
    uint32_t                USART_Clock;
    USART_InitTypeDef       Init;
    USART_TransmissionMode  TxTransmissionMode;
    USART_TransmissionMode  RxTransmissionMode;
}USART_BaseConfigTypedef;

typedef struct
{
    uint32_t                DMA_Clock;
    DMA_Channel_TypeDef*    DMA_Channel;
    uint32_t                DMA_Mode;
    uint8_t                 DMA_IRQChannel;
//    uint32_t                DMA_IT_Bit,/* DMAy Channelx's interrupt pending bits */
}USART_DMAConfigTypedef;

typedef struct
{
    USART_DMAConfigTypedef  TxDMAConfig;
    USART_DMAConfigTypedef  RxDMAConfig;
}USART_ExConfigTypedef;

typedef struct
{
    USART_TypeDef          *Instance;
    USART_Buf_t             TxBuf;
    USART_Buf_t             RxBuf;
}USART_InstanceTypedef;
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_usart_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_usart_Exported_Functions 
 * @{  
 */
void        HAL_USART_Init(uint8_t HAL_USARTx);
void        HAL_USART_Open(uint8_t HAL_USARTx);
void        HAL_USART_Close(uint8_t HAL_USARTx);

void        HAL_USART_SendBytesDMA(uint8_t HAL_USARTx,uint8_t *pBuf,uint16_t length);
void        HAL_USART_SendBytesDMAISR(uint8_t HAL_USARTx);

void        HAL_USART_SendBytesQuery(uint8_t HAL_USARTx,uint8_t* pBuf,uint16_t length);

void        HAL_USART_SendBytesInt(uint8_t HAL_USARTx,uint8_t* pBuf,uint16_t length);
void        HAL_USART_SendBytesIntISR(uint8_t HAL_USARTx);

uint16_t    HAL_USART_ReadBytesDMA(uint8_t HAL_USARTx,uint8_t* pBuf,uint16_t count);
uint16_t    HAL_USART_ReadBytesInt(uint8_t HAL_USARTx,uint8_t *pBuf,uint16_t count);
void        HAL_USART_ReadBytesIntISR(uint8_t HAL_USARTx,uint16_t data);

void        HAL_USART_ITConfig(uint8_t HAL_USARTx,uint16_t USART_IT,uint8_t PrePriority,uint8_t SubPriority,FunctionalState NewState);
void        HAL_USART_Tx_DMAITConfig(uint8_t HAL_USARTx,uint32_t DMA_IT,uint8_t PrePriority,uint8_t SubPriority,FunctionalState NewState);
void        HAL_USART_Rx_DMAITConfig(uint8_t HAL_USARTx,uint32_t DMA_IT,uint8_t PrePriority,uint8_t SubPriority,FunctionalState NewState);

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
