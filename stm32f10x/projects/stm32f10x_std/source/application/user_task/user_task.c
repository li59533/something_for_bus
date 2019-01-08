/**
 **************************************************************************************************
 * @file        user_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "self_def.h"
#include "stm32_bsp_conf.h"
#include "osal.h"
#include "clog.h"
#include "cshell.h"
#include "clock.h"
#include "system_info.h"
#include "user_task.h"
#include "application_process.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    user_task_Modules 
 * @{  
 */

/**
 * @defgroup      user_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      user_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      user_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      user_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      user_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      user_task_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t g_UserTask_Id = 0;
/**
 * @}
 */

/**
 * @defgroup      user_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      user_task_Functions 
 * @brief         
 * @{  
 */
void UserTask_Init(uint8_t taskId)
{
    g_UserTask_Id = taskId;
    App_Open_Func();
}

osal_event_t UserTask_Process(uint8_t taskid,osal_event_t events)
{
    if (events & USER_TASK_SYSTEMRESET_EVENT) // ÏµÍ³¸´Î»
    {
        NVIC_SystemReset();
        return events ^ USER_TASK_SYSTEMRESET_EVENT;
    }
    
    if (events & USER_TASK_SCAN_STATUS_LOOP_EVENT)
    {
        App_Scan_Status_Loop();
        return events ^ USER_TASK_SCAN_STATUS_LOOP_EVENT;
    }
    return 0;
}

void UserTask_Send_Event(osal_event_t events)
{
    OS_Events_Set(g_UserTask_Id,events);
}

void UserTask_Clear_Event(osal_event_t events)
{

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

