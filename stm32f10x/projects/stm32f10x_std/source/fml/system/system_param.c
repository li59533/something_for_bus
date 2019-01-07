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
SystemParam_Config_t g_SystemParam_Config;
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
    //return SystemParam_Read();
	return 0;
}

int16_t SystemParam_Read(void)
{
    BSP_FLASH_ReadBytes(FLASH_PARAM_START_ADDR,(uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
    if (CRC16_Modbus((uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config)) == 0)
    {
    }
    else
    {
        //BSP_FLASH_ReadBytes(FLASH_PARAM_BACK_START_ADDR,(uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
        if (CRC16_Modbus((uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config)) == 0)
        {
        }
        else
        {
            SystemParam_Reset();
            return -1;
        }
    }

    return 0;
}

void SystemParam_Save(void)
{
    //g_SystemParam_Config.crc = CRC16_Modbus((uint8_t*)&g_SystemParam_Config, sizeof(g_SystemParam_Config) - sizeof(g_SystemParam_Config.crc));
   // BSP_FLASH_EraseSector(FLASH_PARAM_START_ADDR);
    //BSP_FLASH_WriteBytes(FLASH_PARAM_START_ADDR,(uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
   // BSP_FLASH_EraseSector(FLASH_PARAM_BACK_START_ADDR);
   // BSP_FLASH_WriteBytes(FLASH_PARAM_BACK_START_ADDR,(uint8_t*)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
}

void SystemParam_Reset(void)
{


    SystemParam_Save();
}

void SystemParam_Apply(void)
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

