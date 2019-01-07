/**
 **************************************************************************************************
 * @file        mc20_app.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MC20_APP_H_
#define _MC20_APP_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    mc20_app_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_app_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Exported_Functions 
 * @{  
 */
void MC20_GPRS_Start(void);
void MC20_GPS_Start(void);
uint8_t  MC20_GPS_Get_Status(void);
void MC20_GPS_GetLocation(uint16_t longitude,uint16_t latitude);
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
