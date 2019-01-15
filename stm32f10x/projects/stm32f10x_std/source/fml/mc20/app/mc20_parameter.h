/**
 **************************************************************************************************
 * @file        mc20_parameter.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MC20_PARAMETER_H_
#define _MC20_PARAMETER_H_
#include "self_def.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    mc20_parameter_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_parameter_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_parameter_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_parameter_Exported_Types 
 * @{  
 */
typedef struct
{
    uint32_t    unique_id;
    uint8_t     ip[4];
    uint16_t    port;
}MC20Parameter_Config_t;
/**
 * @}
 */

/**
 * @defgroup      mc20_parameter_Exported_Variables 
 * @{  
 */
extern MC20Parameter_Config_t g_MC20Parameter_Config;
/**
 * @}
 */

/**
 * @defgroup      mc20_parameter_Exported_Functions 
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
