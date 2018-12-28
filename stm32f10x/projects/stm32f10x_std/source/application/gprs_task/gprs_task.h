/**
 **************************************************************************************************
 * @file        gprs_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _GPRS_TASK_H_
#define _GPRS_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "osal.h"
/**
 * @addtogroup    gprs_task_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_task_Exported_Macros 
 * @{  
 */
#define GPRS_TASK_TEST_EVENT         0x0001
#define GPRS_TASK_TEST2_EVENT        0x0002
/**
 * @}
 */

/**
 * @defgroup      gprs_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Exported_Variables 
 * @{  
 */
extern uint8_t g_GprsTask_Id;
/**
 * @}
 */

/**
 * @defgroup      gprs_task_Exported_Functions 
 * @{  
 */

void GprsTask_Init(uint8_t taskId);

osal_event_t GprsTask_Process(uint8_t taskid,osal_event_t events);
void GprsTask_StartTask(osal_event_t events);
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
