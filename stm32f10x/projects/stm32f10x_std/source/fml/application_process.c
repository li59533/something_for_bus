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
#include "zsproto_tcpip.h"
#include "mc20_core_gprs.h"
#include "mc20_parameter.h"
#include "clog.h"
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

void App_Run_Loop(void)
{
	/*
    uint16_t package_len = 0;
    if (GPS_GNSS_DATA.postion_status[0] == 'A' && GPS_GNSS_DATA.postion_status[1]==0)
    {
        if (MC20_Gprs_Status_Is() == MC20_GPRS_CONNECT_ING)
        {
            Zsproto_Add_To_TLV(1, strlen(GPS_GNSS_DATA.lattude_value),GPS_GNSS_DATA.longitude_value);
            Zsproto_Add_To_TLV(2, strlen(GPS_GNSS_DATA.lattude_hemisphere),GPS_GNSS_DATA.lattude_hemisphere);
            Zsproto_Add_To_TLV(3, strlen(GPS_GNSS_DATA.longitude_value),GPS_GNSS_DATA.longitude_value);
            Zsproto_Add_To_TLV(4, strlen(GPS_GNSS_DATA.longitude_hemisphere),GPS_GNSS_DATA.longitude_hemisphere);
            Zsproto_Make_Package_To_Server(g_MC20Parameter_Config.unique_id,&Zsproto_payload,g_Zsproto_To_Server_Package,&package_len);
            MC20_Send_Data_To_Server((uint8_t *)g_Zsproto_To_Server_Package,package_len);
        }
    }
    else
    {
        INFO("the GNSS DATA is invalid\r\n");
    }
	*/
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

