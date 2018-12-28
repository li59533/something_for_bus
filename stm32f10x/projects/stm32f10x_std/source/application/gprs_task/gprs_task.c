/**
 **************************************************************************************************
 * @file        gprs_task.c
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
#include "osal.h"
#include "gprs_task.h"
#include "gprs_port.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    gprs_task_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t g_GprsTask_Id;

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Functions 
 * @brief         
 * @{  
 */
void GprsTask_Init(uint8_t taskId)
{
    g_GprsTask_Id = taskId;
    OS_Events_Set(g_GprsTask_Id,GPRS_TASK_TEST_EVENT);
}

osal_event_t GprsTask_Process(uint8_t taskid,osal_event_t events)
{
    if (events & GPRS_TASK_TEST_EVENT) 
    {
        Gprs_CMD_Send(test_gprs_dma,sizeof(test_gprs_dma));
        OS_Timer_Start(taskid,GPRS_TASK_TEST_EVENT,1000);
        return events ^ GPRS_TASK_TEST_EVENT;
    }
    if (events & GPRS_TASK_TEST2_EVENT) 
    {
        
        Gprs_Task_uart_R_test();

        return events ^ GPRS_TASK_TEST2_EVENT;
    }
    

    return 0;
}


void GprsTask_StartTask(osal_event_t events)
{
    OS_Events_Set(g_GprsTask_Id,events);
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

