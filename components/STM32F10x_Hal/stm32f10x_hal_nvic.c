/**
 **************************************************************************************************
 * @file        stm32f10x_hal_nvic.c
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
#include "stm32f10x_hal_nvic.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    stm32f10x_hal_nvic_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_nvic_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_nvic_Functions 
 * @brief         
 * @{  
 */
void HAL_NVIC_Config(uint8_t IRQChannel,uint8_t PrePriority,uint8_t SubPriority,FunctionalState NewState)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(HAL_NVIC_PRIORITYGROUP_DEFAULT);
    NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PrePriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
    NVIC_Init(&NVIC_InitStructure);
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

