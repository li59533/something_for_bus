/**
 **************************************************************************************************
 * @file        env_var.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ENV_VAR_H_
#define _ENV_VAR_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    env_var_Modules 
 * @{  
 */

/**
 * @defgroup      env_var_Exported_Macros 
 * @{  
*/
#define PROBE_IN_CHANNEL    0
#define PROBE_OUT_CHANNEL   1
#define PROBE_COUNT_MAX     2

#define DOMAIN_LENGTH_MAX   80

#define MODBUS_SLAVE_COUNT_MAX  2
#define MODBUS_RECV_BUF_SIZE    50

#define COM_USART_GPRS      BSP_USART2
#define COM_USART_MAINTAIN  BSP_USART3

/* stm32 flash ¥Ê¥¢µÿ÷∑∑÷≈‰±Ì */
#define FLASH_PARAM_START_ADDR      (0x7F000)
#define FLASH_PARAM_BACK_START_ADDR (0x7F800)
/**
 * @}
 */

/**
 * @defgroup      env_var_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      env_var_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      env_var_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      env_var_Exported_Functions 
 * @{  
 */

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
