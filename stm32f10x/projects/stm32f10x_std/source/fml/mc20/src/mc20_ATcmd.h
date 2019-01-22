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
    MC20_IDLE  =1,
//---------mc20_device--------
    MC20_CMD_AT_REQ,
    MC20_CMD_AT_RESP,
    MC20_CMD_ATE_REQ,
    MC20_CMD_ATE_RESP,
    MC20_CMD_IPR_REQ,
    MC20_CMD_IPR_RESP,
    MC20_CMD_CSQ_REQ,
    MC20_CMD_CSQ_RESP,
    MC20_HAL_RESTART_REQ,
    MC20_HAL_RESTART_RESP,
//----------------------------

//---------mc20_GPRS----------

    GPRS_CMD_CPIN_REQ = 50,
    GPRS_CMD_CPIN_RESP,
    GPRS_CMD_CSQ_REQ,
    GPRS_CMD_CSQ_RESP,
    GPRS_CMD_CREG_REQ,
    GPRS_CMD_CREG_RESP,
    GPRS_CMD_CGREG_REQ,
    GPRS_CMD_CGREG_RESP,
    GPRS_CMD_QIFGCNT_REQ,
    GPRS_CMD_QIFGCNT_RESP,
    GPRS_CMD_QICSGP_REQ,
    GPRS_CMD_QICSGP_RESP,
    GPRS_CMD_QIDEAT_REQ,
    GPRS_CMD_QIDEAT_RESP,
    GPRS_CMD_QIMODE_REQ,
    GPRS_CMD_QIMODE_RESP,
    GPRS_CMD_QIMUX_REQ,
    GPRS_CMD_QIMUX_RESP,
    GPRS_CMD_QIREGAPP_REQ,
    GPRS_CMD_QIREGAPP_RESP,
    GPRS_CMD_QIACT_REQ,
    GPRS_CMD_QIACT_RESP,
    GPRS_CMD_QILOCIP_REQ,
    GPRS_CMD_QILOCIP_RESP,
    GPRS_CMD_QIDNSIP_IP_REQ,
    GPRS_CMD_QIDNSIP_IP_RESP,
    GPRS_CMD_QIDNSIP_DOMAIN_REQ,
    GPRS_CMD_QIDNSIP_DOMAIN_RESP,
    GPRS_CMD_QIHEAD_REQ,
    GPRS_CMD_QIHEAD_RESP,
    GPRS_CMD_QIOPEN_REQ,
    GPRS_CMD_QIOPEN_RESP,
    GPRS_CMD_QISACT_REQ,
    GPRS_CMD_QISACT_RESP,
    GPRS_LINK_OK,
//-------------------------------


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


extern const char MC20_CMD_QGNSSC_BUF[];
extern const char MC20_CMD_QGNSSTS_BUF[];
extern const char MC20_CMD_QGNSSEPO_BUF[];
extern const char MC20_CMD_QGEPOAID_BUF[];
extern const char MC20_CMD_QGNSSRD_BUF[];
extern const char MC20_CMD_QGNSSRD_RMC_BUF[];

extern       char MC20_CMD_QIOPEN_USER_BUF[60];

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
