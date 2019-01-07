/**
 **************************************************************************************************
 * @file        mc20_app.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "mc20_app.h"
#include "mc20_port.h"
#include "mc20_core.h"
#include "mc20_task.h"
#include "mc20_ATcmd.h"
#include "mc20_queue.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    mc20_app_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_app_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Functions 
 * @brief         
 * @{  
 */
void MC20_GPRS_Start(void)
{

}
void MC20_GPS_Start(void)
{

}
uint8_t  MC20_GPS_Get_Status(void)
{
    return MC20_Status.GPS_Status_Machine.status_machine;
}
void MC20_GPS_GetLocation(uint16_t longitude,uint16_t latitude)
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

