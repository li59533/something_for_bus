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

}

osal_event_t MC20Task_Process(uint8_t taskid,osal_event_t events)
{
    if (events & MC20_TASK_REV_EVENT) 
    {
        return events ^ MC20_TASK_REV_EVENT;
    }
    return 0;
}

void MC20Task_Send_Event(osal_event_t events)
{
    OS_Events_Set(g_MC20Task_Id,events);
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

