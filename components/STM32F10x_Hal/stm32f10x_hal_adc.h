/**
 **************************************************************************************************
 * @file        stm32f10x_hal_adc.h
 * @author
 * @version
 * @date        12/6/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F10X_HAL_ADC_H_
#define _STM32F10X_HAL_ADC_H_

#include "stm32f10x.h"
#include "stm32f10x_hal_tim.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f10x_hal_adc_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_adc_Exported_Macros 
 * @{  
 */
#define HAL_ADC_COUNT   2
#define HAL_ADC1        0
#define HAL_ADC2        1

#define HAL_ADC1_CHANNEL_COUNT  3
#define HAL_ADC2_CHANNEL_COUNT  0
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_adc_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_adc_Exported_Types 
 * @{  
 */
typedef enum
{
    ADC_DataManagement_DMA      = 0,
    ADC_DataManagement_Query    = 1,
}ADC_DataManagement_t;

typedef struct
{
    uint16_t *pBuf;
    uint8_t  Size;
}ADC_Buf_t;

typedef struct
{
    uint32_t                DMA_Clock;      /*!< DMA Clock. */
    DMA_Channel_TypeDef*    DMA_Channel;
    uint32_t                DMA_Mode;       /*!< Specifies the operation mode of the DMAy Streamx */
    uint8_t                 DMA_IRQChannel; /*!< Specifies the IRQ channel to be enabled or disabled. */
}ADC_DMAConfigTypedef;

typedef struct
{
    ADC_TypeDef             *Instance;      /*!< ADC Instance */
    uint8_t                 IRQn;
    uint32_t                ADC_Clock;      /*!< ADC Clock */
    ADC_InitTypeDef         Init;           /*!< ADC_InitTypeDef structure that contains the configuration 
                                                 information for the specified ADC peripheral */
    ADC_DataManagement_t    DataManagement; /*!< ADC DataManagement */
    uint8_t                 ExTrigger;
}ADC_BaseConfigTypedef;

typedef struct
{
    ADC_DMAConfigTypedef        DMA_Config;      /*!< ADC DMA Config */
    TIM_BaseConfigTypedef       TIM_Base;
    uint16_t                    TIM_TRGOSource;
    uint8_t                     TIM_OC_Channelx;
    TIM_OCChannelConfigTypedef  TIM_OC;
    uint32_t                    GPIO_Remap;
}ADC_ExConfigTypedef;

typedef struct
{
    ADC_TypeDef     *Instance;  /*!< ADC Instance */
    ADC_Buf_t       Buf;        /*!< ADC Buf */
}ADC_InstanceTypedef;
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_adc_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_adc_Exported_Functions 
 * @{  
 */
void HAL_ADC_Init(uint8_t HAL_ADCx);
void HAL_ADC_Open(uint8_t HAL_ADCx);
void HAL_ADC_GetValue_DMAISR(uint8_t HAL_ADCx,uint16_t *pBuf,ErrorStatus *status);
void HAL_ADC_GetValue_Query(uint8_t HAL_ADCx,uint16_t *pBuf,ErrorStatus *status);
void HAL_ADC_DMAITConfig(uint8_t HAL_ADCx,uint32_t DMA_IT,uint8_t PrePriority,uint8_t SubPriority,FunctionalState NewState);
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
