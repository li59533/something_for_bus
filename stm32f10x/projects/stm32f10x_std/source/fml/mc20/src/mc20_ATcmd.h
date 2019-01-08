/**
 **************************************************************************************************
 * @file        mc20_ATcmd.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MC20_ATCMD_H_
#define _MC20_ATCMD_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    mc20_ATcmd_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_ATcmd_Exported_Macros 
 * @{  
 */
typedef enum
{
    MC20_IDLE  =0,
    MC20_CMD_AT,
    MC20_CMD_AT_Resp,
    MC20_CMD_ATE,
    MC20_CMD_ATE_Resp,
    MC20_CMD_IPR,
    MC20_CMD_IPR_Resp,
    MC20_CMD_CPIN,
    MC20_CMD_CPIN_Resp,
    MC20_CMD_CSQ,
    MC20_CMD_CSQ_Resp,
    MC20_CMD_CREG,
    MC20_CMD_CREG_Resp,
    MC20_CMD_CGREG,
    MC20_CMD_CGREG_Resp,
    MC20_CMD_QIFGCNT,
    MC20_CMD_QIFGCNT_Resp,
    MC20_CMD_QICSGP,
    MC20_CMD_QICSGP_Resp,
    MC20_CMD_QIDEACT,
    MC20_CMD_QIDEACT_Resp,
    MC20_CMD_QIMODE,
    MC20_CMD_QIMODE_Resp,
    MC20_CMD_QIMUX,
    MC20_CMD_QIMUX_Resp,
    MC20_CMD_QIREGAPP,
    MC20_CMD_QIREGAPP_Resp,
    MC20_CMD_QIACT,
    MC20_CMD_QIACT_Resp,
    MC20_CMD_QILOCIP,
    MC20_CMD_QILOCIP_Resp,
    MC20_CMD_QIDNSIP_IP,
    MC20_CMD_QIDNSIP_IP_Resp,
    MC20_CMD_QIDNSIP_DOMAIN,
    MC20_CMD_QIDNSIP_DOMAIN_Resp,
    MC20_CMD_QIHEAD,
    MC20_CMD_QIHEAD_Resp,
    MC20_CMD_QIOPEN,
    MC20_CMD_QIOPEN_Resp,
    MC20_CMD_QISEND,
    MC20_CMD_QISEND_Resp,
    MC20_CMD_QISACK,
    MC20_CMD_QISACK_Resp,
    MC20_CMD_QPOWD,
    MC20_CMD_QPOWD_Resp,
}MC20_ATcmd_enum;
/**
 * @}
 */

/**
 * @defgroup      mc20_ATcmd_Exported_Constants
 * @{  
 */
extern const char MC20_CMD_AT_BUF[];
extern const char MC20_CMD_ATE_BUF[];
extern const char MC20_CMD_IPR_BUF[];
extern const char MC20_CMD_CPIN_BUF[]; // 5s
extern const char MC20_CMD_CSQ_BUF[]; // 300ms
extern const char MC20_CMD_CREG_BUF[]; // 300ms
extern const char MC20_CMD_CGREG_BUF[]; // 300ms
extern const char MC20_CMD_QIFGCNT_BUF[]; // 300ms
extern const char MC20_CMD_QICSGP_BUF[]; // 300ms
extern const char MC20_CMD_QIDEACT_BUF[]; // 40s
extern const char MC20_CMD_QIMODE_BUF[]; // 300ms
extern const char MC20_CMD_QIMUX_BUF[]; // 300ms
extern const char MC20_CMD_QIREGAPP_BUF[]; // 300ms
extern const char MC20_CMD_QIACT_BUF[]; // 150s
extern const char MC20_CMD_QILOCIP_BUF[]; // 300ms
extern const char MC20_CMD_QIDNSIP_IP_BUF[]; // 300ms
extern const char MC20_CMD_QIDNSIP_DOMAIN_BUF[]; // 300ms
extern const char MC20_CMD_QIHEAD_BUF[]; // 300ms
extern const char MC20_CMD_QIOPEN_BUF[]; // 75s
extern const char MC20_CMD_QISEND_BUF[]; // 300ms
extern const char MC20_CMD_QISACK_BUF[];    // 300ms
extern const char MC20_CMD_QPOWD_BUF[]; // 300ms
/**
 * @}
 */

/**
 * @defgroup      mc20_ATcmd_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_ATcmd_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_ATcmd_Exported_Functions 
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
