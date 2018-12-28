/**
 **************************************************************************************************
 * @file        gprs_AT.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "gprs_AT.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    gprs_AT_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_AT_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_AT_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_AT_Constants_Defines 
 * @brief         
 * @{  
 */
const char GPRS_CMD_AT[] = {"AT\r\n"};
const char GPRS_CMD_ATE[] = {"ATE0\r\n"};
const char GPRS_CMD_IPR[] = {"AT+IPR=115200&W\r\n"};
const char GPRS_CMD_CPIN[] = {"AT+CPIN?\r\n"}; // 5s
const char GPRS_CMD_CSQ[] = {"AT+CSQ\r\n"}; // 300ms
const char GPRS_CMD_CREG[] = {"AT+CREG?\r\n"}; // 300ms
const char GPRS_CMD_CGREG[] = {"AT+CGREG?\r\n"}; // 300ms
const char GPRS_CMD_QIFGCNT[] = {"AT+QIFGCNT=0\r\n"}; // 300ms
const char GPRS_CMD_QICSGP[] = {"AT+QICSGP=1,\"CMNET\"\r\n"}; // 300ms                                                  
const char GPRS_CMD_QIDEACT[] = {"AT+QIDEACT\r\n"}; // 40s
const char GPRS_CMD_QIMODE[] = {"AT+QIMODE=0\r\n"}; // 300ms
const char GPRS_CMD_QIMUX[] = {"AT+QIMUX=1\r\n"}; // 300ms  
const char GPRS_CMD_QIREGAPP[] = {"AT+QIREGAPP\r\n"}; // 300ms
const char GPRS_CMD_QIACT[] = {"AT+QIACT\r\n"}; // 150s
const char GPRS_CMD_QILOCIP[] = {"AT+QILOCIP\r\n"}; // 300ms
const char GPRS_CMD_QIDNSIP_IP[] = {"AT+QIDNSIP=0\r\n"}; // ,300ms
const char GPRS_CMD_QIDNSIP_DOMAIN[] = {"AT+QIDNSIP=1\r\n"}; // ,300ms
const char GPRS_CMD_QIHEAD[] = {"AT+QIHEAD=0\r\n"}; // ,300ms
const char GPRS_CMD_QIOPEN[] = {"AT+QIOPEN=\"TCP\",\"132.232.103.18\",\"20000\"\r\n"}; // 75ms
const char GPRS_CMD_QISEND[] = {"AT+QISEND=1\r\n"}; // 300ms
const char GPRS_CMD_QISACK[] = {"AT+QISACK\r\n"};
/**
 * @}
 */

/**
 * @defgroup      gprs_AT_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_AT_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_AT_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_AT_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_AT_Functions 
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

