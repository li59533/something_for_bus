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
#include "mc20_core_gprs.h"
#include "mc20_core_gps.h"
#include "zsproto_tcpip.h"
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
    OS_Events_Set(g_MC20Task_Id,MC20_TASK_CORE_RUN_LOOP);
    OS_Timer_Start(g_MC20Task_Id,MC20_TASK_GPRS_EVENT,20);
    OS_Timer_Start(g_MC20Task_Id,MC20_TASK_GPS_EVENT,20);
}

osal_event_t MC20Task_Process(uint8_t taskid,osal_event_t events)
{
    if (events & MC20_TASK_REV_EVENT) 
    {
        return events ^ MC20_TASK_REV_EVENT;
    }
    if (events & MC20_TASK_GPRS_EVENT) 
    {
        MC20_GPRS_Start_Process();
        OS_Timer_Start(taskid,MC20_TASK_GPRS_EVENT,20);
        return events ^ MC20_TASK_GPRS_EVENT;
    }
    if (events & MC20_TASK_GPS_EVENT) 
    {
        
        MC20_GPS_Start_Process();
        
        OS_Timer_Start(taskid,MC20_TASK_GPS_EVENT,20);
        return events ^ MC20_TASK_GPS_EVENT;
    }
    if (events & MC20_TASK_CORE_RUN_LOOP) 
    {
       
        MC20_Core_Run_Process();
        OS_Timer_Start(taskid,MC20_TASK_CORE_RUN_LOOP,20);
        return events ^ MC20_TASK_CORE_RUN_LOOP;
    }    
    if (events & MC20_TASK_ANALGSIS_PACKAGE_EVENT) 
    {      
        MC20_Server_Msg_Data_Analysis_Process();
        return events ^ MC20_TASK_ANALGSIS_PACKAGE_EVENT;
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

