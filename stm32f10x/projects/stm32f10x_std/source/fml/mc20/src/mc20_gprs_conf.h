/**
 **************************************************************************************************
 * @file        mc20_gprs_conf.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MC20_GPRS_CONF_H_
#define _MC20_GPRS_CONF_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    mc20_gprs_conf_Modules 
 * @{  
 */
typedef enum
{
    MC20_Gprs_CMD_AT = 1,
    MC20_Gprs_CMD_AT_Resp,

    MC20_Gprs_CMD_ATE,
    MC20_Gprs_CMD_ATE_Resp,
    MC20_Gprs_CMD_IPR,
    MC20_Gprs_CMD_IPR_Resp,
    MC20_Gprs_CMD_CPIN,
    MC20_Gprs_CMD_CPIN_Resp,
    MC20_Gprs_CMD_CSQ,
    MC20_Gprs_CMD_CSQ_Resp,
    MC20_Gprs_CMD_CREG,
    MC20_Gprs_CMD_CREG_Resp,
    MC20_Gprs_CMD_CGREG,
    MC20_Gprs_CMD_CGREG_Resp,
    MC20_Gprs_CMD_QIFGCNT,
    MC20_Gprs_CMD_QIFGCNT_Resp,
    MC20_Gprs_CMD_QICSGP,
    MC20_Gprs_CMD_QICSGP_Resp,
    MC20_Gprs_CMD_QIDEACT,
    MC20_Gprs_CMD_QIDEACT_Resp,
    MC20_Gprs_CMD_QIMODE,
    MC20_Gprs_CMD_QIMODE_Resp,
    MC20_Gprs_CMD_QIMUX,
    MC20_Gprs_CMD_QIMUX_Resp,
    MC20_Gprs_CMD_QIREGAPP,
    MC20_Gprs_CMD_QIREGAPP_Resp,
    MC20_Gprs_CMD_QIACT,
    MC20_Gprs_CMD_QIACT_Resp,
    MC20_Gprs_CMD_QILOCIP,
    MC20_Gprs_CMD_QILOCIP_Resp,
    MC20_Gprs_CMD_QIDNSIP_IP,
    MC20_Gprs_CMD_QIDNSIP_IP_Resp,
    MC20_Gprs_CMD_QIDNSIP_DOMAIN,
    MC20_Gprs_CMD_QIDNSIP_DOMAIN_Resp,
    MC20_Gprs_CMD_QIHEAD,
    MC20_Gprs_CMD_QIHEAD_Resp,
    MC20_Gprs_CMD_QIOPEN,
    MC20_Gprs_CMD_QIOPEN_Resp,
    MC20_Gprs_CMD_QISEND,
    MC20_Gprs_CMD_QISEND_Resp,
    MC20_Gprs_CMD_QISACK,
    MC20_Gprs_CMD_QISACK_Resp,
}MC20_Gprs_ATcmd_enum;
/**
 * @defgroup      mc20_gprs_conf_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_gprs_conf_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_gprs_conf_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_gprs_conf_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_gprs_conf_Exported_Functions 
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
