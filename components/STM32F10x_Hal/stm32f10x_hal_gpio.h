/**
 **************************************************************************************************
 * @file        stm32f10x_hal_gpio.h
 * @author
 * @version
 * @date        12/5/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F10X_HAL_GPIO_H_
#define _STM32F10X_HAL_GPIO_H_

#include "stm32f10x.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f10x_hal_gpio_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_gpio_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_gpio_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_gpio_Exported_Types 
 * @{  
 */
typedef struct
{
    uint32_t            Clock;
    GPIO_TypeDef*       GPIOx;
    GPIO_InitTypeDef    Init;
}GPIO_ConfigTypedef;
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_gpio_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_gpio_Exported_Functions 
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
