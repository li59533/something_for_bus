/**
 **************************************************************************************************
 * @file        mc20_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MC20_TASK_H_
#define _MC20_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "osal.h"
/**
 * @addtogroup    mc20_task_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_task_Exported_Macros 
 * @{  
 */
#define MC20_TASK_REV_EVENT                     0x0001
#define MC20_TASK_MODULE_RESTART_EVENT          0x0002
#define MC20_TASK_CORE_LOOP_EVENT               0X0004
#define MC20_TASK_GPRS_EVENT                    0X0008
#define MC20_TASK_GPS_EVENT                     0X0010
#define MC20_TASK_BT_EVENT                      0X0020
#define MC20_TASK_CORE_RUN_LOOP                 0x0040




/**
 * @}
 */

/**
 * @defgroup      mc20_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_task_Exported_Variables 
 * @{  
 */
extern uint8_t g_MC20Task_Id ;
/**
 * @}
 */

/**
 * @defgroup      mc20_task_Exported_Functions 
 * @{  
 */
void MC20Task_Init(uint8_t taskId);

osal_event_t MC20Task_Process(uint8_t taskid,osal_event_t events);

void MC20Task_Send_Event(osal_event_t events);

void MC20Task_Clear_Event(osal_event_t events);


void MC20Task_Timer_Start_Event(osal_event_t events,uint32_t time);



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
