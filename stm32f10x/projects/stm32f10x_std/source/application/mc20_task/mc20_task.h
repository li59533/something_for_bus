/**
 **************************************************************************************************
 * @file        mc20_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MC20_TASK_H_
#define _MC20_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    mc20_task_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_task_Exported_Macros 
 * @{  
 */
#define MC20_TASK_REV_EVENT          0x0001
/**
 * @}
 */

/**
 * @defgroup      mc20_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_task_Exported_Variables 
 * @{  
 */
extern uint8_t g_MC20Task_Id ;
/**
 * @}
 */

/**
 * @defgroup      mc20_task_Exported_Functions 
 * @{  
 */
void MC20Task_Init(uint8_t taskId);

osal_event_t MC20Task_Process(uint8_t taskid,osal_event_t events);

void MC20Task_Send_Event(osal_event_t events);

void UserTask_Clear_Event(osal_event_t events);

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
