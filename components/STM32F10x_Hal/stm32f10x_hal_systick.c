/**
 **************************************************************************************************
 * @file        stm32f10x_hal_systick.c
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
#include "stm32f10x_hal_systick.h"

#include "stm32f10x.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    stm32f10x_hal_systick_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_systick_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_systick_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_systick_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_systick_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_systick_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_systick_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_systick_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_systick_Functions 
 * @brief         
 * @{  
 */
void HAL_SYSTICK_Init(void)
{
    RCC_ClocksTypeDef  rcc_clocks;

    RCC_GetClocksFreq(&rcc_clocks);
	SysTick_Config(rcc_clocks.HCLK_Frequency/HAL_TICKS_PER_SEC);
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

