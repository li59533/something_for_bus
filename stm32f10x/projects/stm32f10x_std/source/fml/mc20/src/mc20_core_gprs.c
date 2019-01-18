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
}MC20_GPRS_OrderStatus_t;
/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Private_Variables 
 * @brief         
 * @{  
 */
const MC20_GPRS_OrderStatus_t GPRS_ORDER_MACTINESTATUS = 
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

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Functions 
 * @brief         
 * @{  
 */

void MC20_GPRS_Order(uint8_t gprs_atcmd,uint8_t at_cmd_rev)
{
    static uint8_t rev_count = 0;
    switch (gprs_atcmd)
    {
        case GPRS_ORDER_MACTINESTATUS.AT_CMD1_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD2_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD1_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD1_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD2_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD3_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD2_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD2_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD3_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD4_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD3_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD3_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD4_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD5_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD4_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD4_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD5_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD6_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD5_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD5_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD6_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD7_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD6_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD6_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD7_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD8_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD7_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD7_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD8_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD9_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD8_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD8_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD9_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD10_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD9_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD9_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD10_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD11_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD10_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD10_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD11_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD12_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD11_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD11_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD12_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD13_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD12_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD12_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD13_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD14_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD13_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD13_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD14_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD15_REQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD14_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_ATcmd_EnQueue(GPRS_ORDER_MACTINESTATUS.AT_CMD14_REQ):\
                                MC20_ATcmd_EnQueue(MC20_HAL_RESTART_REQ);  
                    break;
                default:break;
            }
            break;
        }
        case GPRS_ORDER_MACTINESTATUS.AT_CMD15_RESP:
        {
            switch (at_cmd_rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    break;
                case Rev_Error:                   
                    break;
                default:break;
            }
            break;
        }      
        default:
        {  

        }
        break;
    }
}




void MC20_Send_Data_To_Server(uint8_t * send_buf,uint16_t send_len)
{
    //MC20_ATcmd_EnQueue(MC20_CMD_QISEND);
    MC20_Gprs_Status_To_Be(MC20_CMD_QISEND);
	MC20_Send_Msg_In_to_Queue(send_buf,send_len);
}

uint8_t MC20_Gprs_Status_Is(void)
{
    return MC20_Status.GPRS_Status_Machine.status_machine ;
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

