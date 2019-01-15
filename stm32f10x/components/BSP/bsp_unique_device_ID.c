/**
 **************************************************************************************************
 * @file        bsp_unique_device_ID.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_unique_device_ID.h"
#include "self_def.h"
#include "clog.h"
#include "string.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_unique_device_ID_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_unique_device_ID_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_unique_device_ID_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_unique_device_ID_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_unique_device_ID_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_unique_device_ID_Private_Variables 
 * @brief         
 * @{  
 */
uint32_t *  unique_ID_32_addr = (uint32_t * )0x1ffff7e8;
char g_Unique_ID[9];
/**
 * @}
 */

/**
 * @defgroup      bsp_unique_device_ID_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_unique_device_ID_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_unique_device_ID_Functions 
 * @brief         
 * @{  
 */
void BSP_Unique_Init(void)
{    
	sprintf(g_Unique_ID,"%08X",*unique_ID_32_addr);
	INFO("g_Unique_ID:%s\r\n",g_Unique_ID);
}

char * BSP_Unique_Get_Addr(void)
{
	return g_Unique_ID;
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

