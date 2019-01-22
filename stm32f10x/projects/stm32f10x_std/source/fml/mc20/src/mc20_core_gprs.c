/**
 **************************************************************************************************
 * @file        mc20_core_gprs.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "mc20_core_gprs.h"
#include "mc20_ATcmd.h"
#include "mc20_core.h"
#include "mc20_queue.h"
#include "clog.h"
#include "zsproto_tcpip.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    mc20_core_gprs_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_core_gprs_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
    uint8_t AT_CMD1_REQ;
    uint8_t AT_CMD2_REQ;
    uint8_t AT_CMD3_REQ;
    uint8_t AT_CMD4_REQ;
    uint8_t AT_CMD5_REQ;
    uint8_t AT_CMD6_REQ;
    uint8_t AT_CMD7_REQ;
    uint8_t AT_CMD8_REQ;
    uint8_t AT_CMD9_REQ;
    uint8_t AT_CMD10_REQ;
    uint8_t AT_CMD11_REQ;
    uint8_t AT_CMD12_REQ;
    uint8_t AT_CMD13_REQ;
    uint8_t AT_CMD14_REQ;
    uint8_t AT_CMD15_REQ;
    uint8_t AT_CMD16_REQ;

    uint8_t AT_CMD1_RESP;
    uint8_t AT_CMD2_RESP;
    uint8_t AT_CMD3_RESP;
    uint8_t AT_CMD4_RESP;
    uint8_t AT_CMD5_RESP;
    uint8_t AT_CMD6_RESP;
    uint8_t AT_CMD7_RESP;
    uint8_t AT_CMD8_RESP;
    uint8_t AT_CMD9_RESP;
    uint8_t AT_CMD10_RESP;
    uint8_t AT_CMD11_RESP;
    uint8_t AT_CMD12_RESP;
    uint8_t AT_CMD13_RESP;
    uint8_t AT_CMD14_RESP;
    uint8_t AT_CMD15_RESP;
    uint8_t AT_CMD16_RESP;

    //-----------------------
    uint8_t AT_CMD_GPRS_OK;
}MC20_GPRS_OrderStatus_t;
/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Private_Variables 
 * @brief         
 * @{  
 */
 MC20_GPRS_OrderStatus_t  GPRS_ORDER_MACTINESTATUS = 
{
    .AT_CMD1_RESP = GPRS_CMD_CPIN_RESP,
    .AT_CMD2_RESP = GPRS_CMD_CSQ_RESP,
    .AT_CMD3_RESP = GPRS_CMD_CREG_RESP,
    .AT_CMD4_RESP = GPRS_CMD_CGREG_RESP,
    .AT_CMD5_RESP = GPRS_CMD_QIFGCNT_RESP,
    .AT_CMD6_RESP = GPRS_CMD_QICSGP_RESP,
    .AT_CMD7_RESP = GPRS_CMD_QIDEAT_RESP,
    .AT_CMD8_RESP = GPRS_CMD_QIMODE_RESP,
    .AT_CMD9_RESP = GPRS_CMD_QIMUX_RESP,
    .AT_CMD10_RESP = GPRS_CMD_QIREGAPP_RESP,
    .AT_CMD11_RESP = GPRS_CMD_QIACT_RESP,
    .AT_CMD12_RESP = GPRS_CMD_QILOCIP_RESP,
    .AT_CMD13_RESP = GPRS_CMD_QIDNSIP_IP_RESP,
    .AT_CMD14_RESP = GPRS_CMD_QIDNSIP_DOMAIN_RESP,
    .AT_CMD15_RESP = GPRS_CMD_QIHEAD_RESP,
    .AT_CMD16_RESP = GPRS_CMD_QIOPEN_RESP,

    .AT_CMD1_REQ = GPRS_CMD_CPIN_REQ,    
    .AT_CMD2_REQ = GPRS_CMD_CSQ_REQ,
    .AT_CMD3_REQ = GPRS_CMD_CREG_REQ,
    .AT_CMD4_REQ = GPRS_CMD_CGREG_REQ,
    .AT_CMD5_REQ = GPRS_CMD_QIFGCNT_REQ,
    .AT_CMD6_REQ = GPRS_CMD_QICSGP_REQ,
    .AT_CMD7_REQ = GPRS_CMD_QIDEAT_REQ,
    .AT_CMD8_REQ = GPRS_CMD_QIMODE_REQ,
    .AT_CMD9_REQ = GPRS_CMD_QIMUX_REQ,
    .AT_CMD10_REQ = GPRS_CMD_QIREGAPP_REQ,
    .AT_CMD11_REQ = GPRS_CMD_QIACT_REQ,
    .AT_CMD12_REQ = GPRS_CMD_QILOCIP_REQ,
    .AT_CMD13_REQ = GPRS_CMD_QIDNSIP_IP_REQ,
    .AT_CMD14_REQ = GPRS_CMD_QIDNSIP_DOMAIN_REQ,
    .AT_CMD15_REQ = GPRS_CMD_QIHEAD_REQ,
    .AT_CMD16_REQ = GPRS_CMD_QIOPEN_REQ,
// -------------------------------
    .AT_CMD_GPRS_OK = GPRS_LINK_OK,
};
/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void mc20_gprs_rev_orderprocess(uint8_t at_cmd_rev,uint8_t pass_atcmd,uint8_t back_atcmd);
/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Functions 
 * @brief         
 * @{  
 */

static void mc20_gprs_rev_orderprocess(uint8_t at_cmd_rev,uint8_t pass_atcmd,uint8_t back_atcmd)
{
    static uint8_t rev_count = 0;
    switch (at_cmd_rev)
    {
        case Rev_Wait:
            break;
        case Rev_Pass:
            MC20_ATcmd_EnQueue(pass_atcmd);
            rev_count = 0;
            break;
        case Rev_Timeout:
            rev_count ++;
            rev_count<3?MC20_ATcmd_EnQueue(back_atcmd):\
                        MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
            break;
        case Rev_Error:
            rev_count ++;
            rev_count<3?MC20_ATcmd_EnQueue(back_atcmd):\
                        MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
            break;
        default:break;
    }
}




void MC20_GPRS_Order(uint8_t gprs_atcmd,uint8_t at_cmd_rev)
{
    switch (gprs_atcmd)
    {
        case GPRS_CMD_CPIN_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev,GPRS_CMD_CSQ_REQ,GPRS_CMD_CPIN_REQ);
            break;
        }
        case GPRS_CMD_CSQ_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_CREG_REQ, GPRS_CMD_CSQ_REQ);
            break;
        }
        case GPRS_CMD_CREG_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_CGREG_REQ, GPRS_CMD_CREG_REQ);
            break;
        }
        case GPRS_CMD_CGREG_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_QIFGCNT_REQ, GPRS_CMD_CGREG_REQ);
            break;
        }
        case GPRS_CMD_QIFGCNT_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_QICSGP_REQ,GPRS_CMD_QIFGCNT_REQ );
            break;
        }
        case GPRS_CMD_QICSGP_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev,GPRS_CMD_QIDEAT_REQ,GPRS_CMD_QICSGP_REQ);
            break;
        }
        case GPRS_CMD_QIDEAT_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_QIMODE_REQ, GPRS_CMD_QIDEAT_REQ);
            break;
        }
        case GPRS_CMD_QIMODE_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_QIMUX_REQ, GPRS_CMD_QIMODE_REQ);
            break;
        }
        case GPRS_CMD_QIMUX_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_QIREGAPP_REQ,GPRS_CMD_QIMUX_REQ);
            break;
        }
        case GPRS_CMD_QIREGAPP_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_QIACT_REQ,GPRS_CMD_QIREGAPP_REQ);
            break;
        }
        case GPRS_CMD_QIACT_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_QILOCIP_REQ , GPRS_CMD_QIACT_REQ);
            break;
        }
        case GPRS_CMD_QILOCIP_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_QIDNSIP_IP_REQ, GPRS_CMD_QILOCIP_REQ);
            break;
        }
        case GPRS_CMD_QIDNSIP_IP_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_QIHEAD_REQ  , GPRS_CMD_QIDNSIP_IP_REQ);
            break;
        }
        case GPRS_CMD_QIDNSIP_DOMAIN_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_QIHEAD_REQ,GPRS_CMD_QIDNSIP_DOMAIN_REQ );
            break;
        }
        case GPRS_CMD_QIHEAD_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, GPRS_CMD_QIOPEN_REQ, GPRS_CMD_QIHEAD_REQ);
            break;
        }    
        case GPRS_CMD_QIOPEN_RESP:
        {
            mc20_gprs_rev_orderprocess(at_cmd_rev, 0, GPRS_CMD_QIOPEN_REQ);
            break;
        }
        case GPRS_LINK_OK:
            break;
        default:
        {  

        }
        break;
    }
}


void MC20_Server_Msg_Data_Analysis_Process(void)
{
    uint8_t data_buf[200];
    uint16_t data_len = 0;
    MC20_Msg_Out_From_Queue(data_buf,&data_len);
    Zsproto_Data_Analysis(data_buf,data_len);
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

