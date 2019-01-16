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

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Private_Variables 
 * @brief         
 * @{  
 */

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
void MC20_GPRS_Start_Process(void)
{
    static uint8_t rev_count = 0;
    switch (MC20_Status.GPRS_Status_Machine.status_machine)
    {
        case MC20_CMD_AT:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_AT);
            MC20_Gprs_Status_To_Be(MC20_CMD_AT_Resp);
            break;
        }
        case MC20_CMD_AT_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:

                    MC20_Gprs_Status_To_Be(MC20_CMD_ATE);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<6?MC20_Gprs_Status_To_Be(MC20_CMD_AT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<6?MC20_Gprs_Status_To_Be(MC20_CMD_AT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_ATE:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_ATE);
            MC20_Gprs_Status_To_Be(MC20_CMD_ATE_Resp);
            break;
        }
        case MC20_CMD_ATE_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_IPR);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_ATE):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_ATE):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_IPR:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_IPR);
            MC20_Gprs_Status_To_Be(MC20_CMD_IPR_Resp);
            break;
        }
        case MC20_CMD_IPR_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_CPIN);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_IPR):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_IPR):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_CPIN:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_CPIN);
            MC20_Gprs_Status_To_Be(MC20_CMD_CPIN_Resp);
            break;
        }
        case MC20_CMD_CPIN_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_CSQ);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_CPIN):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                 
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_CPIN):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_CSQ:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_CSQ);
            MC20_Gprs_Status_To_Be(MC20_CMD_CSQ_Resp);
            break;
        }
        case MC20_CMD_CSQ_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_CREG);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_CSQ):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_CSQ):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_CREG:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_CREG);
            MC20_Gprs_Status_To_Be(MC20_CMD_CREG_Resp);
            break;
        }
        case MC20_CMD_CREG_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_QIFGCNT);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_CREG):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_CREG):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIFGCNT:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIFGCNT);
            MC20_Gprs_Status_To_Be(MC20_CMD_QIFGCNT_Resp);
            break;
        }
        case MC20_CMD_QIFGCNT_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_QIDEACT);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIFGCNT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIFGCNT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIDEACT:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIDEACT);
            MC20_Gprs_Status_To_Be(MC20_CMD_QIDEACT_Resp);
            break;
        }
        case MC20_CMD_QIDEACT_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_QIMODE);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIDEACT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIDEACT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIMODE:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIMODE);
            MC20_Gprs_Status_To_Be(MC20_CMD_QIMODE_Resp);
            break;
        }
        case MC20_CMD_QIMODE_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_QIMUX);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIMODE):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIMODE):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIMUX:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIMUX);
            MC20_Gprs_Status_To_Be(MC20_CMD_QIMUX_Resp);
            break;
        }
        case MC20_CMD_QIMUX_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_QIREGAPP);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIMUX):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIMUX):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIREGAPP:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIREGAPP);
            MC20_Gprs_Status_To_Be(MC20_CMD_QIREGAPP_Resp);
            break;
        }
        case MC20_CMD_QIREGAPP_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_QIACT);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIREGAPP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIREGAPP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIACT:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIACT);
            MC20_Gprs_Status_To_Be(MC20_CMD_QIACT_Resp);
            break;
        }
        case MC20_CMD_QIACT_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_QILOCIP);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIACT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIACT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QILOCIP:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QILOCIP);
            MC20_Gprs_Status_To_Be(MC20_CMD_QILOCIP_Resp);
            break;
        }
        case MC20_CMD_QILOCIP_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_QIDNSIP_IP);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QILOCIP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QILOCIP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIDNSIP_IP:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIDNSIP_IP);
            MC20_Gprs_Status_To_Be(MC20_CMD_QIDNSIP_IP_Resp);
            break;
        }
        case MC20_CMD_QIDNSIP_IP_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_QIHEAD);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIDNSIP_IP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIDNSIP_IP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIHEAD:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIHEAD);
            MC20_Gprs_Status_To_Be(MC20_CMD_QIHEAD_Resp);
            break;
        }
        case MC20_CMD_QIHEAD_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_CMD_QIOPEN);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIHEAD):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIHEAD):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIOPEN:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIOPEN);
            MC20_Gprs_Status_To_Be(MC20_CMD_QIOPEN_Resp);
            break;
        }
        case MC20_CMD_QIOPEN_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    INFO("--LINK_OK\r\n");
                    MC20_Gprs_Status_To_Be(MC20_GPRS_CONNECT_ING);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIOPEN):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIOPEN):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QISEND:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QISEND);
            MC20_Gprs_Status_To_Be(MC20_CMD_QISEND_Resp);
            break;
        }
        case MC20_CMD_QISEND_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_GPRS_CONNECT_ING);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIOPEN):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QIOPEN):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QISACK:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QISACK);
            MC20_Gprs_Status_To_Be(MC20_CMD_QISACK_Resp);
            break;
        }
        case MC20_CMD_QISACK_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_Gprs_Status_To_Be(MC20_GPRS_CONNECT_ING);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QISACK):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_QISACK):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_GPRS_CONNECT_ING:
            break;
        case MC20_GPRS_CONNECT_ING_Resp:
            break;
        default:
        {
            rev_count = 0;
            MC20_Status.GPRS_Status_Machine.status_machine = MC20_CMD_AT;
        }
        break;
    }
}
void MC20_Gprs_Status_To_Be(uint8_t gprs_status)
{
    MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
    MC20_Status.GPRS_Status_Machine.status_machine = gprs_status;
}


void MC20_Send_Data_To_Server(uint8_t * send_buf,uint16_t send_len)
{
    //MC20_ATcmd_In_to_Queue(MC20_CMD_QISEND);
    MC20_Gprs_Status_To_Be(MC20_CMD_QISEND);
	MC20_Send_Msg_In_to_Queue(send_buf,send_len);
}

uint8_t MC20_Gprs_Status_Is(void)
{
    return MC20_Status.GPRS_Status_Machine.status_machine ;
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

