/**
 **************************************************************************************************
 * @file        application_process.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "application_process.h"
#include "mc20_ATcmd.h"
#include "mc20_core_gps.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    application_process_Modules 
 * @{  
 */

/**
 * @defgroup      application_process_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      application_process_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      application_process_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      application_process_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      application_process_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      application_process_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      application_process_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      application_process_Functions 
 * @brief         
 * @{  
 */
void App_Open_Func(void)
{
;
}
void App_Scan_Status_Loop(void)
{

    if (MC20_Gps_Status_Is()==MC20_GPS_GNSS_OK)
    {

    }
}

void App_Logic_Func_Proccess(void)
{

}
/** 
 *  
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

