/**
 **************************************************************************************************
 * @file        gprs_module_power.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "gprs_module_power.h"
#include "stm32_bsp_conf.h"
#include "gprs_port.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    gprs_module_power_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_module_power_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_module_power_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_module_power_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_module_power_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_module_power_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_module_power_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_module_power_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_module_power_Functions 
 * @brief         
 * @{  
 */
void Gprs_Power_Pin_Control(uint8_t Gprs_power_pin)
{
    if (Gprs_power_pin==GPRS_MODULE_POWER_PIN_SET)
    {
       Gprs_Power_Pin_Set() ;
    }
    else
    {
        Gprs_Power_Pin_Rest();
    }
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

