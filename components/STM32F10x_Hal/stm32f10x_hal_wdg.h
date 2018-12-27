/**
 **************************************************************************************************
 * @file        stm32f10x_hal_wdg.h
 * @author
 * @version
 * @date        12/6/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F10X_HAL_WDG_H_
#define _STM32F10X_HAL_WDG_H_

#include "stm32f10x.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f10x_hal_wdg_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Exported_Types 
 * @{  
 */
typedef struct
{
    uint8_t     Prescaler;
    uint16_t    Reload;
}IWDG_BaseConfigTypedef;
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Exported_Functions 
 * @{  
 */
void HAL_IWDG_Init(void);
void HAL_IWDG_Open(void);
void HAL_IWDG_Feed(void);
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
