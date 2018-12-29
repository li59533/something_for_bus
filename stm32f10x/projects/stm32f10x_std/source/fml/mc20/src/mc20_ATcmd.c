/**
 **************************************************************************************************
 * @file        mc20_ATcmd.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "mc20_ATcmd.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    mc20_ATcmd_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_ATcmd_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_ATcmd_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_ATcmd_Constants_Defines 
 * @brief         
 * @{  
 */
const char MC20_CMD_AT_BUF[] = {"AT\r\n"};
const char MC20_CMD_ATE_BUF[] = {"ATE0\r\n"};
const char MC20_CMD_IPR_BUF[] = {"AT+IPR=115200&W\r\n"};
const char MC20_CMD_CPIN_BUF[] = {"AT+CPIN?\r\n"}; // 5s
const char MC20_CMD_CSQ_BUF[] = {"AT+CSQ\r\n"}; // 300ms
const char MC20_CMD_CREG_BUF[] = {"AT+CREG?\r\n"}; // 300ms
const char MC20_CMD_CGREG_BUF[] = {"AT+CGREG?\r\n"}; // 300ms
const char MC20_CMD_QIFGCNT_BUF[] = {"AT+QIFGCNT=0\r\n"}; // 300ms
const char MC20_CMD_QICSGP_BUF[] = {"AT+QICSGP=1,\"CMNET\"\r\n"}; // 300ms                                                  
const char MC20_CMD_QIDEACT_BUF[] = {"AT+QIDEACT\r\n"}; // 40s
const char MC20_CMD_QIMODE_BUF[] = {"AT+QIMODE=0\r\n"}; // 300ms
const char MC20_CMD_QIMUX_BUF[] = {"AT+QIMUX=1\r\n"}; // 300ms  
const char MC20_CMD_QIREGAPP_BUF[] = {"AT+QIREGAPP\r\n"}; // 300ms
const char MC20_CMD_QIACT_BUF[] = {"AT+QIACT\r\n"}; // 150s
const char MC20_CMD_QILOCIP_BUF[] = {"AT+QILOCIP\r\n"}; // 300ms
const char MC20_CMD_QIDNSIP_IP_BUF[] = {"AT+QIDNSIP=0\r\n"}; // ,300ms
const char MC20_CMD_QIDNSIP_DOMAIN_BUF[] = {"AT+QIDNSIP=1\r\n"}; // ,300ms
const char MC20_CMD_QIHEAD_BUF[] = {"AT+QIHEAD=0\r\n"}; // ,300ms
const char MC20_CMD_QIOPEN_BUF[] = {"AT+QIOPEN=\"TCP\",\"132.232.103.18\",\"20000\"\r\n"}; // 75ms
const char MC20_CMD_QISEND_BUF[] = {"AT+QISEND=1\r\n"}; // 300ms
const char MC20_CMD_QISACK_BUF[] = {"AT+QISACK\r\n"};
/**
 * @}
 */

/**
 * @defgroup      mc20_ATcmd_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_ATcmd_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_ATcmd_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_ATcmd_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_ATcmd_Functions 
 * @brief         
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

