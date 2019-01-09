/**
 **************************************************************************************************
 * @file        mc20_queue_process.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "mc20_queue_process.h"
#include "mc20_queue.h"
#include "mc20_task.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    mc20_queue_process_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_queue_process_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_process_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_process_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_process_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_process_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_process_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_process_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_process_Functions 
 * @brief         
 * @{  
 */
void MC20_Rev_Queue_Process(uint8_t * rev_buf,uint16_t rev_len)
{
    MC20_ATcmdMsg_In_to_Queue(rev_buf, rev_len);
	memcpy(rev_buf,0,rev_len);
    MC20Task_Send_Event(MC20_TASK_CORE_RUN_LOOP);
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

