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
#include "mc20_core.h"
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

void MC20_GPRS_Start(MC20_Core_Moduleconf_t * conf);
void MC20_GPRS_SendBytes(uint8_t * buf,uint16_t len);
void MC20_GPRS_Refresh_CSQ(void);
int8_t MC20_GPRS_Get_Link_Status(void);
void MC20_GPRS_Set_RxCallBack();
void MC20_GPRS_Get_Sent_CallBack();
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
