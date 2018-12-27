/**
 **************************************************************************************************
 * @file        hal_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _HAL_TASK_H_
#define _HAL_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    hal_task_Modules 
 * @{  
 */

/**
 * @defgroup      hal_task_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Exported_Variables 
 * @{  
 */
extern uint8_t g_HalTask_Id;
/**
 * @}
 */

/**
 * @defgroup      hal_task_Exported_Functions 
 * @{  
 */
void HalTask_Init(uint8_t taskId);
osal_event_t HalTask_Process(uint8_t taskid,osal_event_t events);
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
