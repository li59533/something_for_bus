/**
 **************************************************************************************************
 * @file        stm32f10x_hal_wdg.c
 * @author
 * @version
 * @date        12/6/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stm32f10x.h"
#include "stm32f10x_hal_wdg.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    stm32f10x_hal_wdg_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_wdg_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Private_Variables 
 * @brief         
 * @{  
 */
IWDG_BaseConfigTypedef IWDG_BaseConfig =
{
    IWDG_Prescaler_32,
    1000,
};
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_wdg_Functions 
 * @brief         
 * @{  
 */
void HAL_IWDG_Init(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_BaseConfig.Prescaler);
    IWDG_SetReload(IWDG_BaseConfig.Reload);
    IWDG_ReloadCounter();
}

void HAL_IWDG_Open(void)
{
    IWDG_Enable();
}

void HAL_IWDG_Feed(void)
{
    IWDG_ReloadCounter();
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

