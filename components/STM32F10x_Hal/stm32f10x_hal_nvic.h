/**
 **************************************************************************************************
 * @file        stm32f10x_hal_nvic.h
 * @author
 * @version
 * @date        5/29/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F10X_HAL_NVIC_H_
#define _STM32F10X_HAL_NVIC_H_

#include "stm32f10x.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f10x_hal_nvic_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Exported_Macros 
 * @{  
 */
#define HAL_NVIC_PRIORITYGROUP_DEFAULT  NVIC_PriorityGroup_2
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Exported_Functions 
 * @{  
 */

void HAL_NVIC_Config(uint8_t IRQChannel,uint8_t PrePriority,uint8_t SubPriority,FunctionalState NewState);
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
