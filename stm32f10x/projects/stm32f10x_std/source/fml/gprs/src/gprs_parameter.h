/**
 **************************************************************************************************
 * @file        gprs_parameter.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _GPRS_PARAMETER_H_
#define _GPRS_PARAMETER_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    gprs_parameter_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_parameter_Exported_Macros 
 * @{  
 */
#define GPRS_POWER_PIN_CONTROL_TIME             2 //let the pin low power more than 3second
/**
 * @}
 */

/**
 * @defgroup      gprs_parameter_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_parameter_Exported_Types 
 * @{  
 */
typedef enum
{ 
    Gprs_Power_On_Req = 1,
    Gprs_Power_On_Resp,
    Gprs_Cmd_AT_Req,
    Gprs_Cmd_AT_Resp,
  
  
}Gprs_Module_Status_List;



/**
 * @}
 */

/**
 * @defgroup      gprs_parameter_Exported_Variables 
 * @{  
 */

extern uint8_t Gprs_Module_Status;

extern int8_t g_Gprs_Power_Status;
/**
 * @}
 */

/**
 * @defgroup      gprs_parameter_Exported_Functions 
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
