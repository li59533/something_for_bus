/**
 **************************************************************************************************
 * @file        ODB_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ODB_TASK_H_
#define _ODB_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "osal.h"
/**
 * @addtogroup    ODB_task_Modules 
 * @{  
 */

/**
 * @defgroup      ODB_task_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_task_Exported_Variables 
 * @{  
 */
extern uint8_t g_ODBTask_Id;
/**
 * @}
 */

/**
 * @defgroup      ODB_task_Exported_Functions 
 * @{  
 */
void ODBTask_Init(uint8_t taskId);

osal_event_t ODBTask_Process(uint8_t taskid,osal_event_t events);

void ODBTask_Send_Event(osal_event_t events);

void ODBTask_Clear_Event(osal_event_t events);


void ODBTask_Timer_Start_Event(osal_event_t events,uint32_t time);
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
