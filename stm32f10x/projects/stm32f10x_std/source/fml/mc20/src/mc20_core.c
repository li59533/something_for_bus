/**
 **************************************************************************************************
 * @file        mc20_core.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "mc20_core.h"
#include "mc20_queue.h"
#include "mc20_ATcmd.h"
#include "osal_clock.h"
#include "mc20_app.h"
#include "mc20_task.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    mc20_core_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_core_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Private_Types
 * @brief         
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      mc20_core_Private_Variables 
 * @brief         
 * @{  
 */
MC20_Status_t MC20_Status;
/**
 * @}
 */

/**
 * @defgroup      mc20_core_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Functions 
 * @brief         
 * @{  
 */
void MC20_Init(void)
{

}
void MC20_Core_Rev_Loop_Process(void)
{
    MC20_Status.GPRS_Status_Machine.status_Rev =1 ;

    MC20Task_Send_Event(MC20_TASK_GPRS_EVENT);

    MC20_Status.GPS_Status_Machine.status_Rev =1 ;
    MC20Task_Send_Event(MC20_TASK_GPS_EVENT);
}

void MC20_Core_Run_Process(void)
{

    switch (MC20_Status.CORE_Status_Machine.status_machine)
    {
    }
}
void MC20_GPRS_Start_Process(void)
{
    switch (MC20_Status.GPRS_Status_Machine.status_machine)
    {
    }
}
void MC20_GPS_Start_Process(void)
{
    switch (MC20_Status.GPS_Status_Machine.status_machine)
    {

    }
}
void MC20_GPS_GetLocation_Process(void)
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

