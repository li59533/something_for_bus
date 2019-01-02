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
void MC20_Module_Init(void);

void MC20_Gprs_Start(void);

void MC20_Gprs_Loop_Process(void);

void MC20_Module_Restart(void);
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
