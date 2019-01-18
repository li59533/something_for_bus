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
    uint8_t AT_cmd1_req;
    uint8_t AT_cmd2_req;
    uint8_t AT_cmd3_req;
    uint8_t AT_cmd4_req;
    uint8_t AT_cmd5_req;
    uint8_t AT_cmd6_req;
    uint8_t AT_cmd7_req;
    uint8_t AT_cmd8_req;
    uint8_t AT_cmd9_req;
    uint8_t AT_cmd10_req;
    uint8_t AT_cmd11_req;
    uint8_t AT_cmd12_req;
    uint8_t AT_cmd13_req;
    uint8_t AT_cmd14_req;
    uint8_t AT_cmd15_req;
    uint8_t AT_cmd16_req;
    uint8_t AT_cmd1_resp;
    uint8_t AT_cmd2_resp;
    uint8_t AT_cmd3_resp;
    uint8_t AT_cmd4_resp;
    uint8_t AT_cmd5_resp;
    uint8_t AT_cmd6_resp;
    uint8_t AT_cmd7_resp;
    uint8_t AT_cmd8_resp;
    uint8_t AT_cmd9_resp;
    uint8_t AT_cmd10_resp;
    uint8_t AT_cmd11_resp;
    uint8_t AT_cmd12_resp;
    uint8_t AT_cmd13_resp;
    uint8_t AT_cmd14_resp;
    uint8_t AT_cmd15_resp;
    uint8_t AT_cmd16_resp;
}MC20_GPRS_OrderStatus_t;
/**
 * @}
 */

/**
 * @defgroup      mc20_core_gprs_Private_Variables 
 * @brief         
 * @{  
 */
MC20_GPRS_OrderStatus_t GPRS_Order_MactineStatus = 
{
    .AT_cmd1_resp = GPRS_CMD_CPIN_RESP,
    .AT_cmd2_resp = GPRS_CMD_CSQ_RESP,
    .AT_cmd3_resp = GPRS_CMD_CREG_RESP,
    .AT_cmd4_resp = GPRS_CMD_CGREG_RESP,
    .AT_cmd5_resp = GPRS_CMD_QIFGCNT_RESP,
    .AT_cmd6_resp = GPRS_CMD_QICSGP_RESP,
    .AT_cmd7_resp = GPRS_CMD_QIDEAT_RESP,
    .AT_cmd8_resp = GPRS_CMD_QIMODE_RESP,
    .AT_cmd9_resp = GPRS_CMD_QIMUX_RESP,
    .AT_cmd10_resp = GPRS_CMD_QIREGAPP_RESP,
    .AT_cmd11_resp = GPRS_CMD_QIACT_RESP,
    .AT_cmd12_resp = GPRS_CMD_QILOCIP_RESP,
    .AT_cmd13_resp = GPRS_CMD_QIDNSIP_IP_RESP,
    .AT_cmd14_resp = GPRS_CMD_QIDNSIP_DOMAIN_RESP,
    .AT_cmd15_resp = GPRS_CMD_QIHEAD_RESP,
    .AT_cmd16_resp = GPRS_CMD_QIOPEN_RESP,
    .AT_cmd1_req = GPRS_CMD_CPIN_REQ,    
    .AT_cmd2_req = GPRS_CMD_CSQ_REQ,
    .AT_cmd3_req = GPRS_CMD_CREG_REQ,
    .AT_cmd4_req = GPRS_CMD_CGREG_REQ,
    .AT_cmd5_req = GPRS_CMD_QIFGCNT_REQ,
    .AT_cmd6_req = GPRS_CMD_QICSGP_REQ,
    .AT_cmd7_req = GPRS_CMD_QIDEAT_REQ,
    .AT_cmd8_req = GPRS_CMD_QIMODE_REQ,
    .AT_cmd9_req = GPRS_CMD_QIMUX_REQ,
    .AT_cmd10_req = GPRS_CMD_QIREGAPP_REQ,
    .AT_cmd11_req = GPRS_CMD_QIACT_REQ,
    .AT_cmd12_req = GPRS_CMD_QILOCIP_REQ,
    .AT_cmd13_req = GPRS_CMD_QIDNSIP_IP_REQ,
    .AT_cmd14_req = GPRS_CMD_QIDNSIP_DOMAIN_REQ,
    .AT_cmd15_req = GPRS_CMD_QIHEAD_REQ,
    .AT_cmd16_req = GPRS_CMD_QIOPEN_REQ,
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

void MC20_GPRS_Order(uint8_t GPRS_ATcmd,uint8_t AT_CMD_Rev)
{
    static uint8_t rev_count = 0;
    switch (GPRS_ATcmd)
    {
        case GPRS_Order_MactineStatus.AT_cmd1_resp:
        {
            switch (AT_CMD_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    MC20_ATcmd_In_to_Queue(GPRS_Order_MactineStatus.AT_cmd2_req);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_AT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<3?MC20_Gprs_Status_To_Be(MC20_CMD_AT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case GPRS_Order_MactineStatus.AT_cmd2_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd3_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd4_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd5_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd6_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd7_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd8_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd9_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd10_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd11_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd12_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd13_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd14_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd15_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd16_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd17_resp:
        {
            switch (AT_CMD_Rev)
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
        case GPRS_Order_MactineStatus.AT_cmd18_resp:
        {
            switch (AT_CMD_Rev)
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
        default:
        {  
            rev_count = 0;
            MC20_Status.GPRS_Status_Machine.status_machine = MC20_CMD_AT;
        }
        break;
    }
}


//ÉèÖÃGPRS×´Ì¬»úÎª£ºgprs_status
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

