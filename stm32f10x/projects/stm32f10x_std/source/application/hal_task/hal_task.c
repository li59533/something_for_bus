/**
 **************************************************************************************************
 * @file        hal_task.c
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
#include "hal_task.h"
#include "bsp_led.h"


/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    hal_task_Modules 
 * @{  
 */

/**
 * @defgroup      hal_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t g_HalTask_Id = 0;
/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Functions 
 * @brief         
 * @{  
 */
void HalTask_Init(uint8_t taskId)
{
    g_HalTask_Id = taskId;

    OS_Events_Set(taskId,HAL_TASK_LED_TOGGLE_EVENT);
}

osal_event_t HalTask_Process(uint8_t taskid,osal_event_t events)
{
    if (events & HAL_TASK_LED_BLINK_EVENT)
    {
        BSP_LED_Update();
        return events ^ HAL_TASK_LED_BLINK_EVENT;
    }
    if (events & HAL_TASK_LED_TOGGLE_EVENT)
    {
        BSP_LED_Toggle(BSP_LEDRUN);
        OS_Timer_Start(taskid,HAL_TASK_LED_TOGGLE_EVENT,200);
        return events ^ HAL_TASK_LED_TOGGLE_EVENT;
    }
    return 0;
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

