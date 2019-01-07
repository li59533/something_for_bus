/**
 **************************************************************************************************
 * @file        ODB_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "ODB_task.h"
#include "osal.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    ODB_task_Modules 
 * @{  
 */

/**
 * @defgroup      ODB_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_task_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t g_ODBTask_Id = 0;
/**
 * @}
 */

/**
 * @defgroup      ODB_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_task_Functions 
 * @brief         
 * @{  
 */
void ODBTask_Init(uint8_t taskId)
{
    g_ODBTask_Id = taskId;
}

osal_event_t ODBTask_Process(uint8_t taskid,osal_event_t events)
{
    if (events & MC20_TASK_REV_EVENT) 
    {
        MC20_Core_Rev_Loop_Process();
        return events ^ MC20_TASK_REV_EVENT;
    }
  
    return 0;
}

void ODBTask_Send_Event(osal_event_t events)
{
    OS_Events_Set(g_ODBTask_Id,events);
}


void ODBTask_Timer_Start_Event(osal_event_t events,uint32_t time)
{
    OS_Timer_Start(g_ODBTask_Id,events,time);
}

void ODBTask_Clear_Event(osal_event_t events)
{
    OS_Events_Clear(g_ODBTask_Id,events);
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

