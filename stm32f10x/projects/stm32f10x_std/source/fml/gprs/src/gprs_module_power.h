/**
 **************************************************************************************************
 * @file        gprs_module_power.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _GPRS_MODULE_POWER_H_
#define _GPRS_MODULE_POWER_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    gprs_module_power_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_module_power_Exported_Macros 
 * @{  
 */
#define GPRS_MODULE_POWER_PIN_SET      1
#define GPRS_MODULE_POWER_PIN_REST     0 
/**
 * @}
 */

/**
 * @defgroup      gprs_module_power_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_module_power_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_module_power_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_module_power_Exported_Functions 
 * @{  
 */
void Gprs_Power_Pin_Control(uint8_t Gprs_power_pin);
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
