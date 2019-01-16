/**
 **************************************************************************************************
 * @file        system_param.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *                      
 **************************************************************************************************
 */
#include "self_def.h"
#include "stm32_bsp_conf.h"
#include "crc.h"
#include "system_info.h"
#include "system_param.h"
#include "mc20_parameter.h"
#include "clog.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    system_param_Modules 
 * @{  
 */

/**
 * @defgroup      system_param_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Macros_Defines 
 * @brief         
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      system_param_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Public_Variables 
 * @brief         
 * @{  
 */
SystemParam_Config_t g_SystemParam_Config = 
{
    .unique_id = (uint32_t *)0x1ffff7e8,
};
/**
 * @}
 */

/**
 * @defgroup      system_param_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Functions 
 * @brief         
 * @{  
 */
int16_t SystemParam_Init(void)
{
    return SystemParam_Read();
}

int16_t SystemParam_Read(void)
{
    BSP_FLASH_ReadBytes(FLASH_PARAM_START_ADDR,(uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
    if (CRC16_Modbus((uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config)) == 0)
    {
        INFO("SysParam_load:OK\r\n");
//----------------------load_MC20_Conf--------------
        g_MC20Parameter_Config.ip[0] = g_SystemParam_Config.ip[0];
        g_MC20Parameter_Config.ip[1] = g_SystemParam_Config.ip[1];
        g_MC20Parameter_Config.ip[2] = g_SystemParam_Config.ip[2];
        g_MC20Parameter_Config.ip[3] = g_SystemParam_Config.ip[3];
        g_MC20Parameter_Config.port = g_SystemParam_Config.port;
        g_MC20Parameter_Config.unique_id = *g_SystemParam_Config.unique_id;
//--------------------------------------------------


    }
    else
    {
        BSP_FLASH_ReadBytes(FLASH_PARAM_BACK_START_ADDR,(uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
        if (CRC16_Modbus((uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config)) == 0)
        {
            INFO("SysParam_load:OK\r\n");
//----------------------load_MC20_Conf--------------
            g_MC20Parameter_Config.ip[0] = g_SystemParam_Config.ip[0];
            g_MC20Parameter_Config.ip[1] = g_SystemParam_Config.ip[1];
            g_MC20Parameter_Config.ip[2] = g_SystemParam_Config.ip[2];
            g_MC20Parameter_Config.ip[3] = g_SystemParam_Config.ip[3];
            g_MC20Parameter_Config.port = g_SystemParam_Config.port;
            g_MC20Parameter_Config.unique_id = *g_SystemParam_Config.unique_id;
//--------------------------------------------------
        }
        else
        {
            INFO("SysParam_load:Error\r\n");
            SystemParam_Reset();
            return -1;
        }
    }

    return 0;
}

void SystemParam_Save(void)
{
    g_SystemParam_Config.crc = CRC16_Modbus((uint8_t*)&g_SystemParam_Config, sizeof(g_SystemParam_Config) - sizeof(g_SystemParam_Config.crc));
    BSP_FLASH_EraseSector(FLASH_PARAM_START_ADDR);
    BSP_FLASH_WriteBytes(FLASH_PARAM_START_ADDR,(uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
    BSP_FLASH_EraseSector(FLASH_PARAM_BACK_START_ADDR);
    BSP_FLASH_WriteBytes(FLASH_PARAM_BACK_START_ADDR,(uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
}

void SystemParam_Reset(void)
{
    g_MC20Parameter_Config.ip[0] = 139;//139.199.153.158 ,46502
    g_MC20Parameter_Config.ip[1] = 199;
    g_MC20Parameter_Config.ip[2] = 153;
    g_MC20Parameter_Config.ip[3] = 158;
    g_MC20Parameter_Config.port = 46502;

    g_SystemParam_Config.ip[0] = 139;
    g_SystemParam_Config.ip[0] = 199;
    g_SystemParam_Config.ip[0] = 153;
    g_SystemParam_Config.ip[0] = 158;
    g_MC20Parameter_Config.port = 46502;

    SystemParam_Save();
}

void SystemParam_Apply(void)
{
    g_MC20Parameter_Config.ip[0] = 139;//139.199.153.158 ,46502
    g_MC20Parameter_Config.ip[1] = 199;
    g_MC20Parameter_Config.ip[2] = 153;
    g_MC20Parameter_Config.ip[3] = 158;
    g_MC20Parameter_Config.port = 35804;
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

