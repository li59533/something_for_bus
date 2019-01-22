/**
 **************************************************************************************************
 * @file        mc20_core.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MC20_CORE_H_
#define _MC20_CORE_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    mc20_core_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_core_Exported_Macros 
 * @{  
 */
#define MC20_TIMEOUT_300MS              300
#define MC20_TIMEOUT_1000MS            1000
#define MC20_TIMEOUT_3000MS            3000
#define MC20_TIMEOUT_6000MS            6000
#define MC20_TIMEOUT_10000MS            10000
#define MC20_TIMEOUT_40000MS            40000
#define MC20_TIMEOUT_60000MS            60000
/**
 * @}
 */

/**
 * @defgroup      mc20_core_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Exported_Types 
 * @{  
 */

typedef enum
{
    Rev_Null=1,
    Rev_Wait,
    Rev_Pass,
    Rev_Timeout,
    Rev_Error,
}Core_Status_enum;

typedef enum
{
    CHECKSUM_XOR_PASS=1,
    CHECKSUM_XOR_ERROR,
    DATA_ERROR,
    DATA_OK,
}Core_OK_ERROR_Status_enum;

typedef struct
{
    uint8_t ip[4];
    uint16_t port;
    int8_t * domian;
    int8_t  QIDNSIP_value;
}MC20_Core_Moduleconf_t;

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Exported_Functions 
 * @{  
 */


void MC20_Init(void);
void MC20_Core_Loop(void);

void MC20_Core_Func_Control(uint8_t gprs_control,uint8_t gps_control,uint8_t bt_control);

void MC20_Core_Gprsconf_Init(MC20_Core_Moduleconf_t * conf);
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
