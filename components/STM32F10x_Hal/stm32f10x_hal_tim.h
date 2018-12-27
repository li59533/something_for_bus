/**
 **************************************************************************************************
 * @file        stm32f10x_hal_tim.h
 * @author
 * @version
 * @date        12/6/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F10X_HAL_TIM_H_
#define _STM32F10X_HAL_TIM_H_

#include "stm32f10x_hal_gpio.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f10x_hal_tim_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_tim_Exported_Macros 
 * @{  
 */
#define HAL_TIM_COUNT   8   /*!< Define the number of ADC modules */
#define HAL_TIM1    0
#define HAL_TIM2    1
#define HAL_TIM3    2
#define HAL_TIM4    3
#define HAL_TIM5    4
#define HAL_TIM6    5
#define HAL_TIM7    6
#define HAL_TIM8    7

#define HAL_TIM_ACTIVE_CHANNEL_COUNT   4
#define HAL_TIM_ACTIVE_CHANNEL_1       0x01
#define HAL_TIM_ACTIVE_CHANNEL_2       0x02
#define HAL_TIM_ACTIVE_CHANNEL_3       0x04
#define HAL_TIM_ACTIVE_CHANNEL_4       0x08
#define HAL_TIM_ACTIVE_CHANNEL_CLEAR   0x00
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_tim_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_tim_Exported_Types 
 * @{  
 */
typedef struct
{
    TIM_TypeDef*            Instance;
    uint8_t                 TIM_IRQn;
    uint32_t                TIM_Clock;      /*!< TIM Clock */
    TIM_TimeBaseInitTypeDef BaseInit;       /*!< TIM Time Base Init Config */
}TIM_BaseConfigTypedef;

typedef struct
{
    uint8_t             State;
    TIM_OCInitTypeDef   OCInit;
    GPIO_ConfigTypedef  Port;
}TIM_OCChannelConfigTypedef;

typedef struct
{
    TIM_OCChannelConfigTypedef  OCConfig[HAL_TIM_ACTIVE_CHANNEL_COUNT];
    uint32_t GPIO_Remap;
}TIM_PWMOCConfigTypedef;

typedef struct
{
    uint8_t             State;
    TIM_ICInitTypeDef   ICInit;
    GPIO_ConfigTypedef  Port;
}TIM_ICChannelConfigTypedef;

typedef struct
{
    TIM_ICChannelConfigTypedef  ICConfig[HAL_TIM_ACTIVE_CHANNEL_COUNT];
    uint32_t GPIO_Remap;
    uint8_t PWMInputMode;
}TIM_ICConfigTypedef;

typedef struct
{
    TIM_TypeDef*    Instance;  /*!< where x can be 1 to 8 to select the TIMx peripheral */
}TIM_InstanceTypedef;
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_tim_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_tim_Exported_Functions 
 * @{  
 */

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
