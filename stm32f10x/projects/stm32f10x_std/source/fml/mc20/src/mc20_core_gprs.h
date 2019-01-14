/**
 **************************************************************************************************
 * @file        mc20_core_gprs.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MC20_CORE_GPRS_H_
#define _MC20_CORE_GPRS_H_
#include "self_def.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    mc20_core_gprs_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_core_gprs_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Exported_Functions 
 * @{  
 */
void MC20_GPRS_Start_Process(void);
void MC20_Gprs_Status_To_Be(uint8_t gprs_status);
void MC20_Send_Data_To_Server(uint8_t * send_buf,uint16_t send_len);
uint8_t MC20_Gprs_Status_Is(void);
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
