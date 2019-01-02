/**
 **************************************************************************************************
 * @file        mc20_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "mc20_task.h"
#include "mc20_core.h"
#include "osal.h"
#include "mc20_app.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    mc20_task_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_task_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t g_MC20Task_Id = 0;
/**
 * @}
 */

/**
 * @defgroup      mc20_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_task_Functions 
 * @brief         
 * @{  
 */
void MC20Task_Init(uint8_t taskId)
{
    g_MC20Task_Id = taskId;
    MC20Task_Timer_Start_Event(MC20_TASK_CORE_LOOP_EVENT,20);
}

osal_event_t MC20Task_Process(uint8_t taskid,osal_event_t events)
{
    if (events & MC20_TASK_MODULE_RESTART_EVENT) 
    {
        MC20_Power_Pin_Set();
        MC20Task_Send_Event(MC20_TASK_GPRS_EVENT);
        return events ^ MC20_TASK_MODULE_RESTART_EVENT;
    }
    if (events & MC20_TASK_CORE_LOOP_EVENT) 
    {
        MC20_Core_Loop_process();
        OS_Timer_Start(taskid,MC20_TASK_CORE_LOOP_EVENT,20);
        return events ^ MC20_TASK_CORE_LOOP_EVENT;
    }
    if (events & MC20_TASK_GPRS_EVENT) 
    {
        MC20_Gprs_Loop_Process();
        OS_Timer_Start(taskid,MC20_TASK_GPRS_EVENT,20);
        return events ^ MC20_TASK_GPRS_EVENT;
    }
    if (events & MC20_TASK_GPS_EVENT) 
    {        
        return events ^ MC20_TASK_GPS_EVENT;
    }
    if (events & MC20_TASK_BT_EVENT) 
    {
        return events ^ MC20_TASK_BT_EVENT;
    }
    return 0;
}

void MC20Task_Send_Event(osal_event_t events)
{
    OS_Events_Set(g_MC20Task_Id,events);
}


void MC20Task_Timer_Start_Event(osal_event_t events,uint32_t time)
{
    OS_Timer_Start(g_MC20Task_Id,events,time);
}



void MC20Task_Clear_Event(osal_event_t events)
{
    OS_Events_Clear(g_MC20Task_Id,events);
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

