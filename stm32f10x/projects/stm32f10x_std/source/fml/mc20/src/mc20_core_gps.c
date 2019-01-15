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
#include "clog.h"
#include "osal_clock.h"
#include "mc20_core_gprs.h"
#include "mc20_parameter.h"
#include "zsproto_tcpip.h"
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
GPS_GNSS_DATA_t GPS_GNSS_DATA;
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
    static uint32_t time_temp = 0;
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
					rev_count ++;
					if(rev_count > 200)
					{
                    	MC20_Gps_Status_To_Be(MC20_GPS_QGNSSRD_RMC);
                    	rev_count = 0;
					}
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
                    INFO("--GNSS_OK\r\n");
                    MC20_Gps_Status_To_Be(MC20_GPS_GNSS_OK);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gps_Status_To_Be(MC20_GPS_QGNSSRD_RMC):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<30?MC20_Gps_Status_To_Be(MC20_GPS_QGNSSRD_RMC):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_GPS_GNSS_OK:
        {
            
            if (OS_Clock_GetSeconds() > 0xffffff00)
            {
                OS_Clock_SetSeconds(0);
            }
            time_temp = OS_Clock_GetSeconds();

            INFO("postion_status:%s\r\n", GPS_GNSS_DATA.postion_status);
            INFO("longitude_value:%s\r\n", GPS_GNSS_DATA.longitude_value);
            INFO("longitude_hemisphere:%s\r\n", GPS_GNSS_DATA.longitude_hemisphere);
            INFO("lattude_value:%s\r\n", GPS_GNSS_DATA.lattude_value);
            INFO("lattude_hemisphere:%s\r\n", GPS_GNSS_DATA.lattude_hemisphere);
            INFO("ground_rate:%s\r\n", GPS_GNSS_DATA.ground_rate);
            INFO("ground_direction:%s\r\n", GPS_GNSS_DATA.ground_direction);
            MC20_Gps_Status_To_Be(MC20_GPS_GNSS_OK_Resp);
            
            break;
        }
        case MC20_GPS_GNSS_OK_Resp:
        {
            if((OS_Clock_GetSeconds() - time_temp )> 5)
            {


                Test_zsproto();//test
                //MC20_Send_Data_To_Server("nihao\r\n",7);//test
                DEBUG("Seconds:%d,time:%d\r\n",OS_Clock_GetSeconds(),time_temp);
                MC20_Gps_Status_To_Be(MC20_GPS_QGNSSRD_RMC);
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


void Test_zsproto(void)
{
    uint16_t package_len = 0;
    Zsproto_Make_Payload(&GPS_GNSS_DATA,0);


    package_len =  Zsproto_Make_Package_To_Server(g_Zsproto_To_Server_Package, strlen((char const *)g_Zsproto_To_Server_Package), g_MC20Parameter_Config.unique_id);
    MC20_Send_Data_To_Server((uint8_t *)g_Zsproto_To_Server_Package,package_len);
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

int8_t  MC20_Core_Gps_GNSS_Data_Analysis(int8_t * gnss_data_buf)
{
    char * GNSS_effect_flag_addr = 0;
    char *ptr_temp;
    if(MC20_Core_GPS_DATA_CheckSum_XOR(gnss_data_buf,0) == CHECKSUM_XOR_PASS)
    {
        GNSS_effect_flag_addr = strstr((const char *)gnss_data_buf , "A");
        if (GNSS_effect_flag_addr > 0)
        {
            ptr_temp = strtok(GNSS_effect_flag_addr,",");
            strcpy(GPS_GNSS_DATA.postion_status,ptr_temp);
            ptr_temp = strtok(NULL,",");
            strcpy(GPS_GNSS_DATA.lattude_value, ptr_temp);
            ptr_temp = strtok(NULL,",");
            strcpy(GPS_GNSS_DATA.lattude_hemisphere, ptr_temp);
            ptr_temp = strtok(NULL,",");
            strcpy(GPS_GNSS_DATA.longitude_value, ptr_temp);
            ptr_temp = strtok(NULL,",");
            strcpy(GPS_GNSS_DATA.longitude_hemisphere, ptr_temp);
            ptr_temp = strtok(NULL,",");
            strcpy(GPS_GNSS_DATA.ground_rate, ptr_temp);
            ptr_temp = strtok(NULL,",");
            strcpy(GPS_GNSS_DATA.ground_direction, ptr_temp);
            return DATA_OK;
            
        }
        else
        {
            INFO("GNSS_V\r\n");
            return DATA_ERROR;
        }
    }
    else
    {
        INFO("GPS_XOR:ERROR\r\n");
        return CHECKSUM_XOR_ERROR;
    }
}

//checksum --XOR
int8_t MC20_Core_GPS_DATA_CheckSum_XOR(int8_t * checkbuf,uint8_t checklen) 
{ 
    char * checkhead;
    char * checktail;
    char checksumresult = 0;
    char * checkvalue_addr ;
    unsigned char i;
    char check_tmep_buf[3];
    checkhead = strstr((const char *)checkbuf,"$");
    checktail = strstr((const char *)checkbuf,"*");
    checkvalue_addr = checktail + 1;

    for(i=0;i<250;i++)
    {
        checksumresult ^=*(checkhead+1+i);
        if(checktail == (checkhead + i +2 ))
        {
            break;
        }
    }

    sprintf(check_tmep_buf,"%2X",checksumresult);

    if (strstr(checkvalue_addr,check_tmep_buf) > 0)
    {
        return CHECKSUM_XOR_PASS;
    }
    else
    {		
        return CHECKSUM_XOR_ERROR;
    }

}

uint8_t MC20_Gps_Status_Is(void)
{
    return MC20_Status.GPS_Status_Machine.status_machine;
}

void MC20_Gps_Flash_GNSS_Data(void)
{
    MC20_Gps_Status_To_Be(MC20_GPS_QGNSSRD_RMC);
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

