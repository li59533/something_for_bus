/**
 **************************************************************************************************
 * @file        gprs_AT.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _GPRS_AT_H_
#define _GPRS_AT_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    gprs_AT_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_AT_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_AT_Exported_Constants
 * @{  
 */
extern const char GPRS_CMD_AT[];
extern const char GPRS_CMD_ATE[];
extern const char GPRS_CMD_IPR[];
extern const char GPRS_CMD_CPIN[]; // 5s
extern const char GPRS_CMD_CSQ[]; // 300ms
extern const char GPRS_CMD_CREG[]; // 300ms
extern const char GPRS_CMD_CGREG[]; // 300ms
extern const char GPRS_CMD_QIFGCNT[]; // 300ms
extern const char GPRS_CMD_QICSGP[]; // 300ms
extern const char GPRS_CMD_QIDEACT[]; // 40s
extern const char GPRS_CMD_QIMODE[]; // 300ms
extern const char GPRS_CMD_QIMUX[]; // 300ms
extern const char GPRS_CMD_QIREGAPP[]; // 300ms
extern const char GPRS_CMD_QIACT[]; // 150s
extern const char GPRS_CMD_QILOCIP[]; // 300ms
extern const char GPRS_CMD_QIDNSIP_IP[]; // 300ms
extern const char GPRS_CMD_QIDNSIP_DOMAIN[]; // 300ms
extern const char GPRS_CMD_QIHEAD[]; // 300ms
extern const char GPRS_CMD_QIOPEN[]; // 75s
extern const char GPRS_CMD_QISEND[]; // 300ms
extern const char GPRS_CMD_QISACK[];
/**
 * @}
 */

/**
 * @defgroup      gprs_AT_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_AT_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_AT_Exported_Functions 
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
