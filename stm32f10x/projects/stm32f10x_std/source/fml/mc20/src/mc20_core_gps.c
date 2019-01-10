/**
 **************************************************************************************************
 * @file        mc20_core_gps.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "mc20_core_gps.h"
#include "mc20_core.h"
#include "mc20_ATcmd.h"
#include "mc20_queue.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    mc20_core_gps_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_core_gps_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gps_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gps_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gps_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gps_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gps_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gps_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gps_Functions 
 * @brief         
 * @{  
 */
void MC20_GPS_Start_Process(void)
{
    static uint8_t rev_count = 0;
    switch (MC20_Status.GPS_Status_Machine.status_machine)
    {
        case MC20_GPS_QGNSSC:
        {
            MC20_ATcmd_In_to_Queue(MC20_GPS_QGNSSC);
            MC20_Gps_Status_To_Be(MC20_GPS_QGNSSC_Resp);
            break;
        }
        case MC20_GPS_QGNSSC_Resp:
        {
            switch (MC20_Status.GPS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gps_Status_To_Be(MC20_GPS_QGNSSTS);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gps_Status_To_Be(MC20_GPS_QGNSSC):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gps_Status_To_Be(MC20_GPS_QGNSSC):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_GPS_QGNSSTS:
        {
            MC20_ATcmd_In_to_Queue(MC20_GPS_QGNSSTS);
            MC20_Gps_Status_To_Be(MC20_GPS_QGNSSTS_Resp);
            break;
        }
        case MC20_GPS_QGNSSTS_Resp:
        {
            switch (MC20_Status.GPS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gps_Status_To_Be(MC20_GPS_QGNSSEPO);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gps_Status_To_Be(MC20_GPS_QGNSSTS):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gps_Status_To_Be(MC20_GPS_QGNSSTS):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_GPS_QGNSSEPO:
        {
            MC20_ATcmd_In_to_Queue(MC20_GPS_QGNSSEPO);
            MC20_Gps_Status_To_Be(MC20_GPS_QGNSSEPO_Resp);
            break;
        }
        case MC20_GPS_QGNSSEPO_Resp:
        {
            switch (MC20_Status.GPS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gps_Status_To_Be(MC20_GPS_QGEPOAID);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gps_Status_To_Be(MC20_GPS_QGNSSEPO):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gps_Status_To_Be(MC20_GPS_QGNSSEPO):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_GPS_QGEPOAID:
        {
            MC20_ATcmd_In_to_Queue(MC20_GPS_QGEPOAID);
            MC20_Gps_Status_To_Be(MC20_GPS_QGEPOAID_Resp);
            break;
        }
        case MC20_GPS_QGEPOAID_Resp:
        {
            switch (MC20_Status.GPS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gps_Status_To_Be(MC20_GPS_QGNSSRD_RMC);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gps_Status_To_Be(MC20_GPS_QGEPOAID):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gps_Status_To_Be(MC20_GPS_QGEPOAID):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_GPS_QGNSSRD_RMC:
        {
            MC20_ATcmd_In_to_Queue(MC20_GPS_QGNSSRD_RMC);
            MC20_Gps_Status_To_Be(MC20_GPS_QGNSSRD_RMC_Resp);
            break;
        }
        case MC20_GPS_QGNSSRD_RMC_Resp:
        {
            switch (MC20_Status.GPS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gps_Status_To_Be(MC20_GPS_QGNSSRD_RMC);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gps_Status_To_Be(MC20_GPS_QGNSSRD_RMC):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gps_Status_To_Be(MC20_GPS_QGNSSRD_RMC):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        default:
        {
            rev_count = 0;
            MC20_Status.GPS_Status_Machine.status_machine = MC20_GPS_QGNSSC;
            break;
        }
    }
}


void MC20_Core_Gps_RevStatus_To_Be(uint8_t rev_status)
{
    MC20_Status.GPS_Status_Machine.status_Rev = rev_status;
}
void MC20_Gps_Status_To_Be(uint8_t gps_status)
{
    MC20_Core_Gps_RevStatus_To_Be(Rev_Wait);
    MC20_Status.GPS_Status_Machine.status_machine = gps_status;
}

void MC20_Core_Gps_GNSS_Data_Analysis(uint8_t * gnss_data_buf)
{
;
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

